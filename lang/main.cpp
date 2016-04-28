#include <iostream>
#include <sstream>
#include <utility>
#include <tuple>
#include <string>
#include <cstring>
#include <cassert>
#include <list>
#include <vector>
#include <deque>
#include <algorithm>

using std::cout;
using std::endl;

namespace meta_programming {

template<class T, class R>
struct eq {
  static constexpr bool value = false;
};;

template<class T>
struct eq<T, T> {
  static constexpr bool value = true;
};


template<class T>
struct value {
  using result = T;
};


template<bool condition, class T, class R>
struct cond {
  using result = R;
};

template<class T, class R>
struct cond<true, T, R> {
  using result = T;
};

struct nil {
  static constexpr bool value = false;
};

template<class First, class Second>
struct list {
  using first = First;
  using rest = Second;
  static constexpr int length = 1 + rest::length;
};

template<class First>
struct list<First, nil> {
  using first = First;
  using rest = nil;
  static constexpr int length = 1;
};

template<class First, class ...Rest>
struct build_list {
  using result =  list<First, typename build_list<Rest...>::result>;
};

template<class First>
struct build_list<First> {
  using result = list<First, nil>;
};

/**
 * This is the core structure, in correspondance with the lists in Lisp.
 * This is a structure.
 */
template<class First, class ...Rest>
struct list_ {
  using first = First;
  using rest = list_<Rest...>;
  static constexpr int length = 1 + rest::length;
};

template<class First>
struct list_<First> {
  using first = First;
  using rest = nil;
  static constexpr int length = 1;
};

template<int index, class Typelist>
struct get {
  using result = typename get<index - 1, typename Typelist::rest>::result;
};

template<class Typelist>
struct get<0, Typelist> {
  using result = typename Typelist::first;
};


template<class Head, class Tail>
struct cons {
  using result = list<Head, Tail>;
};

template<class T>
struct cdr {
  using result = typename T::rest;
};

template<class T>
struct car {
  using result = typename T::first;
};

/**
 * Is syntactic sugar for `cons`.
 */
template<class ...Types>
struct brace {
  using result = typename build_list<Types...>::result;
};

template<template<typename...> class VTempl, class ...Args>
struct apply_var {
  using result = typename VTempl<Args...>::result;
};

template<template<typename...> class VFunc, class TypeList, size_t... Indices>
VFunc<typename get<Indices, TypeList>::result...> help_explode(std::index_sequence<Indices...>) {
  VFunc<typename get<Indices, TypeList>::result...> nonsense;
  return nonsense;
};

/**
 * This is the true apply. Apply a variadic template to a typelist.
 *
 * This is the core part.
 */
template<template<typename...> class VFunc, class TypeList>
struct apply {
  using result = decltype(help_explode<VFunc, TypeList>(std::make_index_sequence<TypeList::length>{}));

};

template<template<typename...> class VFunc, class TypeList>
struct three_apply {
  using result = VFunc<typename TypeList::first, typename TypeList::rest::first, typename TypeList::rest::rest::first>;
};

template<template<typename> class Func, class ...Args>
struct map_list_var {
//  using result = typename VTempl<Args...>::result;
};

template<template<typename> class Func, class TypeList>
struct map {
  using result = typename cons<
      typename Func<
          typename car<TypeList>::result
      >::result,
      typename map<
          Func,
          typename cdr<TypeList>::result
      >::result
  >::result;
};

template<template<typename> class Func>
struct map<Func, nil> {
  using result = nil;
};

}

namespace regexp {
using namespace meta_programming;

using result_tuple_t = std::tuple<std::string, std::string>;
using result_t = std::list<result_tuple_t>;

}

std::ostream &operator<<(std::ostream &os, const regexp::result_t &results) {
  os << "['";
  for (auto &result: results) {
    os << std::get<0>(result) << "','" << std::get<1>(result);
  }
  os << "']";
}

