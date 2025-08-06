//
// Created by 17246 on 2025/8/5.
//

#include <QApplication>
#include "snake.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    snake sw;
    sw.show();
    return QApplication::exec();
}
