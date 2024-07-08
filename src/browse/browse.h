#ifndef BROWSE_H
#define BROWSE_H

#include <QDialog>

namespace Ui {
class browse;
}

class Browse : public QDialog
{
    Q_OBJECT

public:
    explicit Browse(QWidget *parent = nullptr);
    ~Browse();

private:
    Ui::browse *ui;
};

#endif // BROWSE_H
