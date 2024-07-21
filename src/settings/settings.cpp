#include "settings.h"
#include "qcheckbox.h"
#include "qpushbutton.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Settings)
{
    ui->setupUi(this);

    // Set the title of the window
    setWindowTitle("Settings");

    // add vertical layout to the scroll area
    QVBoxLayout *layout = new QVBoxLayout();
    ui->scrollArea->widget()->setLayout(layout);

    // Inside the scroll area, add sections for graph settings, number settings, and other settings
    // Graph settings
    QPushButton *graphSettings = new QPushButton("Graph Settings", this);
    ui->scrollArea->widget()->layout()->addWidget(graphSettings);
    graphSettings->setStyleSheet("background-color: #f0f0f0; border: 1px solid #c0c0c0;");
    graphSettings->show();

    // Number settings
    QPushButton *numberSettings = new QPushButton("Number Settings", this);
    ui->scrollArea->widget()->layout()->addWidget(numberSettings);
    numberSettings->setStyleSheet("background-color: #f0f0f0; border: 1px solid #c0c0c0;");
    numberSettings->show();

    // Other settings
    QPushButton *otherSettings = new QPushButton("Other Settings", this);
    ui->scrollArea->widget()->layout()->addWidget(otherSettings);
    otherSettings->setStyleSheet("background-color: #f0f0f0; border: 1px solid #c0c0c0;");
    otherSettings->show();

    // Set the size of the scroll area
    // ui->scrollArea->setMinimumSize(200, 200);
    // ui->scrollArea->setMaximumSize(200, 200);
    // ui->scrollArea->setWidgetResizable(true);
    // ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    // ui->scrollArea->setStyleSheet("border: 1px solid #c0c0c0;");

    // Attach buttons to slots
    connect(graphSettings, &QPushButton::clicked, this, &Settings::graphSettings);
    connect(numberSettings, &QPushButton::clicked, this, &Settings::numberSettings);
    connect(otherSettings, &QPushButton::clicked, this, &Settings::otherSettings);



}

Settings::~Settings()
{
    delete ui;
}

void Settings::graphSettings()
{
    // Add the graph settings options to settingsLayout
    QCheckBox *showGrid = new QCheckBox("Show Grid", this);
    ui->settingsLayout->addWidget(showGrid);
}

void Settings::numberSettings()
{
    // Open the number settings dialog
    // NumberSettings numberSettings;
    // numberSettings.setModal(true);
    // numberSettings.exec();
}

void Settings::otherSettings()
{
    // Open the other settings dialog
    // OtherSettings otherSettings;
    // otherSettings.setModal(true);
    // otherSettings.exec();
}

