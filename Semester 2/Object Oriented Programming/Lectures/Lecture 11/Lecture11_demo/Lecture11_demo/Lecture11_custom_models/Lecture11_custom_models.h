#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Lecture11_custom_models.h"

class Lecture11_custom_models : public QMainWindow
{
    Q_OBJECT

public:
    Lecture11_custom_models(QWidget *parent = nullptr);
    ~Lecture11_custom_models();

private:
    Ui::Lecture11_custom_modelsClass ui;
};
