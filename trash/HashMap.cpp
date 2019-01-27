

#ifndef __Windows_util_HashMap_cpp
#define __Windows_util_HashMap_cpp


//===========================================================
//===========================================================
#include "HashMap.h"
#include "../lang/Exception.h"
//===========================================================
//===========================================================
HashMapException::HashMapException(){}
HashMapException::~HashMapException(){}
//===========================================================
//===========================================================
template<class K, class V>
HashMap<K,V>::Link::Link(K key, V value, Link* next, Link* previous)
{
    _key = key;
    _value = value;
    _next = next;
    if(previous){
        previous->_next = this;
    }
}
//template<class K, class V> HashMap<K,V>::Link::~Link(){}
template<class K, class V>
void HashMap<K,V>::Link::remove(Link* previous)
{
    if(previous){
        previous->_next = this->_next;
    }
}
//===========================================================
//===========================================================
template<class K, class V>
HashMap<K,V>::HashMap(): _first(0){}
template<class K, class V>
HashMap<K,V>::~HashMap()
{
    clear();
}
template<class K, class V>
void HashMap<K,V>::clear()
{
    Link* link = _first;
    Link* previous;
    for(int i=0; i< size() -1; ++i){
        previous = link;
        link = link->_next;
        delete previous;
    }
    delete link;
    
    _first = 0;
}
template<class K, class V>
const V& HashMap<K,V>::get(K key) const
{
    if(!_first){
        //return *static_cast<V*>(0);
        throw HashMapException();
    }
    
    Link* link = _first;
    while(link->_next){
        if(link->_key == key){
            return link->_value;
        }
        link = link->_next;
    }
    
    if(link->_key == key){
        return link->_value;
    }
    
    //return *static_cast<V*>(0);
    throw HashMapException();
    return 0;
}
template<class K, class V>
const V HashMap<K,V>::put(K key, V value)
{
    if(!_first){
        _first = new Link(key, value, _first, 0);
        return value;
    }
    
    Link* link = _first;
    while(link->_next){
        if(link->_key == key){
            link->_value = value;
            return value;
        }
        link = link->_next;
    }
    
    if(link->_key == key){
        link->_value = value;
        return value;
    }
    
    link->_next = new Link(key, value, 0, link);
    return value;
}
template<class K, class V>
const V HashMap<K,V>::remove(K key)
{
    if(!_first){
        return 0;
    }
    
    Link* link = _first;
    if(link->_key == key){
        V value= link->_value;
        _first = link->_next;
        delete link;
        return value;
    }
    
    while(link->_next){
        if(link->_next->_key == key){
            V value= link->_next->_value;
            link->_next->remove(link);
            delete link->_next;
            return value;
        }
        link = link->_next;
    }
    return 0;
}
template<class K, class V>
const int HashMap<K,V>::size() const
{
    Link* link = _first;
    int count = 0;
    
    if(link){
        ++count;
        
        while(link->_next){
            link = link->_next;
            ++count;
        }
    }
    return count;
}
//===========================================================
//===========================================================


#endif //ifndef __Windows_util_HashMap_cpp

