#include "StudentModel.h"

int StudentModel::rowCount(const QModelIndex& parent) const
{
    return this->studentsRepository.getSize();
}

int StudentModel::columnCount(const QModelIndex& parent) const
{
    return 4;
}

QVariant StudentModel::data(const QModelIndex& index, int role) const
{
    int row = index.row();
    int column = index.column();

    Student currentStudent = this->studentsRepository.getStudents()[row];

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        switch (column)
        {
        case 0:
            return QString::fromStdString(currentStudent.getName());
        
        case 1:
            return QString::fromStdString(currentStudent.getGroup());

        case 2:
            return QString::number(currentStudent.getSeminarGrade());

        case 3:
            return QString::number(currentStudent.getLabGrade());
        }
    }

    return QVariant();
}


Qt::ItemFlags StudentModel::flags(const QModelIndex& index) const
{
    return (index.column() == 0 || index.column() == 1) ? QAbstractTableModel::flags(index) : Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled | QAbstractTableModel::flags(index);
}

QVariant StudentModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return "Name";
        case 1:
            return "Group";
        case 2:
            return "Seminar grade";
        case 3:
            return "Lab grade";
        }
    }
    return QVariant();
}

bool StudentModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    int row = index.row();
    int column = index.column();
    Student& s = studentsRepository.getStudents()[row];
    if (role == Qt::EditRole) {
        switch (column)
        {
        case 2:
            s.setSeminarGrade(value.toDouble());
            break;
        case 3:
            s.setLabGrade(value.toDouble());
            break;
        default:
            break;
        }
        emit dataChanged(index, index);
        return true;
    }
    return false;
}
