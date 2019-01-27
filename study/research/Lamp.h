

#ifndef __Windows_research_Lamp
#define __Windows_research_Lamp


#include "Laboratory.h"

//===========================================================
//===========================================================
class Lamp
{
private:
    //double _maxHeat;
    double _heat;
    double* _cFactor;
    
public:
    Lamp();
    virtual ~Lamp();
    
    void setHeat(double heat);
    void getHeatDistribution(double heatdistribution[], int numElem);
    void setCFactor(
        double maxheat,
        double platex,
        double platey,
        double lampx,
        double lampy,
        double distance,
        double dx,
        double dy,
        int numx,
        int numy);
};
//===========================================================
//===========================================================
Lamp::Lamp()
{
    _heat =0;
    _cFactor =0;
}
Lamp::~Lamp()
{
    delete [] _cFactor;
}
//===========================================================
//===========================================================
void Lamp::setHeat(double heat)
{
    _heat = heat <0?
        0:
        heat >1?
            1:
            heat;
}
void Lamp::setCFactor(
    double maxheat,
    double platex,
    double platey,
    double lampx,
    double lampy,
    double d,
    double dx,
    double dy,
    int numx,
    int numy)
{
    int numElem = numx *numy;
    delete [] _cFactor;
    _cFactor = new double [numElem];
    double xa =0;
    double xb =0;
    double ya =0;
    double yb =0;
    for(int i=0; i< numy; ++i){
        ya = dy *i     -lampy;
        yb = dy *(i+1) -lampy;
        for(int j=0; j< numx; ++j){
            xa = dx *j     -lampx;
            xb = dx *(j+1) -lampx;
            
            _cFactor[i *numx + j] =
                (Math::atan(xb *yb /d /Math::sqrt(xb*xb +yb*yb +d*d))
                +Math::atan(xa *ya /d /Math::sqrt(xa*xa +ya*ya +d*d))
                -Math::atan(xb *ya /d /Math::sqrt(xb*xb +ya*ya +d*d))
                -Math::atan(xa *yb /d /Math::sqrt(xa*xa +yb*yb +d*d))
                ) *maxheat /(4 *Math::PI);
            
        }
    }
    
    //for(int i=0; i< numElem; ++i){
    //    _cFactor[i] *= maxheat;
    //}
}
void Lamp::getHeatDistribution(double heatdistribution[], int numElem)
{
    for(int i=0; i< numElem; ++i){
        heatdistribution[i] = _cFactor[i] *_heat;
    }
}
//===========================================================
//===========================================================


#endif //ifndef __Windows_research_Lamp

