#include <iostream>
#include <queue>
using namespace std;

#define MAX 100

struct character {
  char c;
  int f;
  character* left;
  character* right;
  bool operator < (const character &x) const {

  }
};

character ch[MAX];
priority_queue<character*> q;
queue<character*> que;

class character_pp {

};

int main() {
  cout << "Hello, World!" << endl;
  decltype([]() {

  }) a ;
  vector<character*> container;
  auto lambda = [](character* p1, character* p2) {
    if (p1->f > p2->f) return 1;
    else if (p1->f < p2->f) return -1;
    else return 0;
  };
  auto auto_lambda = [](auto p1, auto p2) {
    if (p1->f > p2->f) return 1;
    else if (p1->f < p2->f) return -1;
    else return 0;
  };
  auto q2 = priority_queue<character*, decltype(container), decltype(lambda)>(lambda, container);
  auto q4 = priority_queue<character*, decltype(container), decltype(auto_lambda)>(lambda, auto_lambda);


  return 0;
}