#include <iostream>
#include <poll.h>
#include <cstring>
#include <vector>



int main(){

  std::vector<int> tt;

  tt.push_back(0);
  tt.push_back(1);
  std::swap(tt[0], tt.back());

  tt.pop_back();

  std::cout<<tt.size()<<std::endl;
}
