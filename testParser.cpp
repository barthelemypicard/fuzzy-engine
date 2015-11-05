#include "Parser.hpp"
#include "StructDonnees.hpp"
#include <vector>
#include <string>

int main( int argc, const char* argv[] )
{
  fuzzy::Parser mon_parser;
  std::vector<fuzzy::Regle> tab= mon_parser.parse("regles.txt");
}
