#include "lorem_ipsum.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Plain checks instead of assert(), which is compiled out in release builds.
static int failures = 0;

#define CHECK(condition)                                                    \
  do                                                                        \
  {                                                                         \
    if (!(condition))                                                       \
    {                                                                       \
      std::cerr << __FILE__ << ":" << __LINE__ << ": CHECK(" #condition ") failed\n"; \
      ++failures;                                                           \
    }                                                                       \
  } while (false)

static std::vector<std::string> words_of(const std::string &text)
{
  std::vector<std::string> words;
  std::istringstream stream(text);
  std::string word;
  while (stream >> word)
    words.push_back(word);
  return words;
}

static void test_generate_has_the_requested_number_of_words()
{
  for (int count : {1, 2, 5, 19, 20, 38, 100, 1000})
    CHECK(words_of(lorelai::generate(count)).size() == static_cast<std::size_t>(count));
}

static void test_generate_starts_with_the_classic_text()
{
  CHECK(lorelai::generate(1) == "lorem");
  CHECK(lorelai::generate(3) == "lorem ipsum dolor");
  CHECK(lorelai::generate(5) == "lorem ipsum dolor sit amet");
}

static void test_generate_cycles_through_the_words()
{
  const auto words = words_of(lorelai::generate(20));
  CHECK(words[18] == "aliqua");
  CHECK(words[19] == "lorem");
}

static void test_generate_has_no_stray_spaces()
{
  const std::string text = lorelai::generate(30);
  CHECK(!text.empty());
  CHECK(text.front() != ' ' && text.back() != ' ');
  CHECK(text.find("  ") == std::string::npos);
}

static void test_zero_and_negative_word_counts_are_empty()
{
  CHECK(lorelai::generate(0).empty());
  CHECK(lorelai::generate(-1).empty());
  CHECK(lorelai::generate(-1000).empty());
}

static void test_generate_paragraphs()
{
  const auto paragraphs = lorelai::generate_paragraphs(3, 7);
  CHECK(paragraphs.size() == 3);
  for (const auto &paragraph : paragraphs)
    CHECK(words_of(paragraph).size() == 7);
  CHECK(paragraphs[0] == lorelai::generate(7));
}

static void test_zero_and_negative_paragraph_counts_are_empty()
{
  CHECK(lorelai::generate_paragraphs(0, 5).empty());
  CHECK(lorelai::generate_paragraphs(-2, 5).empty());
}

static void test_empty_paragraphs()
{
  const auto paragraphs = lorelai::generate_paragraphs(2, 0);
  CHECK(paragraphs.size() == 2);
  CHECK(paragraphs[0].empty() && paragraphs[1].empty());
}

static void test_large_output()
{
  CHECK(words_of(lorelai::generate(200000)).size() == 200000);
}

int main()
{
  test_generate_has_the_requested_number_of_words();
  test_generate_starts_with_the_classic_text();
  test_generate_cycles_through_the_words();
  test_generate_has_no_stray_spaces();
  test_zero_and_negative_word_counts_are_empty();
  test_generate_paragraphs();
  test_zero_and_negative_paragraph_counts_are_empty();
  test_empty_paragraphs();
  test_large_output();

  if (failures != 0)
  {
    std::cerr << failures << " check(s) failed\n";
    return 1;
  }

  std::cout << "all checks passed\n";
  return 0;
}
