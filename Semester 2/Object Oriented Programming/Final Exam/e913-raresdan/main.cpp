#include <QtWidgets/QApplication>
#include "DoctorWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Controller controller;

    QList<DoctorWindow*> windows;
    for (auto doctor : controller.getAllDoctors())
    {
        DoctorWindow* window = new DoctorWindow{ controller, doctor };
        windows.append(window);
    }

    for (auto window : windows)
    {
        controller.registerObserver(window);
        window->show();
    }

    return a.exec();
}
