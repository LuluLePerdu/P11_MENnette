#pragma once
#include <QWidget>
#include <QComboBox>
#include <QSpinBox>
#include <QFormLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QLabel>

class ConfigurationWidget : public QWidget
{
    Q_OBJECT
public:
    enum Difficulty { EASY, NORMAL, HARD, CUSTOM };

    explicit ConfigurationWidget(QWidget* parent = nullptr);

    int getMazeWidth() const;
    int getMazeHeight() const;
    int getMazeTime() const;
    Difficulty getDifficulty() const;

signals:
    void settingsApplied();

private slots:
    void onDifficultyChanged(int index);

private:
    void setupUi();
    void applyBombStyle();
    void updateDifficultySettings();
    void updateUiForDifficulty();

    QComboBox* difficultyCombo;
    QSpinBox* mazeWidthSpin;
    QSpinBox* mazeHeightSpin;
    QSpinBox* mazeTimeSpin;
    QLabel* widthLabel;
    QLabel* heightLabel;
    QLabel* timeLabel;

    struct DifficultyPreset {
        int width;
        int height;
        int time;
    };

    QMap<Difficulty, DifficultyPreset> difficultyPresets;
};