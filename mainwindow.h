#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool eventFilter(QObject *obj, QEvent *event);
private slots:
    void on_pushButton_power_clicked();

    void on_pushButton_reboot_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
