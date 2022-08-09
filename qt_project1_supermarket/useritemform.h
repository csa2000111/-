#ifndef USERITEMFORM_H
#define USERITEMFORM_H

#include <QWidget>

namespace Ui {
class userItemForm;
}

class userItemForm : public QWidget
{
    Q_OBJECT

public:
    explicit userItemForm(QWidget *parent = nullptr);
    ~userItemForm();

public slots:
    void setInfo(const QString& name, const QString& password);
    void getrow(int a);

private slots:

    void on_deleteButton_clicked();

    void on_deleteButton_2_clicked();

private:
    Ui::userItemForm *ui;
    int row = 0;
};

#endif // USERITEMFORM_H
