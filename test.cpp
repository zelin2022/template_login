#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <cstring>
#include <queue>



void foo(int * a){
  int f = 5;
  std::deque<int> *q = new std::deque<int>();
  q->push_back(f);

  *a = q->front();
  delete(q);
}
int main(){

  int x = 0;
  foo(&x);
  std::cout<<x<<std::endl;
  // std::cout<<&x<<std::endl;







}
