#include "TableWidget.h"

TableWidget::TableWidget(ProductModel* model, QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.genesTableView->setModel(model);

	QObject::connect(ui.addButton, &QPushButton::clicked, this,
		[&]() {
			model->addProduct(Product{ "Default", 100 });
		});
}

TableWidget::~TableWidget()
{}
