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

    //assign values to myMatrix and yourMatrix
    std::cout << "Filling matrices linearly\n";
    myMatrix.fillLinear();
    yourMatrix.fillLinear();
    std::cout << to_string(myMatrix);

    //add myMaxtrix and yourMatrix
    std::cout << "Adding myMatrix to yourMatrix\n";
    std::cout << to_string(myMatrix + yourMatrix);

    //multiply myMatrix * x
    std::cout << "Multiplying matrix with 3\n";
    std::cout << to_string(myMatrix * 3);

    //multiply myMatrix * vector
    std::cout << "Creating new matrix and vector\n";
    MathMatrix<float, 3, 2> multMatrix = MathMatrix<float, 3, 2>(0);
    multMatrix.set(0, 0, 5);
    multMatrix.set(1, 0, -1);
    multMatrix.set(2, 0, 8);
    multMatrix.set(0, 1, 7);
    multMatrix.set(1, 1, 0.5f);
    multMatrix.set(2, 1, 0);
    std::cout << to_string(multMatrix);

    MathVec<float, 3> multVec = MathVec<float, 3>(0);
    multVec.set(0, 1);
    multVec.set(1, 0);
    multVec.set(2, 4);
    std::cout << to_string(multVec) << "\n\n";

    std::cout << "Multiplying matrix with vector\n";
    std::cout << to_string(multMatrix * multVec) << "\n\n";

    //multiply myMatrix * yourMatrix
    std::cout << "Creating 2 new matrices";
    MathMatrix<float, 4, 2> aMatrix = MathMatrix<float, 4, 2>(0);
    MathMatrix<float, 3, 4> bMatrix = MathMatrix<float, 3, 4>(0);
    aMatrix.set(0, 0, 1);
    aMatrix.set(1, 0, 2);
    aMatrix.set(2, 0, -3);
    aMatrix.set(3, 0, 1);
    aMatrix.set(0, 1, 5);
    aMatrix.set(1, 1, 0);
    aMatrix.set(2, 1, 6);
    aMatrix.set(3, 1, 1);
    bMatrix.set(0, 0, 1);
    bMatrix.set(1, 0, 8);
    bMatrix.set(2, 0, -1);
    bMatrix.set(0, 1, 0);
    bMatrix.set(1, 1, 0);
    bMatrix.set(2, 1, 1);
    bMatrix.set(0, 2, 0.5f);
    bMatrix.set(1, 2, -1);
    bMatrix.set(2, 2, -2);
    bMatrix.set(0, 3, 1);
    bMatrix.set(1, 3, 0);
    bMatrix.set(2, 3, 4);
    std::cout << to_string(aMatrix);
    std::cout << to_string(bMatrix);
    std::cout << "Multiplying matrices\n";
    std::cout << to_string(aMatrix * bMatrix);

    //bonus
}