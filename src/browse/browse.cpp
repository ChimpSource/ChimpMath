#include "browse.h"
#include "ui_browse.h"

Browse::Browse(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::browse)
{
    ui->setupUi(this);
}

Browse::~Browse()
{
    delete ui;
}
