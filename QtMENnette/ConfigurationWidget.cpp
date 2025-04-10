///@file ConfigurationWidget.cpp
///@brief Fichier source pour la classe ConfigurationWidget. Permet de configurer les paramètres de jeu pour les différents jeux et la création de l'interface utilisateur.
///@author DUFL5093, GAGL1353, ROMZ6050

#include "ConfigurationWidget.h"

/// <summary>
/// Constructeur de la classe ConfigurationWidget.
/// Initialise les préréglages de difficulté et configure l'interface utilisateur.
/// </summary>
/// <param name="parent">Le widget parent (par défaut nullptr).</param>
ConfigurationWidget::ConfigurationWidget(QWidget* parent) : QWidget(parent)
{
    // Initialisation des préréglages de difficulté pour le jeu Snake Maze
    difficultyPresets[EASY] = { 15, 15, 60 };
    difficultyPresets[NORMAL] = { 21, 21, 50 };
    difficultyPresets[HARD] = { 31, 31, 45 };

    setupUi();
    applyBombStyle();
}

/// <summary>
/// Configure l'interface utilisateur pour les différents jeux.
/// </summary>
void ConfigurationWidget::setupUi()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(15, 15, 15, 15);

    // ===== SNAKE MAZE =====
    QWidget* snakeContent = new QWidget();
    QFormLayout* snakeLayout = new QFormLayout(snakeContent);
    snakeLayout->setContentsMargins(10, 10, 10, 10);

    difficultyCombo->addItem("Facile ", EASY);
    difficultyCombo->addItem("Normal ", NORMAL);
    difficultyCombo->addItem("Difficile ", HARD);
    difficultyCombo->addItem("Personaliser ", CUSTOM);

    mazeWidthSpin->setRange(5, 50);
    mazeHeightSpin->setRange(5, 50);
    mazeTimeSpin->setRange(10, 300);
    mazeTimeSpin->setSuffix(" sec");

    mazeHeightSpin->setReadOnly(true);
    mazeWidthSpin->setReadOnly(true);
    mazeTimeSpin->setReadOnly(true);

    snakeLayout->addRow(QString::fromLatin1("Difficulté :"), difficultyCombo);
    snakeLayout->addRow("Largeur :", mazeWidthSpin);
    snakeLayout->addRow("Hauteur :", mazeHeightSpin);
    snakeLayout->addRow("Temps :", mazeTimeSpin);

    mainLayout->addWidget(createGameSection("Labyrinthe Explosif", snakeContent));

    // ===== SIMON SAYS =====
    QWidget* simonContent = new QWidget();
    QFormLayout* simonLayout = new QFormLayout(simonContent);
    simonLayout->setContentsMargins(10, 10, 10, 10);

    simonLengthSpin->setRange(1, 15);
    simonLengthSpin->setValue(8);

    simonLayout->addRow("Longueur :", simonLengthSpin);

    mainLayout->addWidget(createGameSection("Jean Dit", simonContent));

    // ===== THREAD CUTTER =====
    QWidget* threadContent = new QWidget();
    QFormLayout* threadLayout = new QFormLayout(threadContent);
    threadLayout->setContentsMargins(10, 10, 10, 10);

    difficultyThreadCombo->addItem("Facile ", EASY);
    difficultyThreadCombo->addItem("Normal ", NORMAL);
    difficultyThreadCombo->addItem("Difficile ", HARD);
    difficultyThreadCombo->addItem("Personaliser ", CUSTOM);

    threadTimeSpin->setRange(10, 50);
    threadTimeSpin->setSuffix(" sec");
    threadTimeSpin->setReadOnly(true);

    threadLayout->addRow(QString::fromLatin1("Difficulté :"), difficultyThreadCombo);
    threadLayout->addRow(QString::fromLatin1("Pénalité :"), threadTimeSpin);

    connect(difficultyThreadCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ConfigurationWidget::onDiffChangedThread);

    difficultyThreadCombo->setCurrentIndex(NORMAL);
    onDiffChangedThread(NORMAL);

    mainLayout->addWidget(createGameSection("Coupe-fil", threadContent));

    // ===== CRYPTO SEQUENCER =====
    QWidget* cryptoContent = new QWidget();
    QFormLayout* cryptoLayout = new QFormLayout(cryptoContent);
    cryptoLayout->setContentsMargins(10, 10, 10, 10);

    cryptoRangeSpin->setRange(10, 255);
    cryptoRangeSpin->setValue(50);

    cryptoLayout->addRow(QString::fromLatin1("Portée :"), cryptoRangeSpin);

    mainLayout->addWidget(createGameSection(QString::fromLatin1("Crypto Séquence "), cryptoContent));

    // ===== BOUTON APPLIQUER =====
    QPushButton* applyButton = new QPushButton("CONFIRMER");
    applyButton->setFixedHeight(45);
    mainLayout->addWidget(applyButton);

    connect(applyButton, &QPushButton::clicked, this, &ConfigurationWidget::settingsApplied);
    connect(difficultyCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
        this, &ConfigurationWidget::onDifficultyChanged);

    difficultyCombo->setCurrentIndex(NORMAL);
    updateDifficultySettings();
}

