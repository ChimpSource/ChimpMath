#include "newwindow.h"
#include "ui_newwindow.h"

#include <fstream>

newWindow::newWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::newWindow)
{
    ui->setupUi(this);
}

newWindow::~newWindow()
{
    delete ui;
}

void newWindow::on_pushButton_clicked()
{
    std::string filename = ui->lineEdit->text().toStdString();

    // Create a new file with the filename
    std::ofstream file(filename + ".json");

    file << "\"graph\": { \n"
            "   \"equations: [\n"
            "       {\n"
            "           \"equation\": \"x^2\",\n"
            "           \"color\": \"red\",\n"
            "           \"lineStyle\": \"solid\",\n"
            "           \"lineWidth\": 2\n"
            "       },\n"
            "       {\n"
            "           \"equation\": \"x^3\",\n"
            "           \"color\": \"blue\",\n"
            "           \"lineStyle\": \"dashed\",\n"
            "           \"lineWidth\": 2\n"
            "       }\n"
            "   ],\n"
            "   \"xAxis\": {\n"
            "       \"min\": -10,\n"
            "       \"max\": 10,\n"
            "       \"step\": 1\n"
            "   },\n"
            "   \"yAxis\": {\n"
            "       \"min\": -10,\n"
            "       \"max\": 10,\n"
            "       \"step\": 1\n"
            "   }\n"
            "}\n" << std::endl;

    // Close the file
    file.close();
}

