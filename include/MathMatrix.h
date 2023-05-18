#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
#include "MathVec.h"

//row is x axis
//column is y axis
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










//template<class T, unsigned int rowDim, unsigned int colDim>
//inline void MathMatrix<T, rowDim, colDim>::
//{
//    
//}