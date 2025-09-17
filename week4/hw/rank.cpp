#include "rank_functions.h"
#include <iostream>

int main() {
  std::vector<driver> drivers;

  drivers = load_driver_data();
  if (drivers.empty())
    return 1;

  // TODO(student): set the rankings of the drivers using set_rankings()
  drivers = set_rankings(drivers);

  // TODO(student): print the results using print_results()
  print_results(drivers);

  return 0;
}
