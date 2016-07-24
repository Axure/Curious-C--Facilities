#include <iostream>
using namespace std;
class A{
  void fu() {

  }

  void uf() {

  }
};


template <class T>
struct DepValue {
  using V = T;
  T value;
};

template <class T>
typename T::V magic(T depValue) { return depValue.value; }

template <class T>
DepValue<T> mk(T x) {
  DepValue<T> result;
  result.value = x;
  return result;
}


int main() {
//  int a;

  DepValue<int> a;
  a.value = 3; magic(a);

  auto depInt = mk(1);
  auto depString = mk(std::string("two"));

  auto itWorks = magic(depInt);
  auto again = magic(depString);

  std::cout << itWorks << std::endl;
  std::cout << again << std::endl;

//  while(true) {
//    cin >> a;
//    cout << a << endl;
//  }
  return 0;
}