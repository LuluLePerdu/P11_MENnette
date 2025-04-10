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

class ConfigurationWidget : public QWidget
{
   Q_OBJECT
public:
	enum Difficulty { EASY, NORMAL, HARD, CUSTOM }; /// Enumération des niveaux de difficulté

   struct DifficultyPreset {
       int width;  /// Largeur du labyrinthe
       int height; /// Hauteur du labyrinthe
       int time;   /// Temps limite pour résoudre le labyrinthe
   };

   explicit ConfigurationWidget(QWidget* parent = nullptr);

   int getMazeTime() const;    /// Retourne le temps limite du labyrinthe
   int getMazeWidth() const;   /// Retourne la largeur du labyrinthe
   int getMazeHeight() const;  /// Retourne la hauteur du labyrinthe
   int getCryptoRange() const; /// Retourne la plage de cryptographie
   int getSimonLength() const; /// Retourne la longueur du jeu Simon
   int getThreadPenalty() const; /// Retourne la pénalité de temps pour les threads
   Difficulty getDifficulty() const; /// Retourne la difficulté sélectionnée

signals:
   void settingsApplied(); /// Signal émis lorsque les paramètres sont appliqués

private slots:
   void onDiffChangedThread(int index); /// Slot pour gérer le changement de difficulté des threads
   void onDifficultyChanged(int index); /// Slot pour gérer le changement de difficulté générale

private:
   QGroupBox* createGameSection(const QString& title, QWidget* content); /// Crée une section de jeu avec un titre et un contenu
   void setupUi(); /// Configure l'interface utilisateur
   void applyBombStyle(); /// Applique le style spécifique à la bombe
   void updateDifficultySettings(); /// Met à jour les paramètres en fonction de la difficulté

   QSpinBox* mazeTimeSpin = new QSpinBox(); /// SpinBox pour le temps limite du labyrinthe
   QSpinBox* mazeWidthSpin = new QSpinBox(); /// SpinBox pour la largeur du labyrinthe
   QSpinBox* mazeHeightSpin = new QSpinBox(); /// SpinBox pour la hauteur du labyrinthe
   QComboBox* difficultyCombo = new QComboBox(); /// ComboBox pour sélectionner la difficulté

   QSpinBox* simonLengthSpin = new QSpinBox(); /// SpinBox pour la longueur du jeu Simon

   QSpinBox* threadTimeSpin = new QSpinBox(); /// SpinBox pour le temps des threads
   QComboBox* difficultyThreadCombo = new QComboBox(); /// ComboBox pour la difficulté des threads

   QSpinBox* cryptoRangeSpin = new QSpinBox(); /// SpinBox pour la plage de cryptographie

   QMap<Difficulty, DifficultyPreset> difficultyPresets; /// Map des préréglages de difficulté
};