#pragma once

#include <QMainWindow>
#include "ui_AllDepartmentsWindow.h"
#include "Controller.h"

class AllDepartmentsWindow : public QMainWindow, public Observer
{
	Q_OBJECT

public:
	AllDepartmentsWindow(Controller& controller,QWidget *parent = nullptr);
	~AllDepartmentsWindow();
	void populate();
	void update() override { this->populate(); }
private:
	Ui::AllDepartmentsWindowClass ui;
	Controller& controller;
};
