

#ifndef _base_math_analysis_calculus_Diffusion
#define _base_math_analysis_calculus_Diffusion


//===========================================================
//===========================================================
class DifferentialEq
{
protected:
    unsigned int _numDim;
    double* _data;
    unsigned int* _numData;
    double* _bcDirichlet;
    unsigned int* _indexBCD;
    unsigned int _numBCD;
    double** _bcNeumann;
    unsigned int** _indexBCN;
    unsigned int* _numBCN;
    unsigned long long _numTotal;
    
protected:
    DifferentialEq(unsigned int numDim);
    
public:
    void setData(double* data, unsigned int* numData);
    void setBCD(
        double* bcDirichlet,
        unsigned int* indexBCD,
        unsigned int numBCD);
    void setBCN(
        double** bcNeumann,
        unsigned int** indexBCN,
        unsigned int* numBCN);
    
};
//===========================================================
//===========================================================
DifferentialEq::DifferentialEq(unsigned int numDim):
    _numDim(numDim),
    _data(0),
    _numData(0),
    _bcDirichlet(0),
    _indexBCD(0),
    _numBCD(0),
    _bcNeumann(0),
    _indexBCN(0),
    _numBCN(0),
    _numTotal(0)
{}
void DifferentialEq::setData(double* data, unsigned int* numData)
{
    _data = data;
    _numData = numData;
    _numTotal =1;
    for(int i=0; i< _numDim; ++i){
        _numTotal *= _numData[i];
    }
}
void DifferentialEq::setBCD(
    double* bcDirichlet,
    unsigned int* indexBCD,
    unsigned int numBCD)
{
    _bcDirichlet = bcDirichlet;
    _indexBCD = indexBCD;
    _numBCD = numBCD;
}
void DifferentialEq::setBCN(
    double** bcNeumann,
    unsigned int** indexBCN,
    unsigned int* numBCN)
{
    _bcNeumann = bcNeumann;
    _indexBCN = indexBCN;
    _numBCN = numBCN;
}
//===========================================================
//===========================================================
class Function;

//===========================================================
//===========================================================
class Diffusion
{
// dT/dt = nabla(diag(Dxx, Dyy, Dzz) * nabla(T)) + source
protected:
    
public:
    static void fdm_1d(
        double dt,
        int numStep,
        unsigned int numx,
        double dx,
        double vars[],
        double source[],
        unsigned int numBCD,
        unsigned int indexBCD[],
        double bcDirichlet[],
        unsigned int numBCN,
        unsigned int indexBCN[],
        double bcNeumann[],
        double coefficients);
    static void fdm_2d(
        double dt,
        int numStep,
        unsigned int numx[2],
        double dx[2],
        double vars[],
        double source[],
        unsigned int numBCD,
        unsigned int indexBCD[],
        double bcDirichlet[],
        unsigned int numBCN[2],
        unsigned int* indexBCN[2],
        double* bcNeumann[2],
        double coefficients[2]);
    /*
    static void fdm_3d(
        double dt,
        int numStep,
        int numx[3],
        double dx,
        double vars[],
        double source[],
        int numBCD,
        int indexBCD[],
        double bcDirichlet[],
        int numBCN[3],
        int* indexBCN[3],
        double* bcNeumann[3],
        double coefficients[3]);
    */
};
//===========================================================
//===========================================================


#endif //ifndef _base_math_analysis_calculus_Diffusion

