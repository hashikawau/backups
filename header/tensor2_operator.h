#ifndef __TENSOR2_OPERATOR
#define __TENSOR2_OPERATOR
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
template<class typeT>
inline Tensor2<typeT>& Tensor2<typeT>::operator[]( int row )
{
    if( row<0 || row>=numRow )
    {
        //====================
        row = 0;
    }
    
    return this( row, 0, 1, numCol );
}

template<class typeT>
inline Tensor2<typeT>& Tensor2<typeT>::operator()( int col )
{    
    if( col<0 || col>=numCol )
    {
        //=====================
        col = 0;
    }
    
    return this( 0, col, numRow, 1 );
}

template<class typeT>
inline typeT& Tensor2<typeT>::operator()( int row, int col )
{
    if( row <0 || col <0 || row >= numRow || col >= numCol )
    {
        //=========================
        return this->pptypeT[0][0];
    }
    else
    {
        return this->pptypeT[row][col];
    }
}

template<class typeT>
inline Tensor2<typeT>& Tensor2<typeT>::operator()( int rowBeg, int colBeg,
                                                   int numRowElem,
                                                   int numColElem
                                                 )
{
    if( rowBeg +numRowElem > numRow
     || colBeg +numColElem > numCol
     || numRowElem < 0
     || numColElem < 0
     || rowBeg +numRowElem < 0
     || colBeg +numColElem < 0
    )
    {
        //========================
    }
    
    Tensor2<typeT>* tempTensor2;
    tempTensor2 = new Tensor2( numRowElem, numColElem,
                               tens2::reference | tens2::stable
                             );
    storTensor2 = tempTensor2;
    
    for( int i=0; i< numRowElem; i++ )
    {
        tempTensor2->pptypeT[i] = &this->pptypeT[i +rowBeg][colBeg];
    }
    
    return *tempTensor2;
}


/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
template<class typeT>
inline Tensor2<typeT>& Tensor2<typeT>::operator=( Tensor2<typeT>& tempTensor2 )
{
    //================ dynamic or stable
    if( state & tens2::dynamic )
    {
        this->newTensor2( tempTensor2.numRow, tempTensor2.numCol );
        for( int i=0; i< numRow; i++ )
        {
            for( int j=0; j< numCol; j++ )
            {
                pptypeT[i][j] =tempTensor2.pptypeT[i][j];
            }
        }
    }
    else
    if( state & tens2::stable )
    {
        int row = numRow < tempTensor2.numRow ? numRow : tempTensor2.numRow;
        int col = numCol < tempTensor2.numCol ? numCol : tempTensor2.numCol;
        for( int i=0; i< row; i++ )
        {
            for( int j=0; j< col; j++ )
            {
                pptypeT[i][j] = tempTensor2.pptypeT[i][j];
            }
        }
    }
    
    rank = tempTensor2.rank;
    
    return *this;
}

template<class typeT1, class typeT2>
inline Tensor2<typeT1>& operator=( Tensor2<typeT1>& tempTensor21,
                                   Tensor2<typeT2>& tempTensor22
                                 )
{
    //================ dynamic or stable
    if( tempTensor21.state & tens2::dynamic )
    {
        tempTensor21.newTensor2( tempTensor22.numRow, tempTensor22.numCol );
        
        for( int i=0; i< tempTensor22.numRow; i++ )
        {
            for( int j=0; j< tempTensor22.numCol; j++ )
            {
                tempTensor21.pptypeT[i][j]
                    = (typeT1)tempTensor22.pptypeT[i][j];
            }
        }
    }
    else
    if( tempTensor21.state & tens2::stable )
    {
        int row = tempTensor21.numRow < tempTensor22.numRow ?
                  tempTensor21.numRow : tempTensor22.numRow;
                  
        int col = tempTensor21.numCol < tempTensor22.numCol ?
                  tempTensor21.numCol : tempTensor22.numCol;
        
        for( int i=0; i< row; i++ )
        {
            for( int j=0; j< col; j++ )
            {
                tempTensor21.pptypeT[i][j]
                    = (typeT1)tempTensor22.pptypeT[i][j];
            }
        }
    }
    
    tempTensor21.rank = tempTensor22.rank;
    
    return tempTensor21;
}


template<class typeT>
inline Tensor2<typeT>& Tensor2<typeT>::operator=( typeT tVal )
{
    for( int i=0; i< numRow; i++ )
    {
        for( int j=0; j< numCol; j++ )
        {
            pptypeT[i][j] = tVal;
        }
    }
    
    return *this;
}

template<class typeT, class typeT2>
inline Tensor2<typeT>& operator=( Tensor2<typeT>& tempTensor2, typeT2 t2Val )
{
    for( int i=0; i< tempTensor2.numRow; i++ )
    {
        for( int j=0; j< tempTensor2.numCol; j++ )
        {
            tempTensor2.pptypeT[i][j] = (typeT)t2Val;
        }
    }
    
    return tempTensor2;
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/


#endif










