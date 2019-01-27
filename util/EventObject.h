

#ifndef _util_EventObject
#define _util_EventObject


//===========================================================
//===========================================================
class Object;
//===========================================================
//===========================================================
class EventObject
{
protected:
    void* _source__;
    Object* _source;
    
public:
    explicit EventObject(Object& source);
    virtual ~EventObject();
    Object& getSource() const;
    
    explicit EventObject(void* source);
    void* getSource();
};
//===========================================================
//===========================================================
class EventListener
{
public:
    EventListener();
    virtual ~EventListener() =0;
};
//===========================================================
//===========================================================


#endif //ifndef _util_EventObject

