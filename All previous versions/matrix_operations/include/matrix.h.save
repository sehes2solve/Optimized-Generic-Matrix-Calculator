#ifndef MATRIX_H
#define MATRIX_H

#include <fstream>
#include <iostream>

using namespace std;

class matrix
{
    public:
        /// constructors and destructor
        matrix();
        matrix( int _row , int _col , int _set = 0 , bool go = 1 );
        matrix( int ** _copy_matrix , int _row , int _col );
        matrix( matrix& _copy_matrix );
        virtual ~matrix();

        /// setter and getters
        int   get_row();
        int   get_col();
        int** get_matrix();

        /// operators overloaded
        matrix& operator +  ( matrix mat );
        matrix& operator -  ( matrix mat );
        matrix& operator *  ( matrix mat );

        matrix& operator += ( matrix mat );
        matrix& operator -= ( matrix mat );
        matrix& operator *= ( matrix mat );

        matrix& operator +  ( int value );
        matrix& operator -  ( int value );
        matrix& operator *  ( int value );

        matrix& operator += ( int value );
        matrix& operator -= ( int value );
        matrix& operator *= ( int value );

        matrix& operator = ( matrix mat );

        bool operator == ( matrix mat );
        bool operator != ( matrix mat );

        friend ostream& operator << ( ostream& out , matrix mat );
        friend istream& operator >> ( istream& in , matrix& mat );

        /// functions
        void memset_matrix( int val );
        void transpose();

    protected:

    private:
        int row , col;
        int ** data;

        void set_row( int _row );
        void set_col( int _col );
        void setRowCol( int _row , int _col );
};

#endif // MATRIX_H

ostream& operator << ( ostream& out , matrix mat );
istream& operator >> ( istream& in , matrix& mat );
