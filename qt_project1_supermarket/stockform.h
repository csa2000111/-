#ifndef STOCKFORM_H
#define STOCKFORM_H

#include <QWidget>

namespace Ui {
class stockForm;
}

class stockForm : public QWidget
{
    Q_OBJECT

public:
    explicit stockForm(QWidget *parent = nullptr);
    ~stockForm();

public slots:
    void setInfo(int number, const QString& shoppingname,
                  const QString& stock);

private:
    Ui::stockForm *ui;
};

#endif // STOCKFORM_H
