#include "recordform.h"
#include "ui_recordform.h"

recordForm::recordForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::recordForm)
{
    ui->setupUi(this);
}

recordForm::~recordForm()
{
    delete ui;
}

void recordForm::setInfo(int seria, const QString &name, const QString &type,
                         const QString &shoppingname, int number,
                         const QString &money, const QString &up_time)
{
    ui->serialEdit->setText(QString::number(seria));
    ui->nameEdit->setText(name);
    ui->typeEdit->setText(type);
    ui->shoppingnameEdit->setText(shoppingname);
    ui->numberEdit->setText(QString::number(number));
    ui->moneyEdit->setText(money);
    ui->uptimeEdit->setText(up_time);
}
