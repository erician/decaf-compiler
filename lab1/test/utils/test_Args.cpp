#include <iostream>

class A
{
public:
    std::string aa;
    A(std::string a){aa = a;}
    std::string getAA(){return aa;}
    void print(){std::cout << aa << std::endl;}
};

int main()
{
    A a("bb");
    a.print();
    std::string tmp = a.getAA();
    tmp = "cc";
    a.print();
    char array[ ][1];
}