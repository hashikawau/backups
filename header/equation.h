#include <iostream.h>

void gause( int n, double **A, double *b )
{
    double tempA[n][n+1];
    double tempb[n];
    for( int i=0; i< n; i++ )
    {
        tempA[i][n] = b[i];
        for( int j=0; j< i; j++ )
        {
            tempA[i][j] = A[i][j];
        }
    }
    
    for( int i=0; i< n; i++ )
    {   
        for( int j=i+1; j<= n; j++ )
        {
            tempA[i][j] /= tempA[i][i];
            for( int x=0; x< i; x++ )
            {
                tempA[x][j] -= tempA[i][j]*tempA[x][i];
            }
            for( int x=i+1; x< n; x++ )
            {
                tempA[x][j] -= tempA[i][j]*tempA[x][i];
            }
        }
    }
    
    for( int i=0; i< n; i++ )
    {
        tempb[i] = tempA[i][n];
        cout << tempb[i] << endl;
    }
    
    //return tempb;
}