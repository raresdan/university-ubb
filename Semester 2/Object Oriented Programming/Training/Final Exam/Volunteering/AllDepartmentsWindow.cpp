#include "AllDepartmentsWindow.h"

AllDepartmentsWindow::AllDepartmentsWindow(Controller& controller,QWidget *parent)
	:controller{ controller }, QMainWindow(parent)
{
	ui.setupUi(this);
	this->setWindowTitle("ALL DEPARTMENTS");
	this->populate();
}

AllDepartmentsWindow::~AllDepartmentsWindow()
{}

void AllDepartmentsWindow::populate()
{
	this->ui.departmentsListWidget->clear();
	for (auto department : this->controller.getAllDepartments())
	{
		int total = 0;
		for (auto volunteer : this->controller.getAllVolunteers())
		{
			if (volunteer.getDepartment() == department.getName())
				total++;
		}
		
		this->ui.departmentsListWidget->addItem(QString::fromStdString(department.getName() + ": " + std::to_string(total)));
	}
}
