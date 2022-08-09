#ifndef CLINETENQUIREWINDOW_H
#define CLINETENQUIREWINDOW_H

#include <QMainWindow>

namespace Ui {
class clinetEnquireWindow;
}

class clinetEnquireWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit clinetEnquireWindow(QWidget *parent = nullptr);
    ~clinetEnquireWindow();
    void closeEvent(QCloseEvent* );
private:
    Ui::clinetEnquireWindow *ui;
};

#endif // CLINETENQUIREWINDOW_H
