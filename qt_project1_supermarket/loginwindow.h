#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr);
    virtual ~LoginWindow();

private slots:
    void on_rootButton_clicked();

    void on_userButton_clicked();



    void on_passwordButton_clicked();
signals:
    void sendname(const QString& name);
private:
    Ui::LoginWindow *ui;
    bool PasswordButton;
    bool login;
};
#endif // LOGINWINDOW_H
