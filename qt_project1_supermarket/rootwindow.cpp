#include "rootwindow.h"
#include "ui_rootwindow.h"
#include <QDateTime>
#include "loginwindow.h"
#include "userwindow.h"
#include "goodswindow.h"

int a=0;
RootWindow::RootWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RootWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());  //设置窗口大小

    thread = new MyThread(this);  //创建线程对象
    connect(thread,&MyThread::sendtime,this,&RootWindow::settime);
    a=1;
    thread->start();//启动线程

//    connect(this,&RootWindow::destroy,this,[=](){
//        thread->quit();
//        thread->wait();
//        thread->deleteLater();

//    });
}

RootWindow::~RootWindow()
{
    delete thread;
    delete ui;
}

void RootWindow::getname(const QString &name)
{
    ui->userlabel->setText("当前账号: "+name);
    this->name = name;
}

void MyThread::run()//获取实时时间
{
    while(isFalg)
    {
        if(a==1)
        {
             QDateTime dateTime(QDateTime::currentDateTime());
             QString qStr = dateTime.toString("yyyy-MM-dd hh:mm:ss ddd");
             emit sendtime(qStr);
             MyThread::sleep(1);
        }
        if(a==0)
            break;
    }
}

void MyThread::closeEvent(QCloseEvent *)
{

    isFalg = false;
}


void RootWindow::closeEvent(QCloseEvent *)
{

    a=0;
    //MyThread::isFalg = false;
    thread->quit();
    //delete thread;
   // thread->wait();
    //thread->deleteLater();
    dynamic_cast<LoginWindow *>((this->parent()))->show();//返回主界面
    this->hide();
}

void RootWindow::settime(QString strTime)//将时间设置到文本框内
{
    ui->timelabel->setText(strTime);
}

void RootWindow::on_userButton_clicked()
{
    thread->quit();
    //thread->wait();
    userWindow* uw = new userWindow(this);
    uw->show();
    this->hide();
}

void RootWindow::on_goodsButton_clicked()
{
    thread->quit();
    //thread->wait();
    goodsWindow* gw = new goodsWindow(this);
    connect(this,&RootWindow::sendname,gw,&goodsWindow::getname);
    emit sendname(this->name);
    gw->show();
    this->hide();
}
