#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>
#include <QMap>
#include <QComboBox>
#include <QSpinBox>
#include <QOverload>
#include "ConfigurationWidget.h"

ConfigurationWidget::ConfigurationWidget(QWidget* parent) : QWidget(parent)
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
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(15, 15, 15, 15);

    // ===== SNAKE MAZE =====
    QWidget* snakeContent = new QWidget();
    QFormLayout* snakeLayout = new QFormLayout(snakeContent);
    snakeLayout->setContentsMargins(10, 10, 10, 10);

    difficultyCombo = new QComboBox();
    difficultyCombo->addItem("Facile", EASY);
    difficultyCombo->addItem("Normal", NORMAL);
    difficultyCombo->addItem("Difficile", HARD);
    difficultyCombo->addItem("Custom", CUSTOM);

    mazeWidthSpin = new QSpinBox();
    mazeWidthSpin->setRange(5, 50);

    mazeHeightSpin = new QSpinBox();
    mazeHeightSpin->setRange(5, 50);

    mazeTimeSpin = new QSpinBox();
    mazeTimeSpin->setRange(10, 300);
    mazeTimeSpin->setSuffix(" sec");

    snakeLayout->addRow("Difficulte:", difficultyCombo);
    snakeLayout->addRow("Largeur:", mazeWidthSpin);
    snakeLayout->addRow("Hauteur:", mazeHeightSpin);
    snakeLayout->addRow("Temps:", mazeTimeSpin);

    mainLayout->addWidget(createGameSection("SNAKE MAZE", snakeContent));

    // ===== SIMON SAYS =====
    QWidget* simonContent = new QWidget();
    QFormLayout* simonLayout = new QFormLayout(simonContent);
    simonLayout->setContentsMargins(10, 10, 10, 10);

    simonLengthSpin = new QSpinBox();
    simonLengthSpin->setRange(1, 15);
    simonLengthSpin->setValue(8);

    simonLayout->addRow("Longueur:", simonLengthSpin);

    mainLayout->addWidget(createGameSection("SIMON SAYS", simonContent));

    QWidget* threadContent = new QWidget();
    QFormLayout* threadLayout = new QFormLayout(threadContent);
    threadLayout->setContentsMargins(10, 10, 10, 10);

    //COMBOBOX
	//SPINBOX

    //add row

    mainLayout->addWidget(createGameSection("THREAD CUTTER", threadContent));


	// ===== CRYPTO SEQUENCER =====
	QWidget* cryptoContent = new QWidget();
	QFormLayout* cryptoLayout = new QFormLayout(cryptoContent);
	cryptoLayout->setContentsMargins(10, 10, 10, 10);

	cryptoRangeSpin = new QSpinBox();
	cryptoRangeSpin->setRange(10, 255);
	cryptoRangeSpin->setValue(50);
	cryptoLayout->addRow("Range:", cryptoRangeSpin);

    mainLayout->addWidget(createGameSection("CRYPTO SEQUENCER", cryptoContent));

    QPushButton* applyButton = new QPushButton("CONFIRMER");
    applyButton->setFixedHeight(45);
    mainLayout->addWidget(applyButton);

    connect(applyButton, &QPushButton::clicked, this, &ConfigurationWidget::settingsApplied);
    connect(difficultyCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
        this, &ConfigurationWidget::onDifficultyChanged);

    difficultyCombo->setCurrentIndex(NORMAL);
    updateDifficultySettings();
}

QGroupBox* ConfigurationWidget::createGameSection(const QString& title, QWidget* content)
{
    QGroupBox* group = new QGroupBox(title);
    QVBoxLayout* layout = new QVBoxLayout(group);
    layout->addWidget(content);
    group->setLayout(layout);
    return group;
}

void ConfigurationWidget::applyBombStyle()
{
    setStyleSheet(R"(
        ConfigurationWidget {
            background: #111;
            border: 2px solid #ff3333;
            border-radius: 8px;
        }

       QGroupBox {
            background: #222222;
            color: #ff5555;
            border: 1px solid #ff5555;
            border-radius: 6px;
            margin-top: 10px;
            padding-top: 15px;
        }

        QGroupBox::title {
            subcontrol-origin: margin;
            left: 10px;
            padding: 0 5px;
        }

        QLabel {
            color: #cccccc;
            background: transparent;
        }

        QComboBox {
            background: #333333;
            color: #ffffff;
            border: 1px solid #555555;
            padding: 5px;
            border-radius: 4px;
            min-width: 100px;
            selection-background-color: #ff5555;
        }

        QComboBox:hover {
            border: 1px solid #ff5555;
            background: #3a3a3a;
        }

        QComboBox::drop-down {
            border: none;
            width: 20px;
        }

        QComboBox QAbstractItemView {
            background: #333333;
            color: #ffffff;
            border: 1px solid #ff5555;
            selection-background-color: #ff5555;
            outline: none;
        }

        QComboBox QAbstractItemView::item {
            padding: 5px;
        }

        QComboBox QAbstractItemView::item:hover {
            background: #ff5555;
            color: black;
            font-weight: bold;
        }

        QComboBox QAbstractItemView::item:selected {
            background: #ff3333;
            color: black;
        }

        QSpinBox {
            background-color: #333333;
            color: #ffffff;
            border: 1px solid #555555;
            padding: 5px;
            border-radius: 3px;
        }

        QSpinBox:hover {
            border-color: #ff5555;
        }

        QPushButton {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                      stop:0 #ff5555, stop:1 #cc0000);
            color: black;
            font-weight: bold;
            border: 1px solid #880000;
            border-radius: 5px;
            padding: 8px;
            min-width: 120px;
        }

        QPushButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                      stop:0 #ff7777, stop:1 #dd2222);
        }

        QPushButton:pressed {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                      stop:0 #dd3333, stop:1 #aa0000);
        }
    )");
}

void ConfigurationWidget::onDifficultyChanged(int index)
{
    Q_UNUSED(index);
    updateDifficultySettings();
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

ConfigurationWidget::Difficulty ConfigurationWidget::getDifficulty() const {
    return static_cast<Difficulty>(difficultyCombo->currentData().toInt());
}

int ConfigurationWidget::getMazeWidth() const { return mazeWidthSpin->value(); }
int ConfigurationWidget::getMazeHeight() const { return mazeHeightSpin->value(); }
int ConfigurationWidget::getMazeTime() const { return mazeTimeSpin->value(); }

int ConfigurationWidget::getCryptoRange() const { return cryptoRangeSpin->value(); }
int ConfigurationWidget::getSimonLength() const { return simonLengthSpin->value(); }