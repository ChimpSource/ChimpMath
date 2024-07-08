#ifndef NEWWINDOW_H
#define NEWWINDOW_H

#include <QDialog>

namespace Ui {
class newWindow;
}

class newWindow : public QDialog
{
    Q_OBJECT

public:
    explicit newWindow(QWidget *parent = nullptr);
    ~newWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::newWindow *ui;
};

#endif // NEWWINDOW_H
