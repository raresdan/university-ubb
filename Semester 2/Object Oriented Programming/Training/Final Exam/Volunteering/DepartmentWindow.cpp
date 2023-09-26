#include "DepartmentWindow.h"
#include <qmessagebox.h>

DepartmentWindow::DepartmentWindow(Controller& controller, Department department, QWidget *parent)
	: controller{ controller },department {department}, QMainWindow(parent)
{
	ui.setupUi(this);
	this->setWindowTitle(QString::fromStdString(this->department.getName()));
	this->ui.descriptionLabel->setText(QString::fromStdString(this->department.getDescription()));
	this->populateWindow();
}

DepartmentWindow::~DepartmentWindow()
{}

void DepartmentWindow::populateWindow()
{
	this->ui.unassignedListWidget->clear();
	this->ui.volunteersListWidget->clear();
	for (auto currentVolunteer : controller.getAllVolunteers())
	{
		if (currentVolunteer.getDepartment() == this->department.getName())
			this->ui.volunteersListWidget->addItem(QString::fromStdString(currentVolunteer.toString()));
		else if (currentVolunteer.getDepartment() == "-")
			this->ui.unassignedListWidget->addItem(QString::fromStdString(currentVolunteer.toString()));
	}
}

void DepartmentWindow::assignVolunteer()
{
	QListWidgetItem* selectedItem = this->ui.unassignedListWidget->currentItem();
	if (selectedItem != nullptr)
	{
		int row = this->ui.unassignedListWidget->row(selectedItem);
		this->controller.assignVolunteer(row, this->department.getName());
	}
	this->populateWindow();
}

void DepartmentWindow::addVolunteer()
{
	std::string name = this->ui.nameLineEdit->text().toStdString();
	std::string email = this->ui.emailLineEdit->text().toStdString();
	std::string interests = this->ui.interestsLineEdit->text().toStdString();

	std::vector<std::string> interestsVector;
	interestsVector.push_back(interests);
	Volunteer volunteerToAdd{ name, email, interestsVector, "-" };
	try
	{
		this->controller.addVolunteer(volunteerToAdd);
	}
	catch (std::exception ex)
	{
		QMessageBox::critical(this, "ERROR", ex.what());
	}
	this->populateWindow();
}