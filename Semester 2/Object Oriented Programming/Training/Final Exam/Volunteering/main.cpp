#include "DepartmentWindow.h"
#include "AllDepartmentsWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    Controller controller;

    QList<DepartmentWindow*> departmentWindows;
    for (auto department : controller.getAllDepartments())
    {
        DepartmentWindow* departmentWindow = new DepartmentWindow{ controller, department };
        departmentWindows.append(departmentWindow);
    }

    for (auto departmentWindow : departmentWindows)
    {
        controller.registerObserver(departmentWindow);
        departmentWindow->show();
    }
    
    AllDepartmentsWindow* allWindow = new AllDepartmentsWindow{ controller };
    controller.registerObserver(allWindow);
    allWindow->show();

    return a.exec();
}