namespace regexp {


struct parser_base {

};

template<class Parser>
struct parser_base_recur: virtual public parser_base {
  static result_t transform_list(result_t result_list) {
    result_t transformed_list = {};
    std::for_each(result_list.begin(),
                  result_list.end(),
                  [&transformed_list](result_tuple_t &result_tuple) {
                    result_t new_list = Parser::parse(std::get<1>(result_tuple));
                    std::for_each(new_list.begin(),
                                  new_list.end(),
                                  [&new_list,
                                      &result_tuple](result_tuple_t &new_result_tuple) {
                                    std::get<0>(new_result_tuple) =
                                        std::get<0>(result_tuple) + std::get<0>(new_result_tuple);
                                    std::cout
                                        << "Concatnating result: "
                                        << std::get<0>(new_result_tuple) << '\n';
                                  });
                    transformed_list.merge(new_list);
                    std::cout << "Temp result: " << transformed_list << '\n';
                  });
    return transformed_list;
  }
};

struct parser_function_base {

};

template<char content>
struct char_parser: public parser_base_recur<char_parser<content>> {
  static constexpr char value = content;
  static result_t parse(std::string string) {
    assert(string.length() >= 1);
    std::cout << "char parser for std::string" << '\n';

    result_t result;
    if (string.at(0) == content) {
      std::string content_string(1, content);
      result.push_back(std::make_tuple(content_string, string.substr(1)));
    } else {
//      std::string empty_string("");
//      result.push_back(std::make_tuple(empty_string, string));
    };
    return result;
  }
};

template<class Parser, size_t times>
struct repeated_parser {
 private:
  struct result_parser: virtual public parser_base_recur<repeated_parser<Parser, times>> {
    static result_t parse(std::string string) {
      static_assert(times != 0, "The repeated times must be positive!");
      result_t result = {std::make_tuple("", string)};
      result_t temp_result = {};
      for (int i = 0; i < times; ++i) {
        /**
         * Parse each latter, concatnate.
         */
        temp_result = Parser::transform_list(result);
        result = temp_result;
        temp_result.clear();
      }
      return result;
    }
  };
 public:
  static constexpr int value = times;
  using result = result_parser;
};

template<class ParserList>
struct concated_parser {
 private:
  struct result_parser: public parser_base_recur<result_parser> {
    static result_t parse(std::string string) {
      static_assert(ParserList::length >= 1, "The list of parsers to concat must contain at least one element!");
      result_t first_result = ParserList::first::parse(string);
      return concated_parser<typename ParserList::rest>::result::transform_list(first_result);
    }
  };
 public:
  using result = result_parser;
};

template<class T>
struct concated_parser<list<T, nil>> {
 private:
  struct result_parser: public parser_base_recur<result_parser> {
    static result_t parse(std::string string) {
      result_t first_result = T::parse(string);
      return first_result;
    }
  };
 public:
  using result = struct result_parser;
};
}

namespace tree {
using namespace meta_programming;


template<class T>
struct make_tree {
  using result = cons<cons<T, nil>, nil>;
};
}

struct IntWrapper {
  using value = int;
};

struct DoubleWrapper {
  using value = double;
};

template<class T>
struct GetValue {
  using result = typename T::value;
};

template<class T>
struct GetValueType {
  using result = typename T::value_type;
};

template<class Target, class ...Conts>
void zip() {

};

