#include <cstdint>
#include <iostream>
#include <thread>
#include <list>
#include <deque>
#include <tuple>
#include <algorithm>
#include <cassert>
#include <sstream>
#include <unordered_map>

#define MAX 10
#define MAXIMUM 1000

using namespace std;

template<template<typename, typename> class RS,
    template<typename, typename> class L,
    template<typename, typename> class R,
    class LT, class RT,
    class LA, class RA>
/**
 * TODO: make a version using iterators instead of the `at` interace.
 */
RS<tuple<LT, RT>, allocator<tuple<LT, RT>>> zip(L<LT, LA> &left, R<RT, RA> &right) {
  auto lSize = left.size();
  auto rSize = right.size();
  RS<tuple<LT, RT>, allocator<tuple<LT, RT>>> result;
  auto size = lSize < rSize ? lSize : rSize;
  for (int i = 0; i < size; ++i) {
    result.insert(result.end(), make_tuple(left.at(i), right.at(i)));
  }
  return result;
};

template<class ...Types>
class enhanced_tuple { // should receive a type list?

};

class type_list {

};


template<template<typename, typename> class Cont, class LastCont>
auto zip_var(LastCont lastContainer) {
  Cont<tuple<typename LastCont::value_type>, allocator<tuple<typename LastCont::value_type>>> result;
  for_each(lastContainer.begin(), lastContainer.end(), [&](auto &content) {
    result.insert(result.end(), make_tuple(content));
  });
  return result;
}

template<template<typename, typename> class Cont, class FirstCont, class ...RestConts>
auto zip_var(FirstCont firstContainer,
             RestConts... restContainers) {
  auto rightResult = zip_var<Cont>(restContainers...);
  auto lSize = firstContainer.size();
  auto rSize = rightResult.size();
  Cont<tuple<typename FirstCont::value_type, typename RestConts::value_type...>,
       allocator<tuple<typename FirstCont::value_type, typename RestConts::value_type...>>> result;
  auto size = lSize < rSize ? lSize : rSize;
  for (int i = 0; i < size; ++i) {
    result.insert(
        result.end(),
        tuple_cat(
            make_tuple(firstContainer.at(i)),
            rightResult.at(i)
        )
    );
  }
  return result;
}

template<template<typename, typename> class Cont, class T, class A>
void play(Cont<T, A> &haha) {

};

int totient(int n) {

}

deque<int> linear_sieve(deque<int> &numbers) {
  unordered_map<int, bool> isNotPrime;
  deque<int> primes;
  auto max = numbers.at(numbers.size() - 1);
  cout << max << '\n';
  for (auto &number: numbers) {
    if (isNotPrime.find(number) == isNotPrime.end()) {
      primes.push_back(number);
    }
    auto prime_size = primes.size();
    for (int i = 0, product; i < prime_size && (product = primes.at(i) * number) <= max; i++) {
      isNotPrime[product] = true;
      if (number % primes.at(i) == 0) break;
    }
  }
  return primes;
}

deque<int> normal_sieve(deque<int> &numbers) {
  unordered_map<int, bool> isNotPrime;
  deque<int> primes;
  auto max = numbers.at(numbers.size() - 1);
  cout << max << '\n';
  for (auto &number: numbers) {
    if (isNotPrime.find(number) == isNotPrime.end()) {
      primes.push_back(number);
      for (int i = number * number; i <= max; i += number) {
        isNotPrime[i] = true;
      }
    }
  }
  return primes;
}

class bool_set {
 private:
  deque<int64_t> container_;
  size_t size_ = 0;

  static constexpr size_t int_size_ = sizeof(int64_t) * 8; // 8 bits = 1 byte.
  static bool get_bit_(int64_t number, size_t index) {
    auto tool = 1 << index;
    return static_cast<bool>(number & tool);
  }

  static int64_t set_bit_(int64_t number, size_t index, bool value) {
    if (value == true) {
      number = number | (1 << index);
    } else {
      number = number & (~(1 << index));
    }
    return number;
  }
/** The interfaces. **/
 public:
  bool_set() {
  }

  friend void test_bool_set();

  bool_set &push_back(bool value) {
    if (size_ % int_size_ == 0) {
      container_.push_back(static_cast<int64_t>(value));
    } else {
      this->set(size_, value);
    }
    size_ += 1;
  }

  bool at(size_t index) const {
    auto offset = index % int_size_;
    auto periods = index / int_size_;
    return get_bit_(container_.at(periods), offset);
  }

  bool_set &set(size_t index, bool value) {
    auto offset = index % int_size_;
    auto periods = index / int_size_;
    container_[periods] = set_bit_(container_.at(periods), index, value);
    return *this;
  }

  /**
   * How to make this operator to modify the contents?
   */
  bool &operator[](size_t index) {
    auto offset = index % int_size_;
    auto periods = index / int_size_;
//    return
  }

  string toString() const {
    ostringstream oss;
    for (int64_t i = 0; i < size_; ++i) {
      oss << static_cast<int64_t>(this->at(i));
    }
    return oss.str();
  }

};

void test_bool_set() {
  assert(bool_set::get_bit_(7, 0) == true);
  assert(bool_set::get_bit_(7, 1) == true);
  assert(bool_set::get_bit_(7, 2) == true);
  assert(bool_set::get_bit_(7, 3) == false);
  int a = 0;
  a = bool_set::set_bit_(a, 0, true);
  a = bool_set::set_bit_(a, 1, true);
  a = bool_set::set_bit_(a, 2, true);
  a = bool_set::set_bit_(a, 3, false);
  assert(a == 7);
}

ostream &operator<<(ostream &os, const bool_set &bs) {
  return os << bs.toString();
}

int main() {
  test_bool_set();

  cin.sync_with_stdio(false);
  cout.sync_with_stdio(false);
  cout << "Hello, World!" << endl;

  for (int i = 0; i < MAX; ++i) {
    cout << i;
  }

  deque<int> all;
  deque<int> primes;

  for (int i = 2; i <= MAXIMUM; ++i) {
    all.push_back(i);
  }

  auto result = normal_sieve(all);
  for (auto &number: result) {
//    cout << number << '\n';
  }

  result = linear_sieve(all);
  for (auto &number: result) {
//    cout << number << '\n';
  }

  while (false_type::value) {

  }

  ;

  auto zipped = zip<deque>(all, result);
  for (auto &number_pair: zipped) {
//    cout << get<0>(number_pair) << ", " << get<1>(number_pair) << "\n";
  }

  deque<int> a{1, 2, 3, 4};
  deque<double> b{1.2, 3.4, 5.7};
  list <string> c{"haha", "hehe", "xixi"};

  auto zipped_var = zip_var<vector>(a, b, c);
  for (auto &triple: zipped_var) {
    cout << get<0>(triple) << ", " << get<1>(triple) << ", " << get<2>(triple) << "\n";
  }

  bool_set bs;
  bs.push_back(true);
  bs.push_back(false);
  bs.push_back(false);
  bs.push_back(true);
  bs.push_back(false);
  bs.push_back(false);
  bs.push_back(false);
  bs.push_back(false);
  bs.push_back(false);
  bs.push_back(false);
  bs.push_back(false);
  bs.push_back(true);
  bs.push_back(false);

  assert(bs.toString() == "1001000000010");

  cout << bs;


  return 0;
}