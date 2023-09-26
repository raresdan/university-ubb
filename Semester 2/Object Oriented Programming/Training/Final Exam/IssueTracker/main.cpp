#include "IssueTracker.h"
#include "IssuesRepository.h"
#include "UserWindow.h"
#include "Test.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    Test testing;
    testing.testAll();

    QApplication a(argc, argv);
    
    IssuesRepository repository;
    QList<UserWindow*> userWindows;

    for (auto currentUser : repository.getAllUsers())
    {
        UserWindow* userWindow = new UserWindow{ repository, currentUser }; 
        userWindows.append(userWindow); 
    }

    for (auto userWindow : userWindows)
    {
        repository.registerObserver(userWindow);
        userWindow->show();
    }

    return a.exec();
}
