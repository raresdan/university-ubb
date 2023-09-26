#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Volunteering.h"

class Volunteering : public QMainWindow
{
    Q_OBJECT

public:
    Volunteering(QWidget *parent = nullptr);
    ~Volunteering();

private:
    Ui::VolunteeringClass ui;
};
