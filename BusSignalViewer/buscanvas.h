#ifndef BUSCANVAS_H
#define BUSCANVAS_H

#include <QWidget>
#include <QMap>
#include <QTreeWidgetItem>

class BusCanvas : public QWidget {
    Q_OBJECT

public:
    explicit BusCanvas(QWidget *parent = nullptr);

    void updateVisibility();

    void scrollToTime(int sampleIndex);

    void scrollToTimeIndex(int index);

    void onTreeItemChanged(QTreeWidgetItem *item, int column);

    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;

    void wheelEvent(QWheelEvent *event) override;

private:
    QVector<QVector<int> > input_signals;
    QMap<int, bool> visible_channels;
    double zoomFactor = 1.0;
    int offsetX = 0;

    QString computeHexValue(int index) const;

    static QString formatTime(double ns);

public slots:
    void zoomIn();

    void zoomOut();

    void fitToWidth();
};

#endif // BUSCANVAS_H
