#include <iostream>
#include <csetjmp>

std::jmp_buf jump_buffer_one;
std::jmp_buf jump_buffer_two;
std::jmp_buf jump_buffer_two_b;

[[noreturn]] void one(int c) {
  std::cout << "one(" << c << ") called\n";
  std::longjmp(jump_buffer_one, c + 1);  // setjump() will return c+1
}

[[noreturn]] void b(int count);

[[noreturn]] void a(int count) {
  volatile int value;
  value = setjmp(jump_buffer_two);

  switch(value) {
    case 0:
      std::cout << "a(" << count << ") called\n";
      std::cout << "a(" << value << ") one executed\n";
      b(count + 1);
    case 1:
      std::cout << "a(" << value << ") two executed\n";
      b(count + 1);
    default:
      break;
  }


}

[[noreturn]] void b(int count) {
  std::cout << "b(" << count << ") called\n";
  std::setjmp(jump_buffer_two_b);

  std::longjmp(jump_buffer_two, count + 1);

}

int main() {
  volatile int c = 0; // modified locals in setjmp scope must be volatile
  if (setjmp(jump_buffer_one) != 9) { // equality against constant expression in an if
    one(c++);  // This will cause setjmp() to exit
  }

  volatile int count = 0;

  a(count);
}