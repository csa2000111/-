#include "useritemform.h"
#include "ui_useritemform.h"
#include <QDebug>
#include <QFile>
#include <QtDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QInputDialog>
#include <QDir>
#include <QMessageBox>

userItemForm::userItemForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::userItemForm)
{
    ui->setupUi(this);
}

userItemForm::~userItemForm()
{
    delete ui;
}

void userItemForm::setInfo(const QString& name, const QString& password)
{
    ui->namelabel->setText(name);
    ui->passwordlabel->setText(password);
}

void userItemForm::getrow(int a)
{
    row = a;
}
void userItemForm::on_deleteButton_clicked()
{
    ui->passwordlabel->text();
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
    QJsonObject object = doc.object();

    QJsonArray resultArray = object.value("user").toArray();

    QJsonValue likeValue = object.value("user");
     for(int i = 0; i < resultArray.size(); i ++)
     {
         QJsonObject arrayObject =  resultArray.at(i).toObject();
         QString name = arrayObject.value("name").toString();
         QString password = arrayObject.value("password").toString();
         if (ui->namelabel->text()== name && ui->passwordlabel->text() == password) {
             QJsonArray likeArray = likeValue.toArray();


             likeArray.removeAt(i);

             object["user"] = likeArray;
             object.insert("user",likeArray);
             doc.setObject(object);

             QByteArray obje = doc.toJson();
             file.resize(0);
             file.write(obje);

             file.close();// 关闭文件
             this->deleteLater();
         }

     }

}

void userItemForm::on_deleteButton_2_clicked()
{
    ui->passwordlabel->text();
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
    QJsonObject object = doc.object();

    QJsonArray resultArray = object.value("user").toArray();

    QJsonValue likeValue = object.value("user");
     for(int i = 0; i < resultArray.size(); i ++)
     {
         QJsonObject arrayObject =  resultArray.at(i).toObject();
         QString name = arrayObject.value("name").toString();
         QString password = arrayObject.value("password").toString();
         if (ui->namelabel->text()== name && ui->passwordlabel->text() == password) {

             QJsonObject interestObj = resultArray[i].toObject();
             bool ok;
             QString name = QInputDialog::getText(this, tr("修改员工信息"),
                                                  tr("请输入员工姓名:"), QLineEdit::Normal,
                                                  QDir::home().dirName(), &ok);
             interestObj["name"] = name;
             ui->namelabel->setText(name);
             QString password = QInputDialog::getText(this, tr("修改员工信息"),
                                                  tr("请输入员工密码:"), QLineEdit::Normal,
                                                  QDir::home().dirName(), &ok);
             interestObj["password"] = password;
             ui->passwordlabel->setText(password);
             resultArray.replace(i, interestObj);
             object["user"] = resultArray;
             object.insert("user",resultArray);
             doc.setObject(object);

             QByteArray obje = doc.toJson();
             file.resize(0);
             file.write(obje);

             file.close();// 关闭文件
             QMessageBox::information(this,"修改提示","修改成功");

         }

     }
}
