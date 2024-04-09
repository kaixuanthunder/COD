#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Car
{
    public:
        Car(string name):_name(name){}
        virtual void show() = 0;
    protected:
        string _name;
};
class Bmw:public Car
{
    public:
        Bmw(string name):Car(name){}
        void show()
        {
            cout<<"获取了一辆宝马汽车"<<_name<<endl;
        }
};
class Audi:public Car
{
    public:
        Audi(string name):Car(name){}
        void show()
        {
            cout << "获取了一辆奥迪汽车"<<_name<<endl;

        }
};

class Light
{
    public:
        virtual void show() = 0;
};
class BmwLight :public Light
{
    public:
        void show(){cout << "BMW light"<<endl;}
};
class AudiLight :public Light
{
    public:
        void show(){cout << "Audi light"<<endl;}
};

class AbstractFactory
{
    public:
    virtual Car *createCar(string name) = 0;
    virtual Light * createCarLight() = 0;
};

class BMWFactory:public AbstractFactory
{
    public:
        Car*createCar(string name)
        {
            return new Bmw(name);
        }
        Light* createCarLight()
        {
            return new BmwLight();
        }
};

class AudiFactory:public AbstractFactory
{
    public:
    Car* createCar(string name)
    {
        return new Audi(name);
    }
    Light * createCarLight()
    {
        return new AudiLight();
    }
};

int main(int argc, char const *argv[])
{
    unique_ptr<AbstractFactory> bmwfty(new BMWFactory());
    unique_ptr<AbstractFactory> audifty(new AudiFactory());
    unique_ptr<Car>p1(bmwfty->createCar("X6"));
    unique_ptr<Car>p2(audifty->createCar("A8"));
    unique_ptr<Light>l1(bmwfty->createCarLight());
    unique_ptr<Light>l2(audifty->createCarLight());
    p1->show();
    l1->show();
    p2->show();
    l2->show();
    return 0;
}
