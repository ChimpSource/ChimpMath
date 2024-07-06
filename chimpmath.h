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

private:
    Ui::ChimpMath *ui;
};
#endif // CHIMPMATH_H
