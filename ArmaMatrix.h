#ifndef ARMAMATRIX_H
#define ARMAMATRIX_H

#include <QVariant>
#define ARMA_DONT_USE_WRAPPER
#include <armadillo>
#include "GlobalTypes.h"

class ArmaMatrix
{
public:
    ArmaMatrix(AMDATATYPE type);
    virtual ~ArmaMatrix();

    arma::uword rowCount() const;
    arma::uword columnCount() const;

    void setSize(arma::uword rowCount, arma::uword columnCount);
    void resize(arma::uword rowCount, arma::uword columnCount);

    void insertRows(arma::uword row, arma::uword count);
    void insertColumns(arma::uword column, arma::uword count);

    bool canConvert(const QVariant &value) const;

    QVariant data(arma::uword row, arma::uword column) const;
    bool setData(arma::uword row, arma::uword column, const QVariant &value);

private:
    AMDATATYPE m_dataType;
    arma::Mat<int>* m_pDataInt;
    arma::Mat<double>* m_pDataDouble;
    arma::Mat<float>* m_pDataFloat;
};

#endif // ARMAMATRIX_H
