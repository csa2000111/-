#ifndef RECORDFORM_H
#define RECORDFORM_H

#include <QWidget>

namespace Ui {
class recordForm;
}

class recordForm : public QWidget
{
    Q_OBJECT

public:
    explicit recordForm(QWidget *parent = nullptr);
    ~recordForm();
    void setInfo(int seria, const QString& name,
                 const QString& type, const QString& shoppingname,
                 int number,const QString& money,
                 const QString& up_time);
private:
    Ui::recordForm *ui;
};

#endif // RECORDFORM_H
