#include "mainwindow.h"
#include "buscanvas.h"

#include <QTreeWidget>
#include <QSplitter>
#include <QVBoxLayout>
#include <QScrollArea>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
    connectSignals();
}

void MainWindow::setupUI()
{
    auto* splitter = new QSplitter(this);

    tree = new QTreeWidget(splitter);
    tree->setHeaderHidden(true);

    tree->expandAll();

    auto* scrollArea = new QScrollArea(splitter);
    scrollArea->setWidgetResizable(false);

    canvas = new BusCanvas(scrollArea);

    splitter->setStretchFactor(1, 1);

    scrollArea->setWidget(canvas);
    setCentralWidget(splitter);
    setWindowTitle("Bus Signal Viewer");
    resize(1000, 600);
}

void MainWindow::connectSignals()
{
    connect(tree, &QTreeWidget::itemChanged, canvas, &BusCanvas::updateVisibility);
}