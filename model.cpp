#include "model.h"

#include <QFile>
#include <QMap>

Model::Model(QObject* parent, const QVector<bool>* hChecked, const QVector<bool>* vChecked)
    : QAbstractTableModel(parent)
    , m_hChecked(hChecked)
    , m_vChecked(vChecked)
{
    //    QFile file("Data.data");
    //    if (file.open(QFile::ReadOnly)) {
    //        QDataStream in(&file);
    //        in >> m_row;
    //        in >> m_column;
    //        in >> m_data;
    //    }
}

Model::~Model()
{
    //    QFile file("Data.data");
    //    if (file.open(QFile::WriteOnly)) {
    //        QDataStream out(&file);
    //        out << m_row;
    //        out << m_column;
    //        out << m_data;
    //    }
}

int Model::rowCount(const QModelIndex& /*parent*/) const { return m_row; }

int Model::columnCount(const QModelIndex& /*parent*/) const { return m_column; }

QVariant Model::data(const QModelIndex& index, int role) const
{
    switch (role) {
    case Qt::DisplayRole:
    case Qt::EditRole:
        return m_data[index.row()][index.column()];
    case Qt::TextAlignmentRole:
        return Qt::AlignCenter;
    default:
        return QVariant();
    }
}

bool Model::setData(const QModelIndex& index, const QVariant& value, int role)
{
    switch (role) {
    case Qt::DisplayRole:
    case Qt::EditRole:
        m_data[index.row()][index.column()] = value.toInt();
        return true;
    default:
        return false;
    }
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const
{

    switch (role) {
    case Qt::DisplayRole:
        return QString(orientation == Qt::Horizontal
                ? "C%1"
                : (m_vChecked ? "       R%1" : "R%1")) // spase to checkbox
            .arg(++section);
    case Qt::TextAlignmentRole:
        return orientation == Qt::Horizontal
            ? static_cast<int>(Qt::AlignCenter)
            : static_cast<int>(Qt::AlignLeft | Qt::AlignVCenter);
    default:
        break;
    }
    return QVariant();
}

Qt::ItemFlags Model::flags(const QModelIndex& index) const
{
    Qt::ItemFlags flags = Qt::ItemIsEditable;
    bool enabled = false;
    if (m_hChecked && m_vChecked)
        enabled = m_hChecked->value(index.column()) & m_vChecked->value(index.row());
    else if (m_hChecked)
        enabled = m_hChecked->value(index.column());
    else if (m_vChecked)
        enabled = m_vChecked->value(index.row());
    else
        enabled = true;
    return flags | (enabled ? Qt::ItemIsEnabled | Qt::ItemIsSelectable : Qt::NoItemFlags);
}

void Model::onChecked(int index, int orientation)
{
    if (orientation == Qt::Horizontal)
        emit dataChanged(createIndex(0, index), createIndex(m_row - 1, index), { Qt::DisplayRole });
    else
        emit dataChanged(createIndex(index, 0), createIndex(index, m_column - 1), { Qt::DisplayRole });
}

void Model::setRowCount(int row)
{
    if (m_row < row && insertRows(m_row, row - 1))
        m_row = row;
    else if (m_row > row && removeRows(row, m_row - 1))
        m_row = row;
}

void Model::setColumnCount(int column)
{
    if (m_column < column && insertColumns(m_column, column - 1))
        m_column = column;
    else if (m_column > column && removeColumns(column, m_column - 1))
        m_column = column;
}

bool Model::insertRows(int row, int count, const QModelIndex& parent)
{
    beginInsertRows(parent, row, count);
    m_data.resize(count + 1);
    for (QVector<int>& data : m_data)
        data.resize(m_column);
    endInsertRows();
    return true;
}

bool Model::removeRows(int row, int count, const QModelIndex& parent)
{
    beginRemoveRows(parent, row, count);
    m_data.resize(row);
    for (QVector<int>& data : m_data)
        data.resize(m_column);
    endRemoveRows();
    return true;
}

bool Model::insertColumns(int column, int count, const QModelIndex& parent)
{
    beginInsertColumns(parent, column, count);
    for (QVector<int>& data : m_data)
        data.resize(count + 1);
    endInsertColumns();
    return true;
}

bool Model::removeColumns(int column, int count, const QModelIndex& parent)
{
    beginRemoveColumns(parent, column, count);
    for (QVector<int>& data : m_data)
        data.resize(column);
    endRemoveColumns();
    return true;
}
