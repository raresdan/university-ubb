#include "Observer_stub.h"
#include <QtWidgets/QApplication>
#include "ShoppingBasketWidget.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	ShoppingBasket basket{};
	basket.addProduct(Product{ "Apples", 18 });
	basket.addProduct(Product{ "Butter", 16 });
	basket.addProduct(Product{ "Orange juice", 22 });
	basket.addProduct(Product{ "Surgical mask", 3 });

	ShoppingBasketWidget w1{basket};
	ShoppingBasketWidget w2{basket};
	ShoppingBasketWidget w3{basket};

	basket.addObserver(&w1);
	basket.addObserver(&w2);
	basket.addObserver(&w3);

	w1.show();
	w2.show();
	w3.show();

	return a.exec();
}
