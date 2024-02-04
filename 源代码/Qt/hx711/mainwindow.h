#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QThread>
#include <QQueue>
#include <QTimer>

#include <QByteArray>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QProcess>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void timer_timeout_solt();

    float read_hx711();

    //void on_pushButton_clicked(bool checked);



    void on_pushButton_unit_clicked(bool checked);

    void on_pushButton_netweight_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
};
#endif // MAINWINDOW_H
