#pragma once

#include <QMainWindow>
#include <QAbstractItemModel>
#include "ui_TeacherWindow.h"
#include "StudentModel.h"

class TeacherWindow : public QMainWindow
{
	Q_OBJECT

public:
	TeacherWindow(QAbstractItemModel* studentModel, bool isMain, QWidget *parent = nullptr);
	~TeacherWindow();

private:
	Ui::TeacherWindowClass ui;
	bool isMainTeacher;
};
