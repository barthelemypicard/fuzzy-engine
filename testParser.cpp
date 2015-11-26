#include "Parser.hpp"
#include "StructDonnees.hpp"
#include <vector>
#include <string>
#include <iostream>

int main( int argc, const char* argv[] )
{
  fuzzy::BaseRegles br= fuzzy::Parser::parseRegles("regles.txt");
  fuzzy::BaseFaits  bf= fuzzy::Parser::parseFaits(br);
  //std::cout<<br;
}
