#include<iostream.h>


enum DIRECT
{
    ROW,
    COLM
};

enum MESHSTATE
{
    BLANK,
    BLACK,
    WHITE
};

enum STATEDETL
{
    MANY = -2,
    ONE,
    ZERO
};

class Mesh
{
    MESHSTATE state;
    STATEDETL detail;
    
public:
    Mesh()
    {
        state = BLANK;
        detail = MANY;
        cout << sizeof(state) << endl;
    }
    
    void show()
    {
        switch(state)
        {
            case BLANK:
                cout << "H";
                break;
            case BLACK:
                cout << "¡";
                break;
            case WHITE:
                cout << "@";
                break;
            default:
                cout << state;
                break;
        }
    }
    
    
    void set(int num){ state = (MESHSTATE)num; }//***************************
};

class WholeMesh : public Mesh
{
    const unsigned char row, colm;    //used as integer
    Mesh **ppMesh;
    
public:
    WholeMesh( int r, int c ) : row(r), colm(c)
    {
        int i = 0;
        while(i< row)
        {
            *(ppMesh+i) = new Mesh[colm];
            i++;
        }
        while(i< row+colm)
        {
            *(ppMesh+i) = new Mesh[row]
            i++;
        }
    }
    
    ~WholeMesh()
    {
        if( sizeof(ppMesh) ){ delete [] ppMesh; }
        cout << "sizeof(ppMesh) " << sizeof(ppMesh) << endl;
    }
    
    void show()
    {
        for(int i= 0; i< row; i++ )
        {
            for(int j= 1; j; j++ )
            {
                (*(ppMesh)+j)->show();
            }
            cout << endl;
        }
    }
    
    
    void set(int num[])//*****************************************************
    {
        for(int i=0; i < sizeof(num); i++ )
        {
            (*(ppMesh)+i)->set(num[i]);
        }
    }
};

void iraroji()
{
    WholeMesh m(1, 30);
    m.show();
    int u = '\0';
    if(!u){cout << "u is NULL\n"; }
    
    int array[30]//*********10******************20******************30*******
        ={1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    m.set(array);
    m.show();
}