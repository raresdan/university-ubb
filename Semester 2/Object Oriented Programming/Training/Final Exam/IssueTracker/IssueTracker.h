#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_IssueTracker.h"

class IssueTracker : public QMainWindow
{
    Q_OBJECT

public:
    IssueTracker(QWidget *parent = nullptr);
    ~IssueTracker();

private:
    Ui::IssueTrackerClass ui;
};
