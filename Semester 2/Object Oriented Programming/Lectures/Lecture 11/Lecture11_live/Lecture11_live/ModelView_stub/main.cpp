#include "ModelView_stub.h"
#include <QtWidgets/QApplication>
#include "ShoppingBasket.h"
#include "TableWidget.h"
#include "ListWidget.h"
#include "ProductModel.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ShoppingBasket basket{};
    basket.addProduct(Product{ "Apples", 18 });
    basket.addProduct(Product{ "Butter", 16 });
    basket.addProduct(Product{ "Orange juice", 22 });
    basket.addProduct(Product{ "Surgical mask", 3 });

    ProductModel* model = new ProductModel{ basket };

    TableWidget tableWnd{model};
    tableWnd.show();

    ListWidget listWnd{model};
    listWnd.show();

    return a.exec();
}
