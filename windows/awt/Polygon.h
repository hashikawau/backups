

#ifndef __Windows_awt_Polygon
#define __Windows_awt_Polygon


//===========================================================
//===========================================================
class Polygon
{
private:
    int _capacity;
    
public:
    int npoints;
    int* xpoints;
    int* ypoints;
    
    Polygon();
    Polygon(int xpoints[], int ypoints[], int npoints);
    ~Polygon();
    
    void addPoint(int x, int y);
    void translate(int deltaX, int deltaY);
};
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_Polygon

