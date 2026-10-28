#ifndef LOREM_IPSUM_HPP
#define LOREM_IPSUM_HPP

#include <string>
#include <vector>

namespace lorelai
{
  /// Lorem Ipsum text of exactly `word_count` words, separated by single spaces.
  ///
  /// The classic 19 words repeat when more are asked for. A `word_count` of zero
  /// or less gives an empty string.
  [[nodiscard]] std::string generate(int word_count);

  /// `paragraph_count` paragraphs of `words_per_paragraph` words each, as made by `generate`.
  ///
  /// Every paragraph starts at the beginning of the text, so they are identical.
  /// A `paragraph_count` of zero or less gives an empty vector.
  [[nodiscard]] std::vector<std::string> generate_paragraphs(int paragraph_count, int words_per_paragraph);
}

#endif
