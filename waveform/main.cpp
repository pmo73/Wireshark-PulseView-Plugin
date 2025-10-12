#include <QApplication>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPainter>
#include <QVBoxLayout>
#include <QWheelEvent>
#include <QWidget>
#include <cmath>
#include <qregularexpression.h>
#include <vector>

class TimeRuler : public QWidget
{
    Q_OBJECT
public:
    explicit
    TimeRuler(QWidget *parent = nullptr) : QWidget(parent), scale_(1e-6), offset_(0)
    {
        setFixedHeight(40);
    }
    void
    setScale(double s)
    {
        scale_ = s;
        update();
        emit scaleChanged(scale_);
    }
    double
    scale() const
    {
        return scale_;
    }
    void
    setOffset(double o)
    {
        offset_ = o;
        update();
        emit offsetChanged(offset_);
    }
    double
    offset() const
    {
        return offset_;
    }
signals:
    void scaleChanged(double);
    void offsetChanged(double);

protected:
    void
    paintEvent(QPaintEvent *event) override
    {
        Q_UNUSED(event);
        QPainter p(this);
        p.fillRect(rect(), Qt::white);
        p.setPen(Qt::black);

        int const    min_px     = 80;
        double const min_period = scale_ * min_px;

        int    order     = (int)floor(log10(min_period));
        double base      = pow(10.0, order);
        double tick_step = base;
        if (min_period > 5 * base)
            tick_step = 10 * base;
        else if (min_period > 2 * base)
            tick_step = 5 * base;
        else if (min_period > base)
            tick_step = 2 * base;

        char const *prefixes[] = { "f", "p", "n", "µ", "m", "", "k", "M", "G" };
        int         prefix_idx = 5;

        double step = tick_step;
        while (step < 1 && prefix_idx > 0) {
            step *= 1000;
            prefix_idx--;
        }
        while (step >= 1000 && prefix_idx < 8) {
            step /= 1000;
            prefix_idx++;
        }

        double start_time = offset_;
        double first_tick = floor(start_time / tick_step) * tick_step;

        for (double t = first_tick;; t += tick_step) {
            int x = (int)((t - offset_) / scale_);
            if (x > width())
                break;
            if (x < 0)
                continue;

            p.drawLine(x, 0, x, height() / 2);

            double unit_factor = pow(1000.0, 5 - prefix_idx);
            double val         = t * unit_factor;

            QString label;
            if (prefix_idx < 5) {
                long long intval = llround(val);
                label            = QString::number(intval);
            } else {
                label = QString::number(val, 'f', 3).remove(QRegularExpression("\\.?0+$"));
            }
            label += " " + QString(prefixes[prefix_idx]) + "s";
            p.drawText(x, height() - 4, label);
        }
    }
    void
    wheelEvent(QWheelEvent *event) override
    {
        handleWheelEvent(event);
    }

public:
    void
    handleWheelEvent(QWheelEvent *event)
    {
        if (event->modifiers() & Qt::ControlModifier) {
            double delta = (event->angleDelta().y() > 0) ? -scale_ * 50 : scale_ * 50;
            offset_ += delta;
            emit offsetChanged(offset_);
        } else {
            double mouse_x        = event->position().x();
            double time_at_cursor = offset_ + mouse_x * scale_;
            double factor         = (event->angleDelta().y() > 0) ? 0.8 : 1.25;
            scale_ *= factor;
            offset_ = time_at_cursor - mouse_x * scale_;
            emit scaleChanged(scale_);
            emit offsetChanged(offset_);
        }
        update();
    }

private:
    double scale_;
    double offset_;
};

