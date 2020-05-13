#ifndef Q3TTABLEMODEL_H
#define Q3TTABLEMODEL_H

#include <QColor>
#include "GlobalTypes.h"
#include "Q3TAbstractTableModel.h"

class ArmaMatrix;
class Q3TTableModel : public Q3TAbstractTableModel
{
    Q_OBJECT

public:
    explicit Q3TTableModel(AMDATATYPE dataType, QObject *parent = nullptr);
    ~Q3TTableModel() override;

    int actualRowCount() const override;
    int actualColumnCount() const override;
    void setActualSize(int rowCount, int columnCount) override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    void setSize(int rowCount, int columnCount) override;
    void resize(int rowCount, int columnCount) override;

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole)const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

Q_SIGNALS:
    void actualRowColumnCountChange(int actualRowCount, int actualColumnCount);

private:
   ArmaMatrix* m_pArmaMatrix;
   QObject* m_parent;

   int m_virtualRowCount;
   int m_virtualColumnCount;
};


#endif // Q3TTABLEMODEL_H
