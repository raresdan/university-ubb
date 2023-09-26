#pragma once
#include <qobject.h>
#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QListWidget>
#include "AdministratorService.h"
#include "UserService.h"

class Gui :
    public QObject
{
    Q_OBJECT
private:
    AdministratorService administratorService;
    UserService userService;
    int argumentCount;
    char** argumentVector;

public:
    Gui(AdministratorService initialAdminService, UserService initialUserService, int initialArgumentCount = 0, char** initialArgumentVector = nullptr);
    int startScreen();
    
    int printAdminMenu();
    int printUserMenu();
    
    int addTutorial();
    int removeTutorialFromAdmin();
    int updateTutorial();
    int displayAllTutorials();
    
    int searchTutorialsByPresenter();
    int removeTutorialFromWatchlist();
    int displayWatchlist();
    void detailsOfTutorial(const Tutorial& tutorial, QLabel& tutorialLabel);
    int saveWatchlistToFile();
    int openWatchlist();

    void displayError(const char* message);

private slots:
    
    void on_addAdminButton_clicked();
    void on_removeAdminButton_clicked();
    void on_updateAdminButton_clicked();

    void handleUserMode();
    void handleAdminMode();

};

