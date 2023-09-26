#include "TeacherWindow.h"

TeacherWindow::TeacherWindow(QAbstractItemModel* studentModel, bool isMain, QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.studentTableView->setModel(studentModel);
	isMainTeacher = isMain;
}

TeacherWindow::~TeacherWindow()
{}
