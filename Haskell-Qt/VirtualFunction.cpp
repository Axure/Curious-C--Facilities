//
// Created by lluvi on 2016/7/24.
//
#include <iostream>
class A{
 public:
  virtual int getSealed() = 0;
};

class B : public A {
 private:
  int sealed = 13;
 public:
  int getSealed() {
    return this->sealed;
  }
};

int main() {
  A* b = new B();
  std::cout << b->getSealed();
}