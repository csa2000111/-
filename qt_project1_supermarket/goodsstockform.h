#ifndef GOODSSTOCKFORM_H
#define GOODSSTOCKFORM_H

#include <QWidget>

namespace Ui {
class GoodsStockForm;
}

class GoodsStockForm : public QWidget
{
    Q_OBJECT

public:
    explicit GoodsStockForm(QWidget *parent = nullptr);
    ~GoodsStockForm();
public slots:
    void setInfo(int number, const QString& name,
                 const QString& total, const QString& Purchase,
                 int money, const QString& up_time);

private:
    Ui::GoodsStockForm *ui;
};

#endif // GOODSSTOCKFORM_H
