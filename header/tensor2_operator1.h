#ifndef __TENSOR2_OPERATOR1
#define __TENSOR2_OPERATOR1
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
template<class typeT>
inline Tensor2<typeT>& Tensor2<typeT>::operator+( typeT tVal )
{
    Tensor2<typeT>* tempTensor2;
    tempTensor2 = new Tensor2( numRow, numCol,
                               tens2::origin | tens2::stable
                             );
    storTensor2 = tempTensor2;
    
    for( int i=0; i< numRow; i++ )
    {
        for( int j=0; j< numCol; j++ )
        {
            tempTensor2->pptypeT[i][j] = pptypeT[i][j] +tVal;
        }
    }
    
    return *tempTensor2;
}

template<class typeT>
inline Tensor2<typeT>& Tensor2<typeT>::operator+=( typeT tVal )
{    
    for( int i=0; i< numRow; i++ )
    {
        for( int j=0; j< numCol; j++ )
        {
            pptypeT[i][j] += tVal;
        }
    }
    
    return *this;
}

template<class typeT, class typeT2>
inline Tensor2<typeT>& operator+( Tensor2<typeT>& tempTensor2, typeT2 t2Val )
{
    return tempTensor2 +(typeT)t2Val;
}

template<class typeT, class typeT2>
inline Tensor2<typeT>& operator+( typeT2 t2Val, Tensor2<typeT>& tempTensor2 )
{
    return tempTensor2 +(typeT)t2Val;
}


/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
template<class typeT>
inline Tensor2<typeT>& Tensor2<typeT>::operator-()
{
    Tensor2<typeT>* tempTensor2;
    tempTensor2 = new Tensor2( numRow, numCol,
                               tens2::origin | tens2::stable
                             );
    storTensor2 = tempTensor2;
    
    for( int i=0; i< numRow; i++ )
    {
        for( int j=0; j< numCol; j++ )
        {
            tempTensor2->pptypeT[i][j] = -pptypeT[i][j];
        }
    }
    
    return *tempTensor2;
}

template<class typeT>
inline Tensor2<typeT>& Tensor2<typeT>::operator-( typeT tVal )
{
    Tensor2<typeT>* tempTensor2;
    tempTensor2 = new Tensor2( numRow, numCol,
                               tens2::origin | tens2::stable
                             );
    storTensor2 = tempTensor2;
    
    for( int i=0; i< numRow; i++ )
    {
        for( int j=0; j< numCol; j++ )
        {
            tempTensor2->pptypeT[i][j] = pptypeT[i][j] -tVal;
        }
    }
    
    return *tempTensor2;
}

template<class typeT>
inline Tensor2<typeT>& Tensor2<typeT>::operator-=( typeT tVal )
{    
    for( int i=0; i< numRow; i++ )
    {
        for( int j=0; j< numCol; j++ )
        {
            pptypeT[i][j] -= tVal;
        }
    }
    
    return *this;
}

template<class typeT, class typeT2>
inline Tensor2<typeT>& operator-( Tensor2<typeT>& tempTensor2, typeT2 t2Val )
{
    return tempTensor2 -(typeT)t2Val;
}

