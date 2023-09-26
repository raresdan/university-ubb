#include "test3.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controller controller{ "D:\\_DOCUMENTE_RARES\\Desktop\\Semester 2\\Object Oriented Programming\\Local Tests\\test3\\items.txt" };
    test3 gui{controller};
    gui.show();
    return a.exec();
}
