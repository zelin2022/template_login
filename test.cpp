#include <iostream>
#include <poll.h>
#include <cstring>
#include <vector>
#include <memory>


// class foo
// {
// public:
//   static void boo(){
//     poo();
//   }
//   static void poo(){
//     std::cout<<"a"<<std::endl;
//   }
// };


template<class T> std::vector<T> foo(int a, T f){
  std::vector<T> out;
  out.push_back(a);
  return out;
}

int main(int argc, char** argv){
  std::vector<int> x;
  x = foo(122,1);

  std::cout<<x[0]<<std::endl;


}
