#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Lecture12_demo.h"

class Lecture12_demo : public QMainWindow
{
    Q_OBJECT

public:
    Lecture12_demo(QWidget *parent = nullptr);
    ~Lecture12_demo();

private:
    Ui::Lecture12_demoClass ui;
};
