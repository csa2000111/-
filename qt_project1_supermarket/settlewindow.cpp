#include "settlewindow.h"
#include "ui_settlewindow.h"
#include "clientwindow.h"
#include <QInputDialog>
#include <QListWidgetItem>
#include <QFile>
#include <QtDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QInputDialog>
#include <QDir>
#include <QMessageBox>
#include <QDateTime>
#include "stockform.h"
#include "shoppingform.h"
#include "invoiceform.h"
int b=0;
settleWindow::settleWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::settleWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());  //设置窗口大小
    thread = new MyThread2(this);  //创建线程对象
    connect(thread,&MyThread2::sendtime,this,&settleWindow::settime);
    b=1;
    thread->start();//启动线程
    shoppingPrice=0;
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
       QListWidgetItem *item = new QListWidgetItem;

       stockForm* form = new stockForm(this);


       form->setInfo(number,name,total);

       item->setSizeHint(QSize(244,22));

       ui->stocklistWidget->addItem(item);

       ui->stocklistWidget->setItemWidget(item,form);
    }
}

settleWindow::~settleWindow()
{
    delete ui;
}

void settleWindow::closeEvent(QCloseEvent *)
{
    b=0;
    dynamic_cast<clientWindow *>((this->parent()))->show();//返回主界面
    this->hide();
}

void settleWindow::getname(const QString &name)
{
    this->name = name;
    ui->userlabel->setText("当前账号："+name);
}

void settleWindow::settime(QString strTime)
{
    ui->timelabel->setText(strTime);
}

void settleWindow::on_searchButton_clicked()
{
    ui->invoicelistWidget->clear();
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
    int flag = 0;

   for(int i = 0; i < resultArray.size(); i ++)//判断info.json里是否有此用户
   {
       QJsonObject arrayObject =  resultArray.at(i).toObject();
       QString name = arrayObject.value("name").toString();
       if(name == ui->shoppingnameEdit_->text())
       {
           ui->shoppingnameEdit_->setText("");
           bool ok;
           QString number1 = QInputDialog::getText(this, tr("购买数量"),
                                                tr("请输入购买数量:"), QLineEdit::Normal,
                                                QDir::home().dirName(), &ok);
            QString quantity = arrayObject.value("quantity").toString();
           if(quantity >= number1)
           {
               shoppingPrice= shoppingPrice+1;
               flag = 1;
               QString shoppingname = arrayObject.value("name").toString();
               QString price = arrayObject.value("outprice").toString();


               QListWidgetItem *item = new QListWidgetItem;

               shoppingForm* form = new shoppingForm(this);
                int mon = number1.toInt()*price.toInt();
               QString money = QString::number(mon);

               numLists<<QString::number(shoppingPrice);
               shoppingNumberList<<shoppingname;
               numberList<<number1;
               outpriceList<<price;
               moneyList<<money;

               form->setInfo(shoppingPrice,shoppingname,number1,price,money);

               item->setSizeHint(QSize(483,21));

               ui->shoppinglistWidget->addItem(item);

               ui->shoppinglistWidget->setItemWidget(item,form);
           }
           else
           {
               QMessageBox::information(this,"购买提示","没有足够商品库存");
               return;
           }
       }
   }
   int money1=0;
   for(int i=0;i<moneyList.size();i++)
   {
       money1 += moneyList[i].toInt();
   }
   ui->moneylabel->setNum(money1);
   money1=0;
   if(flag==0)
   {
       ui->shoppingnameEdit_->setText("");
       QMessageBox::information(this,"购买提示","没有此商品");
       return;
   }
}

