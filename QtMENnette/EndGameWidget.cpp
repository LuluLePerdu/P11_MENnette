#include "EndGameWidget.h"

EndGameWidget::EndGameWidget(QTime finalTime, bool victory, QWidget* parent)
    : QWidget(parent), playerTime(finalTime), isVictory(victory)
{
    setupUI();
    loadLeaderboard();

    timeLabel->setText(playerTime.toString("mm:ss"));

    if (!isVictory) {
        titleLabel->setText("Bombe explosée!");
        titleLabel->setStyleSheet("QLabel { color: #FF0000; font-size: 24px; font-weight: bold; padding: 10px; }");
        nameEdit->setEnabled(false);
        saveButton->setEnabled(false);
        nameLabel->setText("Temps écoulé - Classement en lecture seule:");
        nameLabel->setStyleSheet("font-size: 16px; color: #FF0000;");
    }
    else {
        titleLabel->setText("Bombe désamorcée!");
        titleLabel->setStyleSheet("QLabel { color: #00FF00; font-size: 24px; font-weight: bold; padding: 10px; }");
    }
}

EndGameWidget::~EndGameWidget() {}

void EndGameWidget::setupUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(30, 30, 30, 30);

    this->setStyleSheet(
        "background-color: #121212;"
        "color: #E0E0E0;"
    );

    titleLabel = new QLabel(this);
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    timeLabel = new QLabel(this);
    timeLabel->setStyleSheet(
        "QLabel {"
        "   font-size: 48px;"
        "   font-weight: bold;"
        "   background-color: rgba(0, 0, 0, 150);"
        "   border-radius: 10px;"
        "   padding: 10px;"
        "}"
    );
    timeLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(timeLabel);

    QHBoxLayout* nameLayout = new QHBoxLayout();
    nameLabel = new QLabel(this);
    nameLabel->setStyleSheet("font-size: 16px;");

    nameEdit = new QLineEdit(this);
    nameEdit->setStyleSheet(
        "background-color: #222222;"
        "color: #E0E0E0;"
        "border-radius: 5px;"
        "padding: 5px;"
        "font-size: 16px;"
    );
    nameEdit->setMaximumWidth(300);

    saveButton = new QPushButton("Enregistrer", this);
    saveButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #333333;"
        "   color: #E0E0E0;"
        "   border-radius: 5px;"
        "   padding: 8px;"
        "   min-width: 100px;"
        "   font-size: 16px;"
        "}"
    );

    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(nameEdit);
    nameLayout->addWidget(saveButton);
    nameLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addLayout(nameLayout);

    leaderboardTitle = new QLabel("Classement:", this);
    leaderboardTitle->setStyleSheet(
        "QLabel {"
        "   font-size: 20px;"
        "   font-weight: bold;"
        "   padding: 5px;"
        "}"
    );
    mainLayout->addWidget(leaderboardTitle);

    leaderboardList = new QListWidget(this);
    leaderboardList->setStyleSheet(
        "QListWidget {"
        "   background-color: #222222;"
        "   color: #E0E0E0;"
        "   border-radius: 5px;"
        "   font-size: 14px;"
        "}"
        "QListWidget::item {"
        "   padding: 5px;"
        "}"
    );
    leaderboardList->setMaximumHeight(300);
    mainLayout->addWidget(leaderboardList);

    menuButton = new QPushButton("Retour au menu", this);
    menuButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #333333;"
        "   color: #E0E0E0;"
        "   border-radius: 5px;"
        "   padding: 10px;"
        "   min-width: 150px;"
        "   font-size: 16px;"
        "}"
    );
    mainLayout->addWidget(menuButton, 0, Qt::AlignCenter);

    if (isVictory) {
        timeLabel->setStyleSheet(timeLabel->styleSheet() + "color: #00FF00; border: 2px solid #00FF00;");
        nameEdit->setStyleSheet(nameEdit->styleSheet() + "border: 1px solid #00FF00;");
        saveButton->setStyleSheet(saveButton->styleSheet() +
            "border: 1px solid #00FF00;"
            "QPushButton:hover { background-color: #00FF00; color: #000000; }");
        leaderboardTitle->setStyleSheet(leaderboardTitle->styleSheet() + "color: #00FF00;");
        leaderboardList->setStyleSheet(leaderboardList->styleSheet() + "border: 1px solid #00FF00;");
        menuButton->setStyleSheet(menuButton->styleSheet() +
            "border: 1px solid #00FF00;"
            "QPushButton:hover { background-color: #00FF00; color: #000000; }");
    }
    else {
        timeLabel->setStyleSheet(timeLabel->styleSheet() + "color: #FF0000; border: 2px solid #FF0000;");
        nameEdit->setStyleSheet(nameEdit->styleSheet() + "border: 1px solid #FF0000;");
        saveButton->setStyleSheet(saveButton->styleSheet() +
            "border: 1px solid #FF0000;"
            "QPushButton:hover { background-color: #FF0000; color: #000000; }");
        leaderboardTitle->setStyleSheet(leaderboardTitle->styleSheet() + "color: #FF0000;");
        leaderboardList->setStyleSheet(leaderboardList->styleSheet() + "border: 1px solid #FF0000;");
        menuButton->setStyleSheet(menuButton->styleSheet() +
            "border: 1px solid #FF0000;"
            "QPushButton:hover { background-color: #FF0000; color: #000000; }");
    }

    connect(saveButton, &QPushButton::clicked, this, &EndGameWidget::onSaveClicked);
    connect(menuButton, &QPushButton::clicked, this, &EndGameWidget::onMenuClicked);
}

