#ifndef BROWSE_H
#define BROWSE_H

#include <QDialog>
#include <QListWidgetItem>

namespace Ui {
class browse;
}

class Browse : public QDialog
{
    Q_OBJECT

public:
    explicit Browse(QWidget *parent = nullptr);
    ~Browse();

private slots:
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::browse *ui;
};

#endif // BROWSE_H
