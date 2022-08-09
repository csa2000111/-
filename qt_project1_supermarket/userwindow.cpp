#include "userwindow.h"
#include "ui_userwindow.h"
#include <QListWidgetItem>
#include "useritemform.h"
#include "rootwindow.h"
#include <QFile>
#include <QtDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QInputDialog>
#include <QDir>
#include <QMessageBox>
#include "useritemform.h"

userWindow::userWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::userWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());  //设置窗口大小

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
      // QStringList nameLists,passwordLists;
       for(int i = 0; i < resultArray.size(); i ++)
       {
           QJsonObject arrayObject =  resultArray.at(i).toObject();
           QString name = arrayObject.value("name").toString();
           QString password = arrayObject.value("password").toString();
           QListWidgetItem *item = new QListWidgetItem;

           userItemForm* form = new userItemForm(this);

           connect(this,&userWindow::sendrow,form,&userItemForm::getrow);
           form->setInfo(name,password);

           item->setSizeHint(QSize(400,75));

           ui->listWidget->addItem(item);

           ui->listWidget->setItemWidget(item,form);
       }

}

userWindow::~userWindow()
{
    delete ui;
}

void userWindow::closeEvent(QCloseEvent *)
{
    dynamic_cast<RootWindow *>((this->parent()))->show();//返回主界面
    this->hide();
}

void userWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    //1.根据文件路径，将文件转换成文件类对象
    QFile file("./data/info.json");
    emit sendrow(ui->listWidget->row(item));
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
    //file.close();

    //5.数据解析
    //第一步：将QByteArray转QJsonDocument
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject object = doc.object();

    QJsonArray resultArray = object.value("user").toArray();
    int row = ui->listWidget->row(item);
    QJsonValue likeValue = object.value("user");
    if (likeValue.type() == QJsonValue::Array) {
        QJsonArray likeArray = likeValue.toArray();


        likeArray.removeAt(row);

        object["user"] = likeArray;
        object.insert("user",likeArray);
        doc.setObject(object);

        QByteArray obje = doc.toJson();
        file.resize(0);
        file.write(obje);

        file.close();// 关闭文件
    }
    ui->listWidget->takeItem(ui->listWidget->row(item));

}

void userWindow::on_pushButton_clicked()
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
   //file.close();

   //5.数据解析
   //第一步：将QByteArray转QJsonDocument
   QJsonDocument doc = QJsonDocument::fromJson(data);
   //第二步：根据json文件中，具体json数据的格式，得到数据中的json对象或者json数组
   //通过 array() or object()这两个接口来完成
   QJsonObject object = doc.object();

   QJsonArray resultArray = object.value("user").toArray();//获取对象键admin数组的数据

   // 定义 { } 对象
   QJsonObject interestObj;
   // 插入元素，对应键值对

   bool ok;
   QString name = QInputDialog::getText(this, tr("添加员工"),
                                        tr("请输入员工姓名:"), QLineEdit::Normal,
                                        QDir::home().dirName(), &ok);
   interestObj.insert("name", name);

   QString password = QInputDialog::getText(this, tr("添加员工"),
                                        tr("请输入员工密码:"), QLineEdit::Normal,
                                        QDir::home().dirName(), &ok);
   for(int i = 0; i < resultArray.size(); i ++)//判断info.json里是否有此用户
   {
       QJsonObject arrayObject =  resultArray.at(i).toObject();
       QString name1 = arrayObject.value("name").toString();
       QString password1 = arrayObject.value("password").toString();
       if(name == name1 )
       {
           //管理员界面
           QMessageBox::information(this,"注册提示","该员工已存在");
           dynamic_cast<RootWindow *>((this->parent()))->show();//返回主界面
           this->close();
           return;
       }
   }
   interestObj.insert("password", password);
   resultArray.append(interestObj);
   object.insert("user",resultArray);
   doc.setObject(object);

   QByteArray obje = doc.toJson();
   file.resize(0);
   file.write(obje);

   file.close();// 关闭文件

   QMessageBox::information(this,"注册提示","添加员工成功");

   dynamic_cast<RootWindow *>((this->parent()))->show();//返回主界面
   this->close();
}
