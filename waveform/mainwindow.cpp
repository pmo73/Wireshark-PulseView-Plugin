#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::
MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->SignalTreeWidget, &QTreeWidget::expanded, this,
            &MainWindow::resize_signal_tree_widget);
    connect(ui->SignalTreeWidget, &QTreeWidget::collapsed, this,
            &MainWindow::resize_signal_tree_widget);
    connect(ui->ModuleTreeWidget, &QTreeWidget::expanded, this,
            &MainWindow::resize_module_tree_widget);
    connect(ui->ModuleTreeWidget, &QTreeWidget::collapsed, this,
            &MainWindow::resize_module_tree_widget);
    connect(ui->AddSignal, &QPushButton::clicked, this, &MainWindow::add_signal_to_tree);
    auto *const item = new QTreeWidgetItem();
    item->setText(0, "Signal");
    item->setText(1, "Test");

    auto *const item2 = new QTreeWidgetItem();
    item2->setText(0, "Module");
    item2->setText(1, "Test2");
    item->addChild(item2);
    ui->SignalTreeWidget->addTopLevelItem(item);
}

MainWindow::~
MainWindow()
{
    delete ui;
}
void
MainWindow::set_signal_modell(std::vector<waveform::Module> const &modules)
{
    this->modules = modules;
    for (auto const &module : modules) {
        auto *const module_item = new QTreeWidgetItem();
        module_item->setText(0, module.name.c_str());
        for (auto const &signal : module.signal_list) {
            auto *const signal_item = new QTreeWidgetItem();
            signal_item->setText(0, signal->name.c_str());
            signal_item->setText(1, std::to_string(signal->bit_width).c_str());
            module_item->addChild(signal_item);
            signals_map.emplace(signal->name, signal);
        }
        ui->ModuleTreeWidget->addTopLevelItem(module_item);
    }
}
void
MainWindow::resize_signal_tree_widget() const
{
    ui->SignalTreeWidget->resizeColumnToContents(0);
}
void
MainWindow::resize_module_tree_widget() const
{
    ui->ModuleTreeWidget->resizeColumnToContents(0);
}
void
MainWindow::add_signal_to_tree()
{
    for (auto const &item : ui->ModuleTreeWidget->selectedItems()) {
        auto *const signal_item = new QTreeWidgetItem();
        auto        signal_name = item->text(0);
        signal_item->setText(0, signal_name);

        if (signals_map.contains(signal_name.toStdString())) {
            for (std::size_t i = signals_map[signal_name.toStdString()]->bit_width; i > 0; --i) {
                auto *const       bit_item = new QTreeWidgetItem();
                std::string const bit_name =
                        signal_name.toStdString() + " [" + std::to_string(i - 1) + "]";
                bit_item->setText(0, bit_name.data());
                signal_item->addChild(bit_item);
            }
            ui->SignalTreeWidget->addTopLevelItem(signal_item);
            resize_signal_tree_widget();
        }
    }
}