void do_tests() {
  using namespace meta_programming;
  cout << "Hello, World!" << endl;

  meta_programming::brace<int, double>::result a;
  meta_programming::brace<int, double, char>::result b;

  cout << eq<
      car<
          brace<
              int,
              double
          >::result
      >::result, int
  >::value << '\n';

  cout << eq<
      car<
          cons<
              int,
              double
          >::result
      >::result, int
  >::value << '\n';

  cout
      << eq<
          int,
          car<
              map<
                  GetValue,
                  brace<
                      IntWrapper,
                      DoubleWrapper
                  >::result
              >::result
          >::result
      >::value
      << '\n';

  car<
      map<
          GetValue,
          brace<
              IntWrapper,
              DoubleWrapper
          >::result
      >::result
  >::result
      c = 3;

  get<0, list<int, double>>::result d = 4;

  cout << "The length of the list is " << brace<int, double>::result::length << '\n';

  cout << "First of (int, double) is int: " << eq<get<0, brace<int, double>::result>::result, int>::value << '\n';
  cout << "First of (int, double) is double: " << eq<get<0, brace<int, double>::result>::result, double>::value << '\n';
  cout << "Second of (int, double) is int: " << eq<get<1, brace<int, double>::result>::result, int>::value << '\n';
  cout << "Second of (int, double) is double: " << eq<get<1, brace<int, double>::result>::result, double>::value
      << '\n';


  cout << eq<cond<true, int, double>::result, int>::value << '\n';
  cout << eq<cond<true, int, double>::result, double>::value << '\n';
  cout << eq<cond<false, int, double>::result, int>::value << '\n';
  cout << eq<cond<false, int, double>::result, double>::value << '\n';

  apply<std::tuple, build_list<int, double>::result>::result e = std::make_tuple(1, 1.5);
  cout << std::get<0>(e) << ',' << std::get<1>(e) << '\n';
  cout << "Applying `std::tuple` to (int, double, std::string): " << eq<
      apply<
          std::tuple,
          brace<
              int,
              double,
              std::string
          >::result
      >::result,
      std::tuple<int, double, std::string>
  >::value << '\n';

  cout << "Applying `std::tuple` to (int, double, std::string), retrieved by map on the containers: " << eq<
      apply<
          std::tuple,
          map<
              GetValueType,
              brace<
                  std::list<int>,
                  std::vector<double>,
                  std::deque<std::string>
              >::result
          >::result
      >::result,
      std::tuple<int, double, std::string>
  >::value << '\n';

  apply<std::tuple, brace<int, double, char, bool>::result>::result f = std::make_tuple(1, 1.5, 'c', true);
  cout
      << std::get<0>(f) << ','
      << std::get<1>(f) << ','
      << std::get<2>(f) << ','
      << std::get<3>(f) << ','
      << '\n';
}

template<class T>
inline std::ostringstream &concat_to_stream(std::ostringstream &oss, T &&arg) {
  oss << arg;
  return oss;
}

template<class First, class ...Rest>
inline std::ostringstream &concat_to_stream(std::ostringstream &oss, First &&firstArg, Rest &&... restArgs) {
  oss << firstArg << ',';
  return concat_to_stream(oss, std::forward<Rest &&>(restArgs)...);
}

template<class ...Types>
inline std::string concat_to_string(Types &&... args) {
  std::ostringstream oss; // TODO: How to be thread-safe?
  oss << '(';
  concat_to_stream(oss, std::forward<Types &&>(args)...);
  oss << ')';
  return oss.str();
}

template<class Tuple, size_t... Indices>
std::string help_concat(const Tuple &tuple, std::index_sequence<Indices...>) {
  return concat_to_string(std::get<Indices>(tuple)...);
};

template<class ...Types>
std::string tuple_to_string(const std::tuple<Types...> &tuple) {
  return help_concat(tuple, std::make_index_sequence<sizeof...(Types)>{});
};

template<class ...Types>
std::ostream &operator<<(std::ostream &os, const std::tuple<Types...> &tuple) {
  return os << tuple_to_string(tuple);
}


void parser_tests() {
  using c_parser = regexp::char_parser<'c'>;
  using a_parser = regexp::char_parser<'a'>;

  using regexp::repeated_parser;
  using regexp::concated_parser;
  using meta_programming::brace;

  std::string c("cc");
  std::string a("ac");

  std::cout << c_parser::parse(c) << '\n';
  std::cout << c_parser::parse(a) << '\n';
  std::cout << repeated_parser<c_parser, 2>::result::parse(c) << '\n';
  std::cout << repeated_parser<c_parser, 2>::result::parse(a) << '\n';

  std::cout << concated_parser<
      brace<
          a_parser,
          c_parser
      >::result
  >::result::parse(a) << '\n';

};

int main() {
  do_tests();

  std::tuple<int, double, std::string> sample_tuple = std::make_tuple(3, 1.723, "Hi!");
  std::cout << sample_tuple << '\n';

  std::cout << concat_to_string(1, 2, 3, 4, 5) << '\n';

  std::cout << sample_tuple << '\n';

  parser_tests();

  return 0;
}