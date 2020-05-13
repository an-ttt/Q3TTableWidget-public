#ifndef Q3TABSTRACTTABLEMODEL_H
#define Q3TABSTRACTTABLEMODEL_H

#include <QAbstractTableModel>

class Q3TAbstractTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    Q3TAbstractTableModel()
    {

    }
    ~Q3TAbstractTableModel() override
    {

    }

    Qt::ItemFlags flags(const QModelIndex &index) const override
    {
        Q_UNUSED(index)
        return Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable;
    }


    virtual int actualRowCount() const = 0;
    virtual int actualColumnCount() const = 0;
    virtual void setActualSize(int rowCount, int columnCount) = 0;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override = 0;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override = 0;

    virtual void setSize(int rowCount, int columnCount) = 0;
    virtual void resize(int rowCount, int columnCount) = 0;

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override = 0;
    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override = 0;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole)const override = 0;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override = 0;

};


#endif // Q3TABSTRACTTABLEMODEL_H
