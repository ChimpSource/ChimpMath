#include "browse.h"
#include "src/graph/graph.h"
#include "ui_browse.h"

#include <QDir>
#include <QFile>

Browse::Browse(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::browse)
{
    ui->setupUi(this);

    // load all json files in the current directory
    QDir dir("data/");
    QStringList filters;
    filters << "*.json";
    dir.setNameFilters(filters);
    QStringList fileList = dir.entryList();
    ui->listWidget->addItems(fileList);
}

Browse::~Browse()
{
    delete ui;
}

void Browse::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QString filename = item->text();
    // Open the file
    QFile file("data/" + filename);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);
        QString json = stream.readAll();
        file.close();
        qDebug() << json;

        // Open the graph window with the json file as input
        Graph *graph = new Graph(this, "data/" + filename);
        graph->setJson(json);
        graph->show();

        // Close the browse window
        this->close();
    } else {
        qDebug() << "Failed to open file";
    }
}

