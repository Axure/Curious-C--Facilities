#include <iostream>
using namespace std;

template<size_t length>
void for_haha(const char (&array)[length]) {
  cout << "Hello, array!" << endl;
}

void for_haha(const char* pointer) {
  cout << "Hello, pointer!" << endl;
}


void what(const char* pointer) {
  cout << "Common!" << endl;
}

int main() {
  cout << "Hello, World!" << endl;

  char str[10] = "123456789";
  char str2[11] = "ajsklfiequ";
  char* str3 = "zhj3nvmsj1";
  for_haha(str);
  for_haha(str2);
  for_haha(str3);

  what(str);
  what(str2);
  what(str3);

  return 0;
}