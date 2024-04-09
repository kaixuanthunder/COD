#include <iostream>
#include <string>
#include <memory>

using namespace std;
class Car
{
public:
    Car(string name) :_name(name){}
    virtual void show() = 0;
protected:
    string _name;
};

class Bmw :public Car
{
    public: 
    Bmw(string name):Car(name){}
    void show()
    {
        cout <<"获取了一辆宝马汽车:"<< _name << endl;
    }
};

class Audi :public Car
{
    public:
    Audi(string name):Car(name){}

    void show()
    {
        cout << "获取了一辆奥迪汽车:"<< _name <<endl;
    }
};

enum Cartype
{
    BMW,AUDI
};

class SimpleFactory
{
public:
    Car* createCar(Cartype ct)
    {
        switch(ct)
        {
            case BMW:
                return new Bmw("x6");
            case AUDI:
                return new Audi("a8");
            default:
                cerr << "参数错误" << ct <<endl;
        }
        return nullptr;
    }
};

int main(int argc, char const *argv[])
{
    /* code */
    unique_ptr<SimpleFactory> fac(new SimpleFactory());
    unique_ptr<Car> p1(fac->createCar(BMW));
    unique_ptr<Car> p1(fac->createCar(AUDI));

    unique_ptr<Car> p3(fac->createCar(0));
    unique_ptr<Car> p4(fac->createCar(1));
    p1->show();
    p2->show();

	// SimpleFactory* fac = new SimpleFactory();
	// Car* p1 = fac->createCar(BMW);
	// Car* p2 = fac->createCar(AUDI);

	// p1->show();
	// p2->show();

	// delete fac;
	// delete p1;
	// delete p2;


    return 0;
}
