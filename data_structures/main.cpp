#include <iostream>
#include <memory>
#include <assert.h>

using namespace std;

namespace ax {
namespace data_structure {

template<class T, size_t arity>
class nary_tree {

 public:
  struct node {
    T value;
    node *children[arity] = {};
    size_t least_available = 0;
    bool is_full() {
      return least_available == arity;
    }
    operator T() {
      return value;
    }
  };

 private:


 private:
  void reallocate_() {

  }

  void allocate_node() {

  }
 public:
  nary_tree() {

  }

  ~nary_tree() {

  }

  static bool insert_node_to_node(node &node_to_insert, node *node_to_be_inserted) {
    if (!node_to_insert.is_full()) {
      node_to_insert.children[node_to_insert.least_available] = node_to_be_inserted;
      while (node_to_insert.children[node_to_insert.least_available] != nullptr) node_to_be_inserted->least_available++;
      return true;
    } else {
      return false;
    }
  }

  static bool insert_node_to_node(node &node_to_insert, node *node_to_be_inserted, size_t index) {
    if (node_to_insert.children[index] == nullptr) {
      node_to_insert.children[index] = node_to_be_inserted;
      if (node_to_insert.least_available == index) {
        while (node_to_insert.children[node_to_insert.least_available] != nullptr)
          node_to_be_inserted->least_available++;
      }
    } else {
      return false;
    }
  }


  static
  bool insert_to_node(node &node_to_insert, T value) {

  }

  static bool insert_to_node(node &node_to_insert, T value, size_t children_index) {

  }
};

class rb_tree {

};

template<class T>
class binary_heap {


 public:
  binary_heap() {

  }

  ~binary_heap() {

  }

  binary_heap &insert(T value) {

  }
};

template<class T>
class binomial_heap {

};

template<class T>
class fib_heap {


 public:

 private:

 public:
  fib_heap() {

  }

  virtual ~fib_heap() {

  }
};

class treap {

};

class tango_tree {

};
}
}

void benchmark() {

}

void test() {
  int a = 3;
  int b = 4;
  assert(a == b && "A is not equal to B");

  using ax::data_structure::nary_tree;
  nary_tree<int, 5> five_tree;

}

int main() {
  cout << "Hello, World!" << endl;

  test();
  benchmark();

  return 0;
}