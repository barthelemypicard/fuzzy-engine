#pragma once
#include "StructDonnees.hpp"
#include <vector>
#include <string>

namespace fuzzy{
  class Parser{
  public:
    static BaseFaits parseFaits_firstPass(const std::string filename, int n);
    static BaseRegles parseRegles(std::string filename, int n);
    static void parseFaits_secondPass(BaseFaits& bf, const BaseRegles& br);
    static void parseFaits_bulletin(const std::string filename, BaseFaits& bf); 
  };
}
