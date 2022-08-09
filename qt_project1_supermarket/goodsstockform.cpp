#include "goodsstockform.h"
#include "ui_goodsstockform.h"

GoodsStockForm::GoodsStockForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GoodsStockForm)
{
    ui->setupUi(this);
}

GoodsStockForm::~GoodsStockForm()
{
    delete ui;
}

void GoodsStockForm::setInfo(int number, const QString &name, const QString &total, const QString &Purchase, int money, const QString &up_time)
{
    ui->numberlabel->setNum(number);
    ui->namelabel->setText(name);
    ui->totallabel->setText(total);
    ui->Purchaselabel->setText(Purchase);
    ui->moneylabel->setNum(money);
    ui->up_timelabel->setText(up_time);
}