template<class typeT, class typeT2>
inline Tensor2<typeT>& operator-( typeT2 t2Val, Tensor2<typeT>& tempTensor2 )
{
    return -tempTensor2 +(typeT)t2Val;
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
template<class typeT>
inline Tensor2<typeT>& Tensor2<typeT>::operator*( typeT tVal )
{
    Tensor2<typeT>* tempTensor2;
    tempTensor2 = new Tensor2( numRow, numCol,
                               tens2::origin | tens2::stable
                             );
    storTensor2 = tempTensor2;
    
    for( int i=0; i< numRow; i++ )
    {
        for( int j=0; j< numCol; j++ )
        {
            tempTensor2->pptypeT[i][j] = pptypeT[i][j] *tVal;
        }
    }
    
    return *tempTensor2;
}

template<class typeT>
inline Tensor2<typeT>& Tensor2<typeT>::operator*=( typeT tVal )
{
    *this = *this * tVal;
    
    return *this;
}

template<class typeT, class typeT2>
inline Tensor2<typeT>& operator*=( Tensor2<typeT>& paramTensor2, typeT2 t2Val )
{
    paramTensor2 = paramTensor2 * t2Val;
    
    return paramTensor2;
}

template<class typeT, class typeT2>
inline Tensor2<typeT>& operator*( Tensor2<typeT>& paramTensor2, typeT2 t2Val )
{
    Tensor2<double> doubleTensor2( paramTensor2.numRow, paramTensor2.numCol );
    Tensor2<typeT>* tempTensor2;
    tempTensor2 = new Tensor2<typeT>( paramTensor2.numRow, paramTensor2.numCol,
                                      tens2::origin | tens2::stable
                                    );
    storTensor2 = tempTensor2;
    
    for( int i=0; i< paramTensor2.numRow; i++ )
    {
        for( int j=0; j< paramTensor2.numCol; j++ )
        {
            doubleTensor2(i,j) = paramTensor2.pptypeT[i][j] *t2Val;
        }
    }
    
    *tempTensor2 = doubleTensor2;
    
    return *tempTensor2;
}

template<class typeT, class typeT2>
inline Tensor2<typeT>& operator*( typeT2 t2Val, Tensor2<typeT>& tempTensor2 )
{
    return tempTensor2 *t2Val;
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
template<class typeT>
inline Tensor2<typeT>& Tensor2<typeT>::operator/( typeT tVal )
{
    if( !tVal )
    {
        return *this;
    }
    
    Tensor2<double> doubleTensor2( numRow, numCol );
    Tensor2<typeT>* tempTensor2;
    tempTensor2 = new Tensor2( numRow, numCol,
                               tens2::origin | tens2::stable
                             );
    storTensor2 = tempTensor2;
    
    for( int i=0; i< numRow; i++ )
    {
        for( int j=0; j< numCol; j++ )
        {
            doubleTensor2(i,j) = pptypeT[i][j] /tVal;
        }
    }
    
    *tempTensor2 = doubleTensor2;
    
    return *tempTensor2;
}

template<class typeT>
inline Tensor2<typeT>& Tensor2<typeT>::operator/=( typeT tVal )
{
    *this = *this /tVal;
    
    return *this;
}

template<class typeT, class typeT2>
inline Tensor2<typeT>& operator/( Tensor2<typeT>& paramTensor2, typeT2 t2Val )
{
    if( !t2Val )
    {
        return paramTensor2;
    }
    
    Tensor2<double> doubleTensor2( paramTensor2.numRow, paramTensor2.numCol );
    Tensor2<typeT>* tempTensor2;
    tempTensor2 = new Tensor2<typeT>( paramTensor2.numRow, paramTensor2.numCol,
                                      tens2::origin | tens2::stable
                                    );
    storTensor2 = tempTensor2;
    
    for( int i=0; i< paramTensor2.numRow; i++ )
    {
        for( int j=0; j< paramTensor2.numCol; j++ )
        {
            doubleTensor2(i,j) = paramTensor2.pptypeT[i][j] /t2Val;
        }
    }
    
    *tempTensor2 = doubleTensor2;
    
    return *tempTensor2;
}


template<class typeT, class typeT2>
inline Tensor2<typeT>& operator/( typeT2 t2Val, Tensor2<typeT>& paramTensor2 )
{
    Tensor2<double> doubleTensor2( paramTensor2.numRow, paramTensor2.numCol );
    Tensor2<typeT>* tempTensor2;
    tempTensor2 = new Tensor2<typeT>( paramTensor2.numRow, paramTensor2.numCol,
                                      tens2::origin | tens2::stable
                                    );
    storTensor2 = tempTensor2;
    
    for( int i=0; i< paramTensor2.numRow; i++ )
    {
        for( int j=0; j< paramTensor2.numCol; j++ )
        {
            if( paramTensor2.pptypeT[i][j] )
            {
                doubleTensor2(i,j)
                    = t2Val /paramTensor2.pptypeT[i][j];
            }
            else
            {
                doubleTensor2(i,j) = t2Val;
            }
        }
    }
    
    *tempTensor2 = doubleTensor2;
    
    return *tempTensor2;
}


/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
template<class typeT>
inline Tensor2<typeT>& Tensor2<typeT>::operator%( typeT tVal )
{
    //==================error
    
    return *this;
}

template<>
inline Tensor2<int>& Tensor2<int>::operator%( int tVal )
{
    if( !tVal )
    {
        //=================cout << "error in operator%()----% by zero\n";
        return *this;
    }
    
    Tensor2<int>* tempTensor2;
    tempTensor2 = new Tensor2( numRow, numCol,
                               tens2::origin | tens2::stable
                             );
    storTensor2 = tempTensor2;
    
    for( int i=0; i< numRow; i++ )
    {
        for( int j=0; j< numCol; j++ )
        {
            tempTensor2->pptypeT[i][j] = pptypeT[i][j] %tVal;
        }
    }
    
    return *tempTensor2;
}

template<>
inline Tensor2<double>& Tensor2<double>::operator%( double tVal )
{
    Tensor2<double>* tempTensor2;
    tempTensor2 = new Tensor2( numRow, numCol,
                               tens2::origin | tens2::stable
                             );
    storTensor2 = tempTensor2;
    
    for( int i=0; i< numRow; i++ )
    {
        for( int j=0; j< numCol; j++ )
        {
            tempTensor2->pptypeT[i][j] = pptypeT[i][j]
                                       -tVal *(int)( pptypeT[i][j] /tVal );
        }
    }
    
    return *tempTensor2;
}

template<class typeT>
inline Tensor2<typeT>& Tensor2<typeT>::operator%=( typeT tVal )
{    
    *this = *this %tVal;
    
    return *this;
}


/*
template<class typeT, class typeT2>
inline Tensor2<typeT>& operator/( typeT2 t2Val, Tensor2<typeT>& matx )
{
}
*/

#endif
