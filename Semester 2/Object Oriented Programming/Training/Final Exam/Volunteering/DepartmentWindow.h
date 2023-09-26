#pragma once

#include <QMainWindow>
#include "ui_DepartmentWindow.h"
#include "Department.h"
#include "Controller.h"

class DepartmentWindow : public QMainWindow, public Observer
{
	Q_OBJECT

public:
	DepartmentWindow(Controller& controller, Department department, QWidget *parent = nullptr);
	~DepartmentWindow();

	void populateWindow();
	void update() override
	{
		this->populateWindow();
	}

private:
	Ui::DepartmentWindowClass ui;
	Department department;
	Controller& controller;

public slots:
	void addVolunteer();
	void assignVolunteer();
};
