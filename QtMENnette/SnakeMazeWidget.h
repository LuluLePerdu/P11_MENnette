#ifndef SNAKEMAZEWIDGET_H
#define SNAKEMAZEWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QPainter>
#include "SnakeMaze.h"

class SnakeMazeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SnakeMazeWidget(QWidget* parent = nullptr);
    ~SnakeMazeWidget();

protected:
    void paintEvent(QPaintEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void updateGame();

private:
    SnakeMaze logic;  
    QTimer* gameTimer;     
};

#endif
