#include <iostream>
#include <poll.h>
#include <cstring>
#include <vector>
#include <memory>


class foo
{
public:
  static void boo(){
    poo();
  }
  static void poo(){
    std::cout<<"a"<<std::endl;
  }
};

int main(int argc, char** argv){
  foo::boo();


}
