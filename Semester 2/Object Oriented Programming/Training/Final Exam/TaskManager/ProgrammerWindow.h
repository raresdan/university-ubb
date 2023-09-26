#pragma once

#include <QMainWindow>
#include "ui_ProgrammerWindow.h"
#include "Programmer.h"
#include "TasksRepository.h"

class ProgrammerWindow : public QMainWindow, public Observer
{
	Q_OBJECT

public:
	ProgrammerWindow(TasksRepository& repository, Programmer programmer,QWidget *parent = nullptr);
	~ProgrammerWindow();
	
	void populate();
	void update() { this->populate(); }

private:
	Ui::ProgrammerWindowClass ui;
	Programmer programmer;
	TasksRepository& repository;

public slots:
	void addTask();
	void removeTask();
	void start();
	void toggleDone();
	void done();
};
