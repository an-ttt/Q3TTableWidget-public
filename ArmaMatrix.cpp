#include "ArmaMatrix.h"

ArmaMatrix::ArmaMatrix(AMDATATYPE dataType)
{
    m_dataType = dataType;
    switch (m_dataType) {
    case AMDATATYPE_int:
        m_pDataInt = new arma::Mat<int>();
        break;

    case AMDATATYPE_double:
        m_pDataDouble = new arma::Mat<double>();
        break;

    case AMDATATYPE_float:
        m_pDataFloat = new arma::Mat<float>();
        break;

    default:
        // "not support data type of Q3TTableModel"
        Q_ASSERT(false);
        break;
    }
}

ArmaMatrix::~ArmaMatrix()
{
    switch (m_dataType) {
    case AMDATATYPE_int:
        delete m_pDataInt;
        break;

    case AMDATATYPE_double:
        delete m_pDataDouble;
        break;

    case AMDATATYPE_float:
        delete m_pDataFloat;
        break;

    default:
        // "not support data type of Q3TTableModel"
        Q_ASSERT(false);
        break;
    }

}

#define RUN_METHOD(_codes) \
switch (m_dataType) { \
case AMDATATYPE_int: \
    m_pDataInt->_codes; \
    break; \
case AMDATATYPE_double: \
    m_pDataDouble->_codes; \
    break; \
case AMDATATYPE_float: \
    m_pDataFloat->_codes; \
    break; \
default: \
    Q_ASSERT(false); \
    break; \
} \

#define RUN_METHOD_RETURN(_codes) \
switch (m_dataType) { \
case AMDATATYPE_int: \
    return m_pDataInt->_codes; \
case AMDATATYPE_double: \
    return m_pDataDouble->_codes; \
case AMDATATYPE_float: \
    return m_pDataFloat->_codes; \
default: \
    Q_ASSERT(false); \
    break; \
} \

arma::uword ArmaMatrix::rowCount() const
{
    RUN_METHOD_RETURN(n_rows)
    return 0;
}
arma::uword ArmaMatrix::columnCount() const
{
    RUN_METHOD_RETURN(n_cols)
    return 0;
}

void ArmaMatrix::setSize(arma::uword rowCount, arma::uword columnCount)
{
    RUN_METHOD(set_size(rowCount,columnCount))
    RUN_METHOD(fill(0))
}
void ArmaMatrix::resize(arma::uword rowCount, arma::uword columnCount)
{
    RUN_METHOD(resize(rowCount, columnCount))
    RUN_METHOD(fill(0))
}

void ArmaMatrix::insertRows(arma::uword row, arma::uword count)
{
    RUN_METHOD(insert_rows(row, count))
}

void ArmaMatrix::insertColumns(arma::uword column, arma::uword count)
{
    RUN_METHOD(insert_cols(column, count))
}

bool ArmaMatrix::canConvert(const QVariant &value) const
{
    QVariant valueTemp = value;
    switch (m_dataType) {
    case AMDATATYPE_int:
        return valueTemp.convert(QVariant::Int);

    case AMDATATYPE_double:
        return valueTemp.convert(QVariant::Double);

    case AMDATATYPE_float:
        return valueTemp.convert(QMetaType::Float);

    default:
        // "not support data type of Q3TTableModel"
        Q_ASSERT(false);
        break;
    }

    return false;
}

QVariant ArmaMatrix::data(arma::uword row, arma::uword column) const
{
    switch (m_dataType) {
    case AMDATATYPE_int:
        return QVariant((*m_pDataInt)(row, column));

    case AMDATATYPE_double:
        return QVariant((*m_pDataDouble)(row, column));

    case AMDATATYPE_float:
        return QVariant((*m_pDataFloat)(row, column));

    default:
        // "not support data type of Q3TTableModel"
        Q_ASSERT(false);
        break;
    }

    return QVariant(QVariant::Invalid);
}
bool ArmaMatrix::setData(arma::uword row, arma::uword column, const QVariant &value)
{
    switch (m_dataType) {
    case AMDATATYPE_int:
        (*m_pDataInt)(row, column) = value.toInt();
        break;

    case AMDATATYPE_double:
        (*m_pDataDouble)(row, column) = value.toDouble();
        break;

    case AMDATATYPE_float:
        (*m_pDataFloat)(row, column) = value.toFloat();
        break;

    default:
        // "not support data type of Q3TTableModel"
        Q_ASSERT(false);
        return false;
    }

    return true;
}
