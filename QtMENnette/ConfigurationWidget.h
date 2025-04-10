#pragma once

#include <QMap>
#include <QLabel>
#include <QWidget>
#include <QSpinBox>
#include <QGroupBox>
#include <QComboBox>
#include <QOverload>
#include <QPushButton>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>

class ConfigurationWidget : public QWidget
{
    Q_OBJECT
public:
    enum Difficulty { EASY, NORMAL, HARD, CUSTOM };

    explicit ConfigurationWidget(QWidget* parent = nullptr);

    int getMazeTime() const;
    int getMazeWidth() const;
    int getMazeHeight() const;
    int getCryptoRange() const;
    int getSimonLength() const;
    int getThreadPenalty() const;
    Difficulty getDifficulty() const;

signals:
    void settingsApplied();

private slots:
    void onDiffChangedThread(int index);
    void onDifficultyChanged(int index);

private:

    struct DifficultyPreset {
        int width;
        int height;
        int time;
    };

    QGroupBox* createGameSection(const QString& title, QWidget* content);

    QSpinBox* mazeTimeSpin;
    QSpinBox* mazeWidthSpin;
    QSpinBox* mazeHeightSpin;
    QComboBox* difficultyCombo;

    QSpinBox* simonLengthSpin;
    QComboBox* simonSpeedCombo;

    QSpinBox* threadTimeSpin;
    QComboBox* difficultyThreadCombo;

	QSpinBox* cryptoRangeSpin;

    QMap<Difficulty, DifficultyPreset> difficultyPresets;

    void setupUi();
    void applyBombStyle();
    void updateDifficultySettings();

};