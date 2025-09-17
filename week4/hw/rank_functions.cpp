#include "rank_functions.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

// splits input string by any whitespace
// returns vector of substrings
inline std::vector<std::string> space_split(const std::string &input) {

  std::vector<std::string> split_strings;

  // return if input is empty
  if (input.empty())
    return split_strings;

  size_t cur_pos = 0;
  size_t last_pos = 0;

  // reassign current position on each iteration
  // push each new substring found between whitespace
  while ((cur_pos = (input + " ").find(" ", last_pos)) != std::string::npos) {

    std::string split_string = input.substr(last_pos, cur_pos - last_pos);

    // push non-empty split string to vector
    // empty split strings indicate multiple " " characters next to one another
    if (!split_string.empty())
      split_strings.push_back(split_string);

    // reassign last position + single space length
    last_pos = cur_pos + 1;
  }

  return split_strings;
};

// covert string to unsigned int
inline unsigned int stoui(const std::string &input) {
  // convert to long
  long unsigned_long = stoul(input);
  unsigned int unsigned_int = unsigned_long;

  // check for int overflow
  if (unsigned_int != unsigned_long)
    throw std::out_of_range("Value out of range for unsigned int");

  return unsigned_int;
}

inline bool is_uppercase_letter(char c) { return (c >= 'A' && c <= 'Z'); }
inline bool is_letter(char c) {
  return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

inline void validate_driver(const driver &driver) {
  // check for positive race time
  if (driver.time < 0)
    throw std::invalid_argument("Driver time must be positive.");

  // check for valid country code
  if (driver.country.length() != 3)
    throw std::invalid_argument(
        "Driver country code must be 3 characters in length.");
  // check for valid characters (uppercase letters only)
  else
    for (char c : driver.country)
      if (!is_uppercase_letter(c))
        throw std::invalid_argument(
            "Driver country code must only contain uppercase letters.");

  // check range of car number ([0, 99])
  // no need to check if less than 0 because it is unsigned (already validated
  // during conversion)
  if (driver.number > 99)
    throw std::invalid_argument("Driver car number must be in range [0, 99].");

  // check for valid last name (letters or spaces only, at least 2 letters)
  int letter_count = 0;
  for (char c : driver.lastname) {
    // count letters
    if (is_letter(c))
      letter_count++;
    // validate char type
    else if (c != ' ')
      throw std::invalid_argument(
          "Driver last name must only contain letters or spaces.");
  }
  if (letter_count < 2)
    throw std::invalid_argument(
        "Driver last name must contain at least 2 letters.");
}

// load data from standard input into a vector
//   input format := <time> <country> <number> <name>
//   examples:
//     32.7 AUS 81 Piastri
//     36.5 NED 1  Verstappen
//   rank should be initialized to 0 for each driver
// returns a vector of drivers, or an empty vector if any input is invalid
std::vector<driver> load_driver_data() {

  try {

    std::string current_line;
    std::vector<std::string> lines;

    while (std::getline(std::cin, current_line))
      // if next line is empty break out of loop
      if (current_line.empty())
        break;
      // else push non-empty lines into lines vector
      else
        lines.push_back(current_line);

    std::vector<driver> drivers;

    // parse lines, validate driver info, and push structs to drivers vector
    for (std::string line : lines) {
      std::vector<std::string> driver_props = space_split(line);

      // account for spaces in name
      if (driver_props.size() > 4) {
        driver_props.at(3) += (" " + driver_props.at(4));
      }

      driver cur_driver = {
          driver_props.at(3),        // lastname
          driver_props.at(1),        // country
          stoui(driver_props.at(2)), // number
          stod(driver_props.at(0)),  // time
          0                          // rank
      };

      // validate driver (throws invalid_argument)
      validate_driver(cur_driver);

      drivers.push_back(cur_driver);
    }

    return drivers;

  } catch (std::exception &e) {
    std::cout << "Bad input" << std::endl;
    return {};
  }
}

// returns a copy of the input vector with ranks set based on the time for
// each driver.
//   the fastest/minimum time is ranked 1
// the order of the elements in the vector should not be changed
std::vector<driver> set_rankings(std::vector<driver> drivers) {
  // vector of driver times
  std::vector<double> driver_times;

  // populate vector
  for (const driver &driver : drivers)
    driver_times.push_back(driver.time);

  // bubble sort
  for (size_t i = 0; i < driver_times.size(); i++) {
    for (size_t j = 0; j < driver_times.size() - i - 1; j++) {
      // if driver times are out of order (longer -> shorter) swap
      if (driver_times.at(j) > driver_times.at(j + 1)) {
        double temp_time = driver_times.at(j);

        driver_times.at(j) = driver_times.at(j + 1);
        driver_times.at(j + 1) = temp_time;
      }
    }
  }

  // update ranks based on sorted times
  for (driver &driver : drivers) {
    for (size_t i = 0; i < driver_times.size(); i++) {
      double time = driver_times.at(i);

      if (driver.time == time)
        driver.rank = i + 1;
    }
  }

  return drivers;
}

std::string trim(std::string s) {
  // any sort of whitespace (tab, newline, spaces, etc)
  const char *whitespace = " \t\n\r\f\v";
  size_t begin = s.find_first_not_of(whitespace);
  // if no string content is found (content != whitespace) return empty string
  if (begin == std::string::npos) {
    return std::string{}; // empty string (not equivalent to "")
  }

  // find last index of content before whitespace
  // used to compute length for substr
  size_t end = s.find_last_not_of(whitespace);
  // substr!
  return s.substr(begin, end - begin + 1);
};

// print the results of the race
void print_results(const std::vector<driver> &drivers) {
  // get the fastest time
  double best_time;
  for (const driver &driver : drivers) {
    if (driver.rank == 1) {
      best_time = driver.time;
      break;
    }
  }

  std::cout << "Final results!";
  std::cout << std::setprecision(2) << std::showpoint << std::fixed
            << std::endl;
  for (unsigned rank = 1; rank <= drivers.size(); rank++) {
    for (const driver &driver : drivers) {
      if (driver.rank == rank) {
        std::string rank_str = "[" + std::to_string(rank) + "]";
        std::cout << std::setw(4) << std::left << rank_str << " " << driver.time
                  << " " << std::setw(15) << std::left << driver.lastname
                  << " (" << driver.country << ") +"
                  << (driver.time - best_time) << std::endl;
      }
    }
  }
}
