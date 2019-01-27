#ifndef __TENSOR2_OPERATOR2
#define __TENSOR2_OPERATOR2
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
template<class typeT>
inline Tensor2<typeT>& Tensor2<typeT>::operator+(Tensor2<typeT>& paramTensor2)
{
    Tensor2<typeT>* largeRowTensor2 = (numRow > paramTensor2.numRow)?
                                      this: &paramTensor2;
    Tensor2<typeT>* largeColTensor2 = (numCol > paramTensor2.numCol)?
                                      this: &paramTensor2;
    
    Tensor2<typeT>* tempTensor2;
    tempTensor2 = new Tensor2( largeRowTensor2->numRow,
                               largeColTensor2->numCol,
                               tens2::origin | tens2::stable
                             );
    storTensor2 = tempTensor2;
    
    if( largeRowTensor2 == largeColTensor2 )
    {
        Tensor2<typeT>* largeTensor2 = largeRowTensor2;
        Tensor2<typeT>* smallTensor2 = (largeTensor2 != this)?
                                       this: &paramTensor2;
        
        for( int i=0; i< smallTensor2->numRow; i++ )
        {
            for( int j=0; j< smallTensor2->numCol; j++ )
            {
                tempTensor2->pptypeT[i][j]
                    = this->pptypeT[i][j]
                     + paramTensor2.pptypeT[i][j];
            }
            for( int j= smallTensor2->numCol; j< largeTensor2->numCol; j++ )
            {
                tempTensor2->pptypeT[i][j]
                    = largeTensor2->pptypeT[i][j];
            }
        }
        
        for( int i= smallTensor2->numRow; i< largeTensor2->numRow; i++ )
        {
            for( int j=0; j< largeTensor2->numCol; j++ )
            {
                tempTensor2->pptypeT[i][j]
                    = largeTensor2->pptypeT[i][j];
            }
        }
    }
    else
    {
        for( int i=0; i< largeColTensor2->numRow; i++ )
        {
            for( int j=0; j< largeRowTensor2->numCol; j++ )
            {
                tempTensor2->pptypeT[i][j]
                    = largeRowTensor2->pptypeT[i][j]
                     + largeColTensor2->pptypeT[i][j];
            }
        }
        
        for( int i= largeColTensor2->numRow; i< largeRowTensor2->numRow; i++ )
        {
            for( int j=0; j< largeRowTensor2->numCol; j++ )
            {
                tempTensor2->pptypeT[i][j]
                    = largeRowTensor2->pptypeT[i][j];
            }
        }
        
        for( int i=0; i< largeColTensor2->numRow; i++ )
        {
            for( int j= largeRowTensor2->numCol;
                     j< largeColTensor2->numCol ; j++ )
            {
                tempTensor2->pptypeT[i][j]
                    = largeColTensor2->pptypeT[i][j];
            }
        }
        
        tempTensor2( largeColTensor2->numRow,
                     largeRowTensor2->numCol,
                     largeRowTensor2->numRow -largeColTensor2->numRow,
                     largeColTensor2->numCol -largeRowTensor2->numCol
                   ).ident(0);
    }
    
    return *tempTensor2;
}



