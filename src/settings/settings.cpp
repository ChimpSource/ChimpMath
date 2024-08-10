#include "settings.h"
#include "qboxlayout.h"
#include "qcheckbox.h"
#include "qpushbutton.h"
#include "ui_settings.h"
#include "src/utils/json.hpp"

#include <fstream>
#include <QFile>

Settings::Settings(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Settings)
{
    ui->setupUi(this);

    // Load the user settings file
    loadSettings();

    // Set the title of the window
    setWindowTitle("Settings");

    // add vertical layout to the scroll area
    QVBoxLayout *layout = new QVBoxLayout();
    ui->scrollArea->widget()->setLayout(layout);

    ui->scrollArea->setWidgetResizable(true);

    QVBoxLayout *vLayout = new QVBoxLayout();
    ui->settingsLayout->widget()->setLayout(vLayout);



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

    // Hotkey settings
    QPushButton *hotkeySettings = new QPushButton("Hotkey Settings", this);
    ui->scrollArea->widget()->layout()->addWidget(hotkeySettings);
    hotkeySettings->setStyleSheet("background-color: #f0f0f0; border: 1px solid #c0c0c0;");
    hotkeySettings->show();

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
    connect(hotkeySettings, &QPushButton::clicked, this, &Settings::hotkeySettings);
    connect(otherSettings, &QPushButton::clicked, this, &Settings::otherSettings);



}

Settings::~Settings()
{
    delete ui;
}

void Settings::saveSettings()
{
    // Save the settings to the user settings file
    std::ofstream o(userSettingsFile.toStdString());
    o << userSettings.dump(4);
    o.close();
}

void Settings::loadSettings()
{
    if (!QFile::exists(userSettingsFile)) {
        // Create the user settings file if it doesn't exist
        std::ofstream o(userSettingsFile.toStdString());
        o << "{}";
        o.close();
    }
    // Load the settings from the user settings file
    std::ifstream f(userSettingsFile.toStdString());
    userSettings = nlohmann::json::parse(f);
}

void Settings::graphSettings()
{
    // Clear the settings layout
    QLayoutItem *child;
    while ((child = ui->settingsLayout->widget()->layout()->takeAt(0)) != 0) {
        delete child->widget();
        delete child;
    }

    // Load the user settings file
    loadSettings();

    // Add the graph settings options to settingsLayout
    QCheckBox *showGrid = new QCheckBox("Show Grid", this);
    showGrid->setChecked(userSettings["graph"]["showGrid"]);
    ui->settingsLayout->widget()->layout()->addWidget(showGrid);

    // Save the settings when the checkbox is toggled
    connect(showGrid, &QCheckBox::toggled, [=](bool checked) {
        userSettings["graph"]["showGrid"] = checked;
        saveSettings();
    });
}

void Settings::numberSettings()
{
    // Open the number settings dialog
    // NumberSettings numberSettings;
    // numberSettings.setModal(true);
    // numberSettings.exec();
}

void Settings::hotkeySettings()
{
    // Clear the settings layout
    QLayoutItem *child;
    while ((child = ui->settingsLayout->widget()->layout()->takeAt(0)) != 0) {
        delete child->widget();
        delete child;
    }

    // Load the user settings file
    loadSettings();

    // Add the hotkey settings options to settingsLayout
    QCheckBox *enableHotkeys = new QCheckBox("Enable Hotkeys", this);
    enableHotkeys->setChecked(userSettings["hotkeys"]["enableHotkeys"]);
    ui->settingsLayout->widget()->layout()->addWidget(enableHotkeys);

    // Save the settings when the checkbox is toggled
    connect(enableHotkeys, &QCheckBox::toggled, [=](bool checked) {
        userSettings["hotkeys"]["enableHotkeys"] = checked;
        saveSettings();
    });

    // Add hotkey options to settingsLayout
    // and scrollable area
    // "hotkeys": {
    //     "enableHotkeys": false,
    //                       "hotkeys": {
    //         "toggleDarkMode": "d",
    //                            "toggleFullscreen": "f",
    //                                                 "toggleGraph": "t",
    //                                                                 "toggleGraphSettings": "g",
    //                                                                                         "toggleGrid": "g",
    //                                                                                                        "toggleHelp": "h",
    //                                                                                                                       "toggleHotkeys": "k",
    //                                                                                                                                         "toggleInfo": "i",
    //                                                                                                                                                        "toggleMenu": "m",
    //                                                                                                                                                                       "toggleSettings": "s"
    //     }
    // }
    for (auto &hotkey : userSettings["hotkeys"]["hotkeys"].items()) {
        QLabel *hotkeyLabel = new QLabel(QString::fromStdString(hotkey.key()), this);
        QLineEdit *hotkeyEdit = new QLineEdit(QString::fromStdString(hotkey.key()));
        hotkeyEdit->setText(QString::fromStdString(hotkey.value()));

        ui->settingsLayout->widget()->layout()->addWidget(hotkeyLabel);
        ui->settingsLayout->widget()->layout()->addWidget(hotkeyEdit);

        // Save the settings when the text is changed
        connect(hotkeyEdit, &QLineEdit::textChanged, [=](const QString &text) {
            userSettings["hotkeys"]["hotkeys"][hotkey.key()] = text.toStdString();
            saveSettings();
        });
    }
}

void Settings::otherSettings()
{
    // Open the other settings dialog
    // OtherSettings otherSettings;
    // otherSettings.setModal(true);
    // otherSettings.exec();
}

void Settings::on_saveButton_clicked()
{
    // Save the settings
    saveSettings();
    close();
}

