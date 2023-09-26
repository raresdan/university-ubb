#pragma once
#include "Controller.h"

#include <QtWidgets/QMainWindow>
#include "ui_t3_exercise1.h"

class t3_exercise1 : public QMainWindow
{
    Q_OBJECT

public:
    t3_exercise1(Controller& controller, QWidget *parent = nullptr);
    ~t3_exercise1();

private:
    Controller& controller;
    Ui::t3_exercise1Class ui;

    void populateList();
public slots:
    void totalDuration();
};
