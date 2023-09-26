#pragma once

#include <QMainWindow>
#include "ui_ResearcherWindow.h"
#include "IdeasTableModel.h"
#include "Researcher.h"

class ResearcherWindow : public QMainWindow
{
	Q_OBJECT

public:
	ResearcherWindow(IdeasTableModel* model, Researcher researcher, QWidget *parent = nullptr);
	~ResearcherWindow();

private:
	Ui::ResearcherWindowClass ui;
	IdeasTableModel* model;
	Researcher researcher;

public slots:
	void addIdea();
	void acceptIdea();
	void develop();
	void saveIdea();
	void saveAll();
};
