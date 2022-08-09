#include "clientwindow.h"
#include "ui_clientwindow.h"
#include "loginwindow.h"
#include "clinetenquireform.h"
#include "clinetenquirewindow.h"
#include "settlewindow.h"
int c=0;
clientWindow::clientWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::clientWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());  //设置窗口大小
    thread = new MyThread1(this);  //创建线程对象
    connect(thread,&MyThread1::sendtime,this,&clientWindow::settime);
    c=1;
    thread->start();//启动线程
//    connect(this,&clientWindow::destroy,this,[=](){
//        thread->quit();
//        thread->wait();
//        thread->deleteLater();

//    });
}

clientWindow::~clientWindow()
{
    delete ui;
}

void MyThread1::run()//获取实时时间
{
    while(isFalg)
    {
        if(c==1)
        {
             QDateTime dateTime(QDateTime::currentDateTime());
             QString qStr = dateTime.toString("yyyy-MM-dd hh:mm:ss ddd");
             emit sendtime(qStr);
             MyThread1::sleep(1);
        }
        if(c==0)
            break;
    }
}

void MyThread1::closeEvent(QCloseEvent *)
{
    isFalg = false;
}

bool MyThread1::getIsFalg() const
{
    return isFalg;
}

void MyThread1::setIsFalg(bool value)
{
    isFalg = value;
}

void clientWindow::closeEvent(QCloseEvent *)
{
    c=0;
    thread->quit();
    //thread->wait();
    //thread->deleteLater();
    dynamic_cast<LoginWindow *>((this->parent()))->show();//返回主界面
    this->hide();
}

void clientWindow::getname(const QString &name)
{
    ui->userlabel->setText("当前账号："+name);
    this->name = name;
}

void clientWindow::settime(QString strTime)
{
    ui->timelabel->setText(strTime);
}

void clientWindow::on_enquireButton_clicked()
{
    clinetEnquireWindow* cw = new clinetEnquireWindow(this);
    cw->show();
    this->hide();
}

void clientWindow::on_settleButton_clicked()
{
     settleWindow* sw = new settleWindow(this);
     connect(this,&clientWindow::sendname,sw,&settleWindow::getname);
     emit sendname(this->name);
     sw->show();
     this->hide();
}
