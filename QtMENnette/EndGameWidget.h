///@file EndGameWidget.h
///@brief Fichier d'en-t�te pour la classe EndGameWidget - Fichier fait � la main pour l'�valuation de l'APP7
///@author DUFL5093, GAGL1353, ROMZ6050

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

/// <summary>
///  structure pour stocker les informations de score du joueur.
/// </summary>
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
	explicit EndGameWidget(QTime finalTime, bool victory, QWidget* parent = nullptr); /// Constructeur de la classe EndGameWidget
	~EndGameWidget(); /// Destructeur de la classe EndGameWidget

signals:
	void returnToMainMenu(); /// Signal �mis pour retourner au menu principal

private slots:
	void onSaveClicked(); /// Slot pour g�rer le clic sur le bouton "Enregistrer"
	void onMenuClicked(); /// Slot pour g�rer le clic sur le bouton "Menu"
	 
private:
	QTime playerTime; /// Temps du joueur
	bool isVictory; /// Indique si le joueur a gagn� ou perdu
	QList<PlayerScore> leaderboard; /// Liste des scores des joueurs
	QString leaderboardFile = "leaderboard.txt"; /// Fichier de classement

	QLabel* titleLabel; /// Titre de la fen�tre
	QLabel* timeLabel; /// Affichage du temps du joueur
	QLabel* nameLabel; /// �tiquette pour le nom du joueur
	QLineEdit* nameEdit; /// Champ de saisie pour le nom du joueur
	QPushButton* saveButton; /// Bouton pour sauvegarder le score
	QLabel* leaderboardTitle; /// Titre du classement
	QListWidget* leaderboardList; /// Liste des scores
	QPushButton* menuButton; /// Bouton pour retourner au menu principal

	void loadLeaderboard(); /// Charge le classement � partir du fichier
	void saveLeaderboard(); /// Sauvegarde le classement dans le fichier
	void updateLeaderboardDisplay(); /// Met � jour l'affichage du classement
	void setupUI(); /// Configure l'interface utilisateur
};