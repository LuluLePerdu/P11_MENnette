#include "SnakeMazeWidget.h"
#include "ConfigurationWidget.h"

SnakeMazeWidget::SnakeMazeWidget(int mazeWidth, int mazeHeight, int gameDuration,
    ConfigurationWidget::Difficulty difficulty,
    QWidget* parent)
    : QWidget(parent),
    logic(mazeWidth, mazeHeight, gameDuration),
    gameTimer(new QTimer(this))
{
    switch (difficulty) {
    case ConfigurationWidget::EASY:
		cellSize = 30;
		animationDuration = 0.3f;
        break;
    case ConfigurationWidget::NORMAL:
        cellSize = 25;
		animationDuration = 0.2f;
        gameTimer->setInterval(16);
        break;
    case ConfigurationWidget::HARD:
        cellSize = 20; 
		animationDuration = 0;
        gameTimer->setInterval(16);
        break;
    case ConfigurationWidget::CUSTOM:

        cellSize = 25;
        gameTimer->setInterval(16);
        break;
    }

    connect(gameTimer, &QTimer::timeout, this, [this]() {
        updateGame();
        handleInputs();
        update();
        });
}

SnakeMazeWidget::~SnakeMazeWidget() {}

void SnakeMazeWidget::startGame()
{
    logic.initialize();
    renderPos = QPointF(logic.getPlayerX(), logic.getPlayerY());
    currentAnimation.active = false;
    gameTimer->start(16);
}

void SnakeMazeWidget::stopGame()
{
    gameTimer->stop();
    logic.initialize();

}

void SnakeMazeWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setClipRect(event->rect());
    painter.setRenderHint(QPainter::Antialiasing, cellSize > 20);

    const int mazePixelWidth = logic.WIDTH * cellSize;
    const int mazePixelHeight = logic.HEIGHT * cellSize;
    const int marginX = (width() - mazePixelWidth) / 2;
    const int marginY = (height() - mazePixelHeight - hudHeight) / 2 + hudHeight;

    QLinearGradient bgGradient(0, 0, width(), height());
    bgGradient.setColorAt(0, QColor(40, 40, 45));
    bgGradient.setColorAt(1, QColor(15, 15, 20));
    painter.fillRect(rect(), bgGradient);

    const char** maze = logic.getMaze();

    // Labyrinthe
    for (int y = 0; y < logic.HEIGHT; y++) {
        for (int x = 0; x < logic.WIDTH; x++) {
            QRectF rect(x * cellSize + marginX,
                y * cellSize + marginY,
                cellSize, cellSize);

            if (maze[y][x] == SnakeMaze::WALL) {
                QLinearGradient wallGrad(rect.topLeft(), rect.bottomRight());
                wallGrad.setColorAt(0, QColor(100, 100, 100));
                wallGrad.setColorAt(1, QColor(60, 60, 60));

                painter.setPen(QPen(QColor(150, 150, 150), 1));
                painter.setBrush(wallGrad);
                painter.drawRoundedRect(rect, 2, 2);

                painter.setBrush(QColor(180, 180, 180));
                painter.setPen(Qt::NoPen);
                if ((x + y) % 2 == 0) {
                    painter.drawEllipse(rect.center(), 2, 2);
                }
            }
            else if (maze[y][x] == SnakeMaze::PLAYER ||
                (currentAnimation.active &&
                    QPointF(x, y) == currentAnimation.startPos)) {

                QPointF pixelPos(renderPos.x() * cellSize + marginX,
                    renderPos.y() * cellSize + marginY);

                // Dessin d'Arthur
                painter.setPen(Qt::NoPen);
                painter.setBrush(QColor(200, 200, 200));
                painter.drawEllipse(pixelPos.x() + cellSize / 4, pixelPos.y(), cellSize / 2, cellSize / 2);

                painter.setBrush(QColor(0, 80, 150));
                painter.drawEllipse(pixelPos.x() + cellSize / 4, pixelPos.y() + cellSize / 3, cellSize / 2, cellSize / 1.5);

                painter.setPen(QPen(QColor(255, 200, 0), 2));
                painter.drawLine(pixelPos.x() + cellSize / 2, pixelPos.y() + cellSize / 2,
                    pixelPos.x() + cellSize / 2 + 8, pixelPos.y() + cellSize / 2 - 5);

                QRadialGradient lightGrad(pixelPos + QPointF(cellSize / 2, cellSize / 3), cellSize / 3);
                lightGrad.setColorAt(0, QColor(255, 255, 200, 100));
                lightGrad.setColorAt(1, Qt::transparent);
                painter.setBrush(lightGrad);
                painter.setPen(Qt::NoPen);
                painter.drawEllipse(pixelPos + QPointF(cellSize / 4, cellSize / 4), cellSize / 3, cellSize / 3);
            }
            else if (maze[y][x] == SnakeMaze::OBJECTIVE) {
                // Bombe
                QRadialGradient bombGrad(rect.center(), cellSize / 2);
                bombGrad.setColorAt(0, QColor(200, 50, 50));
                bombGrad.setColorAt(1, QColor(100, 0, 0));

                painter.setPen(QPen(QColor(150, 0, 0), 1.5));
                painter.setBrush(bombGrad);
                painter.drawEllipse(rect.adjusted(2, 2, -2, -2));

                painter.setPen(QColor(255, 200, 200));
                painter.setFont(QFont("Digital", 10, QFont::Bold));
                painter.drawText(rect, Qt::AlignCenter, QString::number(logic.getTimeLeft()));

                painter.setPen(QPen(QColor(255, 150, 0), 2));
                painter.drawLine(rect.center().x(), rect.top() + 2,
                    rect.center().x(), rect.top() - 8);

                qint64 time = QDateTime::currentMSecsSinceEpoch() % 1000;
                float flameProgress = time / 1000.0f;
                QPainterPath flame;
                flame.moveTo(rect.center().x() - 4, rect.top() - 8);
                flame.cubicTo(rect.center().x() - 2, rect.top() - 8 - 10 * sin(flameProgress * M_PI),
                    rect.center().x() + 2, rect.top() - 8 - 10 * sin(flameProgress * M_PI + M_PI / 2),
                    rect.center().x() + 4, rect.top() - 8);
                painter.setBrush(QColor(255, 100, 0, 200));
                painter.setPen(Qt::NoPen);
                painter.drawPath(flame);
            }
            else {
                painter.setPen(QPen(QColor(70, 70, 70), 0.3));
                painter.setBrush(QColor(50, 50, 50));
                painter.drawRect(rect);

                painter.setPen(QPen(QColor(80, 80, 80, 40), 0.5));
                painter.drawLine(rect.left() + 2, rect.center().y(), rect.right() - 2, rect.center().y());
                painter.drawLine(rect.center().x(), rect.top() + 2, rect.center().x(), rect.bottom() - 2);
            }
        }
    }

    QLinearGradient hudGradient(0, 0, width(), hudHeight);
    hudGradient.setColorAt(0, QColor(80, 10, 10));
    hudGradient.setColorAt(1, QColor(40, 5, 5));
    painter.fillRect(0, 0, width(), hudHeight, hudGradient);

    int timeLeft = logic.getTimeLeft();
    bool blinkOn = (QDateTime::currentMSecsSinceEpoch() % 1000) < 500;

    QColor timerColor;
    if (timeLeft > 15) {
        timerColor = QColor(50, 255, 50);
    }
    else {
        timerColor = blinkOn ? QColor(255, 50, 50) : QColor(150, 0, 0);
    }

    if (timeLeft <= 15) {
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(40, 0, 0, blinkOn ? 120 : 60));
        painter.drawRect(width() - 155, 5, 145, 30);
    }

    painter.setPen(QPen(timerColor, 2));
    QFont timerFont("Digital", 14, QFont::Bold);
    timerFont.setLetterSpacing(QFont::AbsoluteSpacing, 1.5);
    painter.setFont(timerFont);

    QRect timeRect(width() - 150, 10, 135, 30);
    painter.drawText(timeRect, Qt::AlignRight,
        QString("%1").arg(timeLeft, 2, 10, QLatin1Char('0')) + " SEC");

    painter.setPen(QPen(QColor(255, 60, 60), 2));
    painter.drawLine(0, hudHeight, width(), hudHeight);
}

