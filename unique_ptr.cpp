#include <iostream>
#include <memory>

class MyClass {
public:
    MyClass(int val) : value(val) {std::cout << "Constructing MyClass with value: " << value << std::endl;}
    ~MyClass() {std::cout << "Destructing MyClass with value: " << value << std::endl;}
    void print() {std::cout << "Value: " << value << std::endl;}
private:
    int value;
};

int main() {
    // 创建一个 unique_ptr，管理一个 MyClass 对象
    std::unique_ptr<MyClass> ptr(new MyClass(42));

    // 使用 get() 函数获取指向所管理对象的原始指针
    MyClass* rawPtr = ptr.get();
    rawPtr->print();

    // 使用 reset() 函数释放当前指针并接管新的指针
    ptr.reset(new MyClass(100));

    // 使用 release() 函数释放对所管理对象的所有权，并返回指针
    MyClass* releasedPtr = ptr.release();
    if (releasedPtr) {
        releasedPtr->print();
        delete releasedPtr; // 手动释放资源
    }

    // 由于 release() 已经释放了所有权，ptr 不再拥有对象，无需手动释放资源
    return 0;
}
