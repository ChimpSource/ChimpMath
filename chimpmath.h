#ifndef CHIMPMATH_H
#define CHIMPMATH_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class ChimpMath;
}
QT_END_NAMESPACE

class ChimpMath : public QMainWindow
{
    Q_OBJECT

public:
    ChimpMath(QWidget *parent = nullptr);
    ~ChimpMath();

private slots:
    void on_calculateButton_clicked();

    void on_lineEdit_returnPressed();

    void on_enterButton_clicked();

private:
    Ui::ChimpMath *ui;
};
#endif // CHIMPMATH_H
