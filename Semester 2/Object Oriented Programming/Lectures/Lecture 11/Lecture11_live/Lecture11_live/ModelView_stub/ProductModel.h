#pragma once
#include <qabstractitemmodel.h>
#include "ShoppingBasket.h"

class ProductModel :
    public QAbstractTableModel
{
private:
    ShoppingBasket& basket;

public:
    ProductModel(ShoppingBasket& b, QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    void addProduct(const Product& p);
    void clearProducts();
};

