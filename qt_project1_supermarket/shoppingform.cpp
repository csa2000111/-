#include "shoppingform.h"
#include "ui_shoppingform.h"

shoppingForm::shoppingForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::shoppingForm)
{
    ui->setupUi(this);
}

shoppingForm::~shoppingForm()
{
    delete ui;
}

void shoppingForm::setInfo(int num, const QString &shoppingname,
                           const QString &number, const QString &outprice,
                           const QString &money)
{
    ui->numEdit->setText(QString::number(num));
    ui->shoppingnameEdit->setText(shoppingname);
    ui->numberEdit->setText(number);
    ui->outpriceEdit->setText(outprice);
    ui->moneyEdit->setText(money);
}
