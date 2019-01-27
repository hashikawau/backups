#ifndef __TENSOR2_BASE
#define __TENSOR2_BASE
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
template<class typeT>
inline Tensor2<typeT>::Tensor2( int row, int col, int stateTemp )
{
    pptypeT = NULL;
    int lstate, hstate;
    
    //=================== origin or reference
    if( stateTemp & tens2::origin )
    {
        lstate = tens2::origin;
    }
    else
    if( stateTemp & tens2::reference )
    {
        lstate = tens2::reference;
    }
    else
    {
        lstate = tens2::origin;
    }
    
    //================ dynamic or stable
    if( stateTemp & tens2::dynamic )
    {
        hstate = tens2::dynamic;
    }
    else
    if( stateTemp & tens2::stable )
    {
        hstate = tens2::stable;
    }
    else
    {
        hstate = tens2::dynamic;
    }
    
    //=================
    if( row >0 && col >0 )
    {
        state = lstate | tens2::dynamic;
        
        newTensor2( row, col );
        
        state = lstate | hstate;
    }
    else
    {
        numRow = 0;
        numCol = 0;
        rank   = 0;
        state = lstate | hstate;
    }
    
}

template<class typeT>
inline Tensor2<typeT>::Tensor2( char *c, int row, int col, int stateTemp )
{
    pptypeT = NULL;
    int lstate, hstate;
    
    //=================== origin or reference
    if( stateTemp & tens2::origin )
    {
        lstate = tens2::origin;
    }
    else
    if( stateTemp & tens2::reference )
    {
        lstate = tens2::reference;
    }
    else
    {
        lstate = tens2::origin;
    }
    
    //================ dynamic or stable
    if( stateTemp & tens2::dynamic )
    {
        hstate = tens2::dynamic;
    }
    else
    if( stateTemp & tens2::stable )
    {
        hstate = tens2::stable;
    }
    else
    {
        hstate = tens2::dynamic;
    }
    
    state = lstate | tens2::dynamic;
    
    readTensor2( c, row, col );
    
    state = lstate | hstate;
}

template<class typeT>
inline Tensor2<typeT>::~Tensor2()
{
    delTensor2();
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
// NewTensor2
template<class typeT>
inline void Tensor2<typeT>::newTensor2( int row, int col )
{
    if( state & tens2::dynamic )
    {
        delTensor2();
        numRow = row;
        numCol = col;
        rank   = row < col ? row:col;
        
        pptypeT = new typeT *[numRow];
    
        if( state & tens2::origin )
        {
            for( int i=0; i< numRow; i++ )
            {
                pptypeT[i] = new typeT [numCol];
            }
        }
    }
    else
    {
        zeros();
    }
}

// DeleteTensor2
template<class typeT>
inline void Tensor2<typeT>::delTensor2()
{
    if( pptypeT )
    {
        if( state & tens2::origin )
        {
            for( int i=0; i< numRow; i++ )
            {
                delete [] pptypeT[i];
                pptypeT[i] = NULL;
            }
        }
        
        delete [] pptypeT;
        pptypeT = NULL;
    }
}

// ReadTensor2
template<class typeT>
inline Tensor2<typeT>& Tensor2<typeT>::readTensor2( char *fileName,
                                                    int row, int col
                                                  )
{
    if( ifstream in( fileName ) )
    {
        if(!col)
        {
            col = 0;
            char c;
            char cprev = ' ';
            while(in.get(c))
            {
                if( c=='\n' && col ){ break; }
                else if( c!=' ' && cprev==' ' ){ col++; }
                cprev = c;
            }
            
            row = 0;
            typeT tempTypeT;
            in.seekg( 0, ios::beg );
            while( in>> tempTypeT ){ row++; }
            
            if(col){ row = (int)(row/col); }
            else { row = 1; col = 1; }
        }
        
        in.seekg( 0, ios::beg );
        newTensor2( row, col );
        for( int i=0; i< numRow; i++ )
        {
            for( int j=0; j< numCol; j++ )
            {
                in >> pptypeT[i][j];
            }
        }
        in.close();
    }
    //=============else{}
    
    return *this;
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
// Zeros
template<class typeT>
inline Tensor2<typeT>& Tensor2<typeT>::zeros( int row, int col )
{
    if( row >0 && col >0 )
    {
        int stateTemp = state;
        state = tens2::dynamic | (state & 0x0F);
        newTensor2( row, col );
        state = stateTemp;
    }
    
    for( int i=0; i< numRow; i++ )
    {
        for( int j=0; j< numCol; j++ )
        {
            pptypeT[i][j] = 0;
        }
    }
    
    return *this;
}


// Identity
template<class typeT>
inline Tensor2<typeT>& Tensor2<typeT>::ident(int direction)
{
    zeros();
    
    if(direction)
    {
        for( int i=0; i< rank; i++ )
        {
            pptypeT[i][i] = 1;
        }
    }
    else
    {
        int row = numRow -rank;
        int col = numCol -rank;
        for( int i=0; i< rank; i++ )
        {
            pptypeT[i +row][i +col] = 1;
        }
    }
    
    return *this;
}
template<class typeT>
inline Tensor2<typeT>& Tensor2<typeT>::ident( int row, int col )
{
    if( row >0 && col >0 )
    {
        int stateTemp = state;
        state = tens2::dynamic | (state & 0x0F);
        newTensor2( row, col );
        state = stateTemp;
    }
    
    ident();
    
    return *this;
}

// Transpose
template<class typeT>
inline Tensor2<typeT>& Tensor2<typeT>::trans()
{
    Tensor2<typeT>* tempTensor2;
    tempTensor2 = new Tensor2( numCol, numRow,
                               tens2::origin | tens2::stable
                             );
    storTensor2 = tempTensor2;
    
    for( int i=0; i< numRow; i++ )
    {
        for( int j=0; j< numCol; j++ )
        {
            tempTensor2->pptypeT[j][i] = pptypeT[i][j];
        }
    }
    
    return *tempTensor2;
}

#endif







