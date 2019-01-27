

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
    
    //setNumGrid(String("iraroji/iraroji(60_50)-01.txt"));
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
        for(int k=0; k< _numver +_numhor; ++k){
            _blackhead[k] = new bool* [_numblack[k]];
            
            int numline = k < _numver?
                _numhor:
                _numver;
            for(int i=0; i< _numblack[k]; ++i){
                _blackhead[k][i] = new bool [numline];
                
                for(int j=0; j< numline; ++j){
                    _blackhead[k][i][j] =true;
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
    bool isfinished =true;
    for(int i=0; i< numline; ++i){
        flagblack[i] = _flagblack[offset +step *i];
        flagwhite[i] = _flagwhite[offset +step *i];
        isfinished &= flagblack[i] | flagwhite[i];
    }
    if(isfinished){ return; }
    
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
    
    //==================================================================
    bool prevflagblack[numline];
    bool prevflagwhite[numline];
    //ismuch =true;
    for(int j=0; j< numline; ++j){
        //ismuch &= prevflagblack[j] == flagblack[j];
        //ismuch &= prevflagwhite[j] == flagwhite[j];
        prevflagblack[j] = flagblack[j];
        prevflagwhite[j] = flagwhite[j];
    }
    bool ismuch =false;
    
    //==================================================================
    while(!ismuch){
        for(int i=0; i< numline; ++i){
            if(flagblack[i]){
                int countblack =0;
                int indexblack =-1;
                for(int j=0; j< numblack; ++j){
                    for(int k=0; k< blacks[j]; ++k){
                        if((i -k) >=0 && blackhead[j][i -k]){
                            ++countblack;
                            indexblack = j;
                            break;
                        }
                    }
                }
                
                if(countblack == 1){
                    for(int j=0; j<= i -blacks[indexblack]; ++j){
                        if(blackhead[indexblack][j]){
                            blackhead[indexblack][j] =false;
                        }
                    }
                    for(int j= i +1; j< numline; ++j){
                        if(blackhead[indexblack][j]){
                            blackhead[indexblack][j] =false;
                        }
                    }
                }else
                if(countblack > 1){
                    bool soloblack[numline];
                    bool blackoverlap[numline];
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
                }
            }
        }
        
        //==================================================================
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
                        }
                    }
                }
            }
        }
        
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
            flagwhite[i] = whiteoverlap[i];
        }
        
        //==================================================================
        for(int i=0; i< numline; ++i){
            if(flagblack[i] & whiteoverlap[i]){
                throw String("error at line ")
                    +String(indexline)
                    +String(" - no much pattern");
            }
        }
        
        //==================================================================
        ismuch =true;
        for(int j=0; j< numline; ++j){
            ismuch &= prevflagblack[j] == flagblack[j];
            ismuch &= prevflagwhite[j] == flagwhite[j];
            prevflagblack[j] = flagblack[j];
            prevflagwhite[j] = flagwhite[j];
        }
    }
    
    
    
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
                    blackhead[indexfirstblack][k] =false;
                }
                break;
            }
        }
    }
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
                break;
            }
        }
    }
    
    
    
    //==================================================================
    bool isrewrited =true;
    while(isrewrited){
        isrewrited =false;
        
        for(int i=0; i< numline; ++i){
            if(flagblack[i]){
                int countblack =0;
                int indexblack =-1;
                for(int j=0; j< numblack; ++j){
                    for(int k=0; k< blacks[j]; ++k){
                        if((i -k) >=0 && blackhead[j][i -k]){
                            ++countblack;
                            indexblack = j;
                            break;
                        }
                    }
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
                    
                    bool soloblack[numline];
                    bool blackoverlap[numline];
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
        flagwhite[i] = whiteoverlap[i];
    }
    
    
    for(int i=0; i< numline; ++i){
        if(flagblack[i] & whiteoverlap[i]){
            throw String("error at line ")
                +String(indexline)
                +String(" - no much pattern");
        }
    }
    
    
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
    bool isfinished =true;
    for(int i=0; i< numline; ++i){
        flagblack[i] = _flagblack[offset +step *i];
        flagwhite[i] = _flagwhite[offset +step *i];
        isfinished &= flagblack[i] | flagwhite[i];
    }
    if(isfinished){ return; }
    
    //==================================================================
    bool blackhead[numblack][numline];
    for(int i=0; i< numblack; ++i){
        bool doexist =true;
        for(int j=0; j< numline; ++j){
            blackhead[i][j] = true;
            doexist &= blackhead[i][j];
        }
    }
    
    //==================================================================
    bool prevflagblack[numline];
    bool prevflagwhite[numline];
    bool prevblackhead[numblack][numline];
    //ismuch =true;
    for(int j=0; j< numline; ++j){
        //ismuch &= prevflagblack[j] == flagblack[j];
        //ismuch &= prevflagwhite[j] == flagwhite[j];
        prevflagblack[j] = flagblack[j];
        prevflagwhite[j] = flagwhite[j];
        for(int i=0; i< numblack; ++i){
            //ismuch &= prevblackhead[i][j] == blackhead[i][j];
            prevblackhead[i][j] = blackhead[i][j];
        }
    }
    bool ismuch =false;
    
    //==================================================================
    while(!ismuch){
        
        //chamber
        //==================================================================
        int numchamber =0;
{//numchamber
        bool iswhite =true;
        for(int j=0; j< numline; ++j){
            if(flagwhite[j]){
                iswhite =true;
            }else{
                if(iswhite){
                    ++numchamber;
                }
                iswhite =false;
            }
        }
}//numchamber
        
        //==================================================================
        int chamberhead[numchamber];
        int sizechamber[numchamber];
{//chamberhead, sizechamber
        for(int i=0; i< numchamber; ++i){
            sizechamber[i] =0;
        }
        bool iswhite =true;
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
}//chamberhead, sizechamber
        
        //==================================================================
        for(int j=0; j< numline; ++j){
            if(flagblack[j]){
                for(int i=0; i< numblack; ++i){
                    if(j -blacks[i] >=0){
                        blackhead[i][j -blacks[i]] =false;
                    }
                    if(j+1 < numline){
                        blackhead[i][j+1] =false;
                    }
                }
            }
            if(flagwhite[j]){
                for(int i=0; i< numblack; ++i){
                    blackhead[i][j] =false;
                }
            }
        }
        
        //==================================================================
        for(int k=0; k< numchamber; ++k){
            for(int i=0; i< numblack; ++i){
                for(int j= chamberhead[k];
                    j< chamberhead[k] +sizechamber[k];
                    ++j)
                {
                    if(sizechamber[k] < blacks[i]){
                        blackhead[i][j] =false;
                    }else
                    if(blackhead[i][j]
                        && j +blacks[i] > chamberhead[k] +sizechamber[k])
                    {
                        blackhead[i][j] = false;
                    }
                }
            }
        }
        
        //==================================================================
{//
        int offsetblack =0;
        for(int k=0; k< numchamber; ++k){
            for(int j= chamberhead[k];
                j< chamberhead[k] +sizechamber[k];
                ++j)
            {
                if(blackhead[offsetblack][j]){
                    int tail = j +blacks[offsetblack];
                    if(tail <= chamberhead[k] +sizechamber[k]){
                        ++offsetblack;
                        if(offsetblack >= numblack){
                            break;
                        }
                        for(int i= offsetblack; i< numblack; ++i){
                            for(int j2=0;
                                j2<= Math::min(numline -1, tail);
                                ++j2)
                            {
                                blackhead[i][j2] =false;
                            }
                        }
                    }else{
                        blackhead[offsetblack][j] =false;
                    }
                }
            }
            if(offsetblack >= numblack){
                break;
            }
        }
}//
{//
        int offsetblack = numblack -1;
        for(int k= numchamber -1; k>= 0; --k){
            int indexwall = chamberhead[k] +sizechamber[k];
            for(int j= chamberhead[k] +sizechamber[k] -1;
                j>= chamberhead[k];
                --j)
            {
                if(blackhead[offsetblack][j]){
                    int tail = j +blacks[offsetblack];
                    if(tail <= indexwall){
                        indexwall = j -1;
                        --offsetblack;
                        if(offsetblack <0){
                            break;
                        }
                        for(int i= offsetblack; i>= 0; --i){
                            for(int j2= Math::max(0, j-1);
                                j2< numline;
                                ++j2)
                            {
                                blackhead[i][j2] =false;
                            }
                        }
                    }else{
                        blackhead[offsetblack][j] =false;
                    }
                }
            }
            if(offsetblack <0){
                break;
            }
        }
}//
        
        //string black
        //==================================================================
        int numstring =0;
{//numstring
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
}//numstring
        
        //==================================================================
        int stringhead[numstring];
        int sizestring[numstring];
{//stringhead, sizestring
        for(int i=0; i< numstring; ++i){
            sizestring[i] =0;
        }
        bool isblack =false;
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
}//stringhead, sizestring
        
        //ispossible
        //==================================================================
        bool ispossible[numstring][numblack];
{//ispossible
        //==================================================================
        bool blackoverlap[numblack][numline];
        for(int i=0; i< numblack; ++i){
            for(int j=0; j< numline; ++j){
                blackoverlap[i][j] = false;
            }
        }
        for(int i=0; i< numblack; ++i){
            for(int j=0; j< numline; ++j){
                if(blackhead[i][j]){
                    for(int k=0; k< blacks[i]; ++k){
                        blackoverlap[i][j +k] |= true;
                    }
                }
            }
        }
        
        //==================================================================
        for(int k=0; k< numstring; ++k){
            for(int i=0; i< numblack; ++i){
                ispossible[k][i] =true;
            }
        }
        for(int k=0; k< numstring; ++k){
            for(int j= stringhead[k];
                j< stringhead[k] +sizestring[k];
                ++j)
            {
                for(int i=0; i< numblack; ++i){
                    ispossible[k][i] &= blackoverlap[i][j];
                }
            }
            for(int i=0; i< numblack; ++i){
                ispossible[k][i] &= blacks[i] >= sizestring[k];
            }
        }
}//
        
        //==================================================================
        int indexchamberstring[numstring];
        for(int k=0; k< numstring; ++k){
            int countchamber = numchamber -1;
            while(chamberhead[countchamber] > stringhead[k]){
                if(--countchamber <0){
                    throw String("error at line ")
                        +String(indexline)
                        +String(" - black string");
                }
            }
            indexchamberstring[k] = countchamber;
        }
        
        //==================================================================
{//
        int indexblackdetermined[numstring];
        for(int k=0; k< numstring; ++k){
            indexblackdetermined[k] =-1;
            for(int i=0; i< numblack; ++i){
                if(ispossible[k][i]){
                    if(indexblackdetermined[k] ==-1){
                        indexblackdetermined[k] = i;
                    }else{
                        indexblackdetermined[k] =-2;
                        break;
                    }
                }
            }
        }
        int prevcount =0;
        for(int k=0; k< numstring; ++k){
            if(indexblackdetermined[k] >=0){
                ++prevcount;
            }
        }
        
        while(1){
            for(int k=0; k< numstring; ++k){
                int index = indexblackdetermined[k];
                if(index >=0){
                    for(int i= index; i< numblack; ++i){
                        for(int k2=0; k2< k; ++k2){
                            if(indexchamberstring[k]
                                != indexchamberstring[k2])
                            {
                                ispossible[k2][i] =false;
                            }else{
                                if(stringhead[k] +blacks[index]
                                    < stringhead[k2] +sizestring[k2])
                                {
                                    ispossible[k2][i] =false;
                                }
                            }
                        }
                    }
                    for(int i=0; i<= index; ++i){
                        for(int k2= k+1; k2< numstring; ++k2){
                            if(indexchamberstring[k]
                                != indexchamberstring[k2])
                            {
                                ispossible[k2][i] =false;
                            }else{
                                if(stringhead[k] +blacks[index]
                                    < stringhead[k2] +sizestring[k2])
                                {
                                    ispossible[k2][i] =false;
                                }
                            }
                        }
                    }
                }
            }
            int count =0;
            for(int k=0; k< numstring; ++k){
                if(indexblackdetermined[k] >=0){
                    ++count;
                }
            }
            if(prevcount == count){ break; }
            prevcount = count;
        }
}//
        
        //==================================================================
        for(int k=0; k< numstring; ++k){
            for(int i=0; i< numblack; ++i){
                if(ispossible[k][i]){
                    for(int j= stringhead[k] +1; j< numline; ++j){
                        blackhead[i][j] =false;
                    }
                    break;
                }
            }
        }
        for(int k= numstring -1; k>= 0; --k){
            for(int i= numblack -1; i>= 0; --i){
                if(ispossible[k][i]){
                    for(int j=0;
                        j< stringhead[k] +sizestring[k] -blacks[i];
                        ++j)
                    {
                        blackhead[i][j] =false;
                    }
                    break;
                }
            }
        }
        
        //==================================================================
{//painting in black string
        bool blackoverlap[numline];
        bool whiteoverlap[numline];
        bool blackoverlapsolo[numline];
        bool whiteoverlapsolo[numline];
        for(int i=0; i< numline; ++i){
            blackoverlap[i] =false;
            //whiteoverlap[i] =true;
            whiteoverlap[i] =false;
        }
        for(int k=0; k< numstring; ++k){
            bool blackoverlapstring[numline];
            bool whiteoverlapstring[numline];
            for(int j=0; j< numline; ++j){
                blackoverlapstring[j] =true;
                whiteoverlapstring[j] =true;
            }
            for(int i=0; i< numblack; ++i){
                if(ispossible[k][i]){
                    for(int j=0; j< numline; ++j){
                        blackoverlapsolo[j] =true;
                        whiteoverlapsolo[j] =true;
                    }
                    for(int j= Math::max(
                            0, 
                            stringhead[k] +sizestring[k] -blacks[i]);
                        j<= stringhead[k];
                        ++j)
                    {
                        if(blackhead[i][j]){
                            for(int j2= 0; j2< j; ++j2){
                                blackoverlapsolo[j2] =false;
                            }
                            for(int j2= j +blacks[i]; j2< numline; ++j2){
                                blackoverlapsolo[j2] =false;
                            }
                            for(int j2= 0; j2< j -1; ++j2){
                                whiteoverlapsolo[j2] =false;
                            }
                            for(int j2= j; j2< j +blacks[i]; ++j2){
                                whiteoverlapsolo[j2] =false;
                            }
                            for(int j2= j +blacks[i] +1; j2< numline; ++j2){
                                whiteoverlapsolo[j2] =false;
                            }
                        }
                    }
                    for(int j=0; j< numline; ++j){
                        blackoverlapstring[j] &= blackoverlapsolo[j];
                        whiteoverlapstring[j] &= whiteoverlapsolo[j];
                    }
                }else{
                    
                }
            }
            
            for(int j=0; j< numline; ++j){
                blackoverlap[j] |= blackoverlapstring[j];
                whiteoverlap[j] |= whiteoverlapstring[j];
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
                    +String(" - painting in black string");
            }
        }
}//painting in black string
    
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
                    for(int k= j; k< j +blacks[i]; ++k){
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
                    +String(" - painting");
            }
        }
}//painting
    
        //==================================================================
        //for(int i=0; i< numblack; ++i){
        //    cout << indexline << ", " << blacks[i] << "==> ";
        //    for(int j=0; j< numline; ++j){
        //        cout << blackhead[i][j];
        //        if(!((j+1)%5)){
        //            cout << " ";
        //        }
        //    }
        //    cout << endl;
        //}
        //cout << endl;
        //==================================================================
        
        //==================================================================
        ismuch =true;
        for(int j=0; j< numline; ++j){
            ismuch &= prevflagblack[j] == flagblack[j];
            ismuch &= prevflagwhite[j] == flagwhite[j];
            prevflagblack[j] = flagblack[j];
            prevflagwhite[j] = flagwhite[j];
            
            for(int i=0; i< numblack; ++i){
                ismuch &= prevblackhead[i][j] == blackhead[i][j];
                prevblackhead[i][j] = blackhead[i][j];
            }
        }
        
    }//while
    
    //==================================================================
    for(int i=0; i< numline; ++i){
        _flagblack[offset +step *i] = flagblack[i];
        _flagwhite[offset +step *i] = flagwhite[i];
    }
    
    for(int i=0; i< numblack; ++i){
        for(int j=0; j< numline; ++j){
            _blackhead[indexline][i][j] = blackhead[i][j];
        }
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
        
        setFile(String("iraroji/iraroji(60_50)-03.txt"));
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
                    }
                    for(int k=0; k< _ic->getNumVer() +_ic->getNumHor(); ++k){
                        int numline = k < _ic->getNumVer()?
                            _ic->getNumHor():
                            _ic->getNumVer();
                        for(int i=0; i< _ic->_numblack[k]; ++i){
                            for(int j=0; j< numline; ++j){
                                _ic->_blackhead[k][i][j] =true;
                            }
                        }
                    }
                }else
                if(line < _ic->getNumVer() +_ic->getNumHor()){
                    _ic->calculateLine(line);
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
        setTitle(filename);
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



