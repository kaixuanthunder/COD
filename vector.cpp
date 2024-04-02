#include <iostream>
#include <vector>

//using namespace std;
int main(int argc, char const *argv[])
{
    vector<int> testVector;
    std::vector<int>::iterator iter = testVector.erase(testVector.begin());
    std::vector<int>::iterator iter = testVector.erase(testVector.end());//删除最后一个元素没有下一个会发生异常
    std::vector<int>::iterator iter = testVector.erase(testVector.begin(),testVector.begin()+1);
    //注意不要越界

    



    return 0;
}
