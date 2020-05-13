#include "Q3TTableWidget.h"
#include "Q3TTableModel.h"

#include <QScrollBar>
#include <QHeaderView>
#include <QWheelEvent>

static const int s_defaultInitActualRowCount = 2000;
static const int s_defaultInitActualColumnCount = 2000;
static const int s_defaultInitRowCount = 2000;
static const int s_defaultInitColumnCount = 2000;
static const int s_incRowCountOneTime = 6;
static const int s_incColumnCountOneTime = 4;
Q3TTableWidget::Q3TTableWidget(AMDATATYPE dataType)
{
    m_pModel = new Q3TTableModel(dataType, this);
    m_pModel->setActualSize(s_defaultInitActualRowCount, s_defaultInitActualColumnCount);
    m_pModel->setSize(s_defaultInitRowCount, s_defaultInitColumnCount);
    setModel(m_pModel);

    init();

    //connect(m_pModel, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&, const QVector<int> &)), this, SLOT(tableDataChanged(const QModelIndex&, const QModelIndex&, const QVector<int> &)));
    connect(m_pModel, SIGNAL(actualRowColumnCountChange(int, int)), this, SLOT(tableActualRowColumnCountChange(int, int)));
}

Q3TTableWidget::~Q3TTableWidget()
{

}


void Q3TTableWidget::init()
{
    setHorizontalScrollMode(ScrollPerPixel);
    setVerticalScrollMode(ScrollPerPixel);
}

void Q3TTableWidget::actualRowColumnCount(int& rowCount, int& columnCount)
{
    if(m_pModel)
    {
        rowCount = m_pModel->actualRowCount();
        columnCount = m_pModel->actualColumnCount();
    }
    else
        Q_ASSERT(false);
}

void Q3TTableWidget::resetRowColumnCountByModelIndex(const QModelIndex &index)
{
    int oldRowCount = m_pModel->rowCount();
    int oldColumnConut = m_pModel->columnCount();
    if(index.row() > oldRowCount - s_incRowCountOneTime)
    {
        m_pModel->insertRows(oldRowCount, index.row() + s_incRowCountOneTime - oldRowCount);
    }
    if(index.column() > oldColumnConut - s_incColumnCountOneTime)
    {
        m_pModel->insertColumns(oldColumnConut, index.column() + s_incColumnCountOneTime - oldColumnConut);
    }
}

void Q3TTableWidget::resetRowColumnCountByGeometry(bool isDecrease)
{
    int oldRowConut = m_pModel->rowCount();
    int oldColumnConut = m_pModel->columnCount();
    QModelIndex index = m_pModel->index(oldRowConut - 1, oldColumnConut - 1);
    QRect rect = visualRect(index);

    QRect clientRect = geometry();
    QHeaderView* horiHV =  horizontalHeader();
    QHeaderView* vertHV =  verticalHeader();
    // make clientRect base (0, 0)
    int incWidth = clientRect.right() - clientRect.left() - (rect.right() + horiHV->height());
    int incHeight = clientRect.bottom() - clientRect.top() - (rect.bottom() + vertHV->width());
    int oneCellWidth = horiHV->defaultSectionSize();
    int oneCellHeight = vertHV->defaultSectionSize();

    int needColumnCount = static_cast<int>(ceil(static_cast<double>(incWidth)/static_cast<double>(oneCellWidth)));
    int needRowCount = static_cast<int>(ceil(static_cast<double>(incHeight)/static_cast<double>(oneCellHeight)));

    int newRowCount = oldRowConut;
    if((isDecrease || needRowCount + s_incRowCountOneTime > 0) && oldRowConut + needRowCount > m_pModel->actualRowCount())
    {
        newRowCount = oldRowConut + needRowCount + s_incRowCountOneTime;
    }
    int newColumnCount = oldColumnConut;
    if((isDecrease || needColumnCount + s_incColumnCountOneTime > 0) && oldColumnConut + needColumnCount > m_pModel->actualColumnCount())
    {
        newColumnCount = oldColumnConut + needColumnCount + s_incColumnCountOneTime;
    }

    m_pModel->resize(newRowCount, newColumnCount);
}


void Q3TTableWidget::resizeEvent(QResizeEvent * event)
{
    QTableView::resizeEvent(event);

    resetRowColumnCountByGeometry();
}

void Q3TTableWidget::scrollTo(const QModelIndex & index, ScrollHint hint)
{
    QTableView::scrollTo(index, hint);
    resetRowColumnCountByModelIndex(index);
}

void Q3TTableWidget::wheelEvent(QWheelEvent *event)
{
    QTableView::wheelEvent(event);
    if(event->delta() < 0)
        resetRowColumnCountByGeometry(false);
}

void Q3TTableWidget::currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    QTableView::currentChanged(current, previous);
    resetRowColumnCountByModelIndex(current);
}

//void Q3TTableWidget::tableDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
//{

//}

void Q3TTableWidget::tableActualRowColumnCountChange(int actualRowCount, int actualColumnCount)
{
    emit actualRowColumnCountChange(actualRowCount, actualColumnCount);
}
