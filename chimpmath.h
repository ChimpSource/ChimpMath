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

    void on_newButton_clicked();

    void on_browseButton_clicked();

    void on_settingsButton_clicked();

private:
    Ui::ChimpMath *ui;
};
#endif // CHIMPMATH_H
