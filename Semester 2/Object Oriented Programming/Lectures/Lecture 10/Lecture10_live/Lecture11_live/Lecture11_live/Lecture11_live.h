#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Lecture11_live.h"

class Lecture11_live : public QMainWindow
{
    Q_OBJECT

public:
    Lecture11_live(QWidget *parent = nullptr);
    ~Lecture11_live();

private:
    Ui::Lecture11_liveClass ui;
};
