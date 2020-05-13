#ifndef Q3TTableWidget_H
#define Q3TTableWidget_H

#include <QTableView>
#include "GlobalTypes.h"

class Q3TAbstractTableModel;
class Q3TTableWidget : public QTableView
{
    Q_OBJECT

public:
    Q3TTableWidget(AMDATATYPE dataType);
    ~Q3TTableWidget() override;

    void actualRowColumnCount(int& actualRowCount, int& actualColumnCount);

protected:
    void init();
    void resetRowColumnCountByModelIndex(const QModelIndex &index);
    void resetRowColumnCountByGeometry(bool isDecrease = true);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void scrollTo (const QModelIndex & index, ScrollHint hint = EnsureVisible) override;
    void wheelEvent(QWheelEvent *) override;
    void currentChanged(const QModelIndex &current, const QModelIndex &previous) override;

Q_SIGNALS:
    void actualRowColumnCountChange(int actualRowCount, int actualColumnCount);

private Q_SLOTS:
    //void tableDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles = QVector<int>());
    void tableActualRowColumnCountChange(int actualRowCount, int actualColumnCount);

private:
    Q3TAbstractTableModel *m_pModel;
};

#endif // Q3TTableWidget_H
