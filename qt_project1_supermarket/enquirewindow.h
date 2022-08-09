#ifndef ENQUIREWINDOW_H
#define ENQUIREWINDOW_H

#include <QMainWindow>

namespace Ui {
class enquireWindow;
}

class enquireWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit enquireWindow(QWidget *parent = nullptr);
    ~enquireWindow();
    void closeEvent(QCloseEvent* );
private:
    Ui::enquireWindow *ui;
};

#endif // ENQUIREWINDOW_H
