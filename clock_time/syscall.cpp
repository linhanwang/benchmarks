#include <cstring>
#include <iostream>
#include <memory>

int main() {
  char p[20];

  std::string_view view = "hello world";
  std::memcpy(p, view.data(), view.size());

  printf("say %s\n", p);

  return 0;
}