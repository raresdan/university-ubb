#pragma once
#include <qabstractitemmodel.h>
#include "Controller.h"

class IdeasTableModel :
    public QAbstractTableModel
{
    public:
	    Controller& controller;

        IdeasTableModel(Controller& controller): controller{controller} {}

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        int columnCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

        void addIdea(Idea& idea);
        void reviseIdea(int indexOfIdea);

        std::vector<Idea> acceptedIdeas(Researcher researcher);
};

