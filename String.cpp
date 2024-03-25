#include <iostream>
#include <math.h>

using namespace std;

class String
{
    public:
        String();
        String& operator=(String & str);
        String& operator=(char* str);
        String& operator=(const char* str);
        char& operator[](int pos);
        friend ostream& operator<<(ostream &out,String &str);
        size_t size(const char* str);
        char* Strcpy(char* str1,char*str2);
        char* Strcpy(char* str1,const char*str2);
        ~String();
    private:
        char *m_str;

};

String & String::operator=(String & str)
{
    if(this != &str ){
    delete[] m_str;
    m_str = new char[size(str.m_str)+1];
    Strcpy(m_str,str.m_str);
    
    }
    return *this;
}

String & String::operator=(char* str)
{
    if(m_str != nullptr){
    delete[] m_str;
    }
    m_str = new char[size(str)+1];
    Strcpy (m_str,str) ;
    return *this;
}

String & String::operator=(const char* str)
{
    if(m_str != nullptr){
    delete[] m_str;
    }
    m_str = new char[size(str)+1];
    Strcpy (m_str,str) ;
    return *this;
}

char& String::operator[](int pos)
{

    if(pos >= size(this->m_str))
    {
        
    }
    return this->m_str[pos];
}

ostream &operator<<(ostream &out,String &str)
{
    out << str.m_str;
    return out;
}

size_t String::size(const char *str)
{
    size_t num = 0;
    while(*str != '\0')
    {num++;
    str++;}
    return num;
}


char* String::Strcpy(char* str1,char*str2)
{
    char* tmp = str1;
    while(*str2 != '\0')
    {*str1++ = *str2++;}
    *str1++ = '\0';
    return tmp;
}

char* String::Strcpy(char* str1,const char*str2)
{
    char* tmp = str1;
    while(*str2 != '\0')
    {*str1++ = *str2++;}
    *str1++ = '\0';
    return tmp;
}

String::String()
{
    m_str = new char[10];
    // cout<<"there"<<endl;
}
String::~String()
{
    if(m_str != nullptr){
    delete[]m_str;
    m_str = nullptr;
    }
    // cout<<"here"<<endl;
}

int main(int argc, char const *argv[])
{
    String str;
    cout<<"1"<<endl;
    str = "hello";
    cout<<str<<endl;
    String  str1;
    cout<<str<<endl;
    cout<<str[1]<<endl;
    // str1 = str;
    return 0;
}
