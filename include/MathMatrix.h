#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
#include "MathVec.h"

//rowDim is x axis size
//colDim is y axis size
//e.g. a matrix with width 3 and height 2 would be <3,2>
//you could also interpret this the other way around, with it being the amount of axes, not their size
//in that case, flip rowDim/colDim and some get/set operations in code
template<class T, unsigned int rowDim, unsigned int colDim>
class MathMatrix
{
private:
    T** data;
    T nullElement;
public:
    MathMatrix(T defaultElement);
	MathMatrix(const MathMatrix& source);
    MathMatrix(MathMatrix&& source);
    ~MathMatrix();
    T get(unsigned int row, unsigned int col) const;
    void set(unsigned int row, unsigned int col, T value);
    T getNullElement();
    MathVec<T, colDim> getColumn(int index) const;
    MathVec<T, rowDim> getRow(int index) const;
	MathMatrix<T, rowDim, colDim>& operator=(const MathMatrix<T, rowDim, colDim>& source);
	MathMatrix<T, rowDim, colDim>& operator=(MathMatrix<T, rowDim, colDim>&& source);
    void fillLinear();
};

template<class T, unsigned int rowDim, unsigned int colDim>
inline MathMatrix<T, rowDim, colDim>::MathMatrix(T defaultElement)
{
    if(colDim == 0 || rowDim == 0)
        throw new logic_error("Error: matrix dimension must be larger than 0");

    //create container array
    data = new T*[rowDim];

    //assign default element
    nullElement = defaultElement;

    //iterate over container array
    for(int x = 0; x < rowDim; x++)
    {
        //fill each container element with a new nested array
        data[x] = new T[colDim];

        //iterate over nested array
        for(int y = 0; y < colDim; y++)
        {
            //set value to default element
            data[x][y] = nullElement;
        }
    }
}

template<class T, unsigned int rowDim, unsigned int colDim>
inline MathMatrix<T, rowDim, colDim>::~MathMatrix()
{
    //if data is nullptr, cancel
    //this is used so the loop doesnt get called after move operations
    if(data == nullptr)
        return;

    //delete nested arrays
    for(int x = 0; x < rowDim; x++)
        delete[] data[x];

    //delete container array
    delete[] data;
}

template<class T, unsigned int rowDim, unsigned int colDim>
inline T MathMatrix<T, rowDim, colDim>::get(unsigned int row, unsigned int col) const
{
    if(row >= rowDim || col >= colDim)
        throw logic_error("Error: Matrix out of bounds for get()");
    return data[row][col];
}

template<class T, unsigned int rowDim, unsigned int colDim>
inline void MathMatrix<T, rowDim, colDim>::set(unsigned int row, unsigned int col, T value)
{
    if(row >= rowDim || col >= colDim)
        throw logic_error("Error: Matrix out of bounds for set()");
    data[row][col] = value;
}

template<class T, unsigned int rowDim, unsigned int colDim>
inline T MathMatrix<T, rowDim, colDim>::getNullElement()
{
    return nullElement;
}

template<class T, unsigned int rowDim, unsigned int colDim>
inline std::string to_string(const MathMatrix<T, rowDim, colDim>& m) 
{
    std::string result = "";
    //print top left corner (v is for var, randomly picked)
    result += "[v] ";

    //print top indices for x axis
    for(int x = 0; x < rowDim; x++)
    {
        result += "[";
        result += std::to_string(x);
        result += "]";
    }

    //new line to start printing values
    result += "\n";

    //loop over values
	for(int y = 0; y < colDim; y ++)
    {
        //print y index indicator
        result += "[";
        result += std::to_string(y);
        result += "]  ";

        //print values for current row
        for(int x = 0; x < rowDim; x++)
        {
            result += std::to_string(m.get(x,y));
            result += "  ";
        }

        //new line for next row
        result += "\n";
    }
    //free line at the end
    result += "\n";

    return result;
}

template<class T, unsigned int rowDim, unsigned int colDim>
inline MathVec<T, colDim> MathMatrix<T, rowDim, colDim>::getColumn(int index) const
{
    if(index >= rowDim)
        throw logic_error("Error: cannot get column, specified index is larger than amount of columns");

    MathVec<T, colDim> column = MathVec<T, colDim>(0);

    for(int y = 0; y < colDim; y++)
        column[y] = get(index, y);

    return column;
}

template<class T, unsigned int rowDim, unsigned int colDim>
inline MathVec<T, rowDim> MathMatrix<T, rowDim, colDim>::getRow(int index) const
{
    if(index >= colDim)
        throw logic_error("Error: cannot get row, specified index is larger than amount of rows");

    MathVec<T, rowDim> row = MathVec<T, rowDim>(0);

    for(int x = 0; x < colDim; x++)
        row[x] = get(x, index);

    return row;
}

