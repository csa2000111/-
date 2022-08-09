#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QFile>
#include <QtDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "rootwindow.h"
#include <qmessagebox.h>
#include "clientwindow.h"

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    PasswordButton = true;
    login = false;

    this->setFixedSize(this->width(),this->height());  //设置窗口大小

    ui->passwordEdit->setEchoMode(QLineEdit::Password);//设置密码模式

    QString map("image: url(:/close_eyes.png);background: #a7a7fa;");
    ui->passwordButton->setStyleSheet(map);
//    QPixmap pixmp(":/logo.png");
//    QIcon icon = QPixmap(pixmp);
//    this->setWindowIcon(icon);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_rootButton_clicked()
{
    //1.根据文件路径，将文件转换成文件类对象
   QFile file("./data/info.json");

   //2.打开文件
   if(!file.open(QIODevice::ReadWrite))
   {
       qDebug() << "打开文件失败";
       return;
   }

   //3.读取文件
   QByteArray data = file.readAll();

   //qDebug() << "data="<<data;

   //4.关闭文件
   file.close();

   //5.数据解析
   //第一步：将QByteArray转QJsonDocument
   QJsonDocument doc = QJsonDocument::fromJson(data);
   //第二步：根据json文件中，具体json数据的格式，得到数据中的json对象或者json数组
   //通过 array() or object()这两个接口来完成
   QJsonObject object = doc.object();

   QJsonArray resultArray = object.value("admin").toArray();//获取对象键admin数组的数据

   for(int i = 0; i < resultArray.size(); i ++)//判断info.json里是否有此用户
   {
       QJsonObject arrayObject =  resultArray.at(i).toObject();
       QString name = arrayObject.value("name").toString();
       QString password = arrayObject.value("password").toString();
       if(name == ui->userEdit->text()&& password == ui->passwordEdit->text())
       {
           //管理员界面
           file.close();
           login  = true;
           QMessageBox::information(this,"登录提示","登录成功");
           RootWindow* rw = new RootWindow(this);
           connect(this,&LoginWindow::sendname,rw,&RootWindow::getname);
           //connect(rw,SIGNAL(ExitWin()),this,SLOT(this.show()));
           emit sendname(ui->userEdit->text());
           rw->show();
           this->hide();
       }
   }
   if(!login)
   {
       QMessageBox::information(this,"登录提示","账号或密码错误，请重新输入");
   }
}

void LoginWindow::on_userButton_clicked()
{
    //1.根据文件路径，将文件转换成文件类对象
       QFile file("./data/info.json");

       //2.打开文件
       if(!file.open(QIODevice::ReadWrite))
       {
           qDebug() << "打开文件失败";
           return;
       }

       //3.读取文件
       QByteArray data = file.readAll();

       //qDebug() << "data="<<data;

       //4.关闭文件
       file.close();

       //5.数据解析
       //第一步：将QByteArray转QJsonDocument
       QJsonDocument doc = QJsonDocument::fromJson(data);
       //第二步：根据json文件中，具体json数据的格式，得到数据中的json对象或者json数组
       //通过 array() or object()这两个接口来完成
       QJsonObject object = doc.object();

       QJsonArray resultArray = object.value("user").toArray();//获取对象键admin数组的数据

       for(int i = 0; i < resultArray.size(); i ++)//判断info.json里是否有此用户
       {
           QJsonObject arrayObject =  resultArray.at(i).toObject();
           QString name = arrayObject.value("name").toString();
           QString password = arrayObject.value("password").toString();
           if(name == ui->userEdit->text()&& password == ui->passwordEdit->text())
           {
               //员工界面
               file.close();
               login  = true;
               QMessageBox::information(this,"登录提示","登录成功");
               clientWindow* cw = new clientWindow(this);
               connect(this,&LoginWindow::sendname,cw,&clientWindow::getname);
               emit sendname(ui->userEdit->text());
               cw->show();
               this->hide();
           }
       }
       if(!login)
       {
           QMessageBox::information(this,"登录提示","账号或密码错误，请重新输入");
       }
}

void LoginWindow::on_passwordButton_clicked()
{
    if( PasswordButton)
    {
        QString map("image: url(:/open_eyes.png);background: #a7a7fa;");//设置显示密码
        ui->passwordButton->setStyleSheet(map);
        ui->passwordEdit->setEchoMode(QLineEdit::Normal);
        PasswordButton = false;
    }
    else
    {
        QString map("image: url(:/close_eyes.png);background: #a7a7fa;");//设置显示密码
        ui->passwordButton->setStyleSheet(map);
        ui->passwordEdit->setEchoMode(QLineEdit::Password);
        PasswordButton = true;
    }
}
