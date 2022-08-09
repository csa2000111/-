#ifndef PURCHASEWINDOW_H
#define PURCHASEWINDOW_H

#include <QMainWindow>

namespace Ui {
class purchaseWindow;
}

class purchaseWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit purchaseWindow(QWidget *parent = nullptr);
    ~purchaseWindow();
    void closeEvent(QCloseEvent* );
private slots:
    void on_pushButton_clicked();

    void on_insertButton_clicked();

public slots:
    void getname(const QString& name);

private:
    Ui::purchaseWindow *ui;
    QStringList nameLists;
    QStringList numberList;
    QStringList inpriceList;
    QStringList outpriceList;
    QString name;
};

#endif // PURCHASEWINDOW_H
