#include "lorem_ipsum.hpp"

#include <cerrno>
#include <cstdlib>
#include <iostream>
#include <string>

namespace
{
  void print_usage(std::ostream &out)
  {
    out << "Usage: lorelai-cli [OPTIONS]\n"
        << "Generate Lorem Ipsum text.\n\n"
        << "Options:\n"
        << "  -w <word_count>          Generate a specific number of words.\n"
        << "  -p <paragraphs> <words>  Generate paragraphs with a specific number of words each.\n"
        << "  -h, --help               Show this help message.\n";
  }

  // Parses a whole non-negative number, so "12abc", "-3" and "" are rejected instead of crashing.
  bool parse_count(const char *text, int &out)
  {
    char *end = nullptr;
    errno = 0;
    const long value = std::strtol(text, &end, 10);
    if (end == text || *end != '\0' || errno == ERANGE || value < 0 || value > 10000000)
      return false;
    out = static_cast<int>(value);
    return true;
  }

  int invalid(const std::string &message)
  {
    std::cerr << "lorelai-cli: " << message << "\n\n";
    print_usage(std::cerr);
    return 1;
  }
}

int main(int argc, char *argv[])
{
  if (argc < 2)
    return invalid("missing option");

  const std::string option = argv[1];

  if (option == "-h" || option == "--help")
  {
    print_usage(std::cout);
    return 0;
  }

  if (option == "-w" && argc == 3)
  {
    int word_count = 0;
    if (!parse_count(argv[2], word_count))
      return invalid("the word count must be a whole number from 0 to 10000000");

    std::cout << lorelai::generate(word_count) << '\n';
    return 0;
  }

  if (option == "-p" && argc == 4)
  {
    int paragraph_count = 0;
    int words_per_paragraph = 0;
    if (!parse_count(argv[2], paragraph_count) || !parse_count(argv[3], words_per_paragraph))
      return invalid("paragraphs and words must be whole numbers from 0 to 10000000");

    for (const auto &paragraph : lorelai::generate_paragraphs(paragraph_count, words_per_paragraph))
      std::cout << paragraph << "\n\n";
    return 0;
  }

  return invalid("invalid arguments");
}
