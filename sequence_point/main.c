#include <stdio.h>

int main() {

  int a = 10;
  printf("%d %d %d %d %d %d %d", a, ++a, a++, a, --a, a--, a);
  putchar('\n');

  int c;
  int b = 11;
//  printf("%d %n %d %n %d %n %d %n %d %n %d %n %d\n", b, &c, ++b, &c, b++, &c, b, &c, --b, &c, b--, &c, b);
  printf("Foo bcr %n %d\n", &c, 42);

  printf("geeks for %ngeeks\n", &c);
  printf("%d\n", c);
  return 0;
}