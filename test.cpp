#include <iostream>
#include <poll.h>
#include <cstring>
#include <vector>
#include <memory>
#include <thread>
#include <atomic>


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


std::atomic_flag FLAG;

class foo
{
public:
  ~foo(){
    using namespace std::chrono_literals;

      std::this_thread::sleep_for(2s);
    std::cout<<"im dead"<< std::endl;
  }
};

class boo
{
public:
  boo(){
    this->ob = std::make_shared<foo>();
  }
  void poo(){while(true){}}
private:
  std::shared_ptr<foo> ob;
};



int main(int argc, char** argv){
  boo* b = new boo();

  std::thread t1 (&boo::poo, b);

  delete(b);

  using namespace std::chrono_literals;

    std::this_thread::sleep_for(2s);

    FLAG.clear();
    std::cout<< "a" << std::flush;


}
