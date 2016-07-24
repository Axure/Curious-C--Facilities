#include <iostream>
#include <stdio.h>
using namespace std;

int func1() {
  int max, i, index, n;
  int ri, repeat;
  int a[10];

  scanf("%d", &repeat);
  for (ri = 1; ri <= repeat; ri++) {
    scanf("%d", &n);
    for (i = 0; i < n; i++)
      scanf("%d", &a[i]);
    max = a[0];
    index = 0;

    for (i = 0; i < n; i++) {
      if (max < a[i]) {
        max = a[i];
        index = i;
      }
    }
    printf("max = %d, index = %d\n", max, index);
  }

}
int func2() {
  int i, index, n;
  int ri, repeat;
  int a[10];

  scanf("%d", &repeat);
  for (ri = 1; ri <= repeat; ri++) {
    scanf("%d", &n);
    for (i = 0; i < n; i++)
      scanf("%d", &a[i]);
    index = 0;
    a[index] = a[0];

    for (i = 1; i < n; i++) {
      if (a[index] < a[i]) {
        a[index] = a[i];
        index = i;
      }
    }
    for (i = 0; i < n; i++) {
      printf("%d, ", a[i]);
    }
    printf("\n");
    printf("max = %d, index = %d\n", a[index], index);
  }

}

int main() {
  cout << "Hello, World!" << endl;

  func1();
  func2();

  return 0;
}