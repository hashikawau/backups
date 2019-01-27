#include <math.h>


/*
long double mean(int iNumData, int *piData )
{
    long double ldDataMean = 0;
    for(int i=0; i<iNumData; i++)
    {
        ldDataMean += *(piData++);
    }
    
    return ldDataMean/iNumData;
}
*/

long double mean(int iNumData, double *pdData )
{
    long double ldDataMean = 0;
    for(int i=0; i<iNumData; i++)
    {
        ldDataMean += *(pdData++);
    }
    
    return ldDataMean / iNumData;
}

long double mean(int iNumData, long double *pldData )
{
    long double ldDataMean = 0;
    for(int i=0; i<iNumData; i++)
    {
        ldDataMean += *(pldData++);
    }
    
    return ldDataMean / iNumData;
}