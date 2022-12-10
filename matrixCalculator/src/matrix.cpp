#include "matrix.h"


/// constructors and destructor ------------------------------------------------------------
template < class T >
matrix <T> :: matrix()
{
    this->row = 0;
    this->col = 0;
}

template < class T >
matrix <T> :: matrix( int _row , int _col , T _set , bool go )
{
    try
    {
        if ( _row < 1 || _col < 1 )
            throw "Dimensions of the matrix must be positive intger value\n";
        if ( _row * _col >= (int)1e7 )
            throw "Size of the matrix is too large\n";

        this->row = _row;
        this->col = _col;

        this->data = new T* [ this->row ];
        for ( int i = 0; i < this->row; i++ )
            this->data[ i ] = new T [ this->col ];

        if ( go ) this->memset_matrix( _set );
    }
    catch( const char* mess )
    {
        cout << "ERROR: " << mess << "\n";
    }
}

template < class T >
matrix <T> :: matrix( T ** _copy_matrix , int _row , int _col ) :
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

template < class T >
matrix <T> :: matrix( matrix <T> & _copy_matrix ) :
    matrix( _copy_matrix.get_row() , _copy_matrix.get_col() , 0 , 0 )
{
    T ** _copy_data = _copy_matrix.get_matrix();
    for ( int i = 0; i < this->row; i++ )
        for ( int j = 0; j < this->col; j++ )
            this->data[ i ][ j ] = _copy_data[ i ][ j ];
}

template < class T >
matrix <T> ::~matrix()
{
    if ( this->row > 0 && this->col > 0 )
    {
        for ( int i = 0; i < this->row; i++ ) delete[] this->data[i];
        delete[] this->data;
    }
}

/// setter and getters ---------------------------------------------------------------------

template < class T >
int   matrix <T> :: get_row()
{
    return this->row;
}

template < class T >
int   matrix <T> :: get_col()
{
    return this->col;
}

template < class T >
T** matrix <T> :: get_matrix()
{
    return this->data;
}

template < class T >
void matrix <T> :: set_row( int _row )
{
    this->row = _row;
}

template < class T >
void matrix <T> :: set_col( int _col )
{
    this->col = _col;
}

/// operators overloaded  ------------------------------------------------------------------

template < class T >
matrix <T> & matrix <T> :: operator = ( matrix <T> mat )
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

    T ** _copy_data = mat.get_matrix();
    for ( int i = 0; i < this->row; i++ )
        for ( int j = 0; j < this->col; j++ )
            this->data[ i ][ j ] = _copy_data[ i ][ j ];

    return *this;
}

