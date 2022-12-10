#include "matrixCalculator.h"
#include "matrix.cpp"

matrixCalculator::matrixCalculator()
{
    cout << "Welcome in ( ehab & hussien ) matrix calculator\n\n";
    this->execute();
}

matrixCalculator::~matrixCalculator()
{
    //dtor
}

void matrixCalculator :: menu()
{
    cout << "1- Perform Matrix Addition\n";
    cout << "2- Perform Matrix Subtraction\n";
    cout << "3- Perform Matrix Multiplication\n";
    cout << "4- Matrix Transpose\n";
    cout << "5- End\n";
    cout << "Choice : ";
}

void matrixCalculator :: execute()
{
    string choice;
    while ( true )
    {
        menu(); cin >> choice;

        if      ( choice == "5" ) break;
        else if ( choice == "1" ) this->Addition();
        else if ( choice == "2" ) this->Subtraction();
        else if ( choice == "3" ) this->multiplication();
        else if ( choice == "4" ) this->transpose();
        else
            cout << "Invalid input\n";
        system( "Pause" ); system( "CLS" );
    }
}

void matrixCalculator :: Addition()
{
    matrix < double > *mat1 = new matrix < double >;
    matrix < double > *mat2 = new matrix < double >;
    matrix < double > *res  = new matrix < double >;

    cout << "\nEnter the first  matrix :- \n"; cin >> *mat1;
    cout << "\nEnter the second matrix :- \n"; cin >> *mat2;

    cout << "The Addition result :- \n\n";
    *res = ( *mat1 + *mat2 );
    cout << *res << "\n";

    delete mat1; delete mat2; delete res;
}

void matrixCalculator :: Subtraction()
{
    matrix < double > *mat1 = new matrix < double >;
    matrix < double > *mat2 = new matrix < double >;
    matrix < double > *res  = new matrix < double >;

    cout << "\nEnter the first  matrix :- \n"; cin >> *mat1;
    cout << "\nEnter the second matrix :- \n"; cin >> *mat2;

    cout << "The Subtraction result :- \n\n";
    *res = ( *mat1 - *mat2 );
    cout << *res << "\n";

    delete mat1; delete mat2; delete res;
}

void matrixCalculator :: multiplication()
{
    matrix < double > *mat1 = new matrix < double >;
    matrix < double > *mat2 = new matrix < double >;
    matrix < double > *res  = new matrix < double >;

    cout << "\nEnter the first  matrix :- \n"; cin >> *mat1;
    cout << "\nEnter the second matrix :- \n"; cin >> *mat2;

    cout << "The Multiplication result :- \n\n";
    *res = ( *mat1 * *mat2 );
    cout << *res << "\n";

    delete mat1; delete mat2; delete res;
}

void matrixCalculator :: transpose()
{
    matrix < double > *mat = new matrix < double >;

    cout << "\nEnter the matrix :- \n"; cin >> *mat;
    cout << "\nThe transpose matrix :- \n\n";
    mat->transpose();
    cout << *mat << "\n";
    delete mat;
}