template<class T, unsigned int rowDim, unsigned int colDim>
inline MathMatrix<T, rowDim, colDim>::MathMatrix(const MathMatrix& source)
{
    //copy null element
    nullElement = source.nullElement;

    data = new T*[rowDim];
    //iterate over container array
    for(int x = 0; x < rowDim; x++)
    {
        //fill each container element with a new nested array
        data[x] = new T[colDim];

        //iterate over nested array
        for(int y = 0; y < colDim; y++)
        {
            //copy value from source element
            data[x][y] = source.get(x, y);
        }
    }
}

template<class T, unsigned int rowDim, unsigned int colDim>
inline MathMatrix<T, rowDim, colDim>::MathMatrix(MathMatrix&& source)
{
    nullElement = source.nullElement;
    data = source.data;
    source.data = nullptr;
    source.nullElement = 0;
}

template<class T, unsigned int rowDim, unsigned int colDim>
inline MathMatrix<T, rowDim, colDim>& MathMatrix<T, rowDim, colDim>::operator=(const MathMatrix<T, rowDim, colDim>& source)
{
    //copy null element
    nullElement = source.nullElement;

    data = new T*[rowDim];
    //iterate over container array
    for(int x = 0; x < rowDim; x++)
    {
        //fill each container element with a new nested array
        data[x] = new T[colDim];

        //iterate over nested array
        for(int y = 0; y < colDim; y++)
        {
            //copy value from source element
            data[x][y] = source.get(x, y);
        }
    }
    return *this;
}

template<class T, unsigned int rowDim, unsigned int colDim>
inline MathMatrix<T, rowDim, colDim>& MathMatrix<T, rowDim, colDim>::operator=(MathMatrix<T, rowDim, colDim>&& source)
{
    nullElement = source.nullElement;
    data = source.data;
    source.data = nullptr;
    source.nullElement = 0;
    return *this;
}

template<class T, unsigned int rowDim, unsigned int colDim>
inline MathMatrix<T, rowDim, colDim> operator+(const MathMatrix<T, rowDim, colDim>& a, const MathMatrix<T, rowDim, colDim>& b)
{
    //new object
    MathMatrix<T, rowDim, colDim> sumMatrix = MathMatrix<T, rowDim, colDim>(0);

    //fill with sum of both matrices
    for(int y = 0; y < colDim; y++)
        for(int x = 0; x < rowDim; x++)
        {
            T operationResult = a.get(x,y) + b.get(x, y);
            sumMatrix.set(x, y, operationResult);
        }

    //return object
    return sumMatrix;
}

template<class T, unsigned int rowDim, unsigned int colDim>
inline MathMatrix<T, rowDim, colDim> operator*(const MathMatrix<T, rowDim, colDim>& a, const T& b)
{
    //new object
    MathMatrix<T, rowDim, colDim> multMatrix = MathMatrix<T, rowDim, colDim>(0);

    //fill with sum of both matrices
    for(int y = 0; y < colDim; y++)
        for(int x = 0; x < rowDim; x++)
        {
            T operationResult = a.get(x,y) * b;
            multMatrix.set(x, y, operationResult);
        }

    //return object
    return multMatrix;
}

//still wip
template<class T, unsigned int rowDim, unsigned int colDim>
MathVec<T, colDim> operator*(const MathMatrix<T, rowDim, colDim>& a, const MathVec<T, rowDim>& b)
{
    //new object
    MathVec<T, colDim> multVec = MathVec<T, colDim>(0);

    //fill with sum of both matrices
    for(int m = 0; m < colDim; m++)
    {
        T ci = 0;
        for(int n = 0; n < rowDim; n++)
            ci += a.get(n, m) * b.get(n);
        multVec.set(m, ci);
    }

    //return object
    return multVec;
}

//placeholder
template<class T, unsigned int mDim, unsigned int nDim, unsigned int lDim>
inline MathMatrix<T, lDim, mDim> operator*(const MathMatrix<T, nDim ,mDim>& a, const MathMatrix<T, lDim, nDim>& b)
{
    //new object
    MathMatrix<T, lDim, mDim> multMatrix = MathMatrix<T, lDim, mDim>(0);

    //for each field in the result matrix
    for(int high = 0; high < mDim; high++)
        for(int wide = 0; wide < lDim; wide++)
        {
            //make a new T
            T cij = 0;

            //loop over the shared side (n)
            for(int n = 0; n < nDim; n++)
                //take value from a/b, multiply it and add to the result
                //for a, row m is same as loop y, then iterate over a row
                //for b, column n is same as loop x, then itherate over b column
                cij += a.get(n, high) * b.get(wide, n);

            //add sum to result matrix
            multMatrix.set(wide, high, cij);
        }

    //return object
    return multMatrix;
}

template<class T, unsigned int rowDim, unsigned int colDim>
inline void MathMatrix<T, rowDim, colDim>::fillLinear()
{
    for(int y = 0; y < colDim; y++)
        for(int x = 0; x < rowDim; x++)
            set(x, y, x);
}