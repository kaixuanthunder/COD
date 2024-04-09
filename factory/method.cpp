#include <iostream>
#include <memory>
#include <string>


using namespace std;
class Car
{
public:
	Car(string name) :_name(name) {}
	virtual void show() = 0;
protected:
	string _name;
};
class Bmw:public Car
{
public:
	Bmw(string name) :Car(name) {}
	void show()
	{
		cout << "获取了一辆宝马汽车：" << _name << endl;
	}
};
class Audi :public Car
{
public:
	Audi(string name) :Car(name) {}
	void show()
	{
		cout << "获取了一辆奥迪汽车：" << _name << endl;
	}
};

class Factory
{
    public:
        virtual Car* createCar(string name) = 0;
};

class BmwFac:public Factory
{
    public:
        Car* createCar(string name)
        {
            return new Bmw(name);
        }
};

class AudiFac:public Factory
{
    public:
        Car* createCar (string name)
        {
            return new Audi(name);
        }
};

int main(int argc, char const *argv[])
{
    unique_ptr<Factory> bmwfty(new BmwFac());
    unique_ptr<Factory> audifty(new AudiFac());
    unique_ptr<Car> p1 (bmwfty->createCar("X6"));
    unique_ptr<Car> p2 (audifty->createCar("A8"));

    p1->show();
    p2->show();

    return 0;
}
