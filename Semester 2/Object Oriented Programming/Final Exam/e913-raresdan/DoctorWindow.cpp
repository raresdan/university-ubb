#include "DoctorWindow.h"
#include "QMessageBox"

DoctorWindow::DoctorWindow(Controller& controller, Doctor doctor, std::vector<Patient> myPatients, QWidget *parent)
	:controller{ controller }, doctor{ doctor }, QMainWindow(parent)
{
	ui.setupUi(this);
	this->setWindowTitle(QString::fromStdString(doctor.getName()));
	this->populateWindow();
}

DoctorWindow::~DoctorWindow()
{}

void DoctorWindow::populateWindow()
{
	myPatients.clear();
	this->ui.patientsListWidget->clear();
	for (auto patient : this->controller.getAllPatients())
	{
		if (patient.getSpecialisation() == doctor.getSpecialisation() || patient.getDiagnosis() == "undiagnosed")
		{
			this->ui.patientsListWidget->addItem(QString::fromStdString(patient.toString()));
			myPatients.push_back(patient);
		}
	}
	for (int i = 0; i < myPatients.size(); i++)
	{
		if (myPatients[i].getDiagnosis() != "undiagnosed")
		{
			QListWidgetItem* item = this->ui.patientsListWidget->item(i);
			QBrush brush(Qt::green);
			item->setBackground(brush);
		}
		
	}
}

void DoctorWindow::update()
{
	this->populateWindow();
}

void DoctorWindow::filter()
{
	if (this->ui.checkBox->checkState() == Qt::Checked)
	{
		this->ui.patientsListWidget->clear();
		for (auto patient : this->controller.getAllPatients())
		{
			if (patient.getSpecialisation() == doctor.getSpecialisation())
			{
				this->ui.patientsListWidget->addItem(QString::fromStdString(patient.toString()));
			}
		}
	}
	else
		this->populateWindow();
}

void DoctorWindow::add()
{
	std::string name = this->ui.namelineEdit->text().toStdString();
	std::string diagnosis = this->ui.diagnosislineEdit->text().toStdString();
	std::string specialisation = this->ui.specialisationlineEdit->text().toStdString();
	std::string doctor = this->ui.doctorlineEdit->text().toStdString();
	std::string date = this->ui.datelineEdit->text().toStdString();

	if (diagnosis == "")
		diagnosis = "undiagnosed";

	Patient newPatient{ name, diagnosis, specialisation, doctor, date };
	try
	{
		this->controller.addPatient(newPatient);
	}
	catch (std::exception ex)
	{
		QMessageBox::critical(this, "ERROR", ex.what());
	}
	this->populateWindow();
}

void DoctorWindow::updatePatient()
{
	std::string name = this->ui.namelineEdit->text().toStdString();
	std::string diagnosis = this->ui.diagnosislineEdit->text().toStdString();
	std::string specialisation = this->ui.specialisationlineEdit->text().toStdString();
	std::string doctor = this->ui.doctorlineEdit->text().toStdString();
	std::string date = this->ui.datelineEdit->text().toStdString();

	QListWidgetItem* selectedItem = this->ui.patientsListWidget->currentItem();
	if(selectedItem != nullptr)
	{
		int row = this->ui.patientsListWidget->row(selectedItem);
		if (specialisation == "")
			specialisation = this->myPatients[row].getSpecialisation();
		else if (specialisation == "ORL")
			doctor = "Tudor";
		else if (specialisation == "chirurgie")
			doctor = "Radu";
		else if (specialisation == "radiologie")
			doctor = "Mircea";
		Patient selectedPatient = this->myPatients[row];
		try
		{
			this->controller.updatePatient(selectedPatient, diagnosis, specialisation, doctor);
		}
		catch (std::exception ex)
		{
			QMessageBox::critical(this, "ERROR", ex.what());
		}
		this->populateWindow();
	}
}


