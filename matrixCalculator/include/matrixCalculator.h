#ifndef MATRIXCALCULATOR_H
#define MATRIXCALCULATOR_H

#include "matrix.h"
#include <iostream>

using namespace std;

class matrixCalculator
{
    public:
        matrixCalculator();
        virtual ~matrixCalculator();

        void menu();
        void execute();
        void Addition();
        void Subtraction();
        void multiplication();
        void transpose();

    protected:

    private:
};

#endif // MATRIXCALCULATOR_H
