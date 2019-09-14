#include <iostream>
#include <poll.h>
#include <cstring>
#include <vector>
#include <memory>


int GLOBAL = 0;



void foo(char * data){
  std::cout<<data[0]<<std::endl;
}

int main(){
  unsigned char a = 255;
  std::cout<< (size_t) a << std::endl;
}
