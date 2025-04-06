#pragma once

#include <QFile>
#include <QFont>
#include <QList>
#include <QTime>
#include <QLabel>
#include <QWidget>
#include <QPalette>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QTextStream>
#include <QMessageBox>

struct PlayerScore {
    QString name;
    QTime time;
    bool operator<(const PlayerScore& other) const {
        return time < other.time;
    }
};

class EndGameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EndGameWidget(QTime finalTime, bool victory, QWidget* parent = nullptr);
    ~EndGameWidget();

signals:
    void returnToMainMenu();

private slots:
    void onSaveClicked();
    void onMenuClicked();

private:
    QTime playerTime;
    bool isVictory;
    QList<PlayerScore> leaderboard;
    QString leaderboardFile = "leaderboard.txt";

    QLabel* titleLabel;
    QLabel* timeLabel;
    QLabel* nameLabel;
    QLineEdit* nameEdit;
    QPushButton* saveButton;
    QLabel* leaderboardTitle;
    QListWidget* leaderboardList;
    QPushButton* menuButton;

    void loadLeaderboard();
    void saveLeaderboard();
    void updateLeaderboardDisplay();
    void setupUI();
};