// add more includes as necessary
#include "functions.h"
#include <iostream>

// deobfuscate a sentence
// arg 1: obfuscated sentence
// arg 2: deobfuscation details
// returns the deobfuscated sentence
std::string deobfuscate(const std::string &sentence,
                        const std::string &spaces) {
  std::string result;

  size_t offset = 0;
  size_t index = 0;

  for (char c : spaces) {
    index = c - '0';

    result += sentence.substr(offset, index);
    result += " ";
    offset += index;
  }

  result.pop_back();

  return result;
}

// replace filter word with octothorpes (#)
// arg 1: sentence
// arg 2: filter word
// returns the filtered sentence
std::string wordFilter(const std::string &sentence, const std::string &filter) {
  // TODO(student)

  std::string result = sentence;

  std::string octothorpes(filter.length(), '#');

  size_t pos = sentence.find(filter);

  while (pos != std::string::npos) {
    result.replace(pos, filter.length(), octothorpes);

    pos = sentence.find(filter, pos + octothorpes.length());
  }

  return result;
}

// convert a string to a secure password
// arg 1: text
// returns a secure password based on the text
std::string passwordConverter(const std::string &) {
  // TODO(student)
  return "";
}

// calculate the result of an arithmetic expression in words
// arg 1: expression using words
// returns an arithmetic equation using numerals and arithmetic symbols
std::string wordCalculator(const std::string &) {
  // TODO(student)
  return "";
}

// count the palindromes in the text
// arg 1: text
// returns the number of palindromes in the text
unsigned int palindromeCounter(const std::string &) {
  // TODO(student)
  return 0;
}
