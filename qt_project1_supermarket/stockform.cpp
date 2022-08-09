#include "stockform.h"
#include "ui_stockform.h"

stockForm::stockForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::stockForm)
{
    ui->setupUi(this);
}

stockForm::~stockForm()
{
    delete ui;
}

void stockForm::setInfo(int number, const QString &shoppingname, const QString &stock)
{
    ui->numEdit->setText(QString::number(number));
    ui->shoppingEdit->setText(shoppingname);
    ui->stockEdit->setText(stock);
}
