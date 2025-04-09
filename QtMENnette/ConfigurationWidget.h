#pragma once
#include <QWidget>
#include <QMap>
#include <QGroupBox>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QFormLayout>

class ConfigurationWidget : public QWidget
{
    Q_OBJECT
public:
    enum Difficulty { EASY, NORMAL, HARD, CUSTOM };

    explicit ConfigurationWidget(QWidget* parent = nullptr);

    Difficulty getDifficulty() const;
    int getMazeWidth() const;
    int getMazeHeight() const;
    int getMazeTime() const;

    int getCryptoRange() const;

signals:
    void settingsApplied();

private slots:
    void onDifficultyChanged(int index);

private:
    void setupUi();
    void applyBombStyle();
    void updateDifficultySettings();

    QGroupBox* createGameSection(const QString& title, QWidget* content);

    QComboBox* difficultyCombo;
    QSpinBox* mazeWidthSpin;
    QSpinBox* mazeHeightSpin;
    QSpinBox* mazeTimeSpin;

    QComboBox* simonSpeedCombo;
    QSpinBox* simonLengthSpin;

	QSpinBox* cryptoRangeSpin;



    struct DifficultyPreset {
        int width;
        int height;
        int time;
    };

    QMap<Difficulty, DifficultyPreset> difficultyPresets;
};