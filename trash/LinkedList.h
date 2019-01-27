

#ifndef __Windows_util_LinkedList
#define __Windows_util_LinkedList


//===========================================================
//===========================================================
#include "../lang/Exception.h"
//===========================================================
//===========================================================
class NoSuchElementException: public RuntimeException
{
public:
    NoSuchElementException();
    virtual ~NoSuchElementException();
};
//===========================================================
//===========================================================
template<class T>
class Iterator
{
public:
    virtual ~Iterator() =0;
};
//===========================================================
//===========================================================
template<class T>
class ListIterator: public Iterator<T>
{
public:
    //virtual void add(const T element) =0;
    virtual const bool hasNext() =0;
    //virtual const bool hasPrevious() =0;
    virtual T& next() =0;
    //virtual const int nextIndex() =0;
    //virtual T& previous() =0;
    //virtual const int prevousIndex() =0;
    //virtual void remove() =0;
    virtual void set(const T element) =0;
    virtual ~ListIterator() =0;
};
//===========================================================
//===========================================================
template<class T>
class Collection
{
public:
    virtual ~Collection() =0;
};
//===========================================================
//===========================================================
template<class T>
class LinkedList: public Collection<T>
{
private:
    class Link
    {
    public:
        T _element;
        Link* _next;
        Link* _previous;
        
        Link(T element, Link* next, Link* previous);
        void remove();
    };
    //friend Link;
    Link* _first;
    Link* _last;
    
    template<class T>
    class LinkedListIterator: ListIterator<T>
    {
    public:
        Link* _nextLink;
        //virtual void add(const T element)
        //{ _nextLink->_element = new Link(const_cast<T>(element), ); }
        virtual const bool hasNext()
        { return _nextLink != 0; }
        //virtual const bool hasPrevious()
        //{ return _nextLink->_previous != 0; }
        virtual T& next()
        {
            if(!_nextLink){ throw NoSuchElementException(); }
            T& element = _nextLink->_element;
            _nextLink = _nextLink->_next;
            return element;
        }
        /*
        virtual const int nextIndex(){ return 0; }
        virtual T& previous()
        {
            if(!_nextLink->_previous){ throw NoSuchElementException(); }
            T& element = _nextLink->_element;
            _nextLink = _nextLink->_previous;
            return element;
        }
        virtual const int prevousIndex(){ return 0; }
        */
        //virtual void remove(){}
        virtual void set(const T element)
        { _nextLink->_element = const_cast<T>(element); }
        LinkedListIterator(Link* link =0): _nextLink(link){}
        LinkedListIterator& operator=(Link* link)
        {
            _nextLink = link;
            return *this;
        }
        ~LinkedListIterator(){}
    };
    friend class LinkedListIterator;
    LinkedListIterator<T> _linkedListIterator;
    
public:
    LinkedList();
    LinkedList(const LinkedList<T>& reference);
    LinkedList<T>& operator=(const LinkedList<T>& reference);
    virtual ~LinkedList();
    T& operator[](const int index);
    const T& operator[](const int index) const;
    T& getFirst();
    T& getLast();
    //const bool add(const T element);
    void add(const int index, const T element);
    void addFirst(const T element);
    void addLast(const T element);
    void clear();
    const int indexOf(const T element) const;
    ListIterator<T>& listIterator(const int index);
    const T remove(const int index);
    const T removeFirst();
    const T removeLast();
    const int size() const;
    const T* toArray(T* array);
    
};
//===========================================================
//===========================================================


#endif //ifndef __Windows_util_LinkedList


