#include "goodswindow.h"
#include "ui_goodswindow.h"
#include "endpointvolume.h"
#include "rootwindow.h"
#include "enquirewindow.h"
#include "purchasewindow.h"
#include "recordwindow.h"

goodsWindow::goodsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::goodsWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());  //设置窗口大小
}

goodsWindow::~goodsWindow()
{
    delete ui;
}

void goodsWindow::closeEvent(QCloseEvent *)
{
    dynamic_cast<RootWindow *>((this->parent()))->show();//返回主界面
    this->hide();
}

void goodsWindow::getname(const QString &name)
{
    this->name = name;
    ui->userlabel->setText("当前账号: "+ name);
}


void goodsWindow::on_enquireButton_clicked()
{
    enquireWindow* ew = new enquireWindow(this);
    ew->show();
    this->hide();
}

void goodsWindow::on_purchasesButton_clicked()
{
    purchaseWindow* pw = new purchaseWindow(this);
    connect(this,&goodsWindow::sendname,pw,&purchaseWindow::getname);
    emit sendname(this->name);
    pw->show();
    this->hide();
}

void goodsWindow::on_incomeButton_clicked()
{
    recordWindow* rw = new recordWindow(this);
    rw->show();
    this->hide();
}
