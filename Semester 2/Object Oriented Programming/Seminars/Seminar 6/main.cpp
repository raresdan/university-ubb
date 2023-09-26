#include "Seminar6_913.h"
#include <QtWidgets/QApplication>
#include <QSortFilterProxyModel>
#include "TeacherWindow.h"
#include "StudentModel.h"

#include "Repository.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    Repository repo{ "students.txt" };
    StudentModel* sm = new StudentModel{ repo };

    TeacherWindow w{ sm, true };
    QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel();
    proxyModel->setSourceModel(sm);
    proxyModel->setFilterRegularExpression(QRegularExpression("913"));
    proxyModel->setFilterKeyColumn(1);
    
    TeacherWindow teacherFor913{ proxyModel,false };
    w.show();
    teacherFor913.show();

    return a.exec();
}
