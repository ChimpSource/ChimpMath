#include "newwindow.h"
#include "ui_newwindow.h"

#include <QFile>
#include <QDebug>
#include <QDir>

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

    QDir dir("data");
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    // Create a new file with the filename in directory "data" with .json
    QFile file(QString::fromStdString("data/" + filename + ".json"));

    // Open the file
    if (file.open(QIODevice::ReadWrite)) {
        // Write the json to the file
        QTextStream stream(&file);
        /*
         * {
                "graph": {
                    "equations": [
                        {
                            "equation": "x^2",
                            "color": "red",
                            "lineStyle": "solid",
                            "lineWidth": 2
                        },
                        {
                            "equation": "x^3",
                            "color": "blue",
                            "lineStyle": "dashed",
                            "lineWidth": 2
                        },
                        {
                            "equation": "x",
                            "color": "green",
                            "lineStyle": "dotted",
                            "lineWidth": 2
                    ],
                    "xAxis": {
                        "min": -10,
                        "max": 10,
                        "step": 1
                    },
                    "yAxis": {
                        "min": -10,
                        "max": 10,
                        "step": 1
                    }
                }
            }

         *
         * */

        stream << "{\n\"graph\": { \n"
                   "   \"equations\": [\n"
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
                   "       },\n"
                   "       {\n"
                   "           \"equation\": \"x\",\n"
                   "           \"color\": \"green\",\n"
                   "           \"lineStyle\": \"dotted\",\n"
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
                   "}\n"
                   "}\n";
        file.close();
    } else {
        qDebug() << "Failed to open file";
    }

    // Close the window
    this->close();
}

