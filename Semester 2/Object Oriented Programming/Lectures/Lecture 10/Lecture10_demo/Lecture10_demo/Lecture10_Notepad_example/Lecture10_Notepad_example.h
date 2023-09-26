#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Lecture10_Notepad_example.h"

class Lecture10_Notepad_example : public QMainWindow
{
    Q_OBJECT

public:
    Lecture10_Notepad_example(QWidget *parent = nullptr);
    ~Lecture10_Notepad_example();

private:
    Ui::Lecture10_Notepad_exampleClass ui;
};
