

#ifndef __Windows_util_HashMap
#define __Windows_util_HashMap


//===========================================================
//===========================================================
#include "../lang/Exception.h"
//===========================================================
//===========================================================
class HashMapException: public RuntimeException
{
public:
    HashMapException();
    virtual ~HashMapException();
};
//===========================================================
//===========================================================
template<class K, class V>
class HashMap
{
private:
    class Link
    {
    public:
        K _key;
        V _value;
        Link* _next;
        
        Link(K key, V value, Link* next, Link* previous);
        ~Link(){}
        void remove(Link* previous);
    };
    
    Link* _first;
    
public:
    HashMap();
    ~HashMap();
    void clear();
    const V& get(K key) const;
    const V put(K key, V value);
    const V remove(K key);
    const int size() const;
};
//===========================================================
//===========================================================


#endif //ifndef __Windows_util_HashMap

