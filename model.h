#ifndef MYTABLEMODEL_H
#define MYTABLEMODEL_H

#include <QAbstractTableModel>

class Model : public QAbstractTableModel {
    Q_OBJECT

public:
    Model(QObject* parent = nullptr,
        const QVector<bool>* hChecked = nullptr,
        const QVector<bool>* vChecked = nullptr);
    ~Model() override;
    // QAbstractItemModel interface
    int rowCount(const QModelIndex& parent) const override;
    int columnCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    void onChecked(int index, int orientation);

    void setRowCount(int row);
    void setColumnCount(int column);

    bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
    bool insertColumns(int column, int count, const QModelIndex& parent = QModelIndex()) override;
    bool removeColumns(int column, int count, const QModelIndex& parent = QModelIndex()) override;

private:
    QVector<QVector<int>> m_data;
    const QVector<bool>* m_hChecked;
    const QVector<bool>* m_vChecked;
    int m_row = 0;
    int m_column = 0;
};

#endif // MYTABLEMODEL_H
