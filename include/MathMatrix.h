#pragma once
#include <iostream>
#include <stdexcept>
#include <string>

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
    ~MathMatrix();
    T get(unsigned int row, unsigned int col) const;
    void set(unsigned int row, unsigned int col, T value);
    T getNullElement();
    T& operator[](unsigned int);
};

template<class T, unsigned int rowDim, unsigned int colDim>
inline MathMatrix<T, rowDim, colDim>::MathMatrix(T defaultElement)
{
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
            //debug
            //std::cout << x << "," << y << " = " << data[x][y] << std::endl;
        }
    }
}

template<class T, unsigned int rowDim, unsigned int colDim>
inline MathMatrix<T, rowDim, colDim>::~MathMatrix()
{
    //delete nested arrays
    for(int x = 0; x < rowDim; x++)
        delete[] data[x];

    //delete container array
    delete[] data;
}

template<class T, unsigned int rowDim, unsigned int colDim>
inline T MathMatrix<T, rowDim, colDim>::get(unsigned int row, unsigned int col) const
{
    return data[row][col];
}

template<class T, unsigned int rowDim, unsigned int colDim>
inline void MathMatrix<T, rowDim, colDim>::set(unsigned int row, unsigned int col, T value)
{
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












//template<class T, unsigned int rowDim, unsigned int colDim>
//inline void MathMatrix<T, rowDim, colDim>::
//{
//    
//}