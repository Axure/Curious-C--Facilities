#include <iostream>
#include <deque>
#include <functional>
using namespace std;

class coroutine_base {
 public:
 protected:
  virtual void yield_() = 0;
 private:
};

template<class Signature>
class coroutine;

template<class TResult, class... TArgs>
class coroutine<TResult(TArgs...)>: virtual public coroutine_base {
 public:

 private:
  std::deque<std::function<TResult(TArgs...)> > callables_;
 protected:
  virtual void yield_() override {

  }

 public:
  coroutine() {

  }

  coroutine<TResult(TArgs...)> next() {

  }

  TResult &value() {

  }
};

template<class TResult, class... TArgs>
coroutine<TResult(TArgs...)> to_coroutine(std::function<TResult(TArgs...)> &&function) {

};

template<class TResult, class... TArgs>
coroutine<TResult(TArgs...)> to_coroutine(std::function<TResult(TArgs...)> &function) {

};

int main() {
  cout << "Hello, World!" << endl;

  std::function<int(int)> to_See;
  coroutine<int(int)> my_coroutine = to_coroutine(to_See);
  return 0;
}