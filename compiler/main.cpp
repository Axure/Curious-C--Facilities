#include <iostream>
#include <string>
#include <tuple>

using std::cout;
using std::cin;
using std::endl;
using std::string;

template<class T>
class state_machine {

};

class specific_state_machine {
 private:

 protected:

 public:

  enum class states {
    FIRST
  };
};

int main() {

  cout.sync_with_stdio(false);
  cin.sync_with_stdio(false);


  cout << "Hello, World!" << endl;

  string s;

  cin >> s;

  for (int i = 0; i < s.length(); ++i) {
//    cout << s[i] << ' ';
  }

  char test[7] = "123456";
  cout << test << '\n';

  return 0;
}