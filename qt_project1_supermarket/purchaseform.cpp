#include "purchaseform.h"
#include "ui_purchaseform.h"

purchaseForm::purchaseForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::purchaseForm)
{
    ui->setupUi(this);
}

purchaseForm::~purchaseForm()
{
    delete ui;
}

void purchaseForm::setInfo(int seria, const QString &name,
                           const QString &number, const QString &inprice,
                           const QString &outprice, int total)
{

    ui->serialEdit->setText(QString::number(seria,10));
    ui->nameEdit->setText(name);
    ui->numberEdit->setText(number);
    ui->inpriceEdit->setText(inprice);
    ui->outpriceEdit->setText(outprice);
    ui->totalEdit->setText(QString::number(total,10));
}
