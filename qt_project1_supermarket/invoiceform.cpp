#include "invoiceform.h"
#include "ui_invoiceform.h"

invoiceForm::invoiceForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::invoiceForm)
{
    ui->setupUi(this);
}

invoiceForm::~invoiceForm()
{
    delete ui;
}

void invoiceForm::setInfo(int num, const QString &shoppingname, const QString &money)
{
    ui->numberEdit->setText(QString::number(num));
    ui->shoppingNameEdit->setText(shoppingname);
    ui->moneyEdit->setText(money);
}
