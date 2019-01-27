
class Test2
{
public:
    Test2();
    ~Test2();
};

template<class T> class Test
{
public:
    int t1;
    void show();
    
    //Test<T>();
    //~Test();
};

void f(int);

template<class T>
void temf(T);
