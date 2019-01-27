

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
class IllustrationLogicCanvas:
    public Canvas,
    public MouseListener,
    public MouseMotionListener
{
private:
    class Combination
    {
    private:
        unsigned long long int _count;
        int _numhole;
        int _numball;
        int* _indexhole;
        int shift(int indexball){
            if(indexball <0 || indexball >=_numball){
                throw String("error in combination");
            }
            
            if(_indexhole[indexball] +(_numball -indexball) < _numhole){
                ++_indexhole[indexball];
            }else{
                if(indexball == 0){
                    _indexhole[indexball] =0;
                }else{
                    _indexhole[indexball] = shift(indexball -1) +1;
                }
            }
            return _indexhole[indexball];
        }
    public:
        Combination(int numhole, int numball){
            _count = 0;
            _numhole = numhole;
            _numball = numball;
            _indexhole = new int [_numball];
            for(int i=0; i< _numball; ++i){
                _indexhole[i] = i;
            }
        }
        Combination(const Combination& com){
            _count = com._count;
            _numhole = com._numhole;
            _numball = com._numball;
            _indexhole = new int [_numball];
            for(int i=0; i< _numball; ++i){
                _indexhole[i] = com._indexhole[i];
            }
        }
        ~Combination(){ delete [] _indexhole; }
        bool increment(){
            _indexhole[_numball -1] = shift(_numball -1);
            ++_count;
            return _indexhole[_numball -1] == _numball -1;
        }
        bool shiftR(int indexball){
            if(indexball <0 || indexball >=_numball){
                throw String("error in combination");
            }
            
            bool ischanged =false;
            if(_indexhole[indexball] +(_numball -indexball) < _numhole){
                if(indexball == _numball -1){
                    ++_indexhole[indexball];
                    ischanged =true;
                }else{
                    if(_indexhole[indexball] +1 < _indexhole[indexball +1]){
                        ++_indexhole[indexball];
                        ischanged =true;
                    }else{
                        if(shiftR(indexball +1)){
                            ++_indexhole[indexball];
                            ischanged =true;
                        }
                        //else{ ischanged =false; }
                    }
                }
            }
            //else{ ischanged =false; }
            
            return ischanged;
        }
        bool shiftL(int indexball){
            if(indexball <0 || indexball >=_numball){
                throw String("error in combination");
            }
            
            bool ischanged =false;
            if(_indexhole[indexball] > indexball){
                if(indexball == 0){
                    --_indexhole[0];
                    ischanged =true;
                }else{
                    if(_indexhole[indexball] -1 > _indexhole[indexball -1]){
                        --_indexhole[indexball];
                        ischanged =true;
                    }else{
                        if(shiftL(indexball -1)){
                            --_indexhole[indexball];
                            ischanged =true;
                        }
                        //else{ ischanged =false; }
                    }
                }
            }
            //else{ ischanged =false; }
            
            return ischanged;
        }
        unsigned long long int getCount(){ return _count; }
        int* getIndices(){ return _indexhole; }
    };
    
public:
    char* _numblack;
    int** _blacks;
    
    int _gridsize;
    int _numver;
    int _numhor;
    bool* _grid;
    bool* _flag;
    
    int _numcalclation;
    
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
};
//===========================================================
//===========================================================
IllustrationLogicCanvas::IllustrationLogicCanvas()
{
    
    _numcalclation =1;
    _numblack =0;
    _blacks   =0;
    
    _gridsize =10;
    _grid =0;
    _flag =0;
    
    setNumGrid(String("iraroji/iraroji-01(15-15).txt"));
    addMouseListener(*this);
    addMouseMotionListener(*this);
    setVisible(true);
}
IllustrationLogicCanvas::~IllustrationLogicCanvas()
{
    if(_blacks){
        for(int i=0; i< _numver +_numhor; ++i){
            delete [] _blacks[i];
        }
        delete [] _blacks;
    }
    delete [] _numblack;
    
    delete [] _grid;
    delete [] _flag;
}
//===========================================================
//===========================================================
void IllustrationLogicCanvas::setNumGrid(const String& filename)
{
    if(_blacks){
        for(int i=0; i< _numver +_numhor; ++i){
            delete [] _blacks[i];
        }
        delete [] _blacks;
    }
    delete [] _numblack;
    delete [] _grid;
    delete [] _flag;
    
    
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
//cout << array[i] << " ";
    }
