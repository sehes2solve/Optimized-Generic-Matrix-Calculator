#include "matrix.h"


/// constructors and destructor ------------------------------------------------------------
matrix::matrix()
{
    this->row = 0;
    this->col = 0;
}

matrix :: matrix( int _row , int _col , int _set , bool go )
{
    try
    {
        if ( _row < 1 || _col < 1 )
            throw "Dimensions of the matrix must be positive intger value\n";
        if ( _row * _col >= (int)1e7 )
            throw "Size of the matrix is too large\n";

        this->row = _row;
        this->col = _col;

        this->data = new int* [ this->row ];
        for ( int i = 0; i < this->row; i++ )
            this->data[ i ] = new int [ this->col ];

        if ( go ) this->memset_matrix( _set );
    }
    catch( const char* mess )
    {
        cout << "ERROR: " << mess << "\n";
    }
}
matrix :: matrix( int ** _copy_matrix , int _row , int _col ) :
    matrix( _row , _col , 0 , 0 )
{
    try
    {
        for ( int i = 0; i < this->row; i++ )
            for ( int j = 0; j < this->col; j++ )
                this->data[i][j] = _copy_matrix[i][j];
    }
    catch( const char* mess )
    {
        cout << "ERROR: " << mess << "\n";
    }
}
matrix :: matrix( matrix& _copy_matrix ) :
    matrix( _copy_matrix.get_row() , _copy_matrix.get_col() , 0 , 0 )
{
    int ** _copy_data = _copy_matrix.get_matrix();
    for ( int i = 0; i < this->row; i++ )
        for ( int j = 0; j < this->col; j++ )
            this->data[ i ][ j ] = _copy_data[ i ][ j ];
}

matrix::~matrix()
{
    if ( this->row > 0 && this->col > 0 )
    {
        for ( int i = 0; i < this->row; i++ ) delete[] this->data[i];
        delete[] this->data;
    }
}

/// setter and getters ---------------------------------------------------------------------

int   matrix :: get_row()
{
    return this->row;
}
int   matrix :: get_col()
{
    return this->col;
}
int** matrix :: get_matrix()
{
    return this->data;
}

void matrix :: set_row( int _row )
{
    this->row = _row;
}

void matrix :: set_col( int _col )
{
    this->col = _col;
}

/// operators overloaded  ------------------------------------------------------------------

matrix& matrix :: operator = ( matrix mat )
{
    if ( this->row != mat.get_row() && this->col != mat.get_col() )
    {
        if ( this->row > 0 && this->col > 0 )
        {
            for ( int i = 0; i < this->row; i++ ) delete[] this->data[i];
            delete[] this->data;

            this->row = 0; this->col = 0;
        }
        this->setRowCol( mat.get_row() , mat.get_col() );
    }

    int ** _copy_data = mat.get_matrix();
    for ( int i = 0; i < this->row; i++ )
        for ( int j = 0; j < this->col; j++ )
            this->data[ i ][ j ] = _copy_data[ i ][ j ];

    return *this;
}

matrix& matrix :: operator +  ( matrix mat )
{
    matrix* object = new matrix( this->row , this->col , 0 , 0 );

    try
    {
        if ( this->row != mat.get_row() || this->col != mat.get_col() )
            throw "tow matrices not have the same dimension";

        int** sub_mat = mat.get_matrix();
        int** mainMat = object->get_matrix();

        for ( int i = 0; i < this->row; i++ )
            for ( int j = 0;j < this->col; j++ )
                mainMat[i][j] = this->data[i][j] + sub_mat[i][j];
    }
    catch ( const char* mess )
    {
        cout << "ERROR: " << mess << "\n";
        object->memset_matrix( 0 );
    }
    return *object;
}

matrix& matrix :: operator -  ( matrix mat )
{
    matrix *object = new matrix( this->row , this->col , 0 , 0 );

    try
    {
        if ( this->row != mat.get_row() || this->col != mat.get_col() )
            throw "tow matrices not have the same dimension";

        int** sub_mat = mat.get_matrix();
        int** mainMat = object->get_matrix();

        for ( int i = 0; i < this->row; i++ )
            for ( int j = 0;j < this->col; j++ )
                mainMat[i][j] = this->data[i][j] - sub_mat[i][j];
    }
    catch ( const char* mess )
    {
        cout << "ERROR: " << mess << "\n";
        object->memset_matrix( 0 );
    }
    return *object;
}

matrix& matrix :: operator *  ( matrix mat )
{
    matrix *object = new matrix( this->row , mat.get_col() , 0 , 0 );
    try
    {
        if ( this->col != mat.get_row() )
            throw "the column not equal the row";

        int ** sub_mat = mat.get_matrix();
        for ( int i = 0; i < this->row; i++ )
        {
            for ( int j = 0; j < mat.get_col(); j++ )
            {
                int value = 0;
                for ( int k = 0; k < mat.get_row(); k++ )
                {
                    value += this->data[i][k] * sub_mat[k][j];
                }
                object->data[i][j] = value;
            }
        }
    }
    catch ( const char* mess )
    {
        cout << "ERROR: " << mess;
        object->memset_matrix( 0 );
    }
    return *object;
}

