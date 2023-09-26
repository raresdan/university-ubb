#include "ListWidget.h"

ListWidget::ListWidget(ProductModel* model, QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.genesListView->setModel(model);

	QObject::connect(ui.addButton, &QPushButton::clicked, this,
		[&]() {
			model->addProduct(Product{"Default", 100});
		});
}

ListWidget::~ListWidget()
{}
