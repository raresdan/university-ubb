#pragma once

#include <QMainWindow>
#include "ui_UserWindow.h"
#include "User.h"
#include "Observer.h"
#include "IssuesRepository.h"

class UserWindow : public QMainWindow, public Observer
{
	Q_OBJECT

public:
	UserWindow(IssuesRepository& repository, User user, QWidget *parent = nullptr);
	~UserWindow();

	void update() override;
	void displayIssues();
	void handleResolve();
private:
	Ui::UserWindowClass ui;
	User user;
	IssuesRepository& repository;
public slots:
	void deleteIssue();
	void addIssue();
	void resolveIssue();
};
