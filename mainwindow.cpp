#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qdebug.h>
#include <qevent.h>

#include <QMessageBox>

#include "main.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);

    qApp->installEventFilter(this);
//    setWindowFlags(Qt::WindowStaysOnTopHint);
//    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);

    QCursor cursor(Qt::BlankCursor);
    QApplication::setOverrideCursor(cursor);
    QApplication::changeOverrideCursor(cursor);

    ui->pushButton_power->setStyleSheet("QPushButton {border: solid ; border-radius: 15;} QPushButton:focus { background-color: LightGrey; border: solid ; border-radius: 15;}");
    ui->pushButton_reboot->setStyleSheet("QPushButton {border: solid ; border-radius: 15;} QPushButton:focus { background-color: LightGrey; border: solid ; border-radius: 15;}");

    qApp->setStyleSheet(
        "QInputDialog {border-style: solid; border-width: 3px; border-radius: 10px; border-color: Orange; background-color: white; padding : 10px} "
        "QAbstractSpinBox {border-style: solid; border-width: 1px; border-radius: 2px; border-color: black; background-color: white; padding : 1px} "
        "QListWidget {background-color: white;show-decoration-selected: 0;} "
        "QListWidget::item:selected {background: #01BAEF;} "
        "QListWidget::item:selected:active {background: #0B4F6C;} "
        "QMessageBox {border-color: Orange; background-color: white; border-style: inset;border-width: 3px;border-radius: 10px; font: bold 12px orange; text-align: center; padding: 3px;} "
        "QMessageBox QLabel {font: bold 12px orange; text-align: center; padding: 3px;} "
        "QPushButton {border-color: grey; background-color: white; border-style: inset;border-width: 1px;border-radius: 10px; padding: 5px; outline: none;} "
        "QPushButton::focus {border: 3px solid #0B4F6C; padding: 5px;} "
        "QLineEdit {border-color: grey; background-color: white; border-style: inset;border-width: 1px;border-radius: 3px; padding: 5px; outline: none;} ");
//    system("setkeycodes 0 1 1 30 2 48  3 46 4 32 5 18 8 33 9 34 a 35 b 23 c 36 d 37 10 38 11 50 12 49 13 24 14 25 15 16 18 19 19 31 1a 20 1b 22 1c 47 1d 17 20 69 21 45 22 21 23 44 24 57 25 28");
    system("setkeycodes 0 1 1 14 2 106 3 103 4 108 5 15 8 33 9 34 a 35 b 2 c 3 d 4 10 38 11 50 12 49 13 5 14 6 15 7 18 19 19 31 1a 20 1b 8 1c 9 1d 10 20 69 21 45 22 21 23 52 24 11 25 28");

//    showFullScreen();

    ui->pushButton_power->setFocus();

    raise();
    activateWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_power_clicked()
{
    qDebug() << "switching off";

    QMessageBox msgBoxMessage(this);
    msgBoxMessage.setWindowTitle("Info!");
    //      msgBoxMessage.setIcon(QMessageBox::Information);
    msgBoxMessage.setStandardButtons(QMessageBox::NoButton);
    msgBoxMessage.setText("SHUTTING DOWN...");
    msgBoxMessage.setStyleSheet("QMessageBox {border-style: inset;border-width: 3px;border-radius: 10px; min-width:500 px; min-height:500 px;} QMessageBox QLabel {min-width: 200px; font: bold 25px;text-align: center; padding: 15px 15px 15px 30px;}");
    msgBoxMessage.show();
    QCoreApplication::processEvents();
    QCoreApplication::processEvents();
    QCoreApplication::processEvents();

    system("shutdown -h now");
}

void MainWindow::on_pushButton_reboot_clicked()
{
    qDebug() << "rebooting";

    QMessageBox msgBoxMessage(this);
    msgBoxMessage.setWindowTitle("Info!");
    //      msgBoxMessage.setIcon(QMessageBox::Information);
    msgBoxMessage.setStandardButtons(QMessageBox::NoButton);
    msgBoxMessage.setText("REBOOTING...");
    msgBoxMessage.setStyleSheet("QMessageBox {border-style: inset;border-width: 3px;border-radius: 10px; min-width:500 px; min-height:500 px;} QMessageBox QLabel {min-width: 200px; font: bold 25px;text-align: center; padding: 15px 15px 15px 30px;}");
    msgBoxMessage.show();
    QCoreApplication::processEvents();
    QCoreApplication::processEvents();
    QCoreApplication::processEvents();
    system("reboot");
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if((event->type() == QEvent::KeyRelease || event->type() == QEvent::KeyPress) && stopped == 1)
    {
        event->accept();
        return true;
    }

    if (event->type() == QEvent::KeyRelease || event->type() == QEvent::KeyPress)
    {
        raise();
        activateWindow();

        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
//        qDebug() << keyEvent->key();
        if(event->type() == QEvent::KeyRelease && keyEvent->key() == Qt::Key_Escape)
        {
            qApp->exit();
        }
    }

    return QObject::eventFilter(obj, event);
}
