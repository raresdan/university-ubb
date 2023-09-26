#include "Controller.h"
#include "ResearcherWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controller controller;

    IdeasTableModel* model = new IdeasTableModel{ controller };

    QList<ResearcherWindow*> windows;
    for (auto researcher : controller.getResearchers())
    {
		ResearcherWindow* window = new ResearcherWindow{ model, researcher };
		window->show();
	}


    return a.exec();
}
