#include "SnakeMazeWidget.h"
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>
#include <QLinearGradient>
#include <QPainterPath>
#include <cstdlib>
#include <QMessageBox>
#include <QPushButton>


SnakeMazeWidget::SnakeMazeWidget(QWidget* parent) :
    QWidget(parent),
    gameTimer(new QTimer(this)),
    animationTimer(new QTimer(this))
{
    logic.initialize();
    setFocusPolicy(Qt::StrongFocus);
    setFixedSize(logic.WIDTH * cellSize, logic.HEIGHT * cellSize + hudHeight);

    connect(gameTimer, &QTimer::timeout, this, &SnakeMazeWidget::updateGame);
    gameTimer->start(16); 

    connect(animationTimer, &QTimer::timeout, this, [this]() {
        update();
        });
    animationTimer->start(16);
}

SnakeMazeWidget::~SnakeMazeWidget()
{
}

void SnakeMazeWidget::startGame() 
{
    logic.initialize();
    gameTimer->start(16);
    animationTimer->start(16);
    update();
}

void SnakeMazeWidget::stopGame() {
    gameTimer->stop();
    animationTimer->stop();
    logic.initialize();
}

void SnakeMazeWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const int mazeWidth = logic.WIDTH * cellSize;
    const int mazeHeight = logic.HEIGHT * cellSize;
    const int totalHeight = mazeHeight + hudHeight;

    QLinearGradient bgGradient(0, 0, width(), height());
    bgGradient.setColorAt(0, QColor(40, 40, 45));
    bgGradient.setColorAt(1, QColor(15, 15, 20));
    painter.fillRect(rect(), bgGradient);

    painter.setPen(QPen(QColor(80, 0, 0, 60), 1.5));
    for (int y = 0; y < height(); y += 25) {
        painter.drawLine(0, y, width(), y);
    }

    const char(&maze)[SnakeMaze::HEIGHT][SnakeMaze::WIDTH] = logic.getMaze();

    // Labyrinthe
    for (int y = 0; y < SnakeMaze::HEIGHT; y++) {
        for (int x = 0; x < SnakeMaze::WIDTH; x++) {
            QRectF rect(x * cellSize, y * cellSize + hudHeight, cellSize, cellSize);

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
            else if (maze[y][x] == SnakeMaze::PLAYER) {
                QPointF renderPos;
                if (isAnimating) {
                    float progress = qMin(animationStartTime.msecsTo(QTime::currentTime()) / (animationDuration * 1000), 1.0f);
                    progress = 1 - pow(1 - progress, 3);
                    renderPos = prevPlayerPos * (1 - progress) + QPointF(logic.getPlayerX(), logic.getPlayerY()) * progress;
                }
                else {
                    renderPos = QPointF(logic.getPlayerX(), logic.getPlayerY());
                }

                QPointF pixelPos(renderPos.x() * cellSize, renderPos.y() * cellSize + hudHeight);

                // Arthur, le désamorceur de bombes
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
    if (!isAnimating) {
        switch (event->key()) {
        case Qt::Key_Up:
            logic.changeDirection(0, -1);
            break;
        case Qt::Key_Down:
            logic.changeDirection(0, 1);
            break;
        case Qt::Key_Left:
            logic.changeDirection(-1, 0);
            break;
        case Qt::Key_Right:
            logic.changeDirection(1, 0);
            break;
        default:
            QWidget::keyPressEvent(event);
            return;
        }
        
        updateGame();
    }
}

void SnakeMazeWidget::updateGame() {
    logic.updateTimer();

    static bool blinkState = false;
    static int blinkCounter = 0;
    bool isOvertime = logic.getTimeLeft() < 0;

    if (isOvertime) {
        if (blinkCounter++ % 10 == 0) {
            blinkState = !blinkState;
        }

        static float pulseScale = 1.0f;
        static bool growing = true;
        if (growing) {
            pulseScale += 0.01f;
            if (pulseScale >= 1.1f) growing = false;
        }
        else {
            pulseScale -= 0.01f;
            if (pulseScale <= 1.0f) growing = true;
        }
    }
    else {
        blinkState = false;
        blinkCounter = 0;
    }

    static QTime lastMoveTime = QTime::currentTime();
    int moveDelay = 120;

    if (QTime::currentTime().msecsTo(lastMoveTime) < -moveDelay) 
    {
        if (!isAnimating) {
            prevPlayerPos = QPointF(logic.getPlayerX(), logic.getPlayerY());
            logic.movePlayer();

            QPointF newPos(logic.getPlayerX(), logic.getPlayerY());
            if (prevPlayerPos != newPos) {
                isAnimating = true;
                animationStartTime = QTime::currentTime();
                lastMoveTime = QTime::currentTime();
            }
        }
        else {
            if (animationStartTime.msecsTo(QTime::currentTime()) >= animationDuration * 1000) {
                isAnimating = false;
            }
        }
    }

    if (!logic.inGame()) {
        showResultDialog();
    }

    update();
}

void SnakeMazeWidget::showResultDialog()
{
    int timeUsed = 60 - logic.getTimeLeft();
    int overtime = (timeUsed > 60) ? (timeUsed - 60) : 0;

    QString message;
    if (overtime == 0) {
        message = "Bombe désamorcée en " + QString::number(timeUsed) + " secondes!";
    }
    else {
        message = "Temps dépassé de " + QString::number(overtime) + " secondes!";
        emit timePenalty(overtime);
    }

    gameTimer->stop();
    animationTimer->stop();

    QMessageBox msgBox;
    msgBox.setWindowTitle(overtime == 0 ? "Mission accomplie" : "Échec");
    msgBox.setText(message);
    msgBox.setStandardButtons(QMessageBox::Ok);

    QPushButton* retryButton = msgBox.addButton("Recommencer", QMessageBox::ActionRole);
    QPushButton* menuButton = msgBox.addButton("Menu", QMessageBox::AcceptRole);

    msgBox.exec();

    if (msgBox.clickedButton() == retryButton) {
        startGame();
    }
    else {
        emit returnToMenuRequested();
    }
}