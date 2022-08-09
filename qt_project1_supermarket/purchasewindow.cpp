#include "purchasewindow.h"
#include "ui_purchasewindow.h"
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

purchaseWindow::purchaseWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::purchaseWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());  //设置窗口大小
}

purchaseWindow::~purchaseWindow()
{
    delete ui;
}

void purchaseWindow::closeEvent(QCloseEvent *)
{
    dynamic_cast<goodsWindow *>((this->parent()))->show();//返回主界面
    this->hide();
}

void purchaseWindow::on_pushButton_clicked()
{
    nameLists << ui->nameEdit->text();
    numberList << ui->quantityBox->text();
    inpriceList << ui->inpriceEdit->text();
    outpriceList << ui->outpriceEdit->text();
    int money=0;
    ui->listWidget->clear();
    for (int i=0;i<nameLists.size();i++) {
         QListWidgetItem *item = new QListWidgetItem;

         purchaseForm* form = new purchaseForm;
         form->setInfo(i+1,nameLists[i],
                       numberList[i],inpriceList[i],
                       outpriceList[i],numberList[i].toInt()*inpriceList[i].toInt());
         item->setSizeHint(QSize(461,40));
         ui->listWidget->addItem(item);
         ui->listWidget->setItemWidget(item,form);
         money += numberList[i].toInt()*inpriceList[i].toInt();
    }
    ui->moneylabel->setNum(money);
    ui->nameEdit->setText("");
    ui->inpriceEdit->setText("");
    ui->outpriceEdit->setText("");
    ui->quantityBox->setValue(0);

}

void purchaseWindow::on_insertButton_clicked()
{
    ui->listWidget->clear();
    ui->moneylabel->setText("");
    ui->nameEdit->setText("");
    ui->inpriceEdit->setText("");
    ui->outpriceEdit->setText("");
    ui->quantityBox->setValue(0);
    for(int i = 0; i < nameLists.size(); i++)
    {
        //1.根据文件路径，将文件转换成文件类对象
       QFile file("./data/goods.json");
       QFile file1("./data/record.json");
       //2.打开文件
       if(!file.open(QIODevice::ReadWrite))
       {
           qDebug() << "打开文件失败";
           return;
       }
       if(!file1.open(QIODevice::ReadWrite))
       {
           qDebug() << "打开文件失败";
           return;
       }

       //3.读取文件
       QByteArray data = file.readAll();
       QByteArray data1 = file1.readAll();
       //qDebug() << "data="<<data;

       //4.关闭文件
       //file.close();

       //5.数据解析
       //第一步：将QByteArray转QJsonDocument
       QJsonDocument doc = QJsonDocument::fromJson(data);
       QJsonDocument doc1 = QJsonDocument::fromJson(data1);
       //第二步：根据json文件中，具体json数据的格式，得到数据中的json对象或者json数组
       //通过 array() or object()这两个接口来完成
       QJsonObject object = doc.object();
       QJsonObject object1 = doc1.object();

       QJsonArray resultArray = object.value("goods").toArray();//获取对象键admin数组的数据
       QJsonArray resultArray1 = object1.value("record").toArray();
       // 定义 { } 对象
       QJsonObject interestObj;
       QJsonObject interestObj1;
       // 插入元素，对应键值对

       QDateTime dateTime(QDateTime::currentDateTime());
       QString qStr = dateTime.toString("yyyy-MM-dd");

       interestObj.insert("inprice", inpriceList[i]);
       interestObj.insert("name", nameLists[i]);
       interestObj.insert("number", resultArray.size()+1);
       interestObj.insert("outprice", outpriceList[i]);
       interestObj.insert("quantity", numberList[i]);
       interestObj.insert("up_time", qStr);

       /******************/
       interestObj1.insert("name", this->name);
       interestObj1.insert("type", "支出");
       interestObj1.insert("shoppingname",  nameLists[i]);
       interestObj1.insert("number", numberList[i].toInt());
       int money  = numberList[i].toInt()*inpriceList[i].toInt();
       QString s = QString::number(money);
       interestObj1.insert("money", s);
       interestObj1.insert("up_time", qStr);
       resultArray1.append(interestObj1);
       object1.insert("record",resultArray1);
       doc1.setObject(object1);

       QByteArray obje1 = doc1.toJson();

       file1.resize(0);
       file1.write(obje1);
       file1.close();// 关闭文件
       /*****************/

       int falg = 1;
       for(int a = 0; a < resultArray.size(); a ++)//判断goods.json里是否有物品
       {
           QJsonObject arrayObject =  resultArray.at(a).toObject();
           QString name1 = arrayObject.value("name").toString();

           if(name1 ==  nameLists[i])
           {
               QString quantity = arrayObject.value("quantity").toString();
               //qDebug()<<quantity;
               int num = quantity.toInt()+numberList[i].toInt();
               quantity = QString::number(num);
              // qDebug()<<quantity;
               falg = 0;
               QJsonObject interestObj = resultArray[a].toObject();


               interestObj.insert("inprice", inpriceList[i]);
               interestObj.insert("name", nameLists[i]);
               interestObj.insert("number", a+1);
               interestObj.insert("outprice", outpriceList[i]);
               interestObj.insert("quantity", quantity);
               interestObj.insert("up_time", qStr);

               resultArray.replace(a, interestObj);
               object["goods"] = resultArray;
               object.insert("goods",resultArray);
               doc.setObject(object);

               QByteArray obje = doc.toJson();
               file.resize(0);
               file.write(obje);

               file.close();// 关闭文件
               if(i < nameLists.size()-1)
               {
                    break;
               }
               QMessageBox::information(this,"采购提示","采购完成");
               inpriceList.clear();
               nameLists.clear();
               outpriceList.clear();
               numberList.clear();
               return;
           }
       }
       if(falg == 1)
       {
           resultArray.append(interestObj);
           object.insert("goods",resultArray);
           doc.setObject(object);

           QByteArray obje = doc.toJson();

           file.resize(0);
           file.write(obje);
           file.close();// 关闭文件
           if(i < nameLists.size()-1)
           {
                break;
           }
           QMessageBox::information(this,"采购提示","采购完成");
           inpriceList.clear();
           nameLists.clear();
           outpriceList.clear();
           numberList.clear();
           return;
       }
    }
}

void purchaseWindow::getname(const QString &name)
{
    this->name = name;
}
