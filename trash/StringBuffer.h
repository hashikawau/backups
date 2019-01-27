

#ifndef __Windows_lang_StringBuffer
#define __Windows_lang_StringBuffer


//===========================================================
//===========================================================
class String;
//===========================================================
//===========================================================
class StringBuffer
{
private:
    char* _str;
    int _capacity;
    
    void setCapacity(int length);
    
public:
    explicit StringBuffer(int capacity =16);
    StringBuffer(const String& string);
    StringBuffer(const StringBuffer& string);
    ~StringBuffer();
    StringBuffer operator+(const StringBuffer& string) const;
    StringBuffer& operator=(const StringBuffer& string);
    StringBuffer& append(const StringBuffer& string);
    StringBuffer& operator+=(const StringBuffer& string);
    StringBuffer& deleteCharAt(int index);
    StringBuffer& delete_(int start, int end);
    StringBuffer& insert(int offset, const String& str);
    
    char& operator[](int index);
    const char operator[](int index) const;
    
    int length() const;
    int capacity() const;
    String substring(int start) const;
    String substring(int start, int end) const;
};
//===========================================================
//===========================================================


#endif //ifndef __Windows_lang_StringBuffer

