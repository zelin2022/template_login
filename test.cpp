#include <iostream>
#include <poll.h>
#include <cstring>
#include <vector>
#include <memory>


int GLOBAL = 0;

class Foo{
public:
  Foo(int x){this->a=x;}
  ~Foo(){std::cout<<this->a<<std::endl;}
  int a;
};

int main(){
  std::unique_ptr<Foo> xx = std::make_unique<Foo>(1);
  GLOBAL++;
  Foo* fff = new Foo(3);
  GLOBAL++;
  xx.reset(fff);
  GLOBAL++;
}
