#ifndef GOODSWINDOW_H
#define GOODSWINDOW_H

#include <QMainWindow>

namespace Ui {
class goodsWindow;
}

class goodsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit goodsWindow(QWidget *parent = nullptr);
    ~goodsWindow();
    void closeEvent(QCloseEvent* );

public slots:
    void getname(const QString& name);

signals:
    void sendname(const QString& name);

private slots:


    void on_enquireButton_clicked();

    void on_purchasesButton_clicked();

    void on_incomeButton_clicked();

private:
    Ui::goodsWindow *ui;
    QString name;
};

#endif // GOODSWINDOW_H
