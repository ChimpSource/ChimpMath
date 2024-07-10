#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>

#include "src/utils/jsonparser.h"

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
    QStringList functions;
    JsonParser::JsonValue json;


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
private:
    Ui::Graph *ui;
};

#endif // GRAPH_H
