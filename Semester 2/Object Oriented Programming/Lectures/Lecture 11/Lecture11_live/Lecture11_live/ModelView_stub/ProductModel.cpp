#include "ProductModel.h"
#include <QBrush>
#include <QColor>

ProductModel::ProductModel(ShoppingBasket& b, QObject* parent):basket{b}
{
}

int ProductModel::rowCount(const QModelIndex& parent) const
{
	return this->basket.getSize();
}

int ProductModel::columnCount(const QModelIndex& parent) const
{
	return 2;
}

QVariant ProductModel::data(const QModelIndex& index, 
								int role) const
{
	int row = index.row();
	int col = index.column();

	Product& p = basket.getAll()[row];

	if (role == Qt::DisplayRole)
		switch (col)
		{
		case 0:
			return QString::fromStdString(p.getName());
		case 1:
			return QString::number(p.getPrice());
		default:
			break;
		}

	if (role == Qt::BackgroundRole)
	{
		if (row % 2 == 0)
			return QBrush(QColor(220, 220, 220));
	}

	return QVariant();
}

void ProductModel::addProduct(const Product& p)
{
	int n = this->basket.getSize();

	this->beginInsertRows(QModelIndex{}, n, n);

	this->basket.addProduct(p);

	this->endInsertRows();
}

void ProductModel::clearProducts()
{
}
