#pragma once

#include <QMainWindow>
#include "ui_TableWidget.h"
#include "ProductModel.h"

class TableWidget : public QMainWindow
{
	Q_OBJECT

public:
	TableWidget(ProductModel* model, QWidget *parent = nullptr);
	~TableWidget();

private:
	Ui::TableWidgetClass ui;
};
