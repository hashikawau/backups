
#ifndef __Storage
#define __Storage

template<class typeT> class Storage
{
    typedef struct Item
    {
        typeT typeTitem;
        Item* pNextItem;
        Item* pPrevItem;
    };
    
    Item* pInitItem;
    int   iNumItem;
    
public:
    Storage()
    {
        pInitItem = new Item;
        pInitItem->pNextItem = pInitItem;
        pInitItem->pPrevItem = pInitItem;
        iNumItem  = 0;
    }
    
    ~Storage()
    {
        newStorage();
        delete pInitItem;
    }
    
    void put(typeT newitem)
    {
        *this = newitem;
    }
    
    typeT& take(int num)
    {
        return *this[num];
    }
    
    void newStorage()
    {
        for( ; iNumItem >0; iNumItem-- )
        {
            pInitItem = pInitItem->pNextItem;
            
            pInitItem->pPrevItem->pNextItem = NULL;
            pInitItem->pPrevItem->pPrevItem = NULL;
            delete pInitItem->pPrevItem;
        }
        
        pInitItem->pNextItem = pInitItem;
        pInitItem->pPrevItem = pInitItem;
        
        //cout << "iNumItem = " << iNumItem << endl;
        iNumItem = 0;
    }
    
    void show()
    {
        cout << *this;
    }
    
    typeT operator=(typeT newitem)
    {
        pInitItem->pPrevItem->typeTitem = newitem;
        
        Item* temp = new Item;
        
        pInitItem->pPrevItem->pNextItem = temp;
        temp->pPrevItem = pInitItem->pPrevItem;
        
        pInitItem->pPrevItem = temp;
        temp->pNextItem = pInitItem;
        
        iNumItem++;
        
        return newitem;
    }
    
    typeT& operator[](int num)
    {
        if( num >= iNumItem )
        {
            cout << "Error in Storage\n";
            //throw iNumItem;
        }
        
        Item* temp = pInitItem;
        
        for( int i=0; i< num; i++ )
        {
            temp = temp->pNextItem;
        }
        
        return temp->typeTitem;
    }
    
    operator int()
    {
        return iNumItem;
    }
    
    template<class typeT>
    friend ostream& operator<<( ostream& stream, Storage<typeT>& st );
    
};


template<class typeT>
inline ostream& operator<<( ostream& stream, Storage<typeT>& st )
{
    Storage<typeT>::Item* temp = st.pInitItem;
    
    cout << "iNumItem = " << st.iNumItem << endl;
    for( int i=0; i< st.iNumItem; i++ )
    {
        cout << "  Storage number  " << &st;
        cout << "  Item number  "    << temp;
        cout << "  item  "           << temp->typeTitem;
        cout << endl;
        temp = temp->pNextItem;
    }
    
    return stream;
}



#endif

