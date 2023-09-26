#pragma once
#include "Controller.h"

#include <QtWidgets/QMainWindow>
#include "ui_t3_exercise2.h"

class t3_exercise2 : public QMainWindow
{
    Q_OBJECT

public:
    t3_exercise2(Controller controller,QWidget *parent = nullptr);
    ~t3_exercise2();

private:
    Controller controller;
    Ui::t3_exercise2Class ui;
    void populateList();
public slots:
    void deleteItem();
    void filterItems();
};
