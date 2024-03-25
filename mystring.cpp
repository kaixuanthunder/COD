#include <iostream>

using namespace std;
class mystring
{
public: 

    mystring(const mystring&) ;
    
    ostream& operator<<(ostream&out,const mystring&);
    
    size_t mysize(const mystring);
    
    mystring mystrcpy(mystring&,const mystring&);
    
    ~mystring();
    
    // char& ostream[](size_t pos)
    // {
    // if(pos<mysize(m_str))
    // return(m_str[pos]);
    // };
    
    mystring& operator=(mystring&);

private:
    char* m_str;
};



mystring::mystring(const char* &str)
{
    
        m_str = new char[mysize(str)+1];
    
        mystrcpy(m_str,str);
    
}

ostream &mystring::operator<<(ostream &out, const mystring &str)
{
    out<<str.m_str;
    return out;
}

size_t mystring::mysize(const char *str)
{
    const char *temp = str;
    while(*temp++);
    return(temp - str -1);
}

mystring mystrcpy(mystring& str1,const mystring& str2)
{
    if(str1 == nullptr && str2 == nullptr)
    return nullptr;
    char* tmp = str1;
    int cnt = mysize(str2)+1;
    while(cnt--)
    *str1++ = *str2++;
    return str1;
}

mystring::~mystring()
{
    delete[]m_str;
    m_str = nullptr;
}

mystring &mystring::operator=(mystring &str)
{
    
    if(this == &str)
    return *this;
    delete m_str;
    m_str = new char[mysize(str)+1];
    mystrcpy(m_str,str.m_str);
    
}

int main()
{
    using namespace std;
    mystring newstr;
    newstr = "hello";
    mystring  str1;
    cout<<newstr<<endl;
    cout<<newstr[1]<<endl;
    str1 = newstr;
}