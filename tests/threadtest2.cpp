#include <memory>
#include <thread>
#include <iostream>


class foo{
public:
  foo(int a){
    this->num = a;
  }
  void seta(int a){
    this->num = a;
  }
  void dao(){
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout<<this->num<<std::endl;
  }
private:
  int num;
};


int main(){
  std::shared_ptr<foo> to1 = std::make_shared<foo>(1);
  // std::unique_ptr<foo> to2 = std::make_unique<foo>(1);

  std::thread t1(&foo::dao, to1);
  // std::thread t2(&foo::dao, to2);
  to1->seta(2);
  t1.join();
  // to2->seta(2);


}
