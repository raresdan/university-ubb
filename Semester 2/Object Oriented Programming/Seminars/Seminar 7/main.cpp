#include <QtWidgets/QApplication>
#include "Observer.h"
#include "ChatWindow.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	ChatSession session{};

	ChatWindow user1{ session, "Dan" };
	ChatWindow user2{ session, "Narcis" };
	ChatWindow user3{ session, "Dragos" };

	session.registerObserver(&user1);
	session.registerObserver(&user2);
	session.registerObserver(&user3);

	user1.show();
	user2.show();
	user3.show();

	app.exec();
	return 0; 
}
