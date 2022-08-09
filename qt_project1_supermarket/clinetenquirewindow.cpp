#include "clinetenquirewindow.h"
#include "ui_clinetenquirewindow.h"
#include "clientwindow.h"
#include <QFile>
#include <QtDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QInputDialog>
#include <QDir>
#include <QMessageBox>
#include "useritemform.h"
#include <QDateTime>
#include "clinetenquireform.h"

clinetEnquireWindow::clinetEnquireWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::clinetEnquireWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());  //设置窗口大小
    //1.根据文件路径，将文件转换成文件类对象
    QFile file("./data/goods.json");

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

    QJsonArray resultArray = object.value("goods").toArray();//获取对象键admin数组的数据

    for(int i = 0; i < resultArray.size(); i ++)
    {
       //qDebug()<<"hh";
       //QDateTime dateTime(QDateTime::currentDateTime());
       //QString qStr = dateTime.toString("yyyy-MM-dd");
       QJsonObject arrayObject =  resultArray.at(i).toObject();
       int number = arrayObject.value("number").toInt();
       QString name = arrayObject.value("name").toString();
       QString total = arrayObject.value("quantity").toString();
       QString Purchase = arrayObject.value("outprice").toString();
       QString up_time = arrayObject.value("up_time").toString();
       QListWidgetItem *item = new QListWidgetItem;

       clinetEnquireForm* form = new clinetEnquireForm(this);


       form->setInfo(number,name,
                     total, Purchase,
                      up_time);

       item->setSizeHint(QSize(494,26));

       ui->listWidget->addItem(item);

       ui->listWidget->setItemWidget(item,form);
    }
}

clinetEnquireWindow::~clinetEnquireWindow()
{
    delete ui;
}

void clinetEnquireWindow::closeEvent(QCloseEvent *)
{
    dynamic_cast<clientWindow *>((this->parent()))->show();//返回主界面
    this->hide();
}
