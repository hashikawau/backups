



#ifndef __Windows_cpp_3d_utils_universe_SimpleUniverse
#define __Windows_cpp_3d_utils_universe_SimpleUniverse


#include "windows\lang\Math.h"
#include "windows\cpp\PointerObject.h"





//===========================================================
//===========================================================
class BranchGroup
{

};
//===========================================================
//===========================================================
class SimpleUniverse
{
private:
    PointerObject<BranchGroup> _branchGroup;
    
public:
    SimpleUniverse();
    virtual ~SimpleUniverse();
    
    
    
};
//===========================================================
//===========================================================
SimpleUniverse::SimpleUniverse(){}
SimpleUniverse::~SimpleUniverse(){}
//===========================================================
//===========================================================

//===========================================================
//===========================================================



#endif //ifndef __Windows_cpp_3d_utils_universe_SimpleUniverse




