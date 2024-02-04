#include "mainwindow.h"
#include "ui_mainwindow.h"


#define IIO_DEVICE "/sys/bus/iio/devices/iio:device0/in_voltage0_raw"

float netweight=0;
QString type_flag="g";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QPalette PAllbackground=this->palette();
    QImage ImgAllbackground(QString::fromUtf8(":/image/Asuna.png"));
    QImage pix=ImgAllbackground.scaled(this->width(),this->height(),Qt::IgnoreAspectRatio);
    PAllbackground.setBrush(QPalette::Window,QBrush(pix));
    this->setPalette(PAllbackground);

    timer=new QTimer(this);
    connect(timer,&QTimer::timeout,this,&MainWindow::timer_timeout_solt);
    if(timer!=nullptr)
    {
        timer->start(300);
    }
    qDebug()<<"is running";
}



float MainWindow::read_hx711()
{
    float value=0.0;
    QString a;
    QFile file(IIO_DEVICE);
    if (!file.open(QIODevice::ReadOnly))
    {
        // 如果文件无法打开，输出错误信息
        qDebug() << "Error opening file for reading: " << file.errorString();
        return -1;
    }

    QByteArray content = file.readAll();
    file.close();
    a=QString::fromUtf8(content);
    bool ok;
    value=a.toFloat(&ok);
    return value;
}

void MainWindow::timer_timeout_solt()
{
    int offset = 8363700;
    float scale = 406.0;
    float weight = 0;
    float actual_weight;
    qDebug()<<"timer_timeout_solt";
    float value;

    value=read_hx711();
    weight = (float)(value - offset) / scale;
    qDebug()<<"netweight="<<netweight<<"\n";
    actual_weight=weight-netweight;
     qDebug()<<"type_flag="<<type_flag;
    if(type_flag=="g")
    {

        ui->lcdNumber->display(actual_weight);
    }
    else if(type_flag=="kg")
    {
        ui->lcdNumber->display(actual_weight/1000);
    }

    /*
    if(actual_weight>=4999)
    {
        QString program="/bin/sh";
        QStringList arguments;
        arguments<<"-c"<<"echo 1 > /sys/class/leds/beep/brightness";
        bool result=QProcess::execute(program,arguments);
        if(result)
        {
            qDebug() << "Command executed successfully.";
        }
        else
        {
            qDebug() << "Failed to execute command.";
        }
        qDebug()<<"BEEP is on";


    }
    else
    {
        QString program="/bin/sh";
        QStringList arguments;
        arguments<<"-c"<<"echo 0 > /sys/class/leds/beep/brightness";
        bool result=QProcess::execute(program,arguments);
        if(result)
        {
            qDebug() << "Command executed successfully.";
        }
        else
        {
            qDebug() << "Failed to execute command.";
        }
        qDebug()<<"BEEP is off";


    }
    */



}




MainWindow::~MainWindow()
{
    delete ui;
}


/*
void MainWindow::on_pushButton_clicked(bool checked)
{
    if(checked)
    {
        qDebug()<<"timer is open";

        if(timer!=nullptr)
        {
            timer->start(300);
        }

    }
    else
    {
        qDebug()<<"timer is close";

        if(timer!=nullptr)
        {
            timer->stop();
        }

    }
}
*/



void MainWindow::on_pushButton_unit_clicked(bool checked)
{
    if(checked)
    {
        ui->label_2->setText("kg");
        type_flag="kg";

    }
    else
    {

        ui->label_2->setText("g");
        type_flag="g";
    }
}


void MainWindow::on_pushButton_netweight_clicked()
{
    float value_n;
    int offset = 8363700;
    float scale = 406.0;
    value_n=read_hx711();
    netweight = (float)(value_n - offset) / scale;
}