void settleWindow::on_settleButton_clicked()
{
    shoppingPrice=0;
    ui->invoicelistWidget->clear();
    ui->moneylabel->setText("");
    ui->shoppinglistWidget->clear();
    for(int i = 0; i < moneyList.size(); i ++)
    {
       int number = numLists[i].toInt();
       QString name = shoppingNumberList[i];
       QString money = moneyList[i];
       QListWidgetItem *item = new QListWidgetItem;

       invoiceForm* form = new invoiceForm(this);

       form->setInfo(number,name,money);
       item->setSizeHint(QSize(241,20));

       ui->invoicelistWidget->addItem(item);
       ui->invoicelistWidget->setItemWidget(item,form);
    }
    int money1=0;
    for(int i=0;i<moneyList.size();i++)
    {
        money1 += moneyList[i].toInt();
    }
    ui->moneylabel1->setNum(money1);
    money1=0;
   for(int i = 0; i < shoppingNumberList.size(); i++)
   {
        QDateTime dateTime(QDateTime::currentDateTime());
        QString qStr = dateTime.toString("yyyy-MM-dd");
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
        //file.close();

        //5.数据解析
        //第一步：将QByteArray转QJsonDocument
        QJsonDocument doc = QJsonDocument::fromJson(data);
        //第二步：根据json文件中，具体json数据的格式，得到数据中的json对象或者json数组
        //通过 array() or object()这两个接口来完成
        QJsonObject object = doc.object();

        QJsonArray resultArray = object.value("record").toArray();//获取对象键admin数组的数据

        QJsonObject interestObj1;
        interestObj1.insert("name", this->name);
        interestObj1.insert("type", "收入");
        interestObj1.insert("shoppingname",  shoppingNumberList[i]);
        interestObj1.insert("number", numberList[i].toInt());

        int money  = numberList[i].toInt()*outpriceList[i].toInt();
        QString s = QString::number(money);

        interestObj1.insert("money", s);
        interestObj1.insert("up_time", qStr);
        resultArray.append(interestObj1);
        object.insert("record",resultArray);
        doc.setObject(object);

        QByteArray obje = doc.toJson();

        file.resize(0);
        file.write(obje);
        file.close();// 关闭文件
   }
   for(int i = 0; i < shoppingNumberList.size(); i++)
   {
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
       //file.close();
       //5.数据解析
       //第一步：将QByteArray转QJsonDocument
       QJsonDocument doc = QJsonDocument::fromJson(data);
       QJsonObject object = doc.object();

       QJsonArray resultArray = object.value("goods").toArray();

       QJsonValue likeValue = object.value("goods");
        for(int a = 0; a < resultArray.size(); a ++)
        {
            QJsonObject arrayObject =  resultArray.at(a).toObject();
            int number = arrayObject.value("number").toInt();
            QString name = arrayObject.value("name").toString();
            QString quantity = arrayObject.value("quantity").toString();
            QString inprice = arrayObject.value("inprice").toString();
            QString outprice = arrayObject.value("outprice").toString();
            QString up_time = arrayObject.value("up_time").toString();

            if (shoppingNumberList[i]== name) {
                int q = quantity.toInt()-numberList[i].toInt();
                quantity = QString::number(q);
                QJsonObject interestObj = resultArray[a].toObject();
                interestObj["inprice"] = inprice;
                interestObj["name"] = name;
                interestObj["number"] = number;
                interestObj["outprice"] = outprice;
                interestObj["quantity"] = quantity;
                interestObj["up_time"] = up_time;

                resultArray.replace(a, interestObj);
                object["goods"] = resultArray;
                object.insert("goods",resultArray);
                doc.setObject(object);

                QByteArray obje = doc.toJson();
                file.resize(0);
                file.write(obje);

                file.close();// 关闭文件

            }

        }
    }
   ui->stocklistWidget->clear();
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
      QListWidgetItem *item = new QListWidgetItem;

      stockForm* form = new stockForm(this);


      form->setInfo(number,name,total);

      item->setSizeHint(QSize(244,22));

      ui->stocklistWidget->addItem(item);

      ui->stocklistWidget->setItemWidget(item,form);
   }
}

void MyThread2::run()
{
    while(isFalg)
    {
        if(b==1)
        {
             QDateTime dateTime(QDateTime::currentDateTime());
             QString qStr = dateTime.toString("yyyy-MM-dd hh:mm:ss ddd");
             emit sendtime(qStr);
             MyThread2::sleep(1);
        }
        if(b==0)
            break;
    }
}

void MyThread2::closeEvent(QCloseEvent *)
{
    isFalg = false;

}
