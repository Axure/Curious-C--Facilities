#include <windows.h>
#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <bitset>
#include <functional>
#include <deque>
#include <algorithm>

std::deque<bool> toByteArray(DWORD dword) {
  using TByteArray = std::deque<bool>;
  TByteArray result;
  int position = 0;
  while (dword != 0) {
    result.push_back(bool(dword % 2));
    dword /= 2;
    position++;
  }
  return result;
}

std::string toReadableDWORD(DWORD dword) {
  std::ostringstream ostringstream;
  int position = 0;
  while (dword != 0) {
    ostringstream << char((dword % 2) ? position + 'A' : ' ');
    dword /= 2;
    position++;
  }
  return ostringstream.str();
}

std::string toReadableDWORDFunctional(DWORD dword) {
  auto binContainer = toByteArray(dword);
  std::deque<char> container(binContainer.size());
  int index = -1;
  std::transform(binContainer.begin(), binContainer.end(), container.begin(), [&index](auto &bin) {
    ++index;
    return bin ? (index + 'A') : ' ';
  });
  std::string result;
  auto imploded = std::accumulate(container.begin(), container.end(), result, [](std::string &before, char &current) {
    return before + current;
  });
  return imploded;
}

int main() {

  std::cout << toReadableDWORD(GetLogicalDrives()) << '\n';
  auto imploded = toReadableDWORDFunctional(GetLogicalDrives());
  std::cout << imploded << '\n';
//  GetLogicalDriveStrings

  return 0;
}