void EndGameWidget::loadLeaderboard()
{
    leaderboard.clear();

    QFile file(leaderboardFile);
    if (!file.exists()) {
        file.open(QIODevice::WriteOnly);
        file.close();
        return;
    }

    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(" - ");
            if (parts.size() == 2) {
                PlayerScore score;
                score.name = parts[0];
                score.time = QTime::fromString(parts[1], "mm:ss");
                leaderboard.append(score);
            }
        }
        file.close();
    }

    std::sort(leaderboard.begin(), leaderboard.end());
    updateLeaderboardDisplay();
}

void EndGameWidget::saveLeaderboard()
{
    if (!isVictory) return;

    QString name = nameEdit->text().trimmed();
    if (name.isEmpty()) {
        name = "Anonyme";
    }

    PlayerScore newScore;
    newScore.name = name;
    newScore.time = playerTime;
    leaderboard.append(newScore);

    std::sort(leaderboard.begin(), leaderboard.end());

    if (leaderboard.size() > 15) {
        leaderboard.resize(15);
    }

    QFile file(leaderboardFile);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const PlayerScore& score : leaderboard) {
            out << score.name << " - " << score.time.toString("mm:ss") << "\n";
        }
        file.close();
    }

    updateLeaderboardDisplay();
    nameEdit->setEnabled(false);
    saveButton->setEnabled(false);
}

void EndGameWidget::updateLeaderboardDisplay()
{
    leaderboardList->clear();

    int rank = 1;
    for (const PlayerScore& score : leaderboard) {
        QString entry = QString("%1. %2 - %3")
            .arg(rank)
            .arg(score.name)
            .arg(score.time.toString("mm:ss"));

        QListWidgetItem* item = new QListWidgetItem(entry);

        if (rank == 1) {
            item->setForeground(QColor(255, 215, 0));
            QFont font = item->font();
            font.setBold(true);
            font.setPointSize(12);
            item->setFont(font);
        }
        else if (rank == 2) {
            item->setForeground(QColor(192, 192, 192));
            QFont font = item->font();
            font.setBold(true);
            font.setPointSize(11);
            item->setFont(font);
        }
        else if (rank == 3) {
            item->setForeground(QColor(205, 127, 50));
            QFont font = item->font();
            font.setBold(true);
            font.setPointSize(10);
            item->setFont(font);
        }

        leaderboardList->addItem(item);
        rank++;
    }
}

void EndGameWidget::onSaveClicked()
{
    saveLeaderboard();
}

void EndGameWidget::onMenuClicked()
{
    emit returnToMainMenu();
}