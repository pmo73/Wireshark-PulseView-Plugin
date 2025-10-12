#include "buscanvas.h"
#include <QPainter>
#include <QWheelEvent>
#include <QTreeWidget>
#include <QDebug>
#include <cmath>
#include <QScrollArea>

BusCanvas::BusCanvas(QWidget *parent)
    : QWidget(parent) {
    input_signals = {
        {
            1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1,
            0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1,
            0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1,
            1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1
        },
        {
            0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1,
            0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1,
            0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1,
            1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1
        },
        {
            1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1,
            0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1,
            0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1,
            1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1
        },
        {
            1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1,
            0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1,
            0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1,
            1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1
        },
        {
            0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1,
            0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1,
            0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1,
            1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1
        },
        {
            1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1,
            0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1,
            0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1,
            1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1
        },
        {
            1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1,
            0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1,
            0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1,
            1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1
        },
        {
            0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1,
            0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1,
            0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1,
            1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1
        },
        {
            1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1,
            0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1,
            0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1,
            1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1
        },
        {
            1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1,
            0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1,
            0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1,
            1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1
        },
        {
            0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1,
            0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1,
            0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1,
            1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1
        },
        {
            1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1,
            0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1,
            0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1,
            1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1
        },
        {
            1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1,
            0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1,
            0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1,
            1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1
        },
        {
            0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1,
            0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1,
            0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1,
            1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1
        },
        {
            1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1,
            0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1,
            0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1,
            1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1
        }
    };

    for (int i = 0; i < input_signals.size(); ++i)
        visible_channels[i] = true;

    setFocusPolicy(Qt::StrongFocus);

    if (auto *tree = parent->findChild<QTreeWidget *>()) {
        auto *bus_item = new QTreeWidgetItem(tree);
        bus_item->setText(0, "DataBus");
        bus_item->setFlags(bus_item->flags() | Qt::ItemIsUserCheckable);
        bus_item->setCheckState(0, Qt::Checked);

        for (int i = input_signals.size(); i > 0; --i) {
            auto *signal_item = new QTreeWidgetItem(bus_item);
            signal_item->setText(0, QString("D%1").arg(i - 1));
            signal_item->setFlags(signal_item->flags() | Qt::ItemIsUserCheckable);
            signal_item->setCheckState(0, Qt::Checked);
        }

        connect(tree, &QTreeWidget::itemChanged, this, &BusCanvas::onTreeItemChanged);
    }
}

auto BusCanvas::formatTime(double ns) -> QString {
    if (ns >= 1e9) {
        return QString::number(ns / 1e9, 'f', 2) + " s";
    }
    if (ns >= 1e6) {
        return QString::number(ns / 1e6, 'f', 2) + " ms";
    }
    if (ns >= 1e3) {
        return QString::number(ns / 1e3, 'f', 2) + " µs";
    }
    return QString::number(ns, 'f', 0) + " ns";
}

QString BusCanvas::computeHexValue(int index) const {
    int value = 0;
    for (int i = 0; i < input_signals.size(); ++i) {
        if (visible_channels.value(i, false)) {
            value <<= 1;
            value |= input_signals[i][index];
        }
    }
    return QString::number(value, 16).toUpper().rightJustified(2, '0');
}

