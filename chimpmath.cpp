#include "chimpmath.h"
#include "ui_chimpmath.h"

ChimpMath::ChimpMath(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ChimpMath)
{
    ui->setupUi(this);
}

ChimpMath::~ChimpMath()
{
    delete ui;
}
