

#include "windows\awt\Frame.h"
#include "windows\awt\Label.h"
#include "windows\awt\Button.h"
#include "windows\awt\Canvas.h"
#include "windows\awt\ScrollPane.h"
#include "windows\awt\TextField.h"
#include "windows\awt\FileDialog.h"
#include "windows\lang\String.h"
#include "windows\lang\Math.h"
#include "windows\lang\Number.h"
#include "windows\_lang.h"
#include "windows\util\LinkedList.h"

#include <fstream.h>



//===========================================================
//===========================================================
class MenuFile: public Menu
{
public:
    class MenuNew: public MenuItem
    {
    private:
        class Listener: public ActionListener
        {
        public:
            virtual void actionPerformed(ActionEvent& e){}
        };
    public:
        MenuNew(): MenuItem(String("&New"))
        {
            addActionListener(*new Listener());
        }
        virtual ~MenuNew(){}
    };
    //===========================================================
    //===========================================================
    class MenuOpen: public MenuItem
    {
    private:
        class Listener: public ActionListener
        {
        public:
            virtual void actionPerformed(ActionEvent& e);
        };
    public:
        MenuOpen(): MenuItem(String("&Open"))
        {
            addActionListener(*new Listener());
        }
        virtual ~MenuOpen(){}
    };
    //===========================================================
    //===========================================================
    class MenuSave: public MenuItem
    {
    private:
        class Listener: public ActionListener
        {
        public:
            virtual void actionPerformed(ActionEvent& e){}
        };
    public:
        MenuSave(): MenuItem(String("&Save"))
        {
            addActionListener(*new Listener());
        }
        virtual ~MenuSave(){}
    };
    //===========================================================
    //===========================================================
    class MenuSaveAs: public MenuItem
    {
    private:
        class Listener: public ActionListener
        {
        public:
            virtual void actionPerformed(ActionEvent& e)
            {
                MenuSaveAs& m
                    = *static_cast<MenuSaveAs*>(e.getSource());
                MenuComponent* mc
                    = dynamic_cast<MenuComponent*>(&m.getParent());
                if(!mc){ return; }
                
                Frame* f
                    = static_cast<Frame*>(&mc->getParent());
                    //= dynamic_cast<Frame*>(&mc->getParent());
                //if(!f){ throw int(); }
                
                FileDialog fd(*f, L"Save As", FileDialog::SAVE);
                fd.setVisible(true);
                //String filename
                //    = String(fd.getDirectory())
                //    +String(fd.getFile());
            }
        };
    public:
        MenuSaveAs(): MenuItem(String("Save &As..."))
        {
            addActionListener(*new Listener());
        }
        virtual ~MenuSaveAs(){}
    };
    //===========================================================
    //===========================================================
    class MenuExit: public MenuItem
    {
    private:
        class Listener: public ActionListener
        {
        public:
            virtual void actionPerformed(ActionEvent& e){}
        };
    public:
        MenuExit(): MenuItem(String("&Exit"))
        {
            addActionListener(*new Listener());
        }
        virtual ~MenuExit(){}
    };
    //===========================================================
    //===========================================================
    MenuFile(): Menu(L"&File")
    {
        add(*new MenuNew());
        add(*new MenuOpen());
        addSeparator();
        add(*new MenuSave());
        add(*new MenuSaveAs());
        addSeparator();
        add(*new MenuExit());
    }
};
//===========================================================
//===========================================================
class Combination
{
private:
    unsigned long long int _count;
    int _numblack;
    int _numline;
    bool** _blackhead;
    int* _blacks;
    int* _indexblackhead;
    int* _indexblackheadfirst;
    
