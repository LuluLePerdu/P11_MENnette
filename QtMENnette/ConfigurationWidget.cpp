#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>
#include <QMap>
#include <QComboBox>
#include <QSpinBox>
#include <QOverload>
#include "ConfigurationWidget.h"

ConfigurationWidget::ConfigurationWidget(QWidget* parent)
    : QWidget(parent)
{
    difficultyPresets[EASY] = { 15, 15, 60 };
    difficultyPresets[NORMAL] = { 21, 21, 50 };
    difficultyPresets[HARD] = { 31, 31, 45 };

    setupUi();
    applyBombStyle();
}

void ConfigurationWidget::setupUi()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    difficultyCombo = new QComboBox(this);
    difficultyCombo->addItem("Facile", EASY);
    difficultyCombo->addItem("Normal", NORMAL);
    difficultyCombo->addItem("Difficile", HARD);
    difficultyCombo->addItem("Personnalise", CUSTOM);
    connect(difficultyCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ConfigurationWidget::onDifficultyChanged);

    mazeWidthSpin = new QSpinBox;
    mazeWidthSpin->setRange(5, 50);

    mazeHeightSpin = new QSpinBox;
    mazeHeightSpin->setRange(5, 50);

    mazeTimeSpin = new QSpinBox;
    mazeTimeSpin->setRange(10, 300);
    mazeTimeSpin->setSuffix(" sec");

    widthLabel = new QLabel("Largeur:");
    heightLabel = new QLabel("Hauteur:");
    timeLabel = new QLabel("Temps limite:");

    QFormLayout* formLayout = new QFormLayout;
    formLayout->addRow(new QLabel("Difficulte:"), difficultyCombo);
    formLayout->addRow(widthLabel, mazeWidthSpin);
    formLayout->addRow(heightLabel, mazeHeightSpin);
    formLayout->addRow(timeLabel, mazeTimeSpin);

    QPushButton* applyButton = new QPushButton("APPLIQUER");
    connect(applyButton, &QPushButton::clicked, this, &ConfigurationWidget::settingsApplied);

    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(applyButton);
    mainLayout->addStretch();

    setLayout(mainLayout);

    difficultyCombo->setCurrentIndex(NORMAL);
    updateDifficultySettings();
    updateUiForDifficulty();
}

void ConfigurationWidget::onDifficultyChanged(int index)
{
    Q_UNUSED(index);
    updateDifficultySettings();
    updateUiForDifficulty();
}

void ConfigurationWidget::updateDifficultySettings()
{
    Difficulty diff = static_cast<Difficulty>(difficultyCombo->currentData().toInt());

    if (diff != CUSTOM) {
        DifficultyPreset preset = difficultyPresets[diff];
        mazeWidthSpin->setValue(preset.width);
        mazeHeightSpin->setValue(preset.height);
        mazeTimeSpin->setValue(preset.time);
    }
}

void ConfigurationWidget::updateUiForDifficulty()
{
    bool isCustom = (difficultyCombo->currentData().toInt() == CUSTOM);

    mazeWidthSpin->setEnabled(isCustom);
    mazeHeightSpin->setEnabled(isCustom);
    mazeTimeSpin->setEnabled(isCustom);

    widthLabel->setEnabled(isCustom);
    heightLabel->setEnabled(isCustom);
    timeLabel->setEnabled(isCustom);
}

void ConfigurationWidget::applyBombStyle()
{
    this->setStyleSheet(
        "ConfigurationWidget {"
        "   background-color: #2a2a2a;"
        "}"
        "QGroupBox {"
        "   color: #ff5555;"
        "   font-weight: bold;"
        "   border: 2px solid #ff5555;"
        "   border-radius: 5px;"
        "   margin-top: 1ex;"
        "}"
        "QGroupBox::title {"
        "   subcontrol-origin: margin;"
        "   left: 10px;"
        "   padding: 0 3px;"
        "}"
        "QSpinBox {"
        "   background-color: #333;"
        "   color: white;"
        "   border: 1px solid #ff5555;"
        "   padding: 2px;"
        "}"
        "QPushButton {"
        "   background-color: #ff5555;"
        "   color: black;"
        "   font-weight: bold;"
        "   border: 2px solid #ff0000;"
        "   padding: 5px;"
        "   min-width: 100px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #ff7777;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #ff3333;"
        "}"
        "QComboBox {"
        "   background-color: #333;"
        "   color: white;"
        "   border: 1px solid #ff5555;"
        "   padding: 3px;"
        "}"
        "QComboBox::drop-down {"
        "   border: none;"
        "}"
        "QComboBox QAbstractItemView {"
        "   background: #2a2a2a;"
        "   color: white;"
        "   selection-background-color: #ff5555;"
        "}"
    );
}

ConfigurationWidget::Difficulty ConfigurationWidget::getDifficulty() const {
    return static_cast<Difficulty>(difficultyCombo->currentData().toInt());
}

int ConfigurationWidget::getMazeWidth() const { return mazeWidthSpin->value(); }
int ConfigurationWidget::getMazeHeight() const { return mazeHeightSpin->value(); }
int ConfigurationWidget::getMazeTime() const { return mazeTimeSpin->value(); }