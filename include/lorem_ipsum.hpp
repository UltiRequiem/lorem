#ifndef LOREM_IPSUM_HPP
#define LOREM_IPSUM_HPP

#include <string>
#include <vector>

namespace lorelai
{
  std::string generate(int word_count);

  std::vector<std::string> generate_paragraphs(int paragraph_count, int words_per_paragraph);
}

#endif