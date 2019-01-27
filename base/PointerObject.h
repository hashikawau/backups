

#ifndef __Windows_cpp_PointerObject
#define __Windows_cpp_PointerObject


//#include "../_windows.h"
#include "../lang/Exception.h"
#include "../util/LinkedList.h"


//===========================================================
//===========================================================
class PointerObjectException: public RuntimeException
{
public:
    PointerObjectException();
    virtual ~PointerObjectException();
};
//===========================================================
//===========================================================
class RCPointer
{
private:
    static LinkedList<void*> _listAddress;
    void* _data;
    int _referenceCount;
    
    explicit RCPointer(const void* data);
    RCPointer(const RCPointer& reference);
    RCPointer& operator=(const void* data);
    RCPointer& operator=(const RCPointer& reference);
    ~RCPointer();
    static void* operator new(size_t size);
    static void operator delete(void* pointer);
    
public:
    template<class T> static int addReference(const T* data);
    template<class T> static int removeReference(T*& typedata);
    void* get() const;
    const bool operator==(const void* data) const;
    const bool operator==(const RCPointer& reference) const;
};
//===========================================================
//===========================================================
template<class T>
class PointerObject
{
private:
    LinkedList<T*> _listPointer;
    T** _arrayPointer;
    
    static void* operator new(size_t size);
    static void operator delete(void* pointer);
    
public:
    PointerObject(const T* pointer =0);
    PointerObject(const PointerObject<T>& reference);
    PointerObject<T>& operator=(const T* pointer);
    PointerObject<T>& operator=(const PointerObject<T>& reference);
    ~PointerObject();
    T* operator[](int index);
    const T* operator[](int index) const;
    T& operator*() const;
    T* operator->() const;
    //operator T*() const;
    T** get();
    void clear();
    void add(const T* pointer);
    void add(const T* pointer, int index);
    void addFirst(const T* pointer);
    void addLast(const T* pointer);
    bool remove(const T* pointer);
    int size() const;
    //const bool operator==(const PointerObject<T>& reference) const;
    operator bool() const;
    
    
    
    operator T&() const;
};
//===========================================================
//===========================================================


#endif //ifndef __Windows_cpp_PointerObject


#include "PointerObject_cpp.h"

