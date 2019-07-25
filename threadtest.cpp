// tests thread with some stdio

#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <thread>


void foocheck(std::string b){
  if(b.compare("end") == 0){
    std::cout<<"okay"<<std::endl;
  }
}
void foo(){
  while(true){
    std::string buff;
    std::cin>>buff;
    foocheck(buff);
  }
}



// void foo(){
//   int a;
//   std::cin>>a;
//   std::cout<<"ok"<<a<<std::endl;
// }

int main(int argc, char** argv){
  std::thread t(foo);
  int count = 0;
  while(true){
    for(int i =0; i < 100000000; i++){
    }
    std::cout <<"this is "<< count << std::endl;
    count++;
  }
  t.join();
}
