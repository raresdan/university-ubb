#pragma once

#include <QMainWindow>
#include "ui_ListWidget.h"
#include "ProductModel.h"

class ListWidget : public QMainWindow
{
	Q_OBJECT

public:
	ListWidget(ProductModel* model, QWidget *parent = nullptr);
	~ListWidget();

private:
	Ui::ListWidgetClass ui;
};
