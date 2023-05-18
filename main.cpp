#include <iostream>
#include "include/MathVec.h"
#include "include/MathMatrix.h"

int main()
{
    //test memory leak for destructor
    MathMatrix<int, 9, 9> myMatrix = MathMatrix<int, 9, 9>(0);
    std::cout << to_string(myMatrix);

    myMatrix.set(4, 4, 6);

    std::cout << to_string(myMatrix);
}