    bool shift(int index);
    
public:
    Combination(int numblack, int numline, bool** blackhead, int* blacks);
    Combination(const Combination& com);
    ~Combination(){
        delete [] _indexblackhead;
        delete [] _indexblackheadfirst;
    }
    bool increment();
    bool shiftR(int index);
    unsigned long long int getCount(){ return _count; }
    //int* getIndices(){ return _indexhole; }
    int* getIndices(){ return _indexblackhead; }
};
//===========================================================
bool Combination::shift(int index){
    if(index <0 || index >=_numblack){
        throw String("error in combination");
    }
    
    bool doexistnext =false;
    for(int j= _indexblackhead[index] +1; j< _numline; ++j){
        if(_blackhead[index][j]){
            doexistnext =true;
            _indexblackhead[index] = j;
            break;
        }
    }
    if(!doexistnext){
        if(index == 0){
            _indexblackhead[index] = _indexblackheadfirst[index];
        }else{
            shift(index -1);
            
            bool doexistnext =false;
            for(int j= _indexblackhead[index -1] +1; j< _numline; ++j){
                if(_blackhead[index][j]){
                    doexistnext =true;
                    _indexblackhead[index] = j;
                    break;
                }
            }
            if(!doexistnext){
                _indexblackhead[index] = _indexblackheadfirst[index];
            }
        }
    }
    return true;
}
//===========================================================
Combination::Combination(
    int numblack,
    int numline,
    bool** blackhead,
    int* blacks)
{
    _count = 0;
    _numblack = numblack;
    _numline = numline;
    _blackhead = blackhead;
    _blacks = blacks;
    _indexblackhead = new int [_numblack];
    _indexblackheadfirst = new int [_numblack];
    for(int i=0; i< _numblack; ++i){
        for(int j=0; j< _numline; ++j){
            if(_blackhead[i][j]){
                _indexblackhead[i] = j;
                _indexblackheadfirst[i] = j;
                break;
            }
        }
        
        
        
//cout << _blacks[i] << "==> " << _indexblackhead[i] << endl;
    }
    
    
    
/*
for(int i=0; i< _numblack; ++i){
    cout << _blacks[i] << "==> ";
    for(int j=0; j< _numline; ++j){
        cout << _blackhead[i][j];
        if(!((j+1)%5)){
            cout << " ";
        }
    }
    cout << endl;
}
*/
}
//===========================================================
bool Combination::increment(){
    shift(_numblack -1);
    bool isfinished =true;
    for(int i=0; i< _numblack; ++i){
        isfinished &=
            (_indexblackhead[i] == _indexblackheadfirst[i]);
    }
    ++_count;
    
    return isfinished; //if true then end the trial
}
//===========================================================
bool Combination::shiftR(int index){
    if(index <0 || index >=_numblack){
        throw String("error in combination");
    }
    
    int indexblackheadnew[_numblack];
    for(int i=0; i< _numblack; ++i){
        indexblackheadnew[i] = _indexblackhead[i];
    }
    
    bool ischanged =true;
    register int j= indexblackheadnew[index] +1;
    for(int i= index; i< _numblack; ++i){
        bool doexist =false;
        for(; j< _numline; ++j){
            if(_blackhead[i][j]){
                if(_indexblackhead[i] < j){
                    indexblackheadnew[i] = j;
                    j += _blacks[i] +1;
                }else{
                    //indexblackheadnew[i] = j;
                    j = _indexblackhead[i] +_blacks[i] +1;
                }
                doexist =true;
                break;
            }
        }
        
        ischanged &= doexist;
    }
    
    
    
    if(ischanged){
        for(int i=0; i< _numblack; ++i){
            _indexblackhead[i] = indexblackheadnew[i];
        }
    }
    return ischanged;
    
    
    /*
    if(_indexblackhead[index] +(_numblack -index) < _numline){
        if(index == _numblack -1){
            ++_indexblackhead[index];
            ischanged =true;
        }else{
            if(_indexblackhead[index] +1 < _indexblackhead[index +1]){
                ++_indexblackhead[index];
                ischanged =true;
            }else{
                if(shiftR(index +1)){
                    ++_indexblackhead[index];
                    ischanged =true;
                }
                //else{ ischanged =false; }
            }
        }
    }
    //else{ ischanged =false; }
    
    return ischanged;
    */
}
//===========================================================
//===========================================================
class IllustrationLogicCanvas:
    public Canvas,
    public MouseListener,
    public MouseMotionListener
{
private:
    
public:
    char* _numblack;
    int** _blacks;
    
    int _gridsize;
    int _numver;
    int _numhor;
    
    int _numcalclation;
    
    bool* _flagblack;
    bool* _flagwhite;
    bool*** _blackhead;
    
    
public:
    IllustrationLogicCanvas();
    virtual ~IllustrationLogicCanvas();
    virtual void update(Graphics& g);
    virtual void paint(Graphics& g);
    
    virtual void mouseClicked(MouseEvent& e);
    virtual void mouseEntered(MouseEvent& e);
    virtual void mouseExited(MouseEvent& e);
    virtual void mousePressed(MouseEvent& e);
    virtual void mouseReleased(MouseEvent& e);
    virtual void mouseDragged(MouseEvent& e);
    virtual void mouseMoved(MouseEvent& e);
    
    void setNumGrid(const String& filename);
    int getNumVer(){ return _numver; }
    int getNumHor(){ return _numhor; }
    void calculateLine(int indexline);
    void calculateLine2(int indexline);
};
//===========================================================
//===========================================================
IllustrationLogicCanvas::IllustrationLogicCanvas()
{
    
    _numcalclation =1;
    _numblack =0;
    _blacks   =0;
    
    _gridsize =10;
    
    _flagblack =0;
    _flagwhite =0;
    _blackhead =0;
    
    setNumGrid(String("iraroji/iraroji(60_50)-04.txt"));
    addMouseListener(*this);
    addMouseMotionListener(*this);
    setVisible(true);
}
IllustrationLogicCanvas::~IllustrationLogicCanvas()
{
    delete [] _flagblack;
    delete [] _flagwhite;
    if(_blackhead){
        for(int i=0; i< _numver +_numhor; ++i){
            for(int j=0; j< _numblack[i]; ++j){
                delete [] _blackhead[i][j];
            }
            delete [] _blackhead[i];
        }
        delete [] _blackhead;
    }
    
    if(_blacks){
        for(int i=0; i< _numver +_numhor; ++i){
            delete [] _blacks[i];
        }
        delete [] _blacks;
    }
    delete [] _numblack;
}
//===========================================================
//===========================================================
void IllustrationLogicCanvas::setNumGrid(const String& filename)
{
    delete [] _flagblack;
    delete [] _flagwhite;
    if(_blackhead){
        for(int i=0; i< _numver +_numhor; ++i){
            for(int j=0; j< _numblack[i]; ++j){
                delete [] _blackhead[i][j];
            }
            delete [] _blackhead[i];
        }
        delete [] _blackhead;
    }
    
    if(_blacks){
        for(int i=0; i< _numver +_numhor; ++i){
            delete [] _blacks[i];
        }
        delete [] _blacks;
    }
    delete [] _numblack;
    
    _blacks   =0;
    _numblack =0;
    
    _flagblack =0;
    _flagwhite =0;
    _blackhead =0;
    
    //===========================================================
    if(filename.length() > 0){
        
        char name[255];
        wcstombs(name, filename.toCharArray(), filename.length() +1);
        ifstream stream;
        stream.open(name);
        char ch;
        char str[10];
        LinkedList<int> list;
        int count =0;
        while(stream.get(ch)){
            if(ch == '\n'){
                if(count){
                    str[count] = '\0';
                    list.addLast(Integer::parseInt(String(str)));
                }
                list.addLast(0);
                count =0;
            }else
            if(ch == ' '){
                str[count] = '\0';
                list.addLast(Integer::parseInt(String(str)));
                count =0;
            }else{
                str[count] = ch;
                ++count;
            }
        }
        if(count){
            str[count] = '\0';
            list.addLast(Integer::parseInt(String(str)));
        }
        list.addLast(0);
        
        stream.close();
        
        //===========================================================
        int size = list.size();
        int array[size];
        list.toArray(array);
        int num[] ={0, 0, 0};
        int index =0;
        int countzero =0;
        for(int i=0; i< size; ++i){
            if(array[i]){
                if(countzero >1){
                    ++index;
                }
                countzero =0;
                if(!index){
                    array[i] =0;
                }
            }else{
                if(!countzero){
                    ++num[index];
                }
                ++countzero;
            }
        }
        
        _numver = num[1];
        _numhor = num[2];
        
        
        _blacks   = new int* [_numver +_numhor];
        _numblack = new char [_numver +_numhor];
        
        int start =0;
        index =-1;
        count =0;
        countzero =0;
        for(int i=0; i< size; ++i){
            if(array[i]){
                if(countzero >0){
                    start =i;
                    ++index;
                }
                countzero =0;
                ++count;
            }else{
                if(countzero == 0){
                    _numblack[index] =count;
                    _blacks[index] = new int [count];
                    for(int j= start, k=0; j< i; ++j){
                        if(array[j]){
                            _blacks[index][k] = array[j];
                            ++k;
                        }
                    }
                }
                count =0;
                ++countzero;
            }
        }
        
        //===========================================================
        _flagblack = new bool [_numver *_numhor];
        _flagwhite = new bool [_numver *_numhor];
        for(int i=0; i< _numver *_numhor; ++i){
            _flagblack[i] =false;
            _flagwhite[i] =false;
        }
        //===========================================================
        _blackhead = new bool** [_numver +_numhor];
        for(int i=0; i< _numver +_numhor; ++i){
            _blackhead[i] = new bool* [_numblack[i]];
            
            int numline = i < _numver?
                _numhor:
                _numver;
            for(int j=0; j< _numblack[i]; ++j){
                _blackhead[i][j] = new bool [numline];
                
                int blackheadFirst = 0;
                int blackheadLast = numline -_blacks[i][j];
                for(int k=0; k< j; ++k){
                    blackheadFirst += _blacks[i][k] +1;
                }
                for(int k= j+1; k< _numblack[i]; ++k){
                    blackheadLast -= _blacks[i][k] +1;
                }
                
                int k =0;
                for(; k< blackheadFirst; ++k){
                    _blackhead[i][j][k] =false;
                }
                for(; k<= blackheadLast; ++k){
                    _blackhead[i][j][k] =true;
                }
                for(; k< numline; ++k){
                    _blackhead[i][j][k] =false;
                }
            }
        }
    }else{
        _numver =0;
        _numhor =0;
    }
    
    setSize(_gridsize *_numhor +2, _gridsize *_numver +2);
}
//===========================================================
//===========================================================
void IllustrationLogicCanvas::update(Graphics& g)
{
    Canvas::update(g);
    //paint(g);
}
void IllustrationLogicCanvas::paint(Graphics& g)
{
    g.setColor(Color(0x808080));
    for(int i=0; i< _numver; ++i){
        for(int j=0; j< _numhor; ++j){
            if(_flagblack[_numhor *i +j]){
                g.fillRect(
                    _gridsize *j, _gridsize *i,
                    _gridsize, _gridsize);
            }else
            if(_flagwhite[_numhor *i +j]){
                g.drawLine(
                    _gridsize *j, _gridsize *i,
                    _gridsize *(j+1), _gridsize *(i+1));
                g.drawLine(
                    _gridsize *(j+1), _gridsize *i,
                    _gridsize *j, _gridsize *(i+1));
            }
        }
    }
    
    g.setColor(Color(0x00));
    int width = getWidth();
    int height = getHeight();
    
    for(int i=0; i<= Math::max(_numver, _numhor); ++i){
        g.drawLine(0, _gridsize *i, width, _gridsize *i);
        g.drawLine(_gridsize *i, 0, _gridsize *i, height);
    }
    for(int i=0; i<= Math::max(_numver, _numhor); i +=5){
        g.drawLine(0, _gridsize *i +1, width, _gridsize *i +1);
        g.drawLine(_gridsize *i +1, 0, _gridsize *i +1, height);
    }
}
//===========================================================
//===========================================================
void IllustrationLogicCanvas::mouseClicked(MouseEvent& e){}
void IllustrationLogicCanvas::mouseEntered(MouseEvent& e){}
void IllustrationLogicCanvas::mouseExited(MouseEvent& e){}
void IllustrationLogicCanvas::mousePressed(MouseEvent& e)
{
    int button = e.getButton();
    int numver = e.getY() /_gridsize;
    int numhor = e.getX() /_gridsize;
    
    if(button == MouseEvent::BUTTON1){
        _flagblack[_numhor *numver +numhor] = true;
        _flagwhite[_numhor *numver +numhor] = false;
    }else
    if(button == MouseEvent::BUTTON2){
        _flagblack[_numhor *numver +numhor] = false;
        _flagwhite[_numhor *numver +numhor] = true;
    }else
    if(button == MouseEvent::BUTTON3){
        _flagblack[_numhor *numver +numhor] = false;
        _flagwhite[_numhor *numver +numhor] = false;
    }
        
    repaint();
}
void IllustrationLogicCanvas::mouseReleased(MouseEvent& e){}
//===========================================================
//===========================================================
void IllustrationLogicCanvas::mouseDragged(MouseEvent& e)
{
    static int prenumver;
    static int prenumhor;
    int button = e.getButton();
    int numver = e.getY() /_gridsize;
    int numhor = e.getX() /_gridsize;
    if(prenumver !=numver || prenumhor !=numhor){
        if(button == MouseEvent::BUTTON1){
            _flagblack[_numhor *numver +numhor] = true;
            _flagwhite[_numhor *numver +numhor] = false;
        }else
        if(button == MouseEvent::BUTTON2){
            _flagblack[_numhor *numver +numhor] = false;
            _flagwhite[_numhor *numver +numhor] = true;
        }else
        if(button == MouseEvent::BUTTON3){
            _flagblack[_numhor *numver +numhor] = false;
            _flagwhite[_numhor *numver +numhor] = false;
        }
        
        repaint();
    }
    prenumver =numver;
    prenumhor =numhor;
    
}
void IllustrationLogicCanvas::mouseMoved(MouseEvent& e){}
//===========================================================
//===========================================================
void IllustrationLogicCanvas::calculateLine(int indexline)
{
    int numline;
    int offset;
    int step;
    if(indexline < _numver){
        numline = _numhor;
        offset  = indexline *_numhor;
        step    = 1;
    }else
    if(indexline < _numver +_numhor){
        numline = _numver;
        offset  = indexline -_numver;
        step    = _numhor;
    }else{
        throw String("error at line ")
            +String(indexline)
            +String(" - initialization");
    }
    
    //==================================================================
    int numblack = _numblack[indexline];
    int blacks[numblack];
    for(int i=0; i< numblack; ++i){
        blacks[i] = _blacks[indexline][i];
    }
    
    //==================================================================
    bool flagblack[numline];
    bool flagwhite[numline];
    for(int i=0; i< numline; ++i){
        flagblack[i] = _flagblack[offset +step *i]?
            true:
            false;
        flagwhite[i] = _flagwhite[offset +step *i]?
            true:
            false;
    }
    
    //==================================================================
    bool* blackhead[numblack];
    for(int i=0; i< numblack; ++i){
        blackhead[i] = new bool [numline];
        for(int j=0; j< numline; ++j){
            blackhead[i][j] = false;//_blackhead[indexline][i][j];
        }
    }
    
    //==================================================================
    
    
    
    
    
    
    
    
    
    
    int indexfirst =0;
    for(int i=0; i< numblack; ++i){
        if(indexfirst > numline -blacks[i]){
            throw String("error at line ")
                +String(indexline)
                +String(" - no much pattern");
        }
        
        int head = numline;
        for(int j= indexfirst; j<= numline -blacks[i]; ++j){
            blackhead[i][j] =true;
            if(j >0){
                blackhead[i][j] &= !flagblack[j -1];
            }
            for(int k=0; k< blacks[i]; ++k){
                blackhead[i][j] &= !flagwhite[j +k];
            }
            if(j < numline -blacks[i]){
                blackhead[i][j] &= !flagblack[j +blacks[i]];
            }
            head = (j <head) & blackhead[i][j]?
                j:
                head;
        }
        indexfirst = head +blacks[i] +1;
    }
    
    int indexlast =numline;
    for(int i= numblack -1; i>= 0; --i){
        
        int j= numline -1;
        for(; j>= 0; --j){
            if(blackhead[i][j]){
                if(j +blacks[i] >indexlast){
                    blackhead[i][j] =false;
                    continue;
                }else{
                    indexlast = j -1;
                    break;
                }
            }
        }
        
        if(j <0){
            throw String("error at line ")
                +String(indexline)
                +String(" - no much pattern");
        }
        
    }
    
/*
cout << "first step";
cout << endl;
for(int i=0; i< numblack; ++i){
    for(int j=0; j< numline; j++){
        cout << blackhead[i][j];
        if(!((j+1)%5)){
            cout << " ";
        }
    }
    cout << endl;
}
*/
    
    
    
    
    
{//==================================================================
    //==================================================================
    bool isrewrited =true;
    while(isrewrited){
        isrewrited =false;
        
        for(int i=0; i< numline; ++i){
            if(flagblack[i]){
                int countblack =0;
                int indexblack =-1;
                for(int j=0; j< numblack; ++j){
//cout << i << " " << j << " ";
                    for(int k=0; k< blacks[j]; ++k){
                        if((i -k) >=0 && blackhead[j][i -k]){
                            ++countblack;
                            indexblack = j;
//cout << i -k;
                            break;
                        }
                    }
//cout << endl;
                }
                
                if(countblack == 1){
                    for(int j=0; j<= i -blacks[indexblack]; ++j){
                        if(blackhead[indexblack][j]){
                            blackhead[indexblack][j] =false;
                            isrewrited =true;
                        }
                    }
                    for(int j= i +1; j< numline; ++j){
                        if(blackhead[indexblack][j]){
                            blackhead[indexblack][j] =false;
                            isrewrited =true;
                        }
                    }
                }else
                if(countblack > 1){
                    
                    bool* soloblack  = new bool [numline];
                    bool* blackoverlap = new bool [numline];
                    for(int k=0; k< numline; ++k){
                        blackoverlap[k] =true;
                    }
                        
                    
                    for(int j=0; j< numblack; ++j){
                        
                        
                        
                        for(int k=0; k< blacks[j]; ++k){
                            if((i -k) >=0 && blackhead[j][i -k]){
                                for(int n=0; n< numline; ++n){
                                    soloblack[n]  =false;
                                }
                                for(int n=0; n< blacks[j]; ++n){
                                    soloblack[i -k +n] = true;
                                }
                                for(int n=0; n< numline; ++n){
                                    blackoverlap[n] &= soloblack[n];
                                }
                                
                            }
                        }
                        
                        
                    }
                    
                    
                    for(int k=0; k< numline; ++k){
                        flagblack[k] |= blackoverlap[k];
                    }
                    
                    delete [] soloblack;
                    delete [] blackoverlap;
                }
                
                
            }
        }
    }
    
    //==================================================================
    isrewrited =true;
    while(isrewrited){
        isrewrited =false;
        
        for(int i=0; i< numblack; ++i){
            
            int countblack =0;
            int indexline =-1;
            for(int j=0; j< numline; ++j){
                if(blackhead[i][j]){
                    ++countblack;
                    indexline =j;
                }
            }
            if(countblack ==1){
                for(int j=0; j< i; ++j){
                    for(int k= Math::max(0, indexline -blacks[j] );
                        k< numline;
                        ++k)
                    {
                        if(blackhead[j][k]){
                            blackhead[j][k] =false;
                            isrewrited =true;
                        }
                    }
                }
                for(int j= i+1; j< numblack; ++j){
                    for(int k=0;
                        k<= Math::min(numline +1, indexline +blacks[i]);
                        ++k)
                    {
                        if(blackhead[j][k]){
                            blackhead[j][k] =false;
                            isrewrited =true;
                        }
                    }
                }
            }
            
            
            
        }
    }
}//==================================================================
    

    
    
    //==================================================================
    bool soloblack[numline];
    bool blackoverlap[numline];
    bool whiteoverlap[numline];
    for(int i=0; i< numline; ++i){
        whiteoverlap[i] =true;
    }
    for(int i=0; i< numblack; ++i){
        for(int j=0; j< numline; ++j){
            blackoverlap[j] =true;
        }
        for(int j=0; j< numline; ++j){
            if(blackhead[i][j]){
                for(int k=0; k< numline; ++k){
                    soloblack[k]  =false;
                }
                for(int k=0; k< blacks[i]; ++k){
                    soloblack[j +k]  =true;
                    whiteoverlap[j +k] =false;
                }
                for(int k=0; k< numline; ++k){
                    blackoverlap[k] &= soloblack[k];
                }
                
            }
        }
    
        
        for(int j=0; j< numline; ++j){
            flagblack[j] |= blackoverlap[j];
        }
        
        
    }
    
    
    for(int i=0; i< numline; ++i){
        if(flagblack[i] & whiteoverlap[i]){
            throw String("error at line ")
                +String(indexline)
                +String(" - no much pattern");
        }
    }
    
/*
cout << "last step";
cout << endl;
for(int i=0; i< numblack; ++i){
    for(int j=0; j< numline; j++){
        cout << blackhead[i][j];
        if(!((j+1)%5)){
            cout << " ";
        }
    }
    cout << endl;
}
*/
    
    
    
    //==================================================================
    //find if there is a box which is unpaintable
    int indexfirstblack = 0;
    for(int i=0; i< numblack; ++i){
        bool doBlackExist =false;
        for(int j=0; j< numline; ++j){
            if(blackhead[i][j]){
                if(doBlackExist){
                    doBlackExist =false;
                    break;
                }else{
                    doBlackExist =true;
                }
            }
        }
        if(doBlackExist){
            ++indexfirstblack;
        }else{
            break;
        }
    }
    
    int indexlastblack = numblack -1;
    for(int i= numblack -1; i>= 0; --i){
        bool doBlackExist =false;
        for(int j=0; j< numline; ++j){
            if(blackhead[i][j]){
                if(doBlackExist){
                    doBlackExist =false;
                    break;
                }else{
                    doBlackExist =true;
                }
            }
        }
        if(doBlackExist){
            --indexlastblack;
        }else{
            break;
        }
    }
    
    
//cout << "indexfirstblack = " << indexfirstblack << "; ";
    if(indexfirstblack < numblack){
        int countblack =0;
        bool wasblack =false;
        for(int j=0; j< numline; ++j){
            if(flagblack[j]){
                if(!wasblack){
                    ++countblack;
                }
                wasblack =true;
            }else{
                wasblack =false;
            }
            
            if(countblack > indexfirstblack){
                for(int k= j+1; k< numline; ++k){
                    blackhead[indexfirstblack][k] = false;
                }
//cout << "countblack = " << countblack << "; ";
//cout << j+1 << " -> " << numline;
                break;
            }
        }
    }
//cout << endl;
    
    
//cout << "indexlastblack = " << indexlastblack << "; ";
    if(indexlastblack >= 0){
        int countblack = numblack -1;
        bool wasblack =false;
        for(int j= numline -1; j>= 0; --j){
            if(flagblack[j]){
                if(!wasblack){
                    --countblack;
                }
                wasblack =true;
            }else{
                wasblack =false;
            }
            
            if(countblack < indexlastblack){
                for(int k= j -blacks[indexlastblack]; k>= 0; --k){
                    blackhead[indexlastblack][k] = false;
                }
//cout << "countblack = " << countblack << "; ";
//cout << "0 -> " << j -blacks[indexlastblack];
                break;
            }
        }
    }
//cout << endl;
    
    
    
{//==================================================================
    //==================================================================
    bool isrewrited =true;
    while(isrewrited){
        isrewrited =false;
        
        for(int i=0; i< numline; ++i){
            if(flagblack[i]){
                int countblack =0;
                int indexblack =-1;
                for(int j=0; j< numblack; ++j){
//cout << i << " " << j << " ";
                    for(int k=0; k< blacks[j]; ++k){
                        if((i -k) >=0 && blackhead[j][i -k]){
                            ++countblack;
                            indexblack = j;
//cout << i -k;
                            break;
                        }
                    }
//cout << endl;
                }
                
                if(countblack == 1){
                    for(int j=0; j<= i -blacks[indexblack]; ++j){
                        if(blackhead[indexblack][j]){
                            blackhead[indexblack][j] =false;
                            isrewrited =true;
                        }
                    }
                    for(int j= i +1; j< numline; ++j){
                        if(blackhead[indexblack][j]){
                            blackhead[indexblack][j] =false;
                            isrewrited =true;
                        }
                    }
                }else
                if(countblack > 1){
                    
                    bool* soloblack  = new bool [numline];
                    bool* blackoverlap = new bool [numline];
                    for(int k=0; k< numline; ++k){
                        blackoverlap[k] =true;
                    }
                        
                    
                    for(int j=0; j< numblack; ++j){
                        
                        
                        
                        for(int k=0; k< blacks[j]; ++k){
                            if((i -k) >=0 && blackhead[j][i -k]){
                                for(int n=0; n< numline; ++n){
                                    soloblack[n]  =false;
                                }
                                for(int n=0; n< blacks[j]; ++n){
                                    soloblack[i -k +n] = true;
                                }
                                for(int n=0; n< numline; ++n){
                                    blackoverlap[n] &= soloblack[n];
                                }
                                
                            }
                        }
                        
                        
                    }
                    
                    
                    for(int k=0; k< numline; ++k){
                        flagblack[k] |= blackoverlap[k];
                    }
                    
                    delete [] soloblack;
                    delete [] blackoverlap;
                }
                
                
            }
        }
    }
    
    //==================================================================
    isrewrited =true;
    while(isrewrited){
        isrewrited =false;
        
        for(int i=0; i< numblack; ++i){
            
            int countblack =0;
            int indexline =-1;
            for(int j=0; j< numline; ++j){
                if(blackhead[i][j]){
                    ++countblack;
                    indexline =j;
                }
            }
            if(countblack ==1){
                for(int j=0; j< i; ++j){
                    for(int k= Math::max(0, indexline -blacks[j] );
                        k< numline;
                        ++k)
                    {
                        if(blackhead[j][k]){
                            blackhead[j][k] =false;
                            isrewrited =true;
                        }
                    }
                }
                for(int j= i+1; j< numblack; ++j){
                    for(int k=0;
                        k<= Math::min(numline +1, indexline +blacks[i]);
                        ++k)
                    {
                        if(blackhead[j][k]){
                            blackhead[j][k] =false;
                            isrewrited =true;
                        }
                    }
                }
            }
            
            
            
        }
    }
}//==================================================================
    

    
    
    //==================================================================
    for(int i=0; i< numline; ++i){
        whiteoverlap[i] =true;
    }
    for(int i=0; i< numblack; ++i){
        for(int j=0; j< numline; ++j){
            blackoverlap[j] =true;
        }
        for(int j=0; j< numline; ++j){
            if(blackhead[i][j]){
                for(int k=0; k< numline; ++k){
                    soloblack[k]  =false;
                }
                for(int k=0; k< blacks[i]; ++k){
                    soloblack[j +k]  =true;
                    whiteoverlap[j +k] =false;
                }
                for(int k=0; k< numline; ++k){
                    blackoverlap[k] &= soloblack[k];
                }
                
            }
        }
    
        
        for(int j=0; j< numline; ++j){
            flagblack[j] |= blackoverlap[j];
        }
        
        
    }
    
    
    for(int i=0; i< numline; ++i){
        if(flagblack[i] & whiteoverlap[i]){
            throw String("error at line ")
                +String(indexline)
                +String(" - no much pattern");
        }
    }
    
    //==================================================================
    
    /*
    //==================================================================
    for(int i=0; i< numline; ++i){
        whiteoverlap[i] =true;
        blackoverlap[i] =true;
    }
    for(int i=0; i< numblack; ++i){
        for(int j=0; j< numline; ++j){
            if(blackhead[i][j]){
                for(int k=0; k< numline; ++k){
                    soloblack[k]  = flagblack[k];
                }
                for(int k=0; k< blacks[i]; ++k){
                    soloblack[j +k]  = true;
                }
                
                bool isvalid =true;
                bool isprevblack =false;
                int countblack = i;
                int countblackbox = 0;
                for(int k=j; k< numline; ++k){
                    if(soloblack[k]){
                        if(isprevblack){
                            
                        }else{
                            if(++countblack > numblack){
                                isvalid =false;
                                break;
                            }
                        }
                        isprevblack =true;
                        ++countblackbox;
                    }else{
                        if(isprevblack){
                            if(countblackbox != blacks[countblack -1]){
                                isvalid =false;
                                break;
                            }
                        }else{
                            
                        }
                        isprevblack =false;
                        countblackbox =0;
                    }
                }
                
                if(isprevblack){
                    if(countblackbox != blacks[countblack -1]){
                        isvalid =false;
                    }
                }
                if(countblack != numblack){
                    isvalid =false;
                }
                
                
                if(isvalid){
                    for(int k=0; k< numline; ++k){
                        whiteoverlap[k] &= !soloblack[k];
                        blackoverlap[k] &= soloblack[k];
                    }
                }
            }
        }
    }
    
    
    for(int j=0; j< numline; ++j){
        flagblack[j] |= blackoverlap[j];
    }
    
    for(int i=0; i< numline; ++i){
        if(flagblack[i] & whiteoverlap[i]){
            throw String("error at line ")
                +String(indexline)
                +String(" - no much pattern");
        }
    }
    
    for(int i=0; i< numline; ++i){
        _grid[offset +step *i] = flagblack[i];
        _flag[offset +step *i] = flagblack[i] | whiteoverlap[i];
    }
    
    
    
    
//==================================================================
cout << "index " << indexline << " => ";
for(int i=0; i< numblack; ++i){
    cout << blacks[i];
    cout << " ";
}
cout << endl;
for(int i=0; i< numline; i++){
    cout << flagblack[i];
    if(!((i+1)%5)){
        cout << " ";
    }
}
cout << endl;
for(int i=0; i< numline; i++){
    cout << whiteoverlap[i];
    if(!((i+1)%5)){
        cout << " ";
    }
}
cout << endl;
cout << endl;
for(int i=0; i< numblack; ++i){
    for(int j=0; j< numline; j++){
        cout << blackhead[i][j];
        if(!((j+1)%5)){
            cout << " ";
        }
    }
    cout << endl;
}
cout << endl;

    
    */
    //==================================================================
    for(int i=0; i< numline; ++i){
        _flagblack[offset +step *i] = flagblack[i];
        _flagwhite[offset +step *i] = whiteoverlap[i];
    }
    
    for(int i=0; i< numblack; ++i){
        for(int j=0; j< numline; ++j){
            _blackhead[indexline][i][j] = blackhead[i][j];
        }
        delete [] blackhead[i];
    }
}
//===========================================================
//===========================================================
void IllustrationLogicCanvas::calculateLine2(int indexline)
{
    int numline;
    int offset;
    int step;
    if(indexline < _numver){
        numline = _numhor;
        offset  = indexline *_numhor;
        step    = 1;
    }else
    if(indexline < _numver +_numhor){
        numline = _numver;
        offset  = indexline -_numver;
        step    = _numhor;
    }else{
        throw String("error at line ")
            +String(indexline)
            +String(" - initialization");
    }
    
    //==================================================================
    int numblack = _numblack[indexline];
    int blacks[numblack];
    for(int i=0; i< numblack; ++i){
        blacks[i] = _blacks[indexline][i];
    }
    
    //==================================================================
    bool flagblack[numline];
    bool flagwhite[numline];
    for(int i=0; i< numline; ++i){
        flagblack[i] = _flagblack[offset +step *i];
        flagwhite[i] = _flagwhite[offset +step *i];
    }
    
    //==================================================================
    bool* blackhead[numblack];
    for(int i=0; i< numblack; ++i){
        blackhead[i] = new bool [numline];
        for(int j=0; j< numline; ++j){
            blackhead[i][j] = _blackhead[indexline][i][j];
        }
    }
    
    //==================================================================
{//chamber
    int numchamber =0;
    bool iswhite =true;
    for(int j=0; j< numline; ++j){
        if(flagwhite[j]){
            iswhite =true;
        }else{
            if(iswhite){
                ++numchamber;
                //++countchamber;
                //chamberhead[countchamber] = j;
            }
            iswhite =false;
            //++sizechamber[countchamber];
        }
    }
    
    //==================================================================
    int chamberhead[numchamber];
    int sizechamber[numchamber];
    for(int i=0; i< numchamber; ++i){
        sizechamber[i] =0;
    }
    //bool
    iswhite =true;
    int countchamber =-1;
    for(int j=0; j< numline; ++j){
        if(flagwhite[j]){
            iswhite =true;
        }else{
            if(iswhite){
                //++numchamber;
                ++countchamber;
                chamberhead[countchamber] = j;
            }
            iswhite =false;
            ++sizechamber[countchamber];
        }
    }
    
    //==================================================================
    for(int j=0; j< numline; ++j){
        if(flagwhite[j]){
            for(int i=0; i< numblack; ++i){
                blackhead[i][j] =false;
            }
        }
    }
    
    for(int k=0; k< numchamber; ++k){
        for(int i=0; i< numblack; ++i){
            for(int j= chamberhead[k];
                j< chamberhead[k] +sizechamber[k];
                ++j)
            {
                if(sizechamber[k] < blacks[i]){
                    blackhead[i][j] =false;
                }else
                if(blackhead[i][j]){
                    
                }
            }
        }
    }
}//==================================================================
    
    //==================================================================
{//black string
    int numstring =0;
    bool isblack =false;
    for(int j=0; j< numline; ++j){
        if(flagblack[j]){
            if(!isblack){
                ++numstring;
                //++countstring;
                //stringhead[countstring] = j;
            }
            isblack =true;
            //++sizestring[countstring];
        }else{
            isblack =false;
        }
    }
    
    int stringhead[numstring];
    int sizestring[numstring];
    for(int i=0; i< numstring; ++i){
        sizestring[i] =0;
    }
    //bool
    isblack =false;
    int countstring =-1;
    for(int j=0; j< numline; ++j){
        if(flagblack[j]){
            if(!isblack){
                //++numstring;
                ++countstring;
                stringhead[countstring] = j;
            }
            isblack =true;
            ++sizestring[countstring];
        }else{
            isblack =false;
        }
    }
    
    bool blackoverlap[numblack][numline];
    for(int i=0; i< numblack; ++i){
        for(int j=0; j< numline; ++j){
            blackoverlap[i][j] = false;
        }
    }
    for(int i=0; i< numblack; ++i){
        for(int j=0; j< numline; ++j){
            if(blackhead[i][j]){
                
            }
        }
    }
    
    
}//==================================================================
    
    //==================================================================
{//painting
    bool blackoverlap[numline];
    bool whiteoverlap[numline];
    bool blackoverlapsolo[numline];
    for(int i=0; i< numline; ++i){
        blackoverlap[i] =false;
        whiteoverlap[i] =true;
    }
    for(int i=0; i< numblack; ++i){
        for(int j=0; j< numline; ++j){
            blackoverlapsolo[j] =true;
        }
        for(int j=0; j< numline; ++j){
            if(blackhead[i][j]){
                for(int k=0; k< j; ++k){
                    blackoverlapsolo[k] =false;
                }
                for(int k=j; k< j +blacks[i]; ++k){
                    whiteoverlap[k] =false;
                }
                for(int k= j +blacks[i]; k< numline; ++k){
                    blackoverlapsolo[k] =false;
                }
            }
        }
        for(int j=0; j< numline; ++j){
            blackoverlap[j] |= blackoverlapsolo[j];
        }
    }
    for(int j=0; j< numline; ++j){
        flagblack[j] |= blackoverlap[j];
        flagwhite[j] |= whiteoverlap[j];
    }
    
    for(int i=0; i< numline; ++i){
        if(flagblack[i] & whiteoverlap[i]){
            throw String("error at line ")
                +String(indexline)
                +String(" - no much pattern");
        }
    }
}//==================================================================
    
    //==================================================================
    for(int i=0; i< numline; ++i){
        _flagblack[offset +step *i] = flagblack[i];
        _flagwhite[offset +step *i] = flagwhite[i];
    }
    
    for(int i=0; i< numblack; ++i){
        for(int j=0; j< numline; ++j){
            _blackhead[indexline][i][j] = blackhead[i][j];
        }
        delete [] blackhead[i];
    }
}
//===========================================================
//===========================================================
class IllustrationLogicSolver:
    public Frame,
    public ActionListener
{
private:
    const int NUM;
    IllustrationLogicCanvas* _ic;
    ScrollPane* _sc;
    Label* _label;
    Button* _button;
    TextField* _textfield;
    String _filename;
    
public:
    IllustrationLogicSolver(const String& string =String(L"")):
        Frame(string), NUM(1)
    {
        _ic = new IllustrationLogicCanvas();
        _sc = new ScrollPane(*_ic);
        _sc->setSize(600, 650);
        add(*_sc);
        //add(*_ic);
        
        _label = new Label(String("Calculation time  [ms]"));
        _button = new Button(String("Start Calculation"));
        _button->setBounds(
            0,
            _label->getHeight(),
            2 *_button->getWidth(),
            2 *_button->getHeight());
        _button->addActionListener(*this);
        
        _textfield = new TextField(5);
        _textfield->setBounds(
            0,
            _label->getHeight() +_button->getHeight(),
            1 *_button->getWidth(),
            1 *_button->getHeight());
        _textfield->addActionListener(*this);
        
        Container* container = new Container();
        container->setSize(
            _button->getWidth(),
            1 *(_textfield->getHeight() +_button->getHeight() +_label->getHeight()));
        container->add(*_label);
        container->add(*_button);
        container->add(*_textfield);
        add(*container);
        
        
    
        MenuBar& mb = *new MenuBar();
        setMenuBar(mb);
        mb.add(*new MenuFile());
        
    }
    ~IllustrationLogicSolver(){}
    
    void teststart()
    {
        setSize(850, 700);
        setVisible(true);
        //repaint();
    }
    
    virtual void actionPerformed(ActionEvent& e)
    {
        int elapsed = GetTickCount();
        Component* source = static_cast<Component*>(e.getSource());
        try{
            if(dynamic_cast<Button*>(source)){
//cout << "Button" << endl;
                source = dynamic_cast<Button*>(source);
                if(_ic->_numver >0 && _ic->_numhor >0){
                    for(int k=0; k< _ic->_numcalclation; ++k){
                        for(int i=0;
                            i< _ic->getNumVer() +_ic->getNumHor();
                            ++i)
                        {
                            _ic->calculateLine(i);
                        }
                    }
                }
            }else
            if(dynamic_cast<TextField*>(source)){
                source = dynamic_cast<TextField*>(source);
                int line = Integer::parseInt(source->TextComponent::getText());
//cout << "TextField  " << line << endl;
                if(line <0){
                    for(
                        int i=0;
                        i< _ic->getNumVer() *_ic->getNumHor();
                        ++i)
                    {
                        _ic->_flagblack[i] =false;
                        _ic->_flagwhite[i] =false;
                        
                        for(int i=0; i< _ic->_numver +_ic->_numhor; ++i){
                            int numline = i < _ic->_numver?
                                _ic->_numhor:
                                _ic->_numver;
                            for(int j=0; j< _ic->_numblack[i]; ++j){
                                int blackheadFirst = 0;
                                int blackheadLast = numline -_ic->_blacks[i][j];
                                for(int k=0; k< j; ++k){
                                    blackheadFirst += _ic->_blacks[i][k] +1;
                                }
                                for(int k= j+1; k< _ic->_numblack[i]; ++k){
                                    blackheadLast -= _ic->_blacks[i][k] +1;
                                }
                                
                                int k =0;
                                for(; k< blackheadFirst; ++k){
                                    _ic->_blackhead[i][j][k] =false;
                                }
                                for(; k<= blackheadLast; ++k){
                                    _ic->_blackhead[i][j][k] =true;
                                }
                                for(; k< numline; ++k){
                                    _ic->_blackhead[i][j][k] =false;
                                }
                            }
                        }
                    }
                }else
                if(line < _ic->getNumVer() +_ic->getNumHor()){
                    _ic->calculateLine2(line);
                }else{
                    for(
                        int i=0;
                        i< _ic->getNumVer() +_ic->getNumHor();
                        ++i)
                    {
                        _ic->calculateLine2(i);
                    }
                }
            }
            
            elapsed = GetTickCount() -elapsed;
            _label->setText(
                String("Calculation time ")
                +String(elapsed)
                +String("[ms]"));
        }catch(String s){
            _label->setText(s);
        }
        
        repaint();
    }
    void setFile(const String& filename){
        _filename = filename;
        _ic->setNumGrid(_filename);
        _sc->setSize(600, 650);
    }
};
//===========================================================
//===========================================================
void MenuFile::MenuOpen::Listener::actionPerformed(ActionEvent& e)
{
    MenuOpen& m
        = *static_cast<MenuOpen*>(e.getSource());
    MenuComponent* mc
        = dynamic_cast<MenuComponent*>(&m.getParent());
    MenuBar* mb
        = dynamic_cast<MenuBar*>(&mc->getParent());
    
    Frame* f
        = static_cast<Frame*>(&mb->getParent());
    
    FileDialog fd(*f, L"Open File");
    fd.setVisible(true);
    static_cast<IllustrationLogicSolver*>(f)->setFile(
        String(fd.getDirectory())
        +String(fd.getFile()));
}
//===========================================================
//===========================================================
int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPWSTR lpCmdLine,
    int nCmdShow)
{
    //wchar_t programname[MAX_PATH +1];
    //GetModuleFileNameW(0, programname, MAX_PATH);
    //TestButton test(programname);
    IllustrationLogicSolver test(GetCommandLineW());
    test.teststart();
    
    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return msg.wParam;
}
//===========================================================
//===========================================================



