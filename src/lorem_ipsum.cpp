#include "lorem_ipsum.hpp"

#include <array>
#include <cstddef>
#include <string_view>

namespace lorelai
{
  namespace
  {
    constexpr std::array<std::string_view, 19> LOREM_WORDS = {
        "lorem", "ipsum", "dolor", "sit", "amet", "consectetur",
        "adipiscing", "elit", "sed", "do", "eiusmod", "tempor",
        "incididunt", "ut", "labore", "et", "dolore", "magna", "aliqua"};
  }

  std::string generate(int word_count)
  {
    std::string text;

    for (int i = 0; i < word_count; ++i)
    {
      if (i > 0)
        text += ' ';
      text += LOREM_WORDS[static_cast<std::size_t>(i) % LOREM_WORDS.size()];
    }

    return text;
  }

  std::vector<std::string> generate_paragraphs(int paragraph_count, int words_per_paragraph)
  {
    std::vector<std::string> paragraphs;

    for (int i = 0; i < paragraph_count; ++i)
    {
      paragraphs.push_back(generate(words_per_paragraph));
    }

    return paragraphs;
  }
}
