#include <vector>
#include <string>

// template<class T>
// std::vector<T> ret(std::string b);

template<class T>
std::vector<T> ret(std::string & b){}

int main()
{
  std::string a();
  std::vector<int> b = ret(a);
}
