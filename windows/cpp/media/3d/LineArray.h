

#ifndef __Windows_cpp_media_3d_LineArray
#define __Windows_cpp_media_3d_LineArray



//===========================================================
//===========================================================
class LineArray
{
private:
    
public:
    LineArray();
    virtual ~LineArray() =0;
    
    //void updateData(const GeometeryUpdater& updater);
};
//===========================================================
//===========================================================
LineArray::LineArray(int vertexCount, int vertexFormat):
    GeometryArray(vertexCount, vertexFormat){}
LineArray::~LineArray(){}
//===========================================================
//===========================================================

//===========================================================
//===========================================================

//===========================================================
//===========================================================


#endif //ifndef __Windows_cpp_media_3d_GeometryArray


