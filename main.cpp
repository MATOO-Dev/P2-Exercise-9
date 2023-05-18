#include <iostream>
#include <string>
#include "include/MathVec.h"
#include "include/MathMatrix.h"

int main()
{
    //create a new matrix
    std::cout << "Creating new instance myMatrix\n";
    MathMatrix<int, 9, 5> myMatrix = MathMatrix<int, 9, 5>(0);
    std::cout << to_string(myMatrix);

    //setting a value
    std::cout << "Changing a value in myMatrix\n";
    myMatrix.set(4, 2, 6);
    std::cout << to_string(myMatrix);

    //getting individual rows/columns
    std::cout << "Getting individual row/column of myMatrix\n";
    std::cout << to_string(myMatrix.getColumn(4)) << std::endl;
    std::cout << to_string(myMatrix.getRow(2)) << std::endl << std::endl;

    //testing copy constructor
    std::cout << "Giving yourMatrix a copy of myMatrix\n";
    MathMatrix<int, 9, 5> yourMatrix = MathMatrix<int, 9, 5>(myMatrix);
    std::cout << to_string(yourMatrix);

    //testing move constructor
    std::cout << "Starting a communist revolution (moving myMatrix to ourMatrix)\n";
    MathMatrix<int, 9, 5> ourMatrix = std::move(myMatrix);
    std::cout << to_string(ourMatrix);

    //moving ourMatrix back to myMatrix
    std::cout << "Fall of the soviet union, 26.12.1991, colorized (moving ourMatrix back to myMatrix)\n";
    myMatrix = std::move(ourMatrix);
    std::cout << to_string(myMatrix);

}