//
// Created by 17246 on 2025/8/5.
//

#include <QApplication>
#include "widget.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    widget w;
    w.resize(600,200);
    w.show();
    return QApplication::exec();
}
