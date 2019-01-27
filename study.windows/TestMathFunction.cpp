

#include "windows\awt\Frame.h"
#include "windows\awt\Canvas.h"
#include "windows\awt\TextField.h"
#include "windows\lang\String.h"
#include <iostream.h>



//===========================================================
//===========================================================
class MathFunction
{
public:
    MathFunction();
    virtual ~MathFunction() =0;
    virtual double getValue(double x) =0;
    virtual void getCenter(double& x, double& y) =0;
};
//===========================================================
//===========================================================
MathFunction::MathFunction(){}
MathFunction::~MathFunction(){}
//===========================================================
//===========================================================

//===========================================================
//===========================================================
class F: public MathFunction
{
private:
    int _order;
    double _a[5];
    
public:
    F();
    virtual ~F();
    virtual double getValue(double x);
    virtual void getCenter(double& x, double& y);
    double& getC(int index);
};
//===========================================================
//===========================================================
F::F()
{
    _order =4;
    for(int i=0; i< _order +1; ++i){
        _a[i] =0;
    }
    _a[4]=1;
}
F::~F(){}
double F::getValue(double x)
{
    double value =0;
    for(int i= _order; i> 0; --i){
        value = (value +_a[i]) *x;
    }
    return value +_a[0];
}
void F::getCenter(double& x, double& y)
{
    x = -_a[3] /4 /_a[4];
    y = getValue(x);
}
double& F::getC(int index)
{
    return _a[index];
}
//===========================================================
//===========================================================

//===========================================================
//===========================================================
class ScatterPlot: public Canvas
{
protected:
    PointerObject<Image> _image;
    const Graphics* _graphicsImage;
    PointerObject<MathFunction> _function;
    int _scale;
    
public:
    ScatterPlot();
    //ScatterPlot(const MathFunction& function);
    ~ScatterPlot();
    virtual void update(Graphics& g);
    virtual void paint(Graphics& g);
    
    void addFunction(const MathFunction& function);
    void plot();
};
//===========================================================
//===========================================================
ScatterPlot::ScatterPlot()
{
}/*
ScatterPlot::ScatterPlot(const MathFunction& function):
    _function(&function)
{
    plot();
}*/
ScatterPlot::~ScatterPlot(){}
void ScatterPlot::update(Graphics& g)
{
    paint(g);
}
void ScatterPlot::paint(Graphics& g)
{
    if(_image){
        g.drawImage(*_image, 0, 0, *this);
    }
}
void ScatterPlot::addFunction(const MathFunction& function)
{
    _function = &function;
    _image = createImage(getWidth(), getHeight());
    _graphicsImage = &(_image->getGraphics());
    plot();
}
void ScatterPlot::plot()
{
    _graphicsImage->setColor(Color::white);
    _graphicsImage->fillRect(0, 0, getWidth(), getHeight());
    
    double a =1;
    double b =2;
    double c =3;
    double d =10;
    double e =1;
    _function->F::getC(4) = e;
    _function->F::getC(3) = -e *(a +b +c +d);
    _function->F::getC(2) = e *((a+b)*(c+d) +a*b +c*d);
    _function->F::getC(1) = -e *(a*b*(c+d) +c*d*(a+b));
    _function->F::getC(0) = e *a *b *c *d;
    
    _scale = 1;
    double centerx;
    double centery;
    _function->getCenter(centerx, centery);
    _graphicsImage->setColor(Color::black);
    double x;
    double y;
    for(int i=0; i< 10; ++i){
        
        x = centerx -i;
        y = _function->getValue(x);
        x *= 10;
        y *= -_scale;
        x += getWidth() /2;
        y += getHeight() /2;
        _graphicsImage->fillOval(x -2, y -2, 4, 4);
        cout << x << " " << y << endl;
        
        x = centerx +i;
        y = _function->getValue(x) +centery;
        x *= 10;
        y *= -_scale;
        x += getWidth() /2;
        y += getHeight() /2;
        _graphicsImage->fillOval(x -2, y -2, 4, 4);
        cout << x << " " << y << endl;
        
    }
}
//===========================================================
//===========================================================

//===========================================================
//===========================================================
class Test:
    public Frame,
    //public ActionListener,
    public Thread
{
private:
    ScatterPlot* _plot;
    F* _f;
    
public:
    Test(const String& str);
    //virtual void paint(Graphics& g);
    //virtual void actionPerformed(ActionEvent& e);
    virtual void run();
    
    void teststart();
};
//===========================================================
//===========================================================
Test::Test(const String& str): Frame(str)
{
    setBounds(10, 20, 600, 700);
    
    _f = new F();
    _plot = new ScatterPlot();
    _plot->setSize(getWidth(), getHeight());
    _plot->addFunction(*_f);
    add(*_plot);
}
void Test::run()
{

}
void Test::teststart()
{
    setVisible(true);
    //start();
}
//===========================================================
//===========================================================

//===========================================================
//===========================================================
int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPWSTR lpCmdLine,
    int nCmdShow)
{
    Test test(GetCommandLineW());
    test.teststart();
    
    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return msg.wParam;
}