/// <summary>
/// Permet de créer une section de jeu avec un titre et un contenu.
/// </summary>
/// <param name="title">Le titre de la section</param>
/// <param name="content">Le contenu de la section (essentiellement un widget) </param>
/// <returns>Retourne la section avec le layout visuel approprié</returns>
QGroupBox* ConfigurationWidget::createGameSection(const QString& title, QWidget* content)
{
    QGroupBox* group = new QGroupBox(title);
    QVBoxLayout* layout = new QVBoxLayout(group);
    layout->addWidget(content);
    group->setLayout(layout);
    return group;
}

/// <summary>
/// Permet d'appliquer le style de la bombe sur le widget de configuration avec un QSS.
/// </summary>
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

/// <summary>
/// Permet de signaler que les paramètres de configuration ont été appliqués spécifiquement pour le jeu de snake.
/// </summary>
void ConfigurationWidget::onDifficultyChanged(int index)
{
    Q_UNUSED(index); 
    updateDifficultySettings();
}

/// <summary>
/// Permet de signaler que les paramètres de configuration ont été appliqués spécifiquement pour le jeu de thread.
/// </summary>
void ConfigurationWidget::onDiffChangedThread(int index) {
    Q_UNUSED(index);
    threadTimeSpin->setReadOnly(true);
    switch (difficultyThreadCombo->currentData().toInt())
    {
    case EASY:
        threadTimeSpin->setValue(10);
        break;
    case NORMAL:
        threadTimeSpin->setValue(30);
        break;
    case HARD:
        threadTimeSpin->setValue(50);
        break;
    default:
        threadTimeSpin->setReadOnly(false);
        break;
    }
}

/// <summary>   
/// Applique les paramètres de configuration pour le jeu de snake.
/// </summary>
void ConfigurationWidget::updateDifficultySettings()
{
    Difficulty diff = static_cast<Difficulty>(difficultyCombo->currentData().toInt());

    if (diff != CUSTOM) {
        mazeHeightSpin->setReadOnly(true);
        mazeWidthSpin->setReadOnly(true);
        mazeTimeSpin->setReadOnly(true);
        DifficultyPreset preset = difficultyPresets[diff];
        mazeWidthSpin->setValue(preset.width);
        mazeHeightSpin->setValue(preset.height);
        mazeTimeSpin->setValue(preset.time);
    }
    else {
        mazeHeightSpin->setReadOnly(false);
        mazeWidthSpin->setReadOnly(false);
        mazeTimeSpin->setReadOnly(false);
    }
}
// Retourne le temps du labyrinthe configuré par l'utilisateur.
int ConfigurationWidget::getMazeTime() const {
    return mazeTimeSpin->value();
}

/// <summary>
/// Retourne la largeur du labyrinthe configurée par l'utilisateur.
/// </summary>
/// <returns>La largeur du labyrinthe.</returns>
int ConfigurationWidget::getMazeWidth() const {
    return mazeWidthSpin->value();
}

/// <summary>
/// Retourne la hauteur du labyrinthe configurée par l'utilisateur.
/// </summary>
/// <returns>La hauteur du labyrinthe.</returns>
int ConfigurationWidget::getMazeHeight() const {
    return mazeHeightSpin->value();
}

/// <summary>
/// Retourne la plage de valeurs configurée pour le jeu Crypto Sequencer.
/// </summary>
/// <returns>La plage de valeurs.</returns>
int ConfigurationWidget::getCryptoRange() const {
    return cryptoRangeSpin->value();
}

/// <summary>
/// Retourne la longueur configurée pour le jeu Simon Says.
/// </summary>
/// <returns>La longueur configurée.</returns>
int ConfigurationWidget::getSimonLength() const {
    return simonLengthSpin->value();
}

/// <summary>
/// Retourne la pénalité de temps configurée pour le jeu Thread Cutter.
/// </summary>
/// <returns>La pénalité de temps.</returns>
int ConfigurationWidget::getThreadPenalty() const {
    return threadTimeSpin->value();
}

/// <summary>
/// Retourne le niveau de difficulté sélectionné par l'utilisateur.
/// </summary>
/// <returns>Le niveau de difficulté.</returns>
ConfigurationWidget::Difficulty ConfigurationWidget::getDifficulty() const {
    return static_cast<Difficulty>(difficultyCombo->currentData().toInt());
}