matrix& matrix :: operator += ( matrix mat )
{
    *this = *this + mat;
    return *this;
}

matrix& matrix :: operator -= ( matrix mat )
{
    *this = *this + mat;
    return *this;
}

matrix& matrix :: operator *= ( matrix mat )
{
    *this = *this * mat;
    return *this;
}

matrix& matrix :: operator +  ( int value )
{
    matrix *object = new matrix( this->row , this->col , 0 , 0 );

    int ** sub_mat = object->get_matrix();
    for ( int i = 0; i < this->row; i++ )
        for ( int j = 0; j < this->col; j++ )
            sub_mat[i][j] = this->data[i][j] + value;

    return *object;
}

matrix& matrix :: operator -  ( int value )
{
    matrix *object = new matrix( this->row , this->col , 0 , 0 );

    int ** sub_mat = object->get_matrix();
    for ( int i = 0; i < this->row; i++ )
        for ( int j = 0; j < this->col; j++ )
            sub_mat[i][j] = this->data[i][j] - value;

    return *object;
}

matrix& matrix :: operator *  ( int value )
{
    matrix *object = new matrix( this->row , this->col , 0 , 0 );

    int ** sub_mat = object->get_matrix();
    for ( int i = 0; i < this->row; i++ )
        for ( int j = 0; j < this->col; j++ )
            sub_mat[i][j] = this->data[i][j] * value;

    return *object;
}

matrix& matrix :: operator += ( int value )
{
    *this = *this + value;
    return *this;
}

matrix& matrix :: operator -= ( int value )
{
    *this = *this - value;
    return *this;
}

matrix& matrix :: operator *= ( int value )
{
    *this = *this * value;
    return *this;
}

bool matrix :: operator == ( matrix mat )
{
    if ( this->row == mat.get_row() && this->col == mat.get_col() )
    {
        int ** sub_mat = mat.get_matrix();
        for ( int i = 0; i < this->row; i++ )
            for ( int j = 0; j < this->col; j++ )
                if ( this->data[i][j] != sub_mat[i][j] ) return false;
        return true;
    }
    return false;
}

bool matrix :: operator != ( matrix mat )
{
    if ( *this == mat ) return false;
    return true;
}

ostream& operator << ( ostream& out , matrix mat )
{
    int ** data = mat.get_matrix();
    for ( int i = 0; i < mat.get_row(); i++ )
    {
        for ( int j = 0; j < mat.get_col(); j++ )
            out << data[i][j] << " ";
        out << "\n";
    }
    return out;
}

istream& operator >> ( istream& in , matrix& mat )
{
    try
    {
        int row , col;
        cout << "Enter the row of the matrix : "; cin >> row;
        if ( row < 0 )
            throw "the row of the matrix must be positive intger";

        cout << "Enter the column of the matrix : "; cin >> col;
        if ( col < 0 )
            throw "the col of the matrix must be positive intger";

        if ( row * col > (int)1e7 )
            throw "Size of the matrix is too large\n";


        mat.setRowCol( row , col );
        int ** data = mat.get_matrix();
        for ( int i = 0; i < row; i++ )
            for ( int j = 0; j < col; j++ )
                in >> data[i][j];

    }
    catch( const char* mess )
    {
        cout << "ERROR: " << mess;
    }
    return in;
}

/// functions ------------------------------------------------------------------------------

void matrix :: memset_matrix( int val )
{
    if ( this->row > 0 && this->col > 0 )
    {
        for ( int i = 0; i < this->row; i++ )
            for ( int j = 0; j < this->col; j++ )
                this->data[ i ][ j ] = val;
    }
}

void matrix :: transpose()
{
    int ** mat = new int * [ this->row ];
    for ( int i = 0; i < this->row; i++ )
        mat[ i ] = new int [ this->col ];

    for ( int i = 0; i < this->row; i++ )
    {
        for ( int j = 0; j < this->col; j++ )
            mat[i][j] = this->data[i][j];

        delete[] this->data[i];
    }
    delete[] this->data;

    swap( this->row , this->col );
    this->data = new int* [ this->row ];
    for ( int i = 0; i < this->row; i++ )
    {
        this->data[ i ] = new int [ this->col ];
        for ( int j = 0; j < this->col; j++ )
            this->data[i][j] = mat[j][i];
    }
}

void matrix :: setRowCol( int _row , int _col )
{
    this->row = _row;
    this->col = _col;

    this->data = new int * [ row ];
    for ( int i = 0; i < row; i++ )
        this->data[i] = new int [ col ];
}
