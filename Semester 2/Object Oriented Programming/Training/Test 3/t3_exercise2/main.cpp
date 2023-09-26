#include "t3_exercise2.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controller controller{ "D:\\_DOCUMENTE_RARES\\Desktop\\Semester 2\\Object Oriented Programming\\Training\\Test 3\\t3_exercise2\\items.txt" };
    t3_exercise2 gui{controller};
    gui.show();
    return a.exec();
}
