
#include <iostream>


using namespace std;
class Box
{
    public:
        void getwidth(double width);
        friend class otherBox;
        friend void showwidth(Box box);

    private:
        double width;

};

class otherBox
{
    public:
  
        void other_width(double width,Box &box);
};


void Box::getwidth(double wid)
{
    width = wid;
    cout << "width = "<< width<<endl;
}

void otherBox::other_width(double wid,Box &box)
{
    box.getwidth(wid);
    cout<< "the box's width = " << box.width << endl;
}

void showwidth(Box box)
{
    cout<<"show width = "<< box.width << endl;
}

int main()
{
    Box box;
    box.getwidth(10.0);
    showwidth(box);
    box.getwidth(20.0);
    showwidth(box);
    otherBox otherbox;
    otherbox.other_width(30.0,box);
    showwidth(box);
}