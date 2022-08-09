#ifndef SHOPPINGFORM_H
#define SHOPPINGFORM_H

#include <QWidget>

namespace Ui {
class shoppingForm;
}

class shoppingForm : public QWidget
{
    Q_OBJECT

public:
    explicit shoppingForm(QWidget *parent = nullptr);
    ~shoppingForm();

public slots:
    void setInfo(int num, const QString& shoppingname,
                  const QString& number,const QString& outprice,
                 const QString& money);
private:
    Ui::shoppingForm *ui;
};

#endif // SHOPPINGFORM_H
