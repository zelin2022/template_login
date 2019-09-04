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
  char type = 'a';
  switch(type){
    case 0x61:
    std::cout<<"hello"<<std::endl;
  }
}
