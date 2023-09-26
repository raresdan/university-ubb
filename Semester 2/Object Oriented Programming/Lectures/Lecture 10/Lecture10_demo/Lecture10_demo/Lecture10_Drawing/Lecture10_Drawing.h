#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Lecture10_Drawing.h"

class Lecture10_Drawing : public QMainWindow
{
    Q_OBJECT

public:
    Lecture10_Drawing(QWidget *parent = nullptr);
    ~Lecture10_Drawing();

private:
    Ui::Lecture10_DrawingClass ui;
};
