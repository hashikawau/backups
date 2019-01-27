

#ifndef __Windows_util_LinkedList_cpp
#define __Windows_util_LinkedList_cpp


//===========================================================
//===========================================================
#include "LinkedList.h"
#include "../lang/Exception.h"
//===========================================================
//===========================================================
NoSuchElementException::NoSuchElementException(){}
NoSuchElementException::~NoSuchElementException(){}
//===========================================================
//===========================================================
template<class T>
Iterator<T>::~Iterator(){}
//===========================================================
//===========================================================
template<class T>
ListIterator<T>::~ListIterator(){}
//===========================================================
//===========================================================
template<class T>
Collection<T>::~Collection(){}
//===========================================================
//===========================================================
template<class T>
LinkedList<T>::Link::Link(T element, Link* next, Link* previous)
{
    _element = element;
    _next = next;
    _previous = previous;
    if(_next){ _next->_previous = this; }
    if(_previous){ _previous->_next = this; }
}
template<class T>
void LinkedList<T>::Link::remove()
{
    if(_next){ _next->_previous = this->_previous; }
    if(_previous){ _previous->_next = this->_next; }
}
//===========================================================
//===========================================================
template<class T>
LinkedList<T>::LinkedList(): _first(0), _last(0){}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& reference)
{
    *this = reference;
}
template<class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& reference)
{
    if(static_cast<int>(this) == static_cast<int>(&reference)){
        return *this;
    }
    clear();
    for(int i=0; i< reference.size(); ++i)
    {
        addLast(reference[i]);
    }
    
    return *this;
}
template<class T>
LinkedList<T>::~LinkedList(){ clear(); }

template<class T>
T& LinkedList<T>::operator[](const int index)
{
    if(index<0 || index>=size()){ throw IndexOutOfBoundsException(); }
    
    Link* link = _first;
    for(int i=0; i< index; ++i)
    {
        link = link->_next;
    }
    return link->_element;
}

template<class T>
const T& LinkedList<T>::operator[](const int index) const
{
    if(index<0 || index>=size()){ throw IndexOutOfBoundsException(); }
    
    Link* link = _first;
    for(int i=0; i< index; ++i)
    {
        link = link->_next;
    }
    return link->_element;
}

template<class T>
T& LinkedList<T>::getFirst()
{
    if(!_first){ throw NoSuchElementException(); }
    return _first->_element;
}

template<class T>
T& LinkedList<T>::getLast()
{
    if(!_last){ throw NoSuchElementException(); }
    return _last->_element;
}

/*
template<class T>
const bool LinkedList<T>::add(const T element)
{
    Link* link = new Link(element, 0, _last);
    _last = link;
    if(!_first){ _first = link; }
    
    return true;
}
*/

template<class T>
void LinkedList<T>::add(const int index, const T element)
{
    if(index<0 || index>size()){ throw IndexOutOfBoundsException(); }
    
    Link* nextLink = _first;
    Link* previousLink = 0;
    for(int i=0; i< index; ++i)
    {
        previousLink = nextLink;
        nextLink = nextLink->_next;
    }
    
    Link* link = new Link(element, nextLink, previousLink);
    if(!nextLink){ _last = link; }
    if(!previousLink){ _first = link; }
}

template<class T>
void LinkedList<T>::addFirst(const T element)
{
    Link* link = new Link(element, _first, 0);
    _first = link;
    if(!_last){ _last = link; }
}

template<class T>
void LinkedList<T>::addLast(const T element)
{
    Link* link = new Link(element, 0, _last);
    if(!_first){ _first = link; }
    _last = link;
}

template<class T>
void LinkedList<T>::clear()
{
    Link* link = _first;
    for(int i=0; i< size() -1; ++i)
    {
        link = link->_next;
        delete link->_previous;
    }
    delete link;
    
    _first = 0;
    _last = 0;
}

template<class T>
const int LinkedList<T>::indexOf(const T element) const
{
    if(!_first){ return -1; }
    if(_first->_element == const_cast<T>(element)){ return 0; }
    
    Link* link = _first;
    int index = 0;
    
    while(link->_next)
    {
        link = link->_next;
        ++index;
        if(link->_element == const_cast<T>(element)){ return index; }
    }
    
    return -1;
}

template<class T>
ListIterator<T>& LinkedList<T>::listIterator(const int index)
{
    if(index<0 || index>size()){ throw IndexOutOfBoundsException(); }
    
    Link* link = _first;
    for(int i=0; i< index; ++i)
    {
        link = link->_next;
    }
    
    return _linkedListIterator = link;
}

template<class T>
const T LinkedList<T>::remove(const int index)
{
    if(index<0 || index>=size()){ throw IndexOutOfBoundsException(); }
    
    Link* link = _first;
    for(int i=0; i< index; ++i)
    {
        link = link->_next;
    }
    T element = link->_element;
    
    if(!link->_previous){ _first = link->_next; }
    if(!link->_next){ _last = link->_previous; }
    link->remove();
    
    delete link;
    return element;
}

template<class T>
const T LinkedList<T>::removeFirst()
{
    if(!_first){ throw NoSuchElementException(); }
    
    Link* link = _first;
    T element = link->_element;
    
    _first = link->_next;
    if(!link->_next){ _last = link; }
    link->remove();
    
    delete link;
    return element;
}

template<class T>
const T LinkedList<T>::removeLast()
{
    if(!_last){ throw NoSuchElementException(); }
    
    Link* link = _last;
    T element = link->_element;
    
    if(!link->_previous){ _first = link; }
    _last = link->_previous;
    link->remove();
    
    delete link;
    return element;
}

template<class T>
const int LinkedList<T>::size() const
{
    Link* link = _first;
    int count = 0;
    
    if(link)
    {
        ++count;
        
        while(link->_next)
        {
            link = link->_next;
            ++count;
        }
    }
    
    return count;
}

template<class T>
const T* LinkedList<T>::toArray(T* array)
{
    Link* link = _first;
    int count =0;
    while(link)
    {
        array[count] = link->_element;
        ++count;
        link = link->_next;
    }
    
    return array;
}
//===========================================================
//===========================================================


#endif //ifndef __Windows_util_LinkedList_cpp

