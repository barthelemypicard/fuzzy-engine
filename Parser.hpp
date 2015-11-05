#pragma once
#include "StructDonnees.hpp"
#include <vector>
#include <string>

namespace fuzzy{
  class Parser{
  private:
    std::vector<Regle> tableau_regle;
  public:
    std::vector<Regle> parse(std::string fileName);
  };
}
