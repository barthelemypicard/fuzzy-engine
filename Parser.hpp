#pragma once
#include "StructDonnees.hpp"
#include <vector>
#include <string>

namespace fuzzy{
  class Parser{

  public:
    static BaseRegles parseRegles(const std::string fileName);
    static BaseFaits parseFaits(const BaseRegles& br);
  };
}
