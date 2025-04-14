#include "../include/lorem_ipsum.hpp"
#include <iostream>
#include <string>
#include <vector>

void print_usage()
{
  std::cout << "Usage: lorelai-cli [OPTIONS]\n"
            << "Generate Lorem Ipsum text.\n\n"
            << "Options:\n"
            << "  -w <word_count>          Generate a specific number of words.\n"
            << "  -p <paragraphs> <words>  Generate paragraphs with a specific number of words each.\n"
            << "  -h                       Show this help message.\n";
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    print_usage();
    return 1;
  }

  std::string option = argv[1];

  if (option == "-h")
  {
    print_usage();
    return 0;
  }
  else if (option == "-w" && argc == 3)
  {
    int word_count = std::stoi(argv[2]);
    std::cout << lorelai::generate(word_count) << std::endl;
  }
  else if (option == "-p" && argc == 4)
  {
    int paragraph_count = std::stoi(argv[2]);
    int words_per_paragraph = std::stoi(argv[3]);
    std::vector<std::string> paragraphs = lorelai::generate_paragraphs(paragraph_count, words_per_paragraph);
    for (const auto &paragraph : paragraphs)
    {
      std::cout << paragraph << "\n\n";
    }
  }
  else
  {
    std::cerr << "Invalid arguments.\n";
    print_usage();
    return 1;
  }

  return 0;
}