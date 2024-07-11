#include "graph.h"
#include "ui_graph.h"

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <fstream>

#include "src/utils/json.hpp"
#include "src/utils/math/math.h"

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

    QChartView *chartView = createChartView();

    // Create series
    QLineSeries *series = createSeries("x^2");

    QChart* chart = createChart(series);


    chartView->setChart(chart);

    ui->verticalLayout->addWidget(chartView);
}

Graph::~Graph()
{
    delete ui;
}

QChartView* Graph::createChartView() {
    QChartView *chartView = new QChartView();
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setRubberBand(QChartView::RectangleRubberBand);
    chartView->setRubberBand(QChartView::VerticalRubberBand);
    chartView->setRubberBand(QChartView::HorizontalRubberBand);
    chartView->setRubberBand(QChartView::ClickThroughRubberBand);
    return chartView;
}

QChart* Graph::createChart(QLineSeries* series) {
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("y = x");
    chart->setTitleFont(QFont("Arial", 16));
    chart->setTitleBrush(QBrush(Qt::black));
    chart->setTheme(QChart::ChartThemeDark);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setAnimationDuration(1000);
    return chart;
}

QLineSeries* Graph::createSeries(QString function) {
    QLineSeries *series = new QLineSeries();
    for (int i = -10; i <= 10; i++) {
        int y = Math::evaluateFunction(function.toStdString(), i);
        series->append(i, i * i);
    }
    return series;
}

void Graph::plotGraph()
{
    // Plot the graph
}

void Graph::setJson(QString text)
{
    // Parse the json and plot the graph
    std::ifstream f("data/data.json");
    this->json = nlohmann::json::parse(f);

    // Set functions
    for (auto &function : this->json["graph"]["equations"]) {
        qDebug() << QString::fromStdString(function["equation"]);
        addFunction(QString::fromStdString(function["equation"]));
    }
}

void Graph::addFunction(QString function)
{
    functions.append(function);
}


