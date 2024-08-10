#include "graph.h"
#include "ui_graph.h"

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <fstream>

#include "src/utils/json.hpp"
#include "src/utils/math/mathlib.h"

Graph::Graph(QWidget *parent, QString document)
    : QDialog(parent)
    , ui(new Ui::Graph)
{
    qDebug() << "Graph constructor";
    qDebug() << document;

    fileName = document;

    ui->setupUi(this);

    // Set the json document
    setJson(document);



    // Create series
    plotGraph();

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

QLineSeries* Graph::createSeries(nlohmann::json function) {
    QLineSeries *series = new QLineSeries();
    for (int i = 0; i <= 100; i++) {
        int y = MathLib::evaluateFunction(function, i);
        series->append(i, y);
    }
    // series->append(2, Math::evaluateFunction(function.toStdString(), 10));
    return series;
}

void Graph::plotGraph()
{
    // Delete the current graph and chart view
    if (ui->verticalLayout->count() > 0) {
        ui->verticalLayout->removeWidget(ui->verticalLayout->itemAt(0)->widget());
    }

    // Load the json file
    setJson(fileName);

    // Plot the graph
    // Create a chart view
    QChartView *chartView = createChartView();

    QLineSeries *series = createSeries(json["graph"]["equations"][0]);

    QChart* chart = createChart(series);
    if (json["graph"]["equations"].size() > 1) {
        for (int i = 1; i < json["graph"]["equations"].size(); i++) {
            QLineSeries *newSeries = createSeries(json["graph"]["equations"][i]);
            chart->addSeries(newSeries);
            chart->createDefaultAxes();
        }
    }


    chartView->setChart(chart);

    ui->verticalLayout->addWidget(chartView);
}

void Graph::setJson(QString text)
{
    // Parse the json and plot the graph
    std::ifstream f("data/data.json");
    this->json = nlohmann::json::parse(f);

    // Set functions
    this->functions = this->json["graph"]["equations"];
}

void Graph::addFunction(QString input)
{
    std::vector<std::string> function;
    // Place spaces into input string to separate numbers and operators but maintain the numbers
    // such as numbers with more than one digit or numbers with decimal points and negative numbers
    // are treated as a single number and not separated into individual digits
    for (int i = 0; i < input.size(); i++) {
        if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' || input[i] == '^' || input[i] == '(' || input[i] == ')') {
            input.insert(i, " ");
            input.insert(i+2, " ");
            i += 2;
        }
    }

    // Split the string into tokens using spaces as delimiters
    // This will allow us to parse the string into numbers and operators
    std::string token;
    std::stringstream ss(input.toStdString());

    while (getline(ss, token, ' ')) {
        if (token[0] != ' ' && token[0] != '\0')
            function.push_back(token);
    }

    // Add function to json and save
    std::ifstream f("data/data.json");
    nlohmann::json json = nlohmann::json::parse(f);

    json["graph"]["equations"].push_back({
        {"equation", function},
        {"color", "#000000"},
        {"lineStyle", "solid"},
        {"lineWidth", 2}
    });

    std::ofstream o("data/data.json");
    o << json.dump(4);
    o.close();
}



void Graph::on_pushButton_clicked()
{
    addFunction(ui->lineEdit->text());
    plotGraph();
}

