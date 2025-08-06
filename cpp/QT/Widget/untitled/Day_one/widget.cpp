//
// Created by 17246 on 2025/8/5.
//

#include <QFrame>
#include <QGridLayout>
#include <QPushButton>
#include <QApplication>
#include "widget.h"

using namespace std;

widget::widget(QWidget* parent): QWidget(parent)
{
    auto* frame1 = new QFrame(this);
    frame1->setFrameStyle(QFrame::Box);
    frame1->setCursor(Qt::SizeAllCursor);
    auto* frame2 = new QFrame(this);
    frame2->setFrameStyle(QFrame::Box);
    frame2->setCursor(Qt::WaitCursor);
    auto* frame3 = new QFrame(this);
    frame3->setFrameStyle(QFrame::Box);
    frame3->setCursor(Qt::PointingHandCursor);
    auto* grid = new QGridLayout(this);
    grid->addWidget(frame1, 0, 0);
    grid->addWidget(frame2, 0, 1);
    grid->addWidget(frame3, 0, 2);
    auto* button = new QPushButton("quit", this);
    connect(button, &QPushButton::clicked,qApp, QApplication::quit);
}

widget::~widget()
{
}
