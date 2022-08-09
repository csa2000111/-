#include "clinetenquireform.h"
#include "ui_clinetenquireform.h"

clinetEnquireForm::clinetEnquireForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::clinetEnquireForm)
{
    ui->setupUi(this);
}

clinetEnquireForm::~clinetEnquireForm()
{
    delete ui;
}

void clinetEnquireForm::setInfo(int number, const QString &name,
                                const QString &total, const QString &Purchase,
                                const QString &up_time)
{

    ui->numberEdit->setText(QString::number(number));
    ui->nameEdit->setText(name);
    ui->totalEdit->setText(total);
    ui->PurchaseEdit->setText(Purchase);
    ui->up_timeEdit->setText(up_time);
}
