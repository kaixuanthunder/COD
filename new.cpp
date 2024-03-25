#include <iostream>


using namespace std;


class test
{
    public:
    virtual void func()=0;
    virtual ~test();
};

class usetest : public test
{
    public:
    virtual void func(int);
    
};

void usetest::func(int num)
{
    a = num;
    cout<<a<<endl;

}

int main()
{


}