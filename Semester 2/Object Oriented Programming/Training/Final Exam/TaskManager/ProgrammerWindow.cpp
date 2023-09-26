#include "ProgrammerWindow.h"
#include "TaskNotOpen.h"
#include "qmessagebox.h"

ProgrammerWindow::ProgrammerWindow(TasksRepository& repository, Programmer programmer,QWidget *parent)
	:repository{ repository }, programmer {programmer}, QMainWindow(parent)
{
	ui.setupUi(this);
	this->setWindowTitle(QString::fromStdString(programmer.getName()));
	this->populate();
}

ProgrammerWindow::~ProgrammerWindow()
{}

void ProgrammerWindow::populate()
{
	this->ui.taksListWidget->clear();
	for (auto task : this->repository.getAllTasks())
	{
		this->ui.taksListWidget->addItem(QString::fromStdString(task.toString()));
	}
}

void ProgrammerWindow::removeTask()
{
	QListWidgetItem* selectedItem = this->ui.taksListWidget->currentItem();
	if (selectedItem != nullptr)
	{
		int row = this->ui.taksListWidget->row(selectedItem);
		this->repository.deleteTask(row);
	}
	this->populate();
}

void ProgrammerWindow::start()
{
	QListWidgetItem* selectedItem = this->ui.taksListWidget->currentItem();
	if (selectedItem != nullptr)
	{
		int row = this->ui.taksListWidget->row(selectedItem);
		try
		{
			this->repository.startTask(row, programmer.getId());
		}
		catch (TaskNotOpen ex)
		{
			QMessageBox::critical(this, "ERROR", ex.what());
		}
	}
	this->populate();
}

void ProgrammerWindow::toggleDone()
{
	QListWidgetItem* selectedItem = this->ui.taksListWidget->currentItem();
	if (selectedItem != nullptr)
	{
		int row = this->ui.taksListWidget->row(selectedItem);
		Task currentTask = this->repository.getAllTasks()[row];
		if (currentTask.getStatus() == "in_progress" && currentTask.getId() == programmer.getId())
			this->ui.donePushButton->setVisible(true);
		else
			this->ui.donePushButton->setVisible(false);
	}
}

void ProgrammerWindow::done()
{
	QListWidgetItem* selectedItem = this->ui.taksListWidget->currentItem();
	if (selectedItem != nullptr)
	{
		int row = this->ui.taksListWidget->row(selectedItem);
		this->repository.doneTask(row, programmer.getId());

	}
	this->populate();
}

void ProgrammerWindow::addTask()
{
	std::string description = this->ui.taskLineEdit->text().toStdString();
	Task newTask{ description, "open" , 0 };
	this->repository.addTask(newTask);
	this->populate();
}