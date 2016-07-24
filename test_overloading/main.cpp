#include <iostream>
using namespace std;
//void f(char *c, bool b = false) // f1
//{
//  cout << c << " " << b << " f char*" << endl;
//}
//void f(bool b = false) // f2
//{
//  cout << b << " f bool" << endl;
//}
//
void f(const char *c) {
  cout << "const char*" << '\n';
}

template<size_t length>
void f(const char (&c)[length]) {
  cout << "const char[]" << '\n';
}

template<size_t length>
void f(char (&c)[length]) {
  cout << "char[] array" << '\n';
}


template<size_t length>
void doSomething(const char (&name)[length]) {

}

int main() {
  const char *c = "he";
//  f(c);
  f("he");
  decltype("he") cc = "he";
  char ccc[3] = "he";
  const char cccc[3] = "he";
  f(cc);
  f(ccc);
  f(cccc);
  doSomething("hah");
}