template < class T >
matrix <T> & matrix <T> :: operator +  ( matrix <T> mat )
{
    matrix <T> * object = new matrix <T> ( this->row , this->col , 0 , 0 );

    try
    {
        if ( this->row != mat.get_row() || this->col != mat.get_col() )
            throw "tow matrices not have the same dimension";

        T** sub_mat = mat.get_matrix();
        T** mainMat = object->get_matrix();

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

template < class T >
matrix <T> & matrix <T> :: operator -  ( matrix <T> mat )
{
    matrix <T> * object = new matrix <T> ( this->row , this->col , 0 , 0 );

    try
    {
        if ( this->row != mat.get_row() || this->col != mat.get_col() )
            throw "tow matrices not have the same dimension";

        T** sub_mat = mat.get_matrix();
        T** mainMat = object->get_matrix();

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

template <class T >
matrix <T> & matrix <T> :: operator *  ( matrix <T> mat )
{
    matrix <T> * object = new matrix <T> ( this->row , mat.get_col() , 0 , 0 );
    try
    {
        if ( this->col != mat.get_row() )
            throw "the column not equal the row";

        T ** sub_mat = mat.get_matrix();
        for ( int i = 0; i < this->row; i++ )
        {
            for ( int j = 0; j < mat.get_col(); j++ )
            {
                T value = 0;
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
        cout << "ERROR: " << mess << "\n";
        object->memset_matrix( 0 );
    }
    return *object;
}

template < class T >
matrix <T> & matrix <T> :: operator += ( matrix <T> mat )
{
    *this = *this + mat;
    return *this;
}

template < class T >
matrix <T> & matrix <T> :: operator -= ( matrix <T> mat )
{
    *this = *this + mat;
    return *this;
}

template < class T >
matrix <T> & matrix <T> :: operator *= ( matrix <T> mat )
{
    *this = *this * mat;
    return *this;
}

template < class T >
matrix <T> & matrix <T> :: operator +  ( int value )
{
    matrix <T> * object = new matrix <T> ( this->row , this->col , 0 , 0 );

    T ** sub_mat = object->get_matrix();
    for ( int i = 0; i < this->row; i++ )
        for ( int j = 0; j < this->col; j++ )
            sub_mat[i][j] = this->data[i][j] + value;

    return *object;
}

template < class T >
matrix <T> & matrix <T> :: operator -  ( int value )
{
    matrix <T> * object = new matrix <T> ( this->row , this->col , 0 , 0 );

    T ** sub_mat = object->get_matrix();
    for ( int i = 0; i < this->row; i++ )
        for ( int j = 0; j < this->col; j++ )
            sub_mat[i][j] = this->data[i][j] - value;

    return *object;
}

template < class T >
matrix <T> & matrix <T> :: operator *  ( int value )
{
    matrix <T> * object = new matrix <T> ( this->row , this->col , 0 , 0 );

    T ** sub_mat = object->get_matrix();
    for ( int i = 0; i < this->row; i++ )
        for ( int j = 0; j < this->col; j++ )
            sub_mat[i][j] = this->data[i][j] * value;

    return *object;
}

template < class T >
matrix <T> & matrix <T> :: operator += ( int value )
{
    *this = *this + value;
    return *this;
}

template < class T >
matrix <T> & matrix <T> :: operator -= ( int value )
{
    *this = *this - value;
    return *this;
}

template < class T >
matrix <T> & matrix <T> :: operator *= ( int value )
{
    *this = *this * value;
    return *this;
}

template < class T >
bool matrix <T> :: operator == ( matrix <T> mat )
{
    if ( this->row == mat.get_row() && this->col == mat.get_col() )
    {
        T ** sub_mat = mat.get_matrix();
        for ( int i = 0; i < this->row; i++ )
            for ( int j = 0; j < this->col; j++ )
                if ( this->data[i][j] != sub_mat[i][j] ) return false;
        return true;
    }
    return false;
}

template < class T >
bool matrix <T> :: operator != ( matrix <T> mat )
{
    if ( *this == mat ) return false;
    return true;
}

template < class T >
ostream& operator << ( ostream& out , matrix <T> mat )
{
    T ** data = mat.get_matrix();
    for ( int i = 0; i < mat.get_row(); i++ )
    {
        for ( int j = 0; j < mat.get_col(); j++ )
            out << data[i][j] << " ";
        out << "\n";
    }
    return out;
}

template < class T >
istream& operator >> ( istream& in , matrix <T> & mat )
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
        T ** data = mat.get_matrix();
        for ( int i = 0; i < row; i++ )
            for ( int j = 0; j < col; j++ )
                in >> data[i][j];

    }
    catch( const char* mess )
    {
        cout << "ERROR: " << mess << "\n";
    }
    return in;
}

/// functions ------------------------------------------------------------------------------

template < class T >
void matrix <T> :: memset_matrix( int val )
{
    if ( this->row > 0 && this->col > 0 )
    {
        for ( int i = 0; i < this->row; i++ )
            for ( int j = 0; j < this->col; j++ )
                this->data[ i ][ j ] = val;
    }
}

template < class T >
void matrix <T> :: transpose()
{
    T ** mat = new T * [ this->row ];
    for ( int i = 0; i < this->row; i++ )
        mat[ i ] = new T [ this->col ];

    for ( int i = 0; i < this->row; i++ )
    {
        for ( int j = 0; j < this->col; j++ )
            mat[i][j] = this->data[i][j];

        delete[] this->data[i];
    }
    delete[] this->data;

    swap( this->row , this->col );
    this->data = new T* [ this->row ];
    for ( int i = 0; i < this->row; i++ )
    {
        this->data[ i ] = new T [ this->col ];
        for ( int j = 0; j < this->col; j++ )
            this->data[i][j] = mat[j][i];
    }
}

template <class T>
void matrix <T> :: setRowCol( int _row , int _col )
{
    this->row = _row;
    this->col = _col;

    this->data = new T * [ row ];
    for ( int i = 0; i < row; i++ )
        this->data[i] = new T [ col ];
}

/// --------- explicit template instantiation ------------------------------------------------------------------

template class matrix < int                     >;
template class matrix < long int                >;
template class matrix < short int               >;
template class matrix < unsigned int            >;
template class matrix < long long int           >;
template class matrix < unsigned long int       >;
template class matrix < unsigned short int      >;
template class matrix < unsigned long long int  >;

template class matrix < float       >;
template class matrix < double      >;
template class matrix < long double >;


template ostream& operator << < int >( ostream& out , matrix < int >   mat );
template istream& operator >> < int >( istream& in  , matrix < int > & mat );

template ostream& operator << < long int >( ostream& out , matrix < long int >   mat );
template istream& operator >> < long int >( istream& in  , matrix < long int > & mat );

template ostream& operator << < short int >( ostream& out , matrix < short int >   mat );
template istream& operator >> < short int >( istream& in  , matrix < short int > & mat );

template ostream& operator << < unsigned int >( ostream& out , matrix < unsigned int >   mat );
template istream& operator >> < unsigned int >( istream& in  , matrix < unsigned int > & mat );

template ostream& operator << < long long int >( ostream& out , matrix < long long int >   mat );
template istream& operator >> < long long int >( istream& in  , matrix < long long int > & mat );

template ostream& operator << < unsigned long int >( ostream& out , matrix < unsigned long int >   mat );
template istream& operator >> < unsigned long int >( istream& in  , matrix < unsigned long int > & mat );

template ostream& operator << < unsigned short int >( ostream& out , matrix < unsigned short int >   mat );
template istream& operator >> < unsigned short int >( istream& in  , matrix < unsigned short int > & mat );

template ostream& operator << < unsigned long long int >( ostream& out , matrix < unsigned long long int >   mat );
template istream& operator >> < unsigned long long int >( istream& in  , matrix < unsigned long long int > & mat );

template ostream& operator << < float >( ostream& out , matrix < float >   mat );
template istream& operator >> < float >( istream& in  , matrix < float > & mat );

template ostream& operator << < double >( ostream& out , matrix < double >   mat );
template istream& operator >> < double >( istream& in  , matrix < double > & mat );

template ostream& operator << < long double >( ostream& out , matrix < long double >   mat );
template istream& operator >> < long double >( istream& in  , matrix < long double > & mat );
