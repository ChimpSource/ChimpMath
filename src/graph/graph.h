#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>
#include <QChart>
#include <QLineSeries>
#include <QChartView>

#include "src/utils/json.hpp"

namespace Ui {
class Graph;
}

class Graph : public QDialog
{
    Q_OBJECT

public:
    explicit Graph(QWidget *parent = nullptr, QString document = "");
    ~Graph();

    double xMin;
    double xMax;
    double yMin;
    double yMax;
    nlohmann::json functions;
    nlohmann::json json;

    QChartView* createChartView();
    QChart* createChart(QLineSeries* series);
    QLineSeries* createSeries(nlohmann::json function);
    QLineSeries* createSeriesFromJson(QString functions);
    void plotGraph();

    void setJson(QString json);
    void addFunction(QString function);
    void removeFunction(QString function);
    void clearFunctions();


    void setXRange(double min, double max);
    void setYRange(double min, double max);
    void setXLabel(QString label);
    void setYLabel(QString label);
    void setTitle(QString title);
    void setTheme(int theme);
    void setAnimationOptions(int options);
    void setAnimationDuration(int duration);
    void setAnimationEasingCurve(int curve);

    void openFunctionDialog();
private slots:
    void on_pushButton_clicked();

private:
    Ui::Graph *ui;
};

#endif // GRAPH_H
