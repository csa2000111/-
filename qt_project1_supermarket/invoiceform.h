#ifndef INVOICEFORM_H
#define INVOICEFORM_H

#include <QWidget>

namespace Ui {
class invoiceForm;
}

class invoiceForm : public QWidget
{
    Q_OBJECT

public:
    explicit invoiceForm(QWidget *parent = nullptr);
    ~invoiceForm();

public slots:
    void setInfo(int num, const QString& shoppingname,
                 const QString& money);
private:
    Ui::invoiceForm *ui;
};

#endif // INVOICEFORM_H
