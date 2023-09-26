#pragma once
#include "Controller.h"

#include <QtWidgets/QMainWindow>
#include "ui_test3.h"

class test3 : public QMainWindow
{
    Q_OBJECT

public:
    test3(Controller controller,QWidget *parent = nullptr);
    ~test3();

private:
    Controller controller;
    Ui::test3Class ui;

    void populateList();
public slots:
    void searchItem();
    void filterItems();
};
