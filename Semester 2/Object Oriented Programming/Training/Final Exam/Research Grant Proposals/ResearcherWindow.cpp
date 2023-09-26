#include "ResearcherWindow.h"
#include <QMessageBox>
#include <QTextEdit>
#include <fstream>


ResearcherWindow::ResearcherWindow(IdeasTableModel* model ,Researcher researcher, QWidget *parent)
	: model{ model } , researcher{researcher}, QMainWindow(parent)
{
	ui.setupUi(this);

	ui.ideasTableView->setModel(model);
	this->setWindowTitle(QString::fromStdString(researcher.getName() + " - " + researcher.getPosition()));
	if (researcher.getPosition() != "senior")
	{
		ui.pushButton_2->hide();
		ui.pushButton_5->hide();
	}
}

void ResearcherWindow::addIdea()
{
	std::string title = ui.titleLineEdit->text().toStdString();
	std::string description = ui.descrLineEdit->text().toStdString();
	int duration = ui.durLineEdit->text().toInt();

	Idea idea{ title, description, "proposed", researcher.getName(), duration };
	try
	{
		model->addIdea(idea);
	}
	catch (std::exception& e)
	{
		QMessageBox::critical(this, "Error", e.what());
	}
}

ResearcherWindow::~ResearcherWindow()
{}

void ResearcherWindow::acceptIdea()
{
	int index = ui.ideasTableView->currentIndex().row();
	try
	{
		model->reviseIdea(index);
	}
	catch (std::exception& e)
	{
		QMessageBox::critical(this, "Error", e.what());
	}
}

void ResearcherWindow::develop()
{
	std::vector<Idea> ideas = model->acceptedIdeas(researcher);
	for (auto idea : ideas)
	{
		QWidget* widget = new QWidget();
		QLayout* layout = new QVBoxLayout();
		QTextEdit* edit = new QTextEdit(QString::fromStdString(idea.getDescription()));
		edit->setObjectName("edit");
		layout->addWidget(edit);
		widget->setLayout(layout);
		widget->show();
	}
}

void ResearcherWindow::saveIdea()
{
	for (auto idea : model->acceptedIdeas(researcher))
	{
		std::ofstream outputStream{ idea.filename };
		outputStream << idea.getDescription();
		outputStream.close();
	}
}

void ResearcherWindow::saveAll()
{
	for(auto researcher: model->controller.getResearchers())
		for (auto idea : model->acceptedIdeas(researcher))
		{
			std::ofstream outputStream{ "accepted.txt" };
			outputStream << idea.toString();
			outputStream.close();
		}
}
