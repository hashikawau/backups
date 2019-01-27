

#ifndef _util_Arrays_cpp
#define _util_Arrays_cpp


//===========================================================
//===========================================================
#include "Arrays.h"
#include "Random.h"

template<class T>
inline static void quicksort(T a[], unsigned long long length);
template<class T>
inline static void stsort(T a[], unsigned long long length);
template<class T>
inline static int partitioning(T a[], unsigned long long length);

template<class T>
static void quicksort2(T arr[], unsigned long long n);
template<class T>
static int partitioning(T a[], unsigned long long length, T partition);
//===========================================================
//===========================================================
void Arrays::sort(long long a[], unsigned long long length)
{
    quicksort(a, length);
}
void Arrays::sort(int a[], unsigned long long length)
{
    quicksort(a, length);
}
void Arrays::sort(double a[], unsigned long long length)
{
    quicksort(a, length);
    //cout << "abc  " << partitioning(a, length, 0.7) << endl;
    //stsort(a, length);
}
//===========================================================
//===========================================================
template<class T>
inline static void quicksort(T a[], unsigned long long length)
{
    
    const int M =7;
    const int NUMSTACK =100;
    
    unsigned long long* stack = new unsigned long long[NUMSTACK];
    stack[0] =length;
    stack[1] =0;
    unsigned long long index =1;
    unsigned long long size =length;
    
    while(1){
        if(size < M){
            stsort(a +stack[index], size);
            --index;
            if(index ==0){
                break;
            }
            size = stack[index-1] -stack[index];
            
//cout << "stsort   ";

        }else{
            
            int newindex = partitioning(
                a +stack[index],
                size);
            if(!newindex){
                ++newindex;
            }
            newindex += stack[index];
            ++index;
            stack[index] =stack[index-1];
            stack[index-1] =newindex;
            size = stack[index-1] -stack[index];
            
//cout << "partition";

        }
        
/*
cout << ",  " << index << ", " << size << ", " << endl;
for(int i=index; i>0; --i){
    cout << i << ", " << stack[i] << ", " << stack[i-1] -stack[i] << endl;
}
cout << "0" << ", " << stack[0] << endl;
for(int i=0; i< length; ++i){
    cout << i << ", " << a[i] << endl ;
}
cout << endl;
*/
    
    
    }
    
    delete [] stack;
    
    
    
}
//===========================================================
//===========================================================
template<class T>
inline static void stsort(T a[], unsigned long long length)
{
    T temp;
    for(unsigned long long i=1; i< length; ++i){
        for(unsigned long long j=0; j< i; ++j){
            if(a[i] < a[j]){
                temp = a[i];
                for(unsigned long long k= i; k> j; --k){
                    a[k] = a[k-1];
                }
                a[j] = temp;
                break;
            }
        }
    }
}
template<class T>
inline static int partitioning(T a[], unsigned long long length)
{
    T temp;
    
    if(a[0] > a[length-1]){
        temp = a[0];
        a[0] = a[length-1];
        a[length-1] = temp;
    }
    if(a[0] > a[length/2]){
        temp = a[0];
        a[0] = a[length/2];
        a[length/2] = temp;
    }
    if(a[length/2] > a[length-1]){
        temp = a[length/2];
        a[length/2] = a[length-1];
        a[length-1] = temp;
    }
    T partition = a[length/2];
    
    unsigned long long i =0;
    unsigned long long j =length -1;
    for(; ; ++i){
        if(a[i] >= partition){
            for(; j> i; --j){
                if(a[j] < partition){
                    temp = a[i];
                    a[i] = a[j];
                    a[j] = temp;
                    break;
                }
            }
        }
        if(j <= i){
            break;
        }
    }
    return i;
}
//===========================================================
//===========================================================

//===========================================================
//===========================================================
template<class T>
void swap(T a, T b)
{
    T temp =a;
    a =b;
    b =temp;
}
template<class T>
void quicksort2(T arr[], unsigned long long n)
{
    const int M =7;
    const int NSTACK =50;
    
    unsigned long long i, j, k;
    unsigned long long l =0;
    unsigned long long ir =n-1;
    unsigned long long* istack = new unsigned long long[NSTACK];
    long long jstack =0;
    T a, temp;
    
    for(; ; ){
        if(ir -1 <M){
            for(j= l+1; j<= ir; ++j){
                a =arr[j];
                for(i= j-1; i>= l; --i){
                    if(arr[i] <=a) break;
                    arr[i+1] =arr[i];
                }
                arr[i+1] =a;
            }
            if(jstack == 0) break;
            ir =istack[jstack--];
            l =istack[jstack--];
        }else{
            k =(l +ir) >>1;
            swap(arr[k], arr[l+1]);
            if(arr[l] > arr[ir]){
                swap(arr[l], arr[ir]);
            }
            if(arr[l+1] > arr[ir]){
                swap(arr[l+1], arr[ir]);
            }
            if(arr[l] > arr[l+1]){
                swap(arr[l], arr[l+1]);
            }
            
            i=l+1;
            j=ir;
            a=arr[l+1];
            for(; ; ){
                do i++; while(arr[i] <a);
                do j--; while(arr[j] >a);
                if(j <i) break;
                swap(arr[i], arr[j]);
            }
            arr[l+1] =arr[j];
            arr[j] =a;
            jstack +=2;
            //if(jstack >NSTACK) throw "NSTACK too small in sort.";
            if(ir -i +1 >= j -l){
                istack[jstack] =ir;
                istack[jstack -1] =i;
                ir =j-1;
            }else{
                istack[jstack] =j-1;
                istack[jstack -1] =l;
                l=i;
            }
        }
    }
    
    delete [] istack;
}
//===========================================================
//===========================================================
template<class T>
int partitioning(T a[], unsigned long long length, T partition)
{
    T temp;
    unsigned long long i =0;
    unsigned long long j =length -1;
    for(; ; ++i){
        if(a[i] >= partition){
            for(; j> i; --j){
                if(a[j] < partition){
                    temp = a[i];
                    a[i] = a[j];
                    a[j] = temp;
                    break;
                }
            }
        }
        if(j <= i){
            break;
        }
    }
    return i;
}
//===========================================================
//===========================================================


#endif //ifndef _util_Arrays_cpp

