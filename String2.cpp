#include <iostream>
#include <cstring> // for strcpy

using namespace std;

class String {
public:
    String& operator=(String & str);
    String& operator=(char* str);
    char& operator[](int pos);
    friend ostream& operator<<(ostream &out, String &str);
    static size_t size(const char* str);
    char* Strcpy(char* str1, char* str2);
    ~String();
private:
    char *m_str;
};

String & String::operator=(String & str) {
    if (this != &str) {
        delete[] m_str;
        m_str = new char[size(str.m_str) + 1];
        Strcpy(m_str, str.m_str);
    }
    return *this;
}

String & String::operator=(char* str) {
    if (m_str != nullptr) {
        delete[] m_str;
    }
    m_str = new char[size(str) + 1];
    Strcpy(m_str, str);
    return *this;
}


char& String::operator[](int pos) {
    if (pos >= size(m_str)) {
        // Handle out-of-bounds access
        // You may throw an exception or return a default value
    }
    return m_str[pos];
}

ostream &operator<<(ostream &out, String &str) {
    out << str.m_str;
    return out;
}

size_t String::size(const char *str) {
    size_t num = 0;
    while (*str != '\0') {
        num++;
        str++;
    }
    return num;
}

char* String::Strcpy(char* str1, char* str2) {
    char* tmp = str1;
    while (*str2 != '\0') {
        *str1++ = *str2++;
    }
    *str1 = '\0'; // Add null terminator
    return tmp;
}

String::~String() {
    delete[] m_str;
}

int main() {
    String str;
    char* aa = "hello";
    str = aa;
    cout << str << endl;
    cout << str[1] << endl;
    return 0;
}
