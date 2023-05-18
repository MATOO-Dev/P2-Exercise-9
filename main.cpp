#include <iostream>
#include <string>
#include <cmath>
#include <thread>
#include "include/MathVec.h"
#include "include/MathMatrix.h"
#include "include/ViewPortGL.h"

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
    //its like 00:08 am right now, im not gonna clean this up in the middle of the night
    //it works tho, so spinny thing goes weeeeeee
    ViewPortGL targetWindow = ViewPortGL("Spin to win", 1000, 1000);
    float rotationAngle = 0;
    //measured in radians, not degrees
    //this is ~6 degrees, or 1 rotation in 60 steps for 60fps
    float angleStep = 0.1047198;

    MathMatrix<float, 2, 2> rotationMatrix = MathMatrix<float, 2, 2>(0);

    MathVec<float, 2> topLeft = MathVec<float, 2>(0);
    topLeft.set(0, -250);
    topLeft.set(1, -250);
    MathVec<float, 2> topRight = MathVec<float, 2>(0);
    topRight.set(0, 250);
    topRight.set(1, -250);
    MathVec<float, 2> bottomLeft = MathVec<float, 2>(0);
    bottomLeft.set(0, -250);
    bottomLeft.set(1, 250);
    MathVec<float, 2> bottomRight = MathVec<float, 2>(0);
    bottomRight.set(0, 250);
    bottomRight.set(1, 250);
    MathVec<float, 2> topLeftRotated = MathVec<float, 2>(0);
    MathVec<float, 2> topRightRotated = MathVec<float, 2>(0);
    MathVec<float, 2> bottomLeftRotated = MathVec<float, 2>(0);
    MathVec<float, 2> bottomRightRotated = MathVec<float, 2>(0);

    while(!targetWindow.windowShouldClose())
    {
        targetWindow.clearViewPort();
        if(rotationAngle >= 360)
            rotationAngle -= 360;

        rotationMatrix = MathMatrix<float, 2, 2>(0);
        rotationMatrix.set(0, 0, cos(rotationAngle));
        rotationMatrix.set(1, 0, -sin(rotationAngle));
        rotationMatrix.set(0, 1, sin(rotationAngle));
        rotationMatrix.set(1, 1, cos(rotationAngle));

        topLeftRotated = (rotationMatrix * topLeft);
        topRightRotated = rotationMatrix * topRight;
        bottomLeftRotated = rotationMatrix * bottomLeft;
        bottomRightRotated = rotationMatrix * bottomRight;
        
        //targetWindow.prepareBlock(topLeftRotated.get(0), topLeftRotated.get(1), 500, 500, 50, 75, 100);
        targetWindow.prepareTriangle(   topLeftRotated.get(0)+500,
                                        topLeftRotated.get(1)+500,
                                        topRightRotated.get(0)+500,
                                        topRightRotated.get(1)+500,
                                        bottomLeftRotated.get(0)+500,
                                        bottomLeftRotated.get(1)+500,
                                        50, 75, 100);
        targetWindow.prepareTriangle(   topRightRotated.get(0)+500,
                                        topRightRotated.get(1)+500,
                                        bottomLeftRotated.get(0)+500,
                                        bottomLeftRotated.get(1)+500,
                                        bottomRightRotated.get(0)+500,
                                        bottomRightRotated.get(1)+500,
                                        50, 75, 100);

        targetWindow.sendTriangles();
        targetWindow.swapBuffers();

        this_thread::sleep_for(0.016s);

        rotationAngle += angleStep;
    }
}