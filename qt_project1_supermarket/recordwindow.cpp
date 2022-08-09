#include "recordwindow.h"
#include "ui_recordwindow.h"
#include "goodswindow.h"
#include "goodswindow.h"
#include "purchaseform.h"
#include <QDebug>
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
#include "recordform.h"

recordWindow::recordWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::recordWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());  //设置窗口大小
    expenses = 0;
    income = 0;
    //1.根据文件路径，将文件转换成文件类对象
   QFile file("./data/record.json");

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

   QJsonArray resultArray = object.value("record").toArray();
  // QStringList nameLists,passwordLists;
   for(int i = 0; i < resultArray.size(); i ++)
   {
       QJsonObject arrayObject =  resultArray.at(i).toObject();
       QString name = arrayObject.value("name").toString();
       QString type = arrayObject.value("type").toString();
       QString shoppingname = arrayObject.value("shoppingname").toString();
       int number = arrayObject.value("number").toInt();
       QString money = arrayObject.value("money").toString();
       QString up_time = arrayObject.value("up_time").toString();
       if(type=="收入")
       {
           income+=money.toInt();
       }
       else if(type=="支出")
       {
           expenses+=money.toInt();
       }

       QListWidgetItem *item = new QListWidgetItem;
       recordForm* form = new recordForm(this);

       form->setInfo(i+1,name,type,shoppingname,
                     number,money,up_time);

       item->setSizeHint(QSize(590,35));

       ui->listWidget->addItem(item);

       ui->listWidget->setItemWidget(item,form);
   }
    ui->incomelabel->setNum(income);
    ui->expenseslabel->setNum(expenses);
}

recordWindow::~recordWindow()
{
    delete ui;
}

void recordWindow::closeEvent(QCloseEvent *)
{
    dynamic_cast<goodsWindow *>((this->parent()))->show();//返回主界面
    this->hide();
}
