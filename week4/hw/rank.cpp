#include "rank_functions.h"
#include <iostream>

int main() {
  try {
    std::vector<driver> drivers = load_driver_data();
  } catch (std::exception &e) {
    std::cout << "Bad input" << std::endl;
    return 1;
  }

  // TODO(student): set the rankings of the drivers using set_rankings()

  // TODO(student): print the results using print_results()

  return 0;
}
