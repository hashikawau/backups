

#ifndef __Windows_cpp_media_3d_GeometryArray
#define __Windows_cpp_media_3d_GeometryArray



//===========================================================
//===========================================================
class GeometryArray
{
private:
    int _format;
    int _count;
    Point3d* _coordinates;
    Vector3d* _normals;
    
public:
    static const int COORDINATES;
    static const int NORMALS;
    static const int COLOR_3;
    static const int COLOR_4;
    
    GeometryArray();
    virtual ~GeometryArray() =0;
    
    int getVertexCount();
    int getVertexFormat();
    //void updateData(const GeometeryUpdater& updater);
    void setCoordinate(int index, const double coodinate[]);
    void setCoordinate(int index, const Point3d& coordinate);
};
static const int GeometryArray::COORDINATES =1;
static const int GeometryArray::NORMALS     =2;
static const int GeometryArray::COLOR_3     =4;
static const int GeometryArray::COLOR_4     =12;
//===========================================================
//===========================================================
GeometryArray::GeometryArray(int vertexCount, int vertexFormat):
    _count(vertexCount),
    _format(vertexFormat)
{
    if(_format &COORDINATES){
        _coordinates = new Point3d[_count];
    }else{
        _coordinates =0;
    }
    
    if(_format &NORMALS){
        _normals = new Vector3d[_count];
    }else{
        _normals =0;
    }
}
GeometryArray::~GeometryArray(){}
//===========================================================
//===========================================================

//===========================================================
//===========================================================

//===========================================================
//===========================================================


#endif //ifndef __Windows_cpp_media_3d_GeometryArray


