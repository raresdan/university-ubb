#include "t3_exercise1.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controller controller{ "D:\\_DOCUMENTE_RARES\\Desktop\\Semester 2\\Object Oriented Programming\\Training\\Test 3\\t3_exercise1\\entitites.txt" };
    t3_exercise1 gui{controller};
    gui.show();
    return a.exec();
}
