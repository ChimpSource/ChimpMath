#include "chimpmath.h"
#include "ui_chimpmath.h"
#include "src/calculator/calculator.h"
#include "src/new/newwindow.h"
#include "src/browse/browse.h"


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


void ChimpMath::on_newButton_clicked()
{
    newWindow *newWin = new newWindow(this);
    newWin->show();
}


void ChimpMath::on_browseButton_clicked()
{
    Browse *browse = new Browse(this);
    browse->show();
}

