

#ifndef _base_math_analysis_calculus_Poisson
#define _base_math_analysis_calculus_Poisson


//===========================================================
//===========================================================
class Function;

//===========================================================
//===========================================================
class Poisson
{
public:
    static void fdm_1d(
        int numx,
        double dx,
        double vars[],
        double source[],
        int numBCD,
        int indexBCD[],
        double bcDirichlet[],
        int numBCN,
        int indexBCN[],
        double bcNeumann[]);
    static void fdm_2d(
        int numx[2],
        double dx,
        double vars[],
        double source[],
        int numBCD,
        int indexBCD[],
        double bcDirichlet[],
        int numBCN[2],
        int* indexBCN[2],
        double* bcNeumann[2]);
    static void fdm_3d(
        int numx[3],
        double dx,
        double vars[],
        double source[],
        int numBCD,
        int indexBCD[],
        double bcDirichlet[],
        int numBCN[3],
        int* indexBCN[3],
        double* bcNeumann[3]);
    
};
//===========================================================
//===========================================================


#endif //ifndef _base_math_analysis_calculus_Poisson

