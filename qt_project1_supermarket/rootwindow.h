#ifndef ROOTWINDOW_H
#define ROOTWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QTime>
//定义一个线程类
class MyThread:public QThread
{
    Q_OBJECT
public:
    MyThread(QObject *parent = nullptr):QThread(parent)
    {
        isFalg = true;
    }
     ~MyThread()
    {
        isFalg = false;
    }
    void run() override;

    bool getIsFalg() const;
    void setIsFalg(bool value);
    void closeEvent(QCloseEvent* );
signals:
    void sendtime(QString strTime);
    //void ExitWin();

private:
    bool isFalg;
};

namespace Ui {
class RootWindow;
}

class RootWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RootWindow(QWidget *parent = nullptr);
    ~RootWindow();
    void closeEvent(QCloseEvent* );
public slots:
    void getname(const QString& name);
    void settime(QString strTime);
private slots:
    void on_userButton_clicked();

    void on_goodsButton_clicked();

signals:
    void sendname(const QString& name);

private:
    Ui::RootWindow *ui;
    //声明一个线程类对象
    MyThread* thread;
    QString name;
};

#endif // ROOTWINDOW_H
