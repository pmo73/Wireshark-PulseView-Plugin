#pragma once

#include <QMainWindow>

class QTreeWidget;
class BusCanvas;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    QTreeWidget* tree;
    BusCanvas* canvas;

    void setupUI();
    void connectSignals();
};