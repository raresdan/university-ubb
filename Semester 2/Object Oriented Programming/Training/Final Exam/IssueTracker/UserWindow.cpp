#include "UserWindow.h"
#include "QMessageBox"

UserWindow::UserWindow(IssuesRepository& repository, User user, QWidget *parent)
	: repository{ repository }, user {user}, QMainWindow(parent)
{
	ui.setupUi(this);
	this->setWindowTitle(QString::fromStdString(user.getName() + "-" + user.getType()));
	this->displayIssues();

	if (user.getType() == "programmer")
	{
		this->ui.addPushButton->hide();
		this->ui.descriptionLineEdit->hide();
		this->handleResolve();
	}
	else if(user.getType() == "tester")
		this->ui.resolvePushButton->hide();
}

UserWindow::~UserWindow()
{}

void UserWindow::update()
{	
	this->displayIssues();
}

void UserWindow::displayIssues()
{
	this->ui.issueListWidget->clear();
	for (auto currentIssue : this->repository.getAllIssues())
	{
		this->ui.issueListWidget->addItem(QString::fromStdString(currentIssue.toString()));
	}
}

void UserWindow::handleResolve()
{
	QListWidgetItem* selectedItem = this->ui.issueListWidget->currentItem();
	if (selectedItem != nullptr)
	{
		int row = this->ui.issueListWidget->row(selectedItem);
		if (this->repository.getAllIssues()[row].getStatus() == "open")
		{
			this->ui.resolvePushButton->setEnabled(true);
		}
		else
		{
			this->ui.resolvePushButton->setEnabled(false);
		}
	}
}

void UserWindow::addIssue()
{
	std::string description = this->ui.descriptionLineEdit->text().toStdString();
	Issue issueToAdd{ description, "open", user.getName(), "-" };
	try
	{
		this->repository.addIssue(issueToAdd);
	}
	catch (std::exception ex)
	{
		QMessageBox::critical(this, "ERROR", ex.what());
	}
	this->displayIssues();
}

void UserWindow::resolveIssue()
{
	QListWidgetItem* selectedItem = this->ui.issueListWidget->currentItem();
	if (selectedItem != nullptr)
	{
		int row = this->ui.issueListWidget->row(selectedItem);
		if (this->repository.getAllIssues()[row].getStatus() == "open")
		{
			Issue selectedIssue = this->repository.getAllIssues()[row];
			this->repository.resolveIssue(row, user.getName());
		}
	}
	this->displayIssues();
}

void UserWindow::deleteIssue()
{
	QListWidgetItem* selectedItem = this->ui.issueListWidget->currentItem();
	if (selectedItem != nullptr)
	{
		int row = this->ui.issueListWidget->row(selectedItem);
		if (this->repository.getAllIssues()[row].getStatus() == "closed")
		{
			this->ui.issueListWidget->takeItem(row);
			this->repository.removeIssue(row);
			delete selectedItem;
		}
	}
}