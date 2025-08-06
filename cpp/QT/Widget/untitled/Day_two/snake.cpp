//
// Created by 17246 on 2025/8/6.
//

#include "snake.h"

#include <QKeyEvent>
#include <QPainter>
#include <QRandomGenerator>

snake::snake(QWidget* parent): QWidget(parent)
{
    setFixedSize(WIDGET_WIDTH, WIDGET_HEIGHT);
    setStyleSheet("background-color: black;");
    setWindowTitle("贪吃蛇");
    initGame();
}

void snake::initGame()
{
    body.load("../Day_two/image/body.png");
    head.load("../Day_two/image/head.png");
    food.load("../Day_two/image/food.png");
    body = body.scaled(BODY_SIZE, BODY_SIZE);
    head = head.scaled(BODY_SIZE, BODY_SIZE);
    food = food.scaled(BODY_SIZE, BODY_SIZE);
    timerId = startTimer(100);
    snakeLength = 3;
    heading = moveDirection::right;
    isGamePlay = true;
    for (int i = 0; i < snakeLength; i++)
    {
        x[i] = 100 - i * BODY_SIZE;
        y[i] = 100;
    }
    initFood();
}

void snake::initFood()
{
    int r = QRandomGenerator::global()->bounded(WIDGET_WIDTH / BODY_SIZE);
    food_x = r * BODY_SIZE;
    r = QRandomGenerator::global()->bounded(WIDGET_HEIGHT / BODY_SIZE);
    food_y = r * BODY_SIZE;
}

void snake::snakeMove()
{
    for (int i = snakeLength - 1; i > 0; i--)
    {
        x[i] = x[i - 1];
        y[i] = y[i - 1];
    }
    switch (heading)
    {
    case moveDirection::up:
        y[0] -= BODY_SIZE;
        break;
    case moveDirection::down:
        y[0] += BODY_SIZE;
        break;
    case moveDirection::left:
        x[0] -= BODY_SIZE;
        break;
    case moveDirection::right:
        x[0] += BODY_SIZE;
        break;
    }
}

void snake::checkEatFood()
{
    if (x[0] == food_x && y[0] == food_y)
    {
        snakeLength++;
        initFood();
    }
}

void snake::checkCollision()
{
    if (x[0] < 0 || x[0] >= WIDGET_WIDTH || y[0] < 0 || y[0] >= WIDGET_HEIGHT)
    {
        isGamePlay = false;
    }
    if (snakeLength > 5)
    {
        for (int i = snakeLength - 1; i > 0; --i)
        {
            if (x[0] == x[i] && y[0] == y[i])
            {
                isGamePlay = false;
            }
        }
    }

    if (isGamePlay == false)
    {
        killTimer(timerId);
    }
}

void snake::gameOver(QPainter& painter)
{
    setStyleSheet("background-color: white;");
    const QString message = "Game Over";
    const QFont font("Courier", 30, QFont::Bold);
    const QFontMetrics fm(font);
    const int messageWidth = fm.horizontalAdvance(message);
    const int messageHeight = fm.height();
    const int width = this->width();
    const int height = this->height();
    painter.translate(width / 2, height / 2);
    painter.drawText(-messageWidth / 2, -messageHeight / 2, message);
}

void snake::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    if (isGamePlay)
    {
        painter.drawImage(food_x, food_y, food);
        for (int i = 0; i < snakeLength; i++)
        {
            if (i == 0)
            {
                painter.drawImage(x[i], y[i], head);
            }
            else
            {
                painter.drawImage(x[i], y[i], body);
            }
        }
    }
    else
    {
        gameOver(painter);
    }
}

void snake::timerEvent(QTimerEvent* event)
{
    if (isGamePlay)
    {
        snakeMove();
        checkEatFood();
        checkCollision();
    }
    repaint();
}

void snake::keyPressEvent(QKeyEvent* event)
{
    switch (event->key())
    {
    case Qt::Key_Up:
        if (heading != moveDirection::down)
        {
            heading = moveDirection::up;
        }
        break;
    case Qt::Key_Down:
        if (heading != moveDirection::up)
        {
            heading = moveDirection::down;
        }
        break;
    case Qt::Key_Left:
        if (heading != moveDirection::right)
        {
            heading = moveDirection::left;
        }        break;
    case Qt::Key_Right:
        if (heading != moveDirection::left)
        {
            heading = moveDirection::right;
        }
        break;
    default: break;
    }
    QWidget::keyPressEvent(event);
}


snake::~snake()
= default;
