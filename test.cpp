#include <vector>
#include <string>
#include <atomic>
#include <iostream>
#include <memory>
#include <math.h>
// template<class T>
// std::vector<T> ret(std::string b);



int main()
{
  float a = 90.001;
  float b = 90;
  if(fmod(a,b) == 0){
    std::cout<<"yes"<<std::endl;
  }
}
