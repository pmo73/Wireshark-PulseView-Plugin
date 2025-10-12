#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "SignalModell.hpp"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow final : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~        MainWindow() override;

    MainWindow(MainWindow const &)     = delete;
    MainWindow(MainWindow &&) noexcept = delete;

    auto operator=(MainWindow const &) -> MainWindow & = delete;
    auto operator=(MainWindow &&) -> MainWindow        = delete;

    void set_signal_modell(std::vector<waveform::Module> const &modules);

private:
    Ui::MainWindow *ui;
    std::vector<waveform::Module> modules;
    std::map<std::string, std::shared_ptr<waveform::Signal>> signals_map;

private slots:
    void resize_signal_tree_widget() const;
    void resize_module_tree_widget() const;
    void add_signal_to_tree();
    /*void remove_signal_from_tree() const;
    void replace_signal_in_tree() const;*/
};
#endif // MAINWINDOW_H
