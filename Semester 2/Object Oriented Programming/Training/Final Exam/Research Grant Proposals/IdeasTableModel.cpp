#include "IdeasTableModel.h"

int IdeasTableModel::rowCount(const QModelIndex& parent) const
{
    return this->controller.getIdeas().size();
}

int IdeasTableModel::columnCount(const QModelIndex& parent) const
{
    return 5;
}

QVariant IdeasTableModel::data(const QModelIndex& index, int role) const
{
    int row = index.row();
    int column = index.column();
    Idea currentIdea = this->controller.getIdeas()[row];

    if (role == Qt::DisplayRole)
    {
        switch (column)
        {
			case 0:
				return QString::fromStdString(currentIdea.getTitle());
			case 1:
				return QString::fromStdString(currentIdea.getDescription());
			case 2:
				return QString::fromStdString(currentIdea.getStatus());
			case 3:
				return QString::fromStdString(currentIdea.getCreator());
			case 4:
				return QString::number(currentIdea.getDuration());
			default:
				break;
		}
	}

	return QVariant();
}

QVariant IdeasTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if(role == Qt::DisplayRole)
		if(orientation == Qt::Horizontal)
			switch (section)
			{
				case 0:
					return QString("Title");
				case 1:
					return QString("Description");
				case 2:
					return QString("Status");
				case 3:
					return QString("Creator");
				case 4:
					return QString("Duration");
				default:
					break;
			}
	return QVariant();
}

void IdeasTableModel::addIdea(Idea& idea)
{
	beginInsertRows(QModelIndex(), this->controller.getIdeas().size(), this->controller.getIdeas().size());
	this->controller.addIdea(idea);
	endInsertRows();
}

void IdeasTableModel::reviseIdea(int indexOfIdea)
{
	controller.acceptIdea(indexOfIdea);
	QModelIndex topLeft = createIndex(indexOfIdea, 0);
	QModelIndex bottomRight = createIndex(indexOfIdea, columnCount() - 1);
	emit dataChanged(topLeft, bottomRight);
}

std::vector<Idea> IdeasTableModel::acceptedIdeas(Researcher researcher)
{
	std::vector<Idea> acceptedIdeas = {};
	for (auto idea : controller.getIdeas())
	{
		if (idea.getStatus() == "accepted")
		{
			if (researcher.getName() == idea.getCreator())
				acceptedIdeas.push_back(idea);
		}
	}

	return acceptedIdeas;
}
