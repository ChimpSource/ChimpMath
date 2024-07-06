#include "chimpmath.h"
#include "ui_chimpmath.h"
#include "src/calculator/calculator.h"

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

void ChimpMath::on_calculateButton_clicked()
{
    Calculator *calc = new Calculator(this);
    calc->show();
}