void BusCanvas::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int marginLeft = 100;
    int channelHeight = 30;
    int spacing = 20;

    double stepX = 40.0 * zoomFactor;
    double nsPerSample = 10.0;

    // Dynamische Zeitachse
    int x = marginLeft - offsetX;
    int sampleCount = input_signals[0].size();
    double lastLabelX = -1000;
    const int minSpacing = 60;

    for (int i = 0; i < sampleCount; ++i) {
        int currX = x + i * stepX;
        if (currX - lastLabelX >= minSpacing) {
            double ns = i * nsPerSample;
            painter.drawLine(currX, 25, currX, 35);
            painter.drawText(currX - 20, 20, formatTime(ns));
            lastLabelX = currX;
        }
    }

    // Signalverläufe
    int yOffset = 60;
    for (int i = 0; i < input_signals.size(); ++i) {
        if (!visible_channels.value(i, false)) continue;

        int baseY = yOffset;
        int highY = baseY + 10;
        int lowY = baseY + 20;

        painter.setPen(Qt::black);
        painter.drawText(10, baseY + 20, QString("D%1").arg(input_signals.size() - i - 1));

        int xPos = marginLeft - offsetX;
        int y = input_signals[i][0] ? highY : lowY;

        for (int j = 0; j < input_signals[i].size(); ++j) {
            int nextY = input_signals[i][j] ? highY : lowY;
            painter.setPen(input_signals[i][j] ? Qt::green : Qt::red);

            if (j > 0 && input_signals[i][j] != input_signals[i][j - 1])
                painter.drawLine(xPos, y, xPos, nextY);

            painter.drawLine(xPos, nextY, xPos + stepX, nextY);

            xPos += stepX;
            y = nextY;
        }

        yOffset += channelHeight + spacing;
    }

    // Hex-Werte als Sechsecke
    int xHex = marginLeft - offsetX;
    for (int j = 0; j < input_signals[0].size(); ++j) {
        QString hexVal = computeHexValue(j);
        QRect hexRect(xHex + 0, yOffset, stepX - 0, 20);

        QPoint hexPoints[6] = {
            QPoint(hexRect.left() + 5, hexRect.top()),
            QPoint(hexRect.right() - 5, hexRect.top()),
            QPoint(hexRect.right(), hexRect.center().y()),
            QPoint(hexRect.right() - 5, hexRect.bottom()),
            QPoint(hexRect.left() + 5, hexRect.bottom()),
            QPoint(hexRect.left(), hexRect.center().y())
        };

        painter.setPen(Qt::black);
        painter.drawPolygon(hexPoints, 6);
        painter.drawText(hexRect, Qt::AlignCenter, "0x" + hexVal);

        xHex += stepX;
    }

    // Buslabel
    painter.drawText(10, yOffset + 20, "DataBus");
}


void BusCanvas::wheelEvent(QWheelEvent *event) {
    if (event->angleDelta().y() > 0)
        zoomFactor *= 1.1;
    else
        zoomFactor /= 1.1;
    zoomFactor = std::clamp(zoomFactor, 0.01, 10.0);
    update();
}

void BusCanvas::scrollToTime(int sampleIndex) {
    offsetX = sampleIndex * 40.0 * zoomFactor;
    update();
}

void BusCanvas::updateVisibility() {
    auto *tree = parent()->findChild<QTreeWidget *>();
    if (!tree) return;

    for (int i = 0; i < tree->topLevelItemCount(); ++i) {
        auto *group = tree->topLevelItem(i);
        for (int j = 0; j < group->childCount(); ++j) {
            auto *signalItem = group->child(j);
            visible_channels[j] = (signalItem->checkState(0) == Qt::Checked);
        }
    }

    update();
}

void BusCanvas::onTreeItemChanged(QTreeWidgetItem *item, int) {
    if (!item) return;

    if (!item->parent()) {
        Qt::CheckState parentState = item->checkState(0);
        for (int i = 0; i < item->childCount(); ++i)
            item->child(i)->setCheckState(0, parentState);
    }

    updateVisibility();
}

void BusCanvas::zoomIn() {
    zoomFactor *= 1.1;
    zoomFactor = std::min(zoomFactor, 10.0);
    adjustSize();
}

void BusCanvas::zoomOut() {
    zoomFactor /= 1.1;
    zoomFactor = std::max(zoomFactor, 0.05);
    adjustSize();
}

void BusCanvas::fitToWidth() {
    int totalSamples = input_signals[0].size();
    double targetStep = (width() - 100.0) / totalSamples;
    zoomFactor = targetStep / 40.0;
    zoomFactor = std::clamp(zoomFactor, 0.05, 10.0);
    adjustSize();
}

QSize BusCanvas::sizeHint() const {
    int width = 100 + input_signals[0].size() * zoomFactor * 40;
    int height = 100 + visible_channels.count(true) * 50 + 50;
    return QSize(width, height);
}
