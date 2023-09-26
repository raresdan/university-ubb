#include "ProgrammerWindow.h"
#include "TasksRepository.h"
#include "Tests.h"
#include <QtWidgets/QApplication>
#include <qmessagebox.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    Tests testing;
    testing.testAll();
    QMessageBox messageBox;
    messageBox.setWindowTitle("Tests info");
    messageBox.setText("All tests passed succesfully!");
    messageBox.exec();

    TasksRepository repository;

    QList<ProgrammerWindow*> windows;
    for (auto programmer : repository.getAllProgrammers())
    {
        ProgrammerWindow* window = new ProgrammerWindow{ repository, programmer };
        windows.append(window);
    }

    for (auto window : windows)
    {
        repository.registerObserver(window);
        window->show();
    }

    return a.exec();
}
