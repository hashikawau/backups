

#ifndef __Windows_cpp_PointerObject_cpp
#define __Windows_cpp_PointerObject_cpp


//===========================================================
//===========================================================
#include "PointerObject.h"
#include "../windows/_windows.h"
#include "../lang/Exception.h"
#include "../lang/Exception_cpp.h"
#include "../util/LinkedList.h"
#include "../util/LinkedList_cpp.h"
//===========================================================
//===========================================================
PointerObjectException::PointerObjectException(){}
PointerObjectException::~PointerObjectException(){}
//===========================================================
//===========================================================
LinkedList<void*> RCPointer::_listAddress;
//===========================================================
//===========================================================
void* RCPointer::operator new(size_t size)
{
    void* pointer = ::operator new(size);
    _listAddress.addFirst(pointer);
    return pointer;
}
void RCPointer::operator delete(void* pointer)
{
    _listAddress.remove(_listAddress.indexOf(pointer));
    ::operator delete(pointer);
}
//===========================================================
//===========================================================
RCPointer::RCPointer(const void* data):
    _data(const_cast<void*>(data)),
    _referenceCount(0)
{}
RCPointer::~RCPointer(){}
template<class T>
int RCPointer::addReference(const T* typedata)
{
    const void* data =dynamic_cast<void*>(typedata);
    int count = -1;
    RCPointer* newone = 0;
    for(ListIterator<void*>& it = _listAddress.listIterator(0);
        it.hasNext()
        && !static_cast<bool>(newone) & static_cast<bool>(data);
    )
    {
        RCPointer* temp = static_cast<RCPointer*>(it.next());
        if(temp->_data == data){
            newone = temp;
            count = ++newone->_referenceCount;
        }
    }
    if(!newone){
        if(data){
            newone = new RCPointer(data);
            count = ++newone->_referenceCount;
        }
    }
    
//debug += String("add()     ")
//    +String((int)newone)
//    +String("  ")
//    +String((int)data)
//    +String("  ")
//    +String((int)count)
//    +String("/  ")
//    +String((int)_listAddress.size())
//    +String("\n");
//#ifndef UNICODE
//cout<< "add()     "
//    << (int)newone
//    << "  "
//    << (int)data
//    << "  "
//    << count
//    << "/  "
//    << _listAddress.size()
//    << endl;/////////////////////////////////////
//#endif//ifndef UNICODE
    
    return count;
}
template<class T>
int RCPointer::removeReference(T*& typedata)
{
    const void* data =dynamic_cast<void*>(typedata);
    int count = -1;
    RCPointer* newone = 0;
    for(ListIterator<void*>& it = _listAddress.listIterator(0);
        it.hasNext()
        && !static_cast<bool>(newone) & static_cast<bool>(data);
    )
    {
        RCPointer* temp = static_cast<RCPointer*>(it.next());
        if(temp->_data == data){
            newone = temp;
        }
    }
    if(newone){
        count = --newone->_referenceCount;
        if(count ==0){
            delete typedata;
            typedata =0;
            //typedata->~T();
            //delete newone->get();
            delete newone;
            //delete data;
        }
    }
    
//debug += String("remove()  ")
//    +String((int)newone)
//    +String("  ")
//    +String((int)data)
//    +String("  ")
//    +String((int)count)
//    +String("/  ")
//    +String((int)_listAddress.size())
//    +String("\n");
//#ifndef UNICODE
//cout<< "remove()  "
//    << (int)newone
//    << "  "
//    << (int)data
//    << "  "
//    << count
//    << "/  "
//    << _listAddress.size()
//    << endl;/////////////////////////////
//#endif//ifndef UNICODE
    
    return count;
}
void* RCPointer::get() const{ return _data; }
const bool RCPointer::operator==(const void* data) const
{ return _data==data; }
const bool RCPointer::operator==(const RCPointer& reference) const
{ return _data==reference._data; }
//===========================================================
//===========================================================
template<class T>
PointerObject<T>::PointerObject(const T* pointer): _arrayPointer(0)
{
    if(pointer){
        _listPointer.addFirst(const_cast<T*>(pointer));
        RCPointer::addReference(pointer);
    }
}
template<class T>
PointerObject<T>::PointerObject(const PointerObject<T>& reference): _arrayPointer(0)
{
    _listPointer = reference._listPointer;
    for(ListIterator<T*>& it = _listPointer.listIterator(0);
        it.hasNext();)
    {
        RCPointer::addReference(it.next());
    }
}
template<class T>
PointerObject<T>& PointerObject<T>::operator=(const T* pointer)
{
    if(!pointer){
        _listPointer.clear();
        return *this;
    }
    
    RCPointer::addReference(pointer);
    for(ListIterator<T*>& it = _listPointer.listIterator(0);
        it.hasNext();)
    {
        RCPointer::removeReference(it.next());
    }
    _listPointer.clear();
    _listPointer.addFirst(const_cast<T*>(pointer));
    
    return *this;
}
template<class T>
PointerObject<T>& PointerObject<T>::operator=(const PointerObject<T>& reference)
{
    if(static_cast<int>(this) == static_cast<int>(&reference)){
        return *this;
    }
    
    for(
        ListIterator<T*>& it = const_cast<PointerObject<T>&>(
            reference)._listPointer.listIterator(0);
        it.hasNext();
        )
    {
        RCPointer::addReference(it.next());
    }
    for(
        ListIterator<T*>& it = _listPointer.listIterator(0);
        it.hasNext();
        )
    {
        RCPointer::removeReference(it.next());
    }
    _listPointer = reference._listPointer;
    return *this;
}
//===========================================================
//===========================================================
template<class T>
PointerObject<T>::~PointerObject()
{
    for(ListIterator<T*>& it = _listPointer.listIterator(0);
        it.hasNext();)
    {
        RCPointer::removeReference(it.next());
    }
    _listPointer.clear();
    delete [] _arrayPointer;
    _arrayPointer =0;
}
//===========================================================

