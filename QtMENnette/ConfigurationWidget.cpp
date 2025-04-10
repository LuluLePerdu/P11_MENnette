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

    // Configuration de l'interface utilisateur et application du style
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
    // Création de la section pour le jeu Snake Maze
    QWidget* snakeContent = new QWidget();
    QFormLayout* snakeLayout = new QFormLayout(snakeContent);
    snakeLayout->setContentsMargins(10, 10, 10, 10);

    // Configuration des widgets pour Snake Maze
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

    // Les champs sont en lecture seule par défaut
    mazeHeightSpin->setReadOnly(true);
    mazeWidthSpin->setReadOnly(true);
    mazeTimeSpin->setReadOnly(true);

    // Ajout des widgets au layout
    snakeLayout->addRow("Difficulte:", difficultyCombo);
    snakeLayout->addRow("Largeur:", mazeWidthSpin);
    snakeLayout->addRow("Hauteur:", mazeHeightSpin);
    snakeLayout->addRow("Temps:", mazeTimeSpin);

    // Ajout de la section Snake Maze au layout principal
    mainLayout->addWidget(createGameSection("SNAKE MAZE", snakeContent));

    // ===== SIMON SAYS =====
    // Création de la section pour le jeu Simon Says
    QWidget* simonContent = new QWidget();
    QFormLayout* simonLayout = new QFormLayout(simonContent);
    simonLayout->setContentsMargins(10, 10, 10, 10);

    simonLengthSpin = new QSpinBox();
    simonLengthSpin->setRange(1, 15);
    simonLengthSpin->setValue(8);

    // Ajout des widgets au layout
    simonLayout->addRow("Longueur:", simonLengthSpin);

    // Ajout de la section Simon Says au layout principal
    mainLayout->addWidget(createGameSection("SIMON SAYS", simonContent));

    // ===== THREAD CUTTER =====
    // Création de la section pour le jeu Thread Cutter
    QWidget* threadContent = new QWidget();
    QFormLayout* threadLayout = new QFormLayout(threadContent);
    threadLayout->setContentsMargins(10, 10, 10, 10);

    difficultyThreadCombo = new QComboBox();
    difficultyThreadCombo->addItem("Facile", EASY);
    difficultyThreadCombo->addItem("Normal", NORMAL);
    difficultyThreadCombo->addItem("Difficile", HARD);
    difficultyThreadCombo->addItem("Custom", CUSTOM);

    threadTimeSpin = new QSpinBox();
    threadTimeSpin->setRange(10, 50);
    threadTimeSpin->setSuffix(" sec");
    threadTimeSpin->setReadOnly(true);

    // Ajout des widgets au layout
    threadLayout->addRow(QString::fromLatin1("Difficulté :"), difficultyThreadCombo);
    threadLayout->addRow(QString::fromLatin1("Pénalité :"), threadTimeSpin);

    // Connexion du signal pour gérer les changements de difficulté
    connect(difficultyThreadCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ConfigurationWidget::onDiffChangedThread);

    // Initialisation de la difficulté par défaut
    difficultyThreadCombo->setCurrentIndex(NORMAL);
    onDiffChangedThread(NORMAL);

    // Ajout de la section Thread Cutter au layout principal
    mainLayout->addWidget(createGameSection("THREAD CUTTER", threadContent));

    // ===== CRYPTO SEQUENCER =====
    // Création de la section pour le jeu Crypto Sequencer
    QWidget* cryptoContent = new QWidget();
    QFormLayout* cryptoLayout = new QFormLayout(cryptoContent);
    cryptoLayout->setContentsMargins(10, 10, 10, 10);

    cryptoRangeSpin = new QSpinBox();
    cryptoRangeSpin->setRange(10, 255);
    cryptoRangeSpin->setValue(50);

    // Ajout des widgets au layout
    cryptoLayout->addRow("Range:", cryptoRangeSpin);

    // Ajout de la section Crypto Sequencer au layout principal
    mainLayout->addWidget(createGameSection("CRYPTO SEQUENCER", cryptoContent));

    // ===== BOUTON APPLIQUER =====
    // Création du bouton pour appliquer les paramètres
    QPushButton* applyButton = new QPushButton("CONFIRMER");
    applyButton->setFixedHeight(45);
    mainLayout->addWidget(applyButton);

    // Connexion des signaux pour appliquer les paramètres et gérer les changements de difficulté
    connect(applyButton, &QPushButton::clicked, this, &ConfigurationWidget::settingsApplied);
    connect(difficultyCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
        this, &ConfigurationWidget::onDifficultyChanged);

    // Initialisation de la difficulté par défaut
    difficultyCombo->setCurrentIndex(NORMAL);
    updateDifficultySettings();
}


/// <summary>
/// Permet de créer une section de jeu avec un titre et un contenu.
/// </summary>
/// <param name="title">Le titre de la section</param>
/// <param name="content">Le contenu de la section (essentiellement un widget) </param>
/// <returns>Retopurne la section avec le layout visuel approprié</returns>
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
/// <summary>
///  Permet d'obtenir la difficulté sélectionnée par l'utilisateur.
/// </summary>
/// <returns>La difficulté sélectionnée sous forme d'énumération Difficulty.</returns>
ConfigurationWidget::Difficulty ConfigurationWidget::getDifficulty() const {
    return static_cast<Difficulty>(difficultyCombo->currentData().toInt());
}

/// <summary>
///  Permet d'obtenir la largeur du labyrinthe configurée par l'utilisateur.
/// </summary>
/// <returns>La largeur du labyrinthe en tant qu'entier.</returns>
int ConfigurationWidget::getMazeWidth() const { 
    return mazeWidthSpin->value(); 
}

/// <summary>
///  Permet d'obtenir la hauteur du labyrinthe configurée par l'utilisateur.
/// </summary>
/// <returns>La hauteur du labyrinthe en tant qu'entier.</returns>
int ConfigurationWidget::getMazeHeight() const { 
    return mazeHeightSpin->value(); 
}

/// <summary>
///  Permet d'obtenir le temps limite pour le labyrinthe configuré par l'utilisateur.
/// </summary>
/// <returns>Le temps limite en secondes en tant qu'entier.</returns>
int ConfigurationWidget::getMazeTime() const { 
    return mazeTimeSpin->value(); 
}

/// <summary>
///  Permet d'obtenir la plage de valeurs configurée pour le jeu Crypto Sequencer.
/// </summary>
/// <returns>La plage de valeurs en tant qu'entier.</returns>
int ConfigurationWidget::getCryptoRange() const { 
    return cryptoRangeSpin->value(); 
}

/// <summary>
///  Permet d'obtenir la longueur de la séquence configurée pour le jeu Simon Says.
/// </summary>
/// <returns>La longueur de la séquence en tant qu'entier.</returns>
int ConfigurationWidget::getSimonLength() const { 
    return simonLengthSpin->value(); 
}

/// <summary>
///  Permet d'obtenir la pénalité de temps configurée pour le jeu Thread Cutter.
/// </summary>
/// <returns>La pénalité de temps en secondes en tant qu'entier.</returns>
int ConfigurationWidget::getThreadPenalty() const { 
    return threadTimeSpin->value(); 
}