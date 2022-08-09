#ifndef PURCHASEFORM_H
#define PURCHASEFORM_H

#include <QWidget>

namespace Ui {
class purchaseForm;
}

class purchaseForm : public QWidget
{
    Q_OBJECT

public:
    explicit purchaseForm(QWidget *parent = nullptr);
    ~purchaseForm();
    void setInfo(int seria, const QString& name,
                 const QString& number, const QString& inprice,
                 const QString& outprice, int total );
private:
    Ui::purchaseForm *ui;
};

#endif // PURCHASEFORM_H
