#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QTime>

namespace Ui {
class clientWindow;
}

//定义一个线程类
class MyThread1:public QThread
{
    Q_OBJECT
public:
    MyThread1(QObject *parent = nullptr):QThread(parent)
    {
        isFalg = true;
    }
    ~MyThread1()
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

class clientWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit clientWindow(QWidget *parent = nullptr);
    ~clientWindow();
    void closeEvent(QCloseEvent* );

public slots:
    void getname(const QString& name);
    void settime(QString strTime);


signals:
    void sendname(const QString& name);


private slots:
    void on_enquireButton_clicked();

    void on_settleButton_clicked();

private:
    Ui::clientWindow *ui;
    QString name;
    //声明一个线程类对象
    MyThread1* thread;
};

#endif // CLIENTWINDOW_H
