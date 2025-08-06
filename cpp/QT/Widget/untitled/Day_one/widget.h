//
// Created by 17246 on 2025/8/5.
//

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class widget : public QWidget
{
    Q_OBJECT

public:
    explicit widget(QWidget* parent = nullptr);
    ~widget() override;
};


#endif //WIDGET_H
