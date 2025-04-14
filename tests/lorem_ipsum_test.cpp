#include "../include/lorem_ipsum.hpp"

#include <iostream>
#include <cassert>

void test_generate()
{
  std::string result = lorelai::generate(5);
  std::cout << "test_generate passed!\n";
}

void test_generate_paragraphs()
{
  auto paragraphs = lorelai::generate_paragraphs(2, 5);

  assert(paragraphs.size() == 2);

  std::cout << "test_generate_paragraphs passed!\n";
}

int main()
{
  test_generate();
  test_generate_paragraphs();
  return 0;
}