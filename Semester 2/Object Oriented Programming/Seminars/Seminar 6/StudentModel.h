#pragma once

#include <QAbstractTableModel>

#include "Repository.h"

class StudentModel :
    public QAbstractTableModel
{
private:
    Repository& studentsRepository;

public:
    StudentModel(Repository& studentsRepo) : 
        studentsRepository { studentsRepo} {}

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
};

