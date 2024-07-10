#include "graph.h"
#include "ui_graph.h"

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <fstream>

#include "src/utils/json.hpp"

Graph::Graph(QWidget *parent, QString document)
    : QDialog(parent)
    , ui(new Ui::Graph)
{
    qDebug() << "Graph constructor";
    qDebug() << document;

    ui->setupUi(this);

    // Set the json document
    setJson(document);

    // Create a chart view

    QChartView *chartView = new QChartView(this);
    ui->verticalLayout->addWidget(chartView);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setRubberBand(QChartView::RectangleRubberBand);
    chartView->setRubberBand(QChartView::VerticalRubberBand);
    chartView->setRubberBand(QChartView::HorizontalRubberBand);
    chartView->setRubberBand(QChartView::ClickThroughRubberBand);

    // Plot basic graph of y = x
    QLineSeries *series = new QLineSeries();
    for (int i = 0; i < 100; i++) {
        series->append(i, i);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("y = x");
    chart->setTitleFont(QFont("Arial", 16));
    chart->setTitleBrush(QBrush(Qt::black));
    chart->setTheme(QChart::ChartThemeDark);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setAnimationDuration(1000);
    chartView->setChart(chart);

}

Graph::~Graph()
{
    delete ui;
}

void Graph::plotGraph()
{
    // Plot the graph
}

void Graph::setJson(QString text)
{
    // Parse the json and plot the graph
    std::ifstream f("data/data.json");
    nlohmann::json data = nlohmann::json::parse(f);

    // Set functions
    for (auto &function : data["graph"]["equations"]) {
        qDebug() << QString::fromStdString(function["equation"]);
        addFunction(QString::fromStdString(function["equation"]));
    }
}

void Graph::addFunction(QString function)
{
    functions.append(function);
}


