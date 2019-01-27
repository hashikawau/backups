#include <iostream.h>

template<class T> class Tensor2;

ostream &operator<<( ostream &stream, Tensor2<> &T2 )
{
    cout << "row " << T2.numRow;
    cout << "  column " << T2.numCol;
    cout << "  rank " << T2.rank << endl;
    for( int i=0; i< T2.numRow; i++ )
    {
        for( int j=0; j< T2.numCol; j++ )
        {
            cout << T2.ppT[i][j] << " ";
        }
        cout << endl;
    }
    
    return stream;
}