//cout << num[0] << "  " << num[1] << "  " << num[2] << endl;
//cout << endl;
    
    _numver = num[1];
    _numhor = num[2];
    
    //_numver = numver;
    //_numhor = numhor;
    
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
    
//for(int i=0; i< _numver +_numhor; ++i){
//    cout << (int)_numblack[i] << endl;
//}
//for(int i=0; i< _numver +_numhor; ++i){
//    for(int j=0; j< _numblack[i]; ++j){
//        cout << _blacks[i][j] << "  ";
//    }
//    cout << endl;
//}
    
    _grid = new bool [_numver *_numhor];
    _flag = new bool [_numver *_numhor];
    for(int i=0; i< _numver *_numhor; ++i){
        _grid[i] =false;
        _flag[i] =false;
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
            if(_flag[_numhor *i +j]){
                if(_grid[_numhor *i +j]){
                    g.fillRect(
                        _gridsize *j, _gridsize *i,
                        _gridsize, _gridsize);
                }else{
                    g.drawLine(
                        _gridsize *j, _gridsize *i,
                        _gridsize *(j+1), _gridsize *(i+1));
                    g.drawLine(
                        _gridsize *(j+1), _gridsize *i,
                        _gridsize *j, _gridsize *(i+1));
                }
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
        _grid[_numhor *numver +numhor] = true;
        _flag[_numhor *numver +numhor] = true;
    }else
    if(button == MouseEvent::BUTTON2){
        _grid[_numhor *numver +numhor] = false;
        _flag[_numhor *numver +numhor] = true;
    }else
    if(button == MouseEvent::BUTTON3){
        //_grid[_numhor *numver +numhor] = true;
        _flag[_numhor *numver +numhor] = false;
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
            _grid[_numhor *numver +numhor] = true;
            _flag[_numhor *numver +numhor] = true;
        }else
        if(button == MouseEvent::BUTTON2){
            _grid[_numhor *numver +numhor] = false;
            _flag[_numhor *numver +numhor] = true;
        }else
        if(button == MouseEvent::BUTTON3){
            //_grid[_numhor *numver +numhor] = true;
            _flag[_numhor *numver +numhor] = false;
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
    //int index;
    int numline;
    int offset;
    int step;
    if(indexline < _numver){
        //index   = indexline;
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
    
    int numblack = _numblack[indexline];
    int* blacks = new int [numblack];
    for(int i=0; i< numblack; ++i){
        blacks[i] = _blacks[indexline][i];
    }
    
    
    
    
    int totalwhite = numline;
    for(int i=0; i< numblack; ++i){
        totalwhite -= blacks[i];
    }
    
    double combination =1;
    double factorial =1;
    double max = Math::max(numblack, totalwhite +1 - numblack);
    double min = Math::min(numblack, totalwhite +1 - numblack);
    for(int i=1; i<= min; ++i){
        factorial   *= i;
        combination *= max +i;
    }
    
    combination /= factorial;
    
//cout << indexline << "  ";
//cout << combination /factorial << endl;
    
    
    
    
    
    bool* grid = new bool [numline];
    bool* flag = new bool [numline];
    bool* flagblack = new bool [numline];
    bool* flagwhite = new bool [numline];
    //bool* historygrid = new bool [numline];
    bool* copiedgrid = new bool [numline];
    bool* copiedflag = new bool [numline];
    int numdetermined =0;
    for(int i=0; i< numline; ++i){
        grid[i] = true;
        flag[i] = true;
        flagblack[i] = _flag[offset +step *i] &_grid[offset +step *i]?
            true:
            false;
        flagwhite[i] = _flag[offset +step *i] & !_grid[offset +step *i]?
            true:
            false;
        //historygrid[i] = _grid[offset +step *i];
        copiedgrid[i] = _grid[offset +step *i];
        copiedflag[i] = _flag[offset +step *i];
        numdetermined += _flag[offset +step *i]?
            1:
            0;
    }
    
    
    
    //==================================================================
    
    
//for(int j=0; j< numline; ++j){
//    cout << flagblack[j] << " ";
//}
//cout << endl;
//for(int j=0; j< numline; ++j){
//    cout << flagwhite[j] << " ";
//}
//cout << endl;
    
    
    /*
//cout << endl;
    bool** blackhead;
    blackhead = new bool* [numblack];
    for(int i=0; i< numblack; ++i){
        blackhead[i] = new bool[numline];
        for(int j=0; j< numline; ++j){
            blackhead[i][j] = false;
        }
    }
    
    
    int indexfirst =0;
    for(int i=0; i< numblack; ++i){
        
if(indexfirst > numline -blacks[i]){
    throw String("error at line ")
        +String(indexline)
        +String(" - no much pattern");
}
        
        int head =numline;
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
    
    
//for(int i=0; i< numblack; ++i){
//    cout << blacks[i] << "  - ";
//    for(int j=0; j< numline; ++j){
//        cout << blackhead[i][j];
//        if(!((j+1)%5)){
//            cout << " ";
//        }
//    }
//    cout << endl;
//}
//cout << endl;
    
    
    
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
                                
                                
                                
//cout << "indexblack-" << j  << ", indexline-" << i-k << ", soloblack- ";
//for(int n=0; n< numline; ++n){
//    cout << soloblack[n];
//    if(!((n+1)%5)){
//        cout << " ";
//    }
//}
//cout << endl;
                            
                            
                            
                            }
                        }
                        
                        
//cout << "indexblack-" << j << ", blackoverlap- ";
//for(int n=0; n< numline; ++n){
//    cout << blackoverlap[n];
//    if(!((n+1)%5)){
//        cout << " ";
//    }
//}
//cout << endl;
                        
                        
                        
                        
                   
                        
                        
                    }
                    
                    
                    for(int k=0; k< numline; ++k){
                        flagblack[k] |= blackoverlap[k];
                    }
                        
                             
                        
//cout << ", flagblack- ";
//for(int n=0; n< numline; ++n){
//    cout << flagblack[n];
//    if(!((n+1)%5)){
//        cout << " ";
//    }
//}
//cout << endl;
                
                
                
                
                }
                
                
                
                
            }
        }
    }
    
    
//for(int i=0; i< numblack; ++i){
//    cout << blacks[i] << "  - ";
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
    
    
    
//for(int i=0; i< numblack; ++i){
//    cout << blacks[i] << "  - ";
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
    
    
    
    
    //for(int i=0; i< numline; ++i){
    //    flagblack[i] =false;
    //    flagwhite[i] =false;
    //}
    bool* soloblack  = new bool [numline];
    bool* blackoverlap = new bool [numline];
    bool* whiteoverlap = new bool [numline];
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
                
                
                
                
//cout << "indexblack-" << i  << ", indexline-" << j << ", soloblack- ";
//for(int k=0; k< numline; ++k){
//    cout << soloblack[k];
//    if(!((k+1)%5)){
//        cout << " ";
//    }
//}
//cout << endl;
                
                
                
                
                
            }
        }
        
        
//cout << "indexblack-" << i << ", blackoverlap- ";
//for(int j=0; j< numline; ++j){
//    cout << blackoverlap[j];
//    if(!((j+1)%5)){
//        cout << " ";
//    }
//}
//cout << endl;
        
        
        
        for(int j=0; j< numline; ++j){
            flagblack[j] |= blackoverlap[j];
        }
        
        
        
        
        
//cout << "flagblack-    ";
//for(int j=0; j< numline; ++j){
//    cout << flagblack[j];
//    if(!((j+1)%5)){
//        cout << " ";
//    }
//}
//cout << endl;
        
        
        
        
        
        
        
    }
    
//cout << "whiteoverlap- ";
//for(int j=0; j< numline; ++j){
//    cout << whiteoverlap[j];
//    if(!((j+1)%5)){
//        cout << " ";
//    }
//}
//cout << endl;
    
    
    for(int i=0; i< numline; ++i){
if(flagblack[i] & whiteoverlap[i]){
    throw String("error at line ")
        +String(indexline)
        +String(" - no much pattern");
}
    }
    
    
    
    for(int i=0; i< numline; ++i){
        //if(!_flag[offset +step *i]){
            _grid[offset +step *i] = flagblack[i];
            _flag[offset +step *i] = flagblack[i] | whiteoverlap[i];
        //}
    }
    
    
    delete [] soloblack;
    delete [] blackoverlap;
    delete [] whiteoverlap;
    
    
    
    
    
    
    
    
    for(int i=0; i< numblack; ++i){
        delete [] blackhead[i];
    }
    delete [] blackhead;
    delete [] flagblack;
    delete [] flagwhite;
    
    delete [] blacks;
    delete [] grid;
    delete [] flag;
    delete [] copiedgrid;
    delete [] copiedflag;
    
    return;
}
*/
    //==================================================================
    
    //==================================================================
    
   int count =0;
   for(int i=0; i< numline; ++i){
       count += _flag[i]?
           1:
           0;
   }
   if(count > numline){ return; }
    
    Combination com(totalwhite +1, numblack);
    
    bool isinitialised =false;
    bool isbacked = false;
    while(!isbacked){
        isbacked = com.increment();
        
        int* array = com.getIndices();
        
/*
cout << com.getCount() << " -- ";
for(int i=0; i< numblack; ++i){
    cout << array[i] << " ";
}
cout << " / ";
//cout << endl;
*/
        
        
            int k=0;
            for(int i=0; i< numblack; ++i){
                int width = i >0?
                    array[i] -array[i-1]:
                    array[0];
                
                for(int j=0; j< width; ++j){
                    grid[k] = false;
                    ++k;
                }
                for(int j=0; j< blacks[i]; ++j){
                    grid[k] = true;
                    ++k;
                }
            }
            for(; k< numline; ++k){
                grid[k] = false;
            }
        
        
/*
for(int i=0; i< numline; ++i){
    cout << grid[i] << " ";
}
cout << endl;
*/
        
        
        

        bool isinvalid =false;    
        for(int k=0; k< numline; ++k){
            if(copiedflag[k]){
                if(copiedgrid[k] != grid[k]){
                    isinvalid =true;
                    break;
                }
            }
        }
        //if(isinvalid){ continue; }
        
        if(!isinvalid){
            for(int k=0; k< numline; ++k){
                if(!copiedflag[k]){
                    if(isinitialised){
                        flag[k] = flag[k] & !(copiedgrid[k] ^grid[k]);
                    }
                    copiedgrid[k] = grid[k];
                }
            }
            isinitialised =true;
        }
        
        
/*
for(int i=0; i< numline; ++i){
    cout << flag[i] << " ";
}
cout << endl;
*/
        /*
        int count =0;
        for(int i=0; i< numline; ++i){
            count += flag[i]?
                1:
                0;
        }
        if(count <= numdetermined){ break; }*/
        
/*
for(int i=0; i< numline; ++i){
    cout << grid[i] << " ";
}
cout << endl;
*/
        
        
        
    }
    
    if(!isinitialised){
        throw String("error at line ")
            +String(indexline)
            +String(" - no much pattern");
    }
    
    
    for(int k=0; k< numline; ++k){
        _grid[offset +step *k] = copiedgrid[k];
        _flag[offset +step *k] = flag[k];
    }
    
    delete [] blacks;
    delete [] grid;
    delete [] flag;
    delete [] flagblack;
    delete [] flagwhite;
    //delete [] historygrid;
    delete [] copiedgrid;
    delete [] copiedflag;
    
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
    Label* _label;
    Button* _button;
    TextField* _textfield;
    String _filename;
    
public:
    IllustrationLogicSolver(const String& string =String(L"")):
        Frame(string), NUM(1)
    {
        _ic = new IllustrationLogicCanvas();
        ScrollPane* sc = new ScrollPane(*_ic);
        sc->setSize(600, 650);
        add(*sc);
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
                    for(int i=0; i< _ic->_numver *_ic->_numhor; ++i){
                        _ic->_grid[i] =false;
                        _ic->_flag[i] =false;
                    }
                }else{
                    _ic->calculateLine(line);
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



