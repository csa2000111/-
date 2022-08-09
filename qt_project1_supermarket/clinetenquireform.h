#ifndef CLINETENQUIREFORM_H
#define CLINETENQUIREFORM_H

#include <QWidget>

namespace Ui {
class clinetEnquireForm;
}

class clinetEnquireForm : public QWidget
{
    Q_OBJECT

public:
    explicit clinetEnquireForm(QWidget *parent = nullptr);
    ~clinetEnquireForm();

public slots:
    void setInfo(int number, const QString& name,
                 const QString& total, const QString& Purchase,
                  const QString& up_time);
private:
    Ui::clinetEnquireForm *ui;
};

#endif // CLINETENQUIREFORM_H