template<class typeT>
inline Tensor2<typeT>& Tensor2<typeT>::operator+=(Tensor2<typeT>& paramTensor2)
{
    *this = *this + paramTensor2;
    
    return *this;
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
template<class typeT>
inline Tensor2<typeT>& Tensor2<typeT>::operator-(Tensor2<typeT>& paramTensor2)
{
    Tensor2<typeT>* largeRowTensor2 = (numRow > paramTensor2.numRow)?
                                      this: &paramTensor2;
    Tensor2<typeT>* largeColTensor2 = (numCol > paramTensor2.numCol)?
                                      this: &paramTensor2;
    
    Tensor2<typeT>* tempTensor2;
    tempTensor2 = new Tensor2( largeRowTensor2->numRow,
                               largeColTensor2->numCol,
                               tens2::origin | tens2::stable
                             );
    storTensor2 = tempTensor2;
    
    if( largeRowTensor2 == largeColTensor2 )
    {
        Tensor2<typeT>* largeTensor2 = largeRowTensor2;
        Tensor2<typeT>* smallTensor2 = (largeTensor2 != this)?
                                       this: &paramTensor2;
        
        for( int i=0; i< smallTensor2->numRow; i++ )
        {
            for( int j=0; j< smallTensor2->numCol; j++ )
            {
                tempTensor2->pptypeT[i][j]
                    = smallTensor2->pptypeT[i][j]
                     - largeTensor2->pptypeT[i][j];
            }
            for( int j= smallTensor2->numCol; j< largeTensor2->numCol; j++ )
            {
                tempTensor2->pptypeT[i][j]
                    = largeTensor2->pptypeT[i][j];
            }
        }
        
        for( int i= smallTensor2->numRow; i< largeTensor2->numRow; i++ )
        {
            for( int j=0; j< largeTensor2->numCol; j++ )
            {
                tempTensor2->pptypeT[i][j]
                    = largeTensor2->pptypeT[i][j];
            }
        }
    }
    else
    {
        for( int i=0; i< largeColTensor2->numRow; i++ )
        {
            for( int j=0; j< largeRowTensor2->numCol; j++ )
            {
                tempTensor2->pptypeT[i][j]
                    = this->pptypeT[i][j]
                     - paramTensor2.pptypeT[i][j];
            }
        }
        
        for( int i= largeColTensor2->numRow; i< largeRowTensor2->numRow; i++ )
        {
            for( int j=0; j< largeRowTensor2->numCol; j++ )
            {
                tempTensor2->pptypeT[i][j]
                    = largeRowTensor2->pptypeT[i][j];
            }
        }
        
        for( int i=0; i< largeColTensor2->numRow; i++ )
        {
            for( int j= largeRowTensor2->numCol;
                     j< largeColTensor2->numCol ; j++ )
            {
                tempTensor2->pptypeT[i][j]
                    = largeColTensor2->pptypeT[i][j];
            }
        }
        
        tempTensor2( largeColTensor2->numRow,
                     largeRowTensor2->numCol,
                     largeRowTensor2->numRow -largeColTensor2->numRow,
                     largeColTensor2->numCol -largeRowTensor2->numCol
                   ).ident(0);
    }
    
    return *tempTensor2;
}



template<class typeT>
inline Tensor2<typeT>& Tensor2<typeT>::operator-=(Tensor2<typeT>& paramTensor2)
{
    *this = *this - paramTensor2;
    
    return *this;
}



/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
template<class typeT>
inline Tensor2<typeT>& Tensor2<typeT>::operator*(Tensor2<typeT>& paramTensor2)
{
    Tensor2<typeT>* tempTensor2;
    tempTensor2 = new Tensor2( numRow,
                               paramTensor2.numCol,
                               tens2::origin | tens2::stable
                             );
    storTensor2 = tempTensor2;
    
    if( numCol == paramTensor2.numRow )
    {
        for( int i=0; i< numRow; i++ )
        {
            for( int j=0; j< paramTensor2.numCol; j++ )
            {
                tempTensor2->pptypeT[i][j] = 0;
                
                for( int k=0; k< numCol; k++ )
                {
                    tempTensor2->pptypeT[i][j]
                        += pptypeT[i][k] * paramTensor2.pptypeT[k][j];
                }
            }
        }
    }
    else
    if( numCol > paramTensor2.numRow )
    {
        for( int i=0; i< numRow; i++ )
        {
            for( int j=0; j< paramTensor2.numCol; j++ )
            {
                tempTensor2->pptypeT[i][j] = 0;
                
                for( int k=0; k< paramTensor2.numRow; k++ )
                {
                    tempTensor2->pptypeT[i][j]
                        += pptypeT[i][k] * paramTensor2.pptypeT[k][j];
                }
            }
        }
    }
    else
    {
        //===================cout << "Warning respect to operator*()\n";
        return *this;
    }
    
    return *tempTensor2;
    
}
template<class typeT>
inline Tensor2<typeT>& Tensor2<typeT>::operator*=(Tensor2<typeT>& paramTensor2)
{
    *this = *this * paramTensor2;
    
    return *this;
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
template<class typeT>
inline Tensor2<typeT>& Tensor2<typeT>::operator/(Tensor2<typeT>& paramTensor2)
{
    Tensor2<typeT>* largeRowTensor2 = (numRow > paramTensor2.numRow)?
                                      this: &paramTensor2;
    Tensor2<typeT>* largeColTensor2 = (numCol > paramTensor2.numCol)?
                                      this: &paramTensor2;
    
    Tensor2<typeT>* tempTensor2;
    tempTensor2 = new Tensor2( largeRowTensor2->numRow,
                               largeColTensor2->numCol,
                               tens2::origin | tens2::stable
                             );
    storTensor2 = tempTensor2;
    
    if( largeRowTensor2 == largeColTensor2 )
    {
        Tensor2<typeT>* largeTensor2 = largeRowTensor2;
        Tensor2<typeT>* smallTensor2 = (largeTensor2 != this)?
                                       this: &paramTensor2;
        
        for( int i=0; i< smallTensor2->numRow; i++ )
        {
            for( int j=0; j< smallTensor2->numCol; j++ )
            {
                tempTensor2->pptypeT[i][j]
                    = smallTensor2->pptypeT[i][j]
                     / largeTensor2->pptypeT[i][j];
            }
            for( int j= smallTensor2->numCol; j< largeTensor2->numCol; j++ )
            {
                tempTensor2->pptypeT[i][j]
                    = largeTensor2->pptypeT[i][j];
            }
        }
        
        for( int i= smallTensor2->numRow; i< largeTensor2->numRow; i++ )
        {
            for( int j=0; j< largeTensor2->numCol; j++ )
            {
                tempTensor2->pptypeT[i][j]
                    = largeTensor2->pptypeT[i][j];
            }
        }
    }
    else
    {
        for( int i=0; i< largeColTensor2->numRow; i++ )
        {
            for( int j=0; j< largeRowTensor2->numCol; j++ )
            {
                tempTensor2->pptypeT[i][j]
                    = this->pptypeT[i][j]
                     / paramTensor2.pptypeT[i][j];
            }
        }
        
        for( int i= largeColTensor2->numRow; i< largeRowTensor2->numRow; i++ )
        {
            for( int j=0; j< largeRowTensor2->numCol; j++ )
            {
                tempTensor2->pptypeT[i][j]
                    = largeRowTensor2->pptypeT[i][j];
            }
        }
        
        for( int i=0; i< largeColTensor2->numRow; i++ )
        {
            for( int j= largeRowTensor2->numCol;
                     j< largeColTensor2->numCol ; j++ )
            {
                tempTensor2->pptypeT[i][j]
                    = largeColTensor2->pptypeT[i][j];
            }
        }
        
        tempTensor2( largeColTensor2->numRow,
                     largeRowTensor2->numCol,
                     largeRowTensor2->numRow -largeColTensor2->numRow,
                     largeColTensor2->numCol -largeRowTensor2->numCol
                   ).ident(0);
    }
    
    return *tempTensor2;
}

template<class typeT>
inline Tensor2<typeT>& Tensor2<typeT>::operator/=(Tensor2<typeT>& paramTensor2)
{
    *this = *this / paramTensor2;
    
    return *this;
}
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
template<class typeT>
inline Tensor2<typeT>& Tensor2<typeT>::operator>(Tensor2<typeT>& paramTensor2)
{
    Tensor2<typeT>* largeRowTensor2 = (numRow > paramTensor2.numRow)?
                                      this: &paramTensor2;
    Tensor2<typeT>* largeColTensor2 = (numCol > paramTensor2.numCol)?
                                      this: &paramTensor2;
    
    Tensor2<typeT>* tempTensor2;
    tempTensor2 = new Tensor2( largeRowTensor2->numRow,
                               largeColTensor2->numCol,
                               tens2::origin | tens2::stable
                             );
    storTensor2 = tempTensor2;
    
    if( largeRowTensor2 == largeColTensor2 )
    {
        Tensor2<typeT>* largeTensor2 = largeRowTensor2;
        Tensor2<typeT>* smallTensor2 = (largeTensor2 != this)?
                                       this: &paramTensor2;
        
        for( int i=0; i< smallTensor2->numRow; i++ )
        {
            for( int j=0; j< smallTensor2->numCol; j++ )
            {
                tempTensor2->pptypeT[i][j]
                    = smallTensor2->pptypeT[i][j]
                     * largeTensor2->pptypeT[i][j];
            }
            for( int j= smallTensor2->numCol; j< largeTensor2->numCol; j++ )
            {
                tempTensor2->pptypeT[i][j]
                    = largeTensor2->pptypeT[i][j];
            }
        }
        
        for( int i= smallTensor2->numRow; i< largeTensor2->numRow; i++ )
        {
            for( int j=0; j< largeTensor2->numCol; j++ )
            {
                tempTensor2->pptypeT[i][j]
                    = largeTensor2->pptypeT[i][j];
            }
        }
    }
    else
    if( numCol == 1 && numRow == paramTensor2.numRow )
    {
        for( int i=0; i< numRow; i++ )
        {
            for( int j=0; j< paramTensor2.numCol; j++ )
            {
                tempTensor2->pptypeT[i][j]
                    = pptypeT[i][0] * paramTensor2.pptypeT[i][j];
            }
        }
    }
    else
    {
        for( int i=0; i< largeColTensor2->numRow; i++ )
        {
            for( int j=0; j< largeRowTensor2->numCol; j++ )
            {
                tempTensor2->pptypeT[i][j]
                    = this->pptypeT[i][j]
                     * paramTensor2.pptypeT[i][j];
            }
        }
        
        for( int i= largeColTensor2->numRow; i< largeRowTensor2->numRow; i++ )
        {
            for( int j=0; j< largeRowTensor2->numCol; j++ )
            {
                tempTensor2->pptypeT[i][j]
                    = largeRowTensor2->pptypeT[i][j];
            }
        }
        
        for( int i=0; i< largeColTensor2->numRow; i++ )
        {
            for( int j= largeRowTensor2->numCol;
                     j< largeColTensor2->numCol ; j++ )
            {
                tempTensor2->pptypeT[i][j]
                    = largeColTensor2->pptypeT[i][j];
            }
        }
        
        tempTensor2( largeColTensor2->numRow,
                     largeRowTensor2->numCol,
                     largeRowTensor2->numRow -largeColTensor2->numRow,
                     largeColTensor2->numCol -largeRowTensor2->numCol
                   ).ident(0);
    }
    
    return *tempTensor2;
}
template<class typeT>
inline Tensor2<typeT>& Tensor2<typeT>::operator>=(Tensor2<typeT>& paramTensor2)
{
    *this = (*this > paramTensor2);
    
    return *this;
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
template<class typeT>
inline Tensor2<typeT>& Tensor2<typeT>::operator^( int power )
{
    Tensor2<typeT>* tempTensor2;
    tempTensor2 = new Tensor2( numRow, numCol, tens2::origin | tens2::stable );
    tempTensor2->ident();
    storTensor2 = tempTensor2;
    
    if( numRow == numCol )
    {
        if( power > 0 )
        {
            Tensor2<typeT> P;
            P = *this;
            int maxbit;
            
            for( int i= 8 *sizeof(power) -1; i>= 0 ; i-- )
            {
                if( (power>>i) &1 )
                {
                    maxbit = i +1;
                    break;
                }
            }
            
            for( int i=0; i< maxbit; i++ )
            {
                if( (power>>i) &1 )
                {
                    *tempTensor2 *= P;
               }
               
               P *= P;
            }        
        }
        else
        {
            //=============cout << "Warning with respect to operator^()\n";
            return *this;
        }
    }
    else
    {
        //============cout << "Warning with respect to operator^()\n";
        return *this;
    }
    
    return *tempTensor2;
    
}
template<class typeT>
inline Tensor2<typeT>& Tensor2<typeT>::operator^=( int power )
{
    *this = (*this ^ power);
    
    return *this;
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
template<class typeT>
inline Tensor2<typeT>& Tensor2<typeT>::operator&(Tensor2<typeT>& paramTensor2)
{
    int largeCol = (numCol > paramTensor2.numCol)?
                    numCol: paramTensor2.numCol;
    
    Tensor2<typeT>* tempTensor2;
    tempTensor2 = new Tensor2( numRow +paramTensor2.numRow,
                               largeCol,
                               tens2::origin | tens2::stable
                             );
    storTensor2 = tempTensor2;
    
    *tempTensor2 = *this;
    tempTensor2( numRow, 0, paramTensor2.numRow, largeCol ) = paramTensor2;
    
    return *tempTensor2;
}

template<class typeT>
inline Tensor2<typeT>& Tensor2<typeT>::operator&=( Tensor2<typeT>& paramTensor2 )
{
    *this = (*this & paramTensor2);
    
    return *this;
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
template<class typeT>
inline Tensor2<typeT>& Tensor2<typeT>::operator|(Tensor2<typeT>& paramTensor2)
{
    int largeRow = (numRow > paramTensor2.numRow)?
                    numRow: paramTensor2.numRow;
    
    Tensor2<typeT>* tempTensor2;
    tempTensor2 = new Tensor2( largeRow,
                               numCol +paramTensor2.numCol,
                               tens2::origin | tens2::stable
                             );
    storTensor2 = tempTensor2;
    
    *tempTensor2 = *this;
    tempTensor2( 0, numCol, largeRow, paramTensor2.numCol ) = paramTensor2;
    
    return *tempTensor2;
}

template<class typeT>
inline Tensor2<typeT>& Tensor2<typeT>::operator|=(Tensor2<typeT>& paramTensor2)
{
    *this = (*this | paramTensor2);
    
    return *this;
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

#endif

