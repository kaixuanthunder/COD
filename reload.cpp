#include <iostream>
#include <cmath>

using namespace std;


class reload
{
private:
    double m_real;
    double m_imag;
public:
    reload(double real = 0.0,double imag = 0.0):m_real(real),m_imag(imag){};
    friend reload operator +(reload &a,reload &b);
    friend ostream& operator <<(ostream & out,reload &a);
    friend istream& operator >>(istream & pt,reload &a);
    
    
    ~reload();
};

// reload::reload(double real,double imag)
// {
//     m_real = real;
//     m_imag = imag;
// }

reload::~reload()
{
}

reload operator+(reload &a,reload &b)
{
    reload c;
    c.m_real = a.m_real + b.m_real;
    c.m_imag = a.m_imag + b.m_imag;

    return c;
}

ostream& operator<<(ostream &out, reload &a)
{
    out << "m_real = " << a.m_real << "  m_imag = " << a.m_imag << endl;
    out << a.m_real << "+" << a.m_imag << "i";
    return out;
}

istream& operator>>(istream &in, reload &a)
{   

    in >> a.m_real  >> a.m_imag; 
    return in;
}


int main()
{
    reload c1, c2, c3;
    
    cin >> c1 >> c2;
    c3 = c1 + c2;
    cout << "c3 = " << c3 << endl;
}