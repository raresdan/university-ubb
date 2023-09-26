#pragma once

#include <QMainWindow>
#include "ui_DoctorWindow.h"
#include "Controller.h"

class DoctorWindow : public QMainWindow, public Observer
{
	Q_OBJECT

public:
	DoctorWindow(Controller& controller, Doctor doctor, std::vector<Patient> myPatients = {},QWidget * parent = nullptr);
	~DoctorWindow();


	void populateWindow();
	void update();
private:
	Ui::DoctorWindowClass ui;
	Doctor doctor;
	Controller& controller;
	std::vector<Patient> myPatients;
public slots:
	void filter();
	void add();
	void updatePatient();
};
