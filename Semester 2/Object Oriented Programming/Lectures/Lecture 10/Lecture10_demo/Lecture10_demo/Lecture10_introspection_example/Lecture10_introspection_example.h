#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Lecture10_introspection_example.h"

class Lecture10_introspection_example : public QMainWindow
{
    Q_OBJECT

public:
    Lecture10_introspection_example(QWidget *parent = nullptr);
    ~Lecture10_introspection_example();

private:
    Ui::Lecture10_introspection_exampleClass ui;
};
