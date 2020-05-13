#include "Q3TTableModel.h"
#include "ArmaMatrix.h"

Q3TTableModel::Q3TTableModel(AMDATATYPE dataType, QObject *parent)
{
    m_parent = parent;
    m_pArmaMatrix = new ArmaMatrix(dataType);
}
Q3TTableModel::~Q3TTableModel()
{
    if(m_pArmaMatrix)
    {
        delete m_pArmaMatrix;
        m_pArmaMatrix = nullptr;
    }
}

int Q3TTableModel::actualRowCount() const
{
    return static_cast<int>(m_pArmaMatrix->rowCount());
}

int Q3TTableModel::actualColumnCount() const
{
     return static_cast<int>(m_pArmaMatrix->columnCount());
}
void Q3TTableModel::setActualSize(int rowCount, int columnCount)
{
    bool isChange = false;
    int actualRowCountTemp = actualRowCount();
    int actualColumnCountTemp = actualColumnCount();
    if(rowCount >= 0 && rowCount > actualRowCountTemp)
    {
        isChange = true;
        actualRowCountTemp = rowCount;
    }
    if(columnCount >= 0 && columnCount > actualColumnCountTemp)
    {
        isChange = true;
        actualColumnCountTemp = columnCount;
    }

    if(isChange)
    {
        m_pArmaMatrix->setSize(static_cast<arma::uword>(actualRowCountTemp), static_cast<arma::uword>(actualColumnCountTemp));
        emit actualRowColumnCountChange(actualRowCountTemp, actualColumnCountTemp);
    }
}

int Q3TTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_virtualRowCount;
}
int Q3TTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
   return m_virtualColumnCount;
}

void Q3TTableModel::setSize(int rowCount, int columnCount)
{
    m_virtualRowCount = rowCount;
    m_virtualColumnCount = columnCount;
}
void Q3TTableModel::resize(int rowCount, int columnCount)
{
    QModelIndex parent = QModelIndex();
    if(rowCount > m_virtualRowCount)
    {
        beginInsertRows(parent, m_virtualRowCount, rowCount - 1);
        m_virtualRowCount = rowCount;
        endInsertRows();
    }
    else if(rowCount < m_virtualRowCount)
    {
        beginRemoveRows(parent, rowCount, m_virtualRowCount - 1);
        m_virtualRowCount = rowCount;
        endRemoveRows();
    }

    if(columnCount > m_virtualColumnCount)
    {
        beginInsertColumns(parent, m_virtualColumnCount, columnCount - 1);
        m_virtualColumnCount = columnCount;
        endInsertColumns();
    }
    else if(columnCount < m_virtualColumnCount)
    {
        beginRemoveColumns(parent, columnCount, m_virtualColumnCount - 1);
        m_virtualColumnCount = columnCount;
        endRemoveColumns();
    }
}

bool Q3TTableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if(row > rowCount())
        row = rowCount();

    beginInsertRows(parent, row, row + count - 1);
    m_virtualRowCount += count;
    endInsertRows();
    return true;
}
bool Q3TTableModel::insertColumns(int column, int count, const QModelIndex &parent)
{
    if(column > columnCount())
        column = columnCount();

    beginInsertColumns(parent, column, column + count - 1);
    m_virtualColumnCount += count;
    endInsertColumns();
    return true;
}

QVariant Q3TTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }
    role = (role == Qt::EditRole) ? Qt::DisplayRole : role;

    if((Qt::DisplayRole == role))
    {
        int row = index.row();
        int column = index.column();
        if(row < 0 || column < 0 || row >= actualRowCount() || column >= actualColumnCount())
            return QVariant();

        return m_pArmaMatrix->data(static_cast<arma::uword>(row), static_cast<arma::uword>(column));
    }
    else if (role == Qt::TextAlignmentRole)
    {
        return int(Qt::AlignLeft | Qt::AlignVCenter);
    }
    else if (role == Qt::BackgroundRole)
    {
        return QColor(Qt::white);
    }
    else if (role == Qt::ToolTipRole)
    {
        return QVariant();
    }

    return QVariant(QVariant::Invalid);
}
bool Q3TTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(role)
    if (!index.isValid() || value.isNull() || !value.isValid() || !m_pArmaMatrix->canConvert(value))
    {
        return false;
    }

    setActualSize(index.row() + 1, index.column() + 1);
    m_pArmaMatrix->setData(static_cast<arma::uword>(index.row()), static_cast<arma::uword>(index.column()), value);

    QVector<int> roles;
    roles.append(role);
    emit dataChanged(index, index, roles);
    return true;
}