template<class T>
T* PointerObject<T>::operator[](int index)
{
    return _listPointer[index];
}
template<class T>
const T* PointerObject<T>::operator[](int index) const
{
    return _listPointer[index];
}

template<class T>
T& PointerObject<T>::operator*() const
{
    if(_listPointer.size() <=0){ return *static_cast<T*>(0); }
    return *(_listPointer[0]);
}
template<class T>
T* PointerObject<T>::operator->() const
{
    if(_listPointer.size() <=0){ throw PointerObjectException(); }
    return _listPointer.size() >0?
        _listPointer[0]:
        static_cast<T*>(0);
}
/*
template<class T>
PointerObject<T>::operator T*() const
{
    return _listPointer.size() >0?
        _listPointer[0]:
        static_cast<T*>(0);
}
*/
template<class T>
void PointerObject<T>::clear()
{
    for(ListIterator<T*>& it = _listPointer.listIterator(0);
        it.hasNext();)
    {
        RCPointer::removeReference(it.next());
    }
    _listPointer.clear();
}
template<class T>
void PointerObject<T>::add(const T* pointer)
{
    if(pointer){
        _listPointer.addFirst(const_cast<T*>(pointer));
        RCPointer::addReference(pointer);
    }
}
template<class T>
void PointerObject<T>::add(const T* pointer, int index)
{
    if(pointer){
        _listPointer.add(index, const_cast<T*>(pointer));
        RCPointer::addReference(pointer);
    }
}
template<class T>
void PointerObject<T>::addFirst(const T* pointer)
{
    if(pointer){
        _listPointer.addFirst(const_cast<T*>(pointer));
        RCPointer::addReference(pointer);
    }
}
template<class T>
void PointerObject<T>::addLast(const T* pointer)
{
    if(pointer){
        _listPointer.addLast(const_cast<T*>(pointer));
        RCPointer::addReference(pointer);
    }
}
template<class T>
bool PointerObject<T>::remove(const T* pointer)
{
    int index = _listPointer.indexOf(const_cast<T*>(pointer));
    bool isRemoved = false;
    if(index >= 0){
        _listPointer.remove(index);
        RCPointer::removeReference(pointer);
        isRemoved = true;
    }
    return isRemoved;
}
template<class T>
int PointerObject<T>::size() const
{
    return _listPointer.size();
}
template<class T>
T** PointerObject<T>::get()
{
    delete [] _arrayPointer;
    int size = _listPointer.size();
    _arrayPointer = new T* [size +1];
    T** temp = _arrayPointer;
    for(ListIterator<T*>& it = _listPointer.listIterator(0);
        it.hasNext();
        ++temp)
    {
        *temp = it.next();
    }
    _arrayPointer[size] = 0;
    return _arrayPointer;
}
/*
template<class T>
const bool PointerObject<T>::operator==(const PointerObject<T>& reference) const
{
    if(_listPointer.size() <=0 || reference._listPointer.size() <=0){
        return false;
    }
    return _listPointer[0] == reference ._listPointer[0];
}
*/
template<class T>
PointerObject<T>::operator bool() const
{
    return _listPointer.size() >0;
}
//===========================================================
//===========================================================
template<class T>
PointerObject<T>::operator T&() const
{
    
    return _listPointer.size() >0?
        *_listPointer[0]:
        *static_cast<T*>(0);
    
    //if(_listPointer.size() <=0){
    //    throw PointerObjectException();
    //}
    //return *_listPointer[0];
}
//===========================================================
//===========================================================



#endif //ifndef __Windows_cpp_PointerObject_cpp