class LogicSignalView : public QWidget
{
    Q_OBJECT
public:
    explicit
    LogicSignalView(QWidget *parent = nullptr) :
        QWidget(parent), scale_(1e-6), offset_(0), ruler_(nullptr)
    {
        setMinimumHeight(50);
        signal_ = {
            { 0e-6,   0 },
            { 1e-6,   1 },
            { 2.5e-6, 0 },
            { 4e-6,   1 },
            { 6e-6,   0 },
            { 8e-6,   1 }
        };
    }
    void
    setRuler(TimeRuler *ruler)
    {
        ruler_ = ruler;
    }
public slots:
    void
    setScale(double s)
    {
        scale_ = s;
        update();
    }
    void
    setOffset(double o)
    {
        offset_ = o;
        update();
    }

protected:
    void
    paintEvent(QPaintEvent *event) override
    {
        Q_UNUSED(event);
        QPainter p(this);
        p.fillRect(rect(), Qt::lightGray);
        p.setPen(Qt::black);

        int highY = height() / 4;
        int lowY  = 3 * height() / 4;

        for (size_t i = 0; i < signal_.size() - 1; ++i) {
            double t1 = signal_[i].first;
            double t2 = signal_[i + 1].first;
            int    v1 = signal_[i].second;

            int x1 = (int)((t1 - offset_) / scale_);
            int x2 = (int)((t2 - offset_) / scale_);
            int y  = v1 ? highY : lowY;

            p.drawLine(x1, y, x2, y);
            int y2 = signal_[i + 1].second ? highY : lowY;
            p.drawLine(x2, y, x2, y2);
        }
    }
    void
    wheelEvent(QWheelEvent *event) override
    {
        if (ruler_)
            ruler_->handleWheelEvent(event);
    }

private:
    double                              scale_;
    double                              offset_;
    std::vector<std::pair<double, int>> signal_;
    TimeRuler                          *ruler_;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow()
    {
        auto *central = new QWidget(this);
        auto *grid    = new QGridLayout(central);
        grid->setContentsMargins(0, 0, 0, 0);
        grid->setHorizontalSpacing(5);
        grid->setVerticalSpacing(5);

        // Linke Spalte (Labels) schmaler machen
        grid->setColumnStretch(0, 0);
        grid->setColumnStretch(1, 1);

        // --- Ruler einmalig oben rechts (Spalte 1) ---
        ruler = new TimeRuler(this);
        grid->addWidget(ruler, 0, 1);

        // --- Erstes Signal ---
        signalView      = new LogicSignalView(this);
        signalNameLabel = new QLabel("CLK", this);
        signalNameLabel->setAlignment(Qt::AlignVCenter | Qt::AlignCenter);
        signalNameLabel->setContentsMargins(5, 0, 0, 0);
        grid->addWidget(signalNameLabel, 1, 0);
        grid->addWidget(signalView, 1, 1);

        // --- Zweites Signal ---
        signalView2      = new LogicSignalView(this);
        signalNameLabel2 = new QLabel("DATA", this);
        signalNameLabel2->setAlignment(Qt::AlignVCenter | Qt::AlignCenter);
        signalNameLabel2->setContentsMargins(5, 0, 0, 0);
        grid->addWidget(signalNameLabel2, 2, 0);
        grid->addWidget(signalView2, 2, 1);

        // --- Ruler-Verbindungen ---
        signalView->setRuler(ruler);
        signalView2->setRuler(ruler);
        connect(ruler, &TimeRuler::scaleChanged, signalView, &LogicSignalView::setScale);
        connect(ruler, &TimeRuler::offsetChanged, signalView, &LogicSignalView::setOffset);
        connect(ruler, &TimeRuler::scaleChanged, signalView2, &LogicSignalView::setScale);
        connect(ruler, &TimeRuler::offsetChanged, signalView2, &LogicSignalView::setOffset);

        setCentralWidget(central);
        resize(800, 400);
    }

private:
    TimeRuler       *ruler;
    LogicSignalView *signalView;
    LogicSignalView *signalView2;
    QLabel          *signalNameLabel;
    QLabel          *signalNameLabel2;
};

int
main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MainWindow   win;
    win.show();
    return app.exec();
}

#include "main.moc"
