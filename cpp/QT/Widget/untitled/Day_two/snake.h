//
// Created by 17246 on 2025/8/6.
//

#ifndef SNAKE_H
#define SNAKE_H

#include <QWidget>

class snake final : public QWidget
{
    Q_OBJECT

public:
    explicit snake(QWidget* parent = nullptr);
    ~snake() override;

protected:
    void paintEvent(QPaintEvent* event) override;
    void timerEvent(QTimerEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

    enum class moveDirection
    {
        up,
        down,
        left,
        right
    };

private:
    QImage head;
    QImage body;
    QImage food;

    static constexpr int WIDGET_WIDTH = 600;
    static constexpr int WIDGET_HEIGHT = 600;
    static constexpr int BODY_SIZE = 15;
    static constexpr int SNAKE_MAX_LENGTH = WIDGET_WIDTH * WIDGET_HEIGHT / (BODY_SIZE * BODY_SIZE);

    int timerId;
    int food_x;
    int food_y;
    int x[SNAKE_MAX_LENGTH];
    int y[SNAKE_MAX_LENGTH];
    int snakeLength;
    moveDirection heading;
    bool isGamePlay;

    void initGame();
    void initFood();
    void snakeMove();
    void checkEatFood();
    void checkCollision();
    void gameOver(QPainter&);
};



#endif //SNAKE_H
