#ifndef __TENSOR2_CALCULATOR
#define __TENSOR2_CALCULATOR
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
template<class typeT>
typeT iszero( typeT arg )
{
    if( (arg>0 && arg< ACCURACY) || (arg<0 && arg> -ACCURACY) )
    {
        return 0;
    }
    else
    {
        return arg;
    }
}
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
template<class typeT>
inline Tensor2<typeT>& Tensor2<typeT>::operator~()
{
    Tensor2<typeT>* tempTensor2;
    tempTensor2 = new Tensor2( numRow, numCol, tens2::origin | tens2::stable );
    *tempTensor2 = *this;
    storTensor2 = tempTensor2;
    
    for( int diag=0; diag< tempTensor2->rank; diag++ )
    {
        if( !iszero(tempTensor2->pptypeT[diag][diag]) ) // == 0
        {
            tempTensor2->rank = diag;
            
            for( int i=diag+1; i< tempTensor2->numRow; i++ )
            {
                if( iszero(tempTensor2->pptypeT[i][diag]) )           // != 0
                {
                    Tensor2<typeT> temp;
                    temp = tempTensor2( diag, diag,
                                        1,
                                        tempTensor2->numCol -diag
                                      );
                    
                    tempTensor2(diag, diag, 1, tempTensor2->numCol -diag)
                        = tempTensor2(i, diag, 1, tempTensor2->numCol -diag);
                    tempTensor2(i, diag, 1, tempTensor2->numCol -diag)
                        = temp;
                        
                    tempTensor2->rank = rank;
                    break;
                }
            }
        }
        
        if( iszero(tempTensor2->pptypeT[diag][diag]) ) // != 0
        {
            tempTensor2( diag, diag, 1, tempTensor2->numCol -diag )
                /= tempTensor2->pptypeT[diag][diag];
            
            for( int i=0; i< diag; i++ )
            {
                tempTensor2( i, diag, 1, tempTensor2->numCol -diag )
                    -= tempTensor2->pptypeT[i][diag]
                     * tempTensor2( diag, diag, 1, tempTensor2->numCol -diag );
                      
                tempTensor2->pptypeT[i][diag] = 0;
            }
            
            for( int i=diag+1; i< tempTensor2->numRow; i++ )
            {
                tempTensor2( i, diag, 1, tempTensor2->numCol -diag )
                    -= tempTensor2->pptypeT[i][diag]
                     * tempTensor2( diag, diag, 1, tempTensor2->numCol -diag );
                      
                tempTensor2->pptypeT[i][diag] = 0;
            }
        }
    }
    
    return *tempTensor2;
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
// Inverse Tensor2
template<class typeT>
inline Tensor2<typeT>& Tensor2<typeT>::operator!()
{
    if( numRow == numCol )
    {
        Tensor2<typeT>* tempTensor2;
        tempTensor2 = new Tensor2<typeT>( numRow, 2*numCol,
                                          tens2::origin | tens2::stable
                                        );
        storTensor2 = tempTensor2;
        
        tempTensor2->ident(0);
        *tempTensor2 = *this;
        
        return (~(*tempTensor2))(0,numCol,numRow,numCol);
    }
    else
    {
        return *this;
    }
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
template<class typeT>
inline Tensor2<typeT>& sin( Tensor2<typeT>& paramTensor2 )
{
    Tensor2<typeT>* tempTensor2;
    tempTensor2 = new Tensor2<typeT>( paramTensor2.numRow,
                                      paramTensor2.numCol,
                                      tens2::origin | tens2::stable
                                    );
    storTensor2 = tempTensor2;
    
    for( int i=0; i< paramTensor2.numRow; i++ )
    {
        for( int j=0; j< paramTensor2.numCol; j++ )
        {
            long double x = paramTensor2.pptypeT[i][j] 
                           -2*M_PI *(int)(paramTensor2.pptypeT[i][j]/2/M_PI);
            tempTensor2->pptypeT[i][j] = 0;
            
            for( int k= ACCURACY2; k> 0; k-= 2 )
            {
                tempTensor2->pptypeT[i][j] += 1;
                tempTensor2->pptypeT[i][j] *= x*x;
                tempTensor2->pptypeT[i][j] /= (k+1)*k;
                
                k -= 2;
                
                tempTensor2->pptypeT[i][j] -= 1;
                tempTensor2->pptypeT[i][j] *= x*x;
                tempTensor2->pptypeT[i][j] /= (k+1)*k;
            }
            tempTensor2->pptypeT[i][j] += 1;
            tempTensor2->pptypeT[i][j] *= x;
            tempTensor2->pptypeT[i][j] = iszero(tempTensor2->pptypeT[i][j]);
        }
    }
        
    return *tempTensor2;
}

template<>
inline Tensor2<int>& sin( Tensor2<int>& paramTensor2 )
{
    Tensor2<int>* tempTensor2;
    tempTensor2 = new Tensor2<int>( paramTensor2.numRow,
                                    paramTensor2.numCol,
                                    tens2::origin | tens2::stable
                                  );
    storTensor2 = tempTensor2;
    
    for( int i=0; i< paramTensor2.numRow; i++ )
    {
        for( int j=0; j< paramTensor2.numCol; j++ )
        {
            long double x = paramTensor2.pptypeT[i][j] %360 *M_PI /180;
            
            long double sinx = 0;
            
            for( int k= ACCURACY2; k> 0; k-= 2 )
            {
                sinx += 1;
                sinx *= x*x;
                sinx /= (k+1)*k;
                
                k -= 2;
                
                sinx -= 1;
                sinx *= x*x;
                sinx /= (k+1)*k;
            }
            sinx += 1;
            sinx *= x;
            tempTensor2->pptypeT[i][j] = (int)( sinx*1e3 );
        }
    }
        
    return *tempTensor2;
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
template<class typeT>
inline Tensor2<typeT>& cos( Tensor2<typeT>& paramTensor2 )
{
    Tensor2<typeT>* tempTensor2;
    tempTensor2 = new Tensor2<typeT>( paramTensor2.numRow,
                                      paramTensor2.numCol,
                                      tens2::origin | tens2::stable
                                    );
    storTensor2 = tempTensor2;
    
    for( int i=0; i< paramTensor2.numRow; i++ )
    {
        for( int j=0; j< paramTensor2.numCol; j++ )
        {
            long double x = paramTensor2.pptypeT[i][j] 
                           -2*M_PI *(int)(paramTensor2.pptypeT[i][j]/2/M_PI);
            tempTensor2->pptypeT[i][j] = 0;
            
            for( int k= ACCURACY2; k> 0; k-= 2 )
            {
                tempTensor2->pptypeT[i][j] += 1;
                tempTensor2->pptypeT[i][j] *= x*x;
                tempTensor2->pptypeT[i][j] /= k*(k-1);
                
                k -= 2;
                
                tempTensor2->pptypeT[i][j] -= 1;
                tempTensor2->pptypeT[i][j] *= x*x;
                tempTensor2->pptypeT[i][j] /= k*(k-1);
            }
            tempTensor2->pptypeT[i][j] += 1;
            tempTensor2->pptypeT[i][j] = iszero(tempTensor2->pptypeT[i][j]);
        }
    }
    
    return *tempTensor2;
}

template<>
inline Tensor2<int>& cos( Tensor2<int>& paramTensor2 )
{
    Tensor2<int>* tempTensor2;
    tempTensor2 = new Tensor2<int>( paramTensor2.numRow,
                                    paramTensor2.numCol,
                                    tens2::origin | tens2::stable
                                  );
    storTensor2 = tempTensor2;
    
    for( int i=0; i< paramTensor2.numRow; i++ )
    {
        for( int j=0; j< paramTensor2.numCol; j++ )
        {
            long double x = paramTensor2.pptypeT[i][j] %360 *M_PI /180;
            
            long double cosx = 0;
            
            for( int k= ACCURACY2; k> 0; k-= 2 )
            {
                cosx += 1;
                cosx *= x*x;
                cosx /= k*(k-1);
                
                k -= 2;
                
                cosx -= 1;
                cosx *= x*x;
                cosx /= k*(k-1);
            }
            cosx += 1;
            tempTensor2->pptypeT[i][j] = (int)( cosx*1e3 );
        }
    }
        
    return *tempTensor2;
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
template<class typeT>
inline Tensor2<typeT>& exp( Tensor2<typeT>& paramTensor2 )
{
    Tensor2<typeT>* tempTensor2;
    tempTensor2 = new Tensor2<typeT>( paramTensor2.numRow,
                                      paramTensor2.numCol,
                                      tens2::origin | tens2::stable
                                    );
    storTensor2 = tempTensor2;
    
    for( int i=0; i< paramTensor2.numRow; i++ )
    {
        for( int j=0; j< paramTensor2.numCol; j++ )
        {
            tempTensor2->pptypeT[i][j] = 0;
            
            for( int k= ACCURACY2; k> 0; k-- )
            {
                tempTensor2->pptypeT[i][j] += 1;
                tempTensor2->pptypeT[i][j] *= paramTensor2.pptypeT[i][j];
                tempTensor2->pptypeT[i][j] /= k;
            }
            tempTensor2->pptypeT[i][j] += 1;
        }
    }
    
    return *tempTensor2;
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
template<class typeT>
inline Tensor2<typeT>& atan( Tensor2<typeT>& paramTensor2 )
{
    Tensor2<typeT>* tempTensor2;
    tempTensor2 = new Tensor2<typeT>( paramTensor2.numRow,
                                      paramTensor2.numCol,
                                      tens2::origin | tens2::stable
                                    );
    storTensor2 = tempTensor2;
    
    for( int i=0; i< paramTensor2.numRow; i++ )
    {
        for( int j=0; j< paramTensor2.numCol; j++ )
        {
            long double x = paramTensor2.pptypeT[i][j];
            long double y;
            
            tempTensor2->pptypeT[i][j] = 0;
            
            for( int k= ACCURACY3; k> 0; k-= 2 )
            {
                y = k;
                tempTensor2->pptypeT[i][j] += 1/(y+1);
                tempTensor2->pptypeT[i][j] *= x*x;
                
                k -= 2;
                y = k;
                
                tempTensor2->pptypeT[i][j] -= 1/(y+1);
                tempTensor2->pptypeT[i][j] *= x*x;
            }
            tempTensor2->pptypeT[i][j] += 1;
            tempTensor2->pptypeT[i][j] *= x;
        }
    }
        
    return *tempTensor2;
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

#endif
