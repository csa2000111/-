#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QMainWindow>

#include <QListWidgetItem>

namespace Ui {
class userWindow;
}

class userWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit userWindow(QWidget *parent = nullptr);
    ~userWindow();
    void closeEvent(QCloseEvent* );

signals:
    void sendrow(int a);
private slots:
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButton_clicked();


private:
    Ui::userWindow *ui;
};

#endif // USERWINDOW_H
