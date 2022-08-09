#ifndef SETTLEWINDOW_H
#define SETTLEWINDOW_H

#include <QMainWindow>
#include <QThread>

namespace Ui {
class settleWindow;
}

//定义一个线程类
class MyThread2:public QThread
{
    Q_OBJECT
public:
    MyThread2(QObject *parent = nullptr):QThread(parent)
    {
        isFalg = true;
    }
    ~MyThread2()
    {
        isFalg = false;
    }
    void run() override;

    void closeEvent(QCloseEvent* );
    bool getIsFalg() const;
    void setIsFalg(bool value);

signals:
    void sendtime(QString strTime);
    //void ExitWin();
private:
    bool isFalg;

};
class settleWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit settleWindow(QWidget *parent = nullptr);
    ~settleWindow();
    void closeEvent(QCloseEvent* );

public slots:
    void getname(const QString& name);
    void settime(QString strTime);
private slots:
    void on_searchButton_clicked();

    void on_settleButton_clicked();

private:
    Ui::settleWindow *ui;
    QString name;
    int shoppingPrice;
    QStringList numLists;
    QStringList shoppingNumberList;
    QStringList outpriceList;
    QStringList numberList;
    QStringList moneyList;
    //声明一个线程类对象
    MyThread2* thread;
};

#endif // SETTLEWINDOW_H