void SnakeMazeWidget::keyPressEvent(QKeyEvent* event)
{
    if (currentAnimation.active) return;

    QPointF prevPos(logic.getPlayerX(), logic.getPlayerY());

    switch (event->key()) {
    case Qt::Key_Left:  logic.changeDirection(-1, 0); break;
    case Qt::Key_Right: logic.changeDirection(1, 0);  break;
    case Qt::Key_Up:    logic.changeDirection(0, -1); break;
    case Qt::Key_Down:  logic.changeDirection(0, 1);  break;
    default: return;
    }

    logic.movePlayer();
    startAnimation(prevPos);
}

void SnakeMazeWidget::startAnimation(const QPointF& prevPos)
{
    if (animationDuration <= 0) {
        renderPos = QPointF(logic.getPlayerX(), logic.getPlayerY());
        update();
        return;
    }

    currentAnimation.startPos = prevPos;
    currentAnimation.endPos = QPointF(logic.getPlayerX(), logic.getPlayerY());
    currentAnimation.startTime = QTime::currentTime();
    currentAnimation.active = true;

    renderPos = prevPos;
}

void SnakeMazeWidget::handleInputs()
{
    Communication& comm = Communication::getInstance();
    uint8_t joystickValue = comm.readMsg(MSG_ID_AR_JOYSTICK);
    comm.clear();

    if (joystickValue != -1 ) {
        QPointF prevPos(logic.getPlayerX(), logic.getPlayerY());

        switch (joystickValue) {
            case 4: 
                logic.changeDirection(-1, 0); 
                break; // Gauche
            case 8: 
                logic.changeDirection(1, 0);  
                break; // Droite
            case 2: 
                logic.changeDirection(0, -1); 
                break; // Haut
            case 1: 
                logic.changeDirection(0, 1);  
                break; // Bas
            default: return;
        }

        logic.movePlayer();
        startAnimation(prevPos);
    }
}

void SnakeMazeWidget::updateGame()
{
    logic.updateTimer();

    if (currentAnimation.active) {
        float elapsed = currentAnimation.startTime.msecsTo(QTime::currentTime()) / 1000.0f;
        float progress = qMin(elapsed / animationDuration, 1.0f);

        float easedProgress = progress < 0.5
            ? 2 * progress * progress
            : 1 - pow(-2 * progress + 2, 2) / 2;

        renderPos = currentAnimation.startPos + (currentAnimation.endPos - currentAnimation.startPos) * easedProgress;

        if (progress >= 1.0f) {
            currentAnimation.active = false;
            renderPos = currentAnimation.endPos;
        }
    }

    if (!logic.inGame()) {
        showResultDialog();
    }

    static bool blinkState = false;
    static int blinkCounter = 0;
    bool isOvertime = logic.getTimeLeft() < 0;

    if (isOvertime) {
        if (blinkCounter++ % 10 == 0) blinkState = !blinkState;

        static float pulseScale = 1.0f;
        static bool growing = true;
        pulseScale += growing ? 0.02f : -0.02f;
        if (pulseScale >= 1.15f) growing = false;
        else if (pulseScale <= 1.0f) growing = true;
    }
    else {
        blinkState = false;
        blinkCounter = 0;
    }

    if (!logic.inGame()) {
        showResultDialog();
    }

    update();
}

void SnakeMazeWidget::showResultDialog()
{
    Communication& comm = Communication::getInstance();
    gameTimer->stop();

    int timeUsed = logic.getGameDuration() - logic.getTimeLeft();
    bool victory = timeUsed <= logic.getGameDuration();

    QMessageBox msgBox;
    if (victory) {
        msgBox.setWindowTitle(QString::fromLatin1("Mission accomplie"));
        msgBox.setText(QString::fromLatin1("Bombe désamorcée en %1 secondes!").arg(timeUsed));
        comm.buzz(57);
    }
    else {
        msgBox.setWindowTitle(QString::fromLatin1("Échec"));
        msgBox.setText(QString::fromLatin1("Temps dépassé de %1 secondes!").arg(timeUsed - logic.getGameDuration()));
        comm.buzz(242);
    }

    QPushButton* retryButton = msgBox.addButton("Recommencer", QMessageBox::ActionRole);
    QPushButton* menuButton = msgBox.addButton("Retour au menu", QMessageBox::AcceptRole);

    msgBox.exec();

    if (msgBox.clickedButton() == retryButton) {
        startGame();
    }
    else {
        emit returnToMenuRequested();
        emit timePenalty(timeUsed - logic.getGameDuration());
    }
}