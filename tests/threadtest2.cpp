#include <memory>
#include <thread>
#include <iostream>
#include <atomic>
#include <memory>


class foo{
public:
  foo(std::shared_ptr<std::atomic<bool>> t_var):var(t_var)
  {

  }
  void dao(){
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout<<*(this->var)<<std::endl;
  }
private:
  std::shared_ptr<std::atomic<bool>> var;
};


int main(){
  std::shared_ptr<std::atomic<bool>> toset = std::make_shared<std::atomic<bool>> (false);
  std::shared_ptr<foo> to1 = std::make_shared<foo>(toset);
  // std::unique_ptr<foo> to2 = std::make_unique<foo>(1);

  std::thread t1(&foo::dao, to1);
  *toset = true;
  // std::thread t2(&foo::dao, to2);
  t1.join();
  // to2->seta(2);


}
