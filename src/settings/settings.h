#ifndef SETTINGS_H
#define SETTINGS_H

#include "src/utils/json.hpp"
#include <QDialog>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

private:
    Ui::Settings *ui;

    QString userSettingsFile = "data/settings.json";
    nlohmann::json userSettings;

    void saveSettings();
    void loadSettings();

private slots:
    void graphSettings();
    void numberSettings();
    void hotkeySettings();
    void otherSettings();
    void on_saveButton_clicked();
};

#endif // SETTINGS_H
