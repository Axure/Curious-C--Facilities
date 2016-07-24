#include <iostream>
#include <vector>
#include <unistd.h>
using namespace std;

void make_exit(int n) {
  exit(n);
}

template<class T>
void what() {

}

int main() {
  pid_t pid;
  cout << "Hello, World!" << endl;
  cout << (void*)(what<int>) << '\n';
//  fork();
  vector<int> test_vector;

//  auto pFunc = &vector<int>::push_back;
  void (__thiscall vector<int>::* pFunc)(const int&) = &vector<int>::push_back;
  void* pPtr = (void*&)pFunc;
  cout << pPtr << '\n';

//  cout << (void*)(&test_vector.push_back) << '\n';

  make_exit(1);
}