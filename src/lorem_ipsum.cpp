#include "lorem_ipsum.hpp"
#include <vector>
#include <string>
#include <sstream>

using std::string, std::vector, std::ostringstream;

namespace lorelai
{
  const vector<string> LOREM_WORDS = {
      "lorem", "ipsum", "dolor", "sit", "amet", "consectetur",
      "adipiscing", "elit", "sed", "do", "eiusmod", "tempor",
      "incididunt", "ut", "labore", "et", "dolore", "magna", "aliqua"};

  string generate(int word_count)
  {
    ostringstream oss;

    for (int i = 0; i < word_count; ++i)
    {
      if (i > 0)
        oss << " ";
      oss << LOREM_WORDS[i % LOREM_WORDS.size()];
    }

    return oss.str();
  }

  vector<string> generate_paragraphs(int paragraph_count, int words_per_paragraph)
  {
    vector<string> paragraphs;

    for (int i = 0; i < paragraph_count; ++i)
    {
      paragraphs.push_back(generate(words_per_paragraph));
    }

    return paragraphs;
  }
}