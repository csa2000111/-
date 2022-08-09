#ifndef RECORDWINDOW_H
#define RECORDWINDOW_H

#include <QMainWindow>

namespace Ui {
class recordWindow;
}

class recordWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit recordWindow(QWidget *parent = nullptr);
    ~recordWindow();
    void closeEvent(QCloseEvent* );
private:
    Ui::recordWindow *ui;
    int expenses;//支出
    int income;  //收入
};

#endif // RECORDWINDOW_H
