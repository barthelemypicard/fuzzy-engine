#include "Parser.hpp"
#include "StructDonnees.hpp"
#include <vector>
#include <string>
#include <iostream>

int main( int argc, const char* argv[] )
{
  // fuzzy::BaseRegles br= fuzzy::Parser::parseRegles("regles.txt");
  // fuzzy::BaseFaits  bf= fuzzy::Parser::parseFaits(br);
  //std::cout<<br;

  fuzzy::Fait f1("niveau_math", true, false, 0, "décrit le niveau en math de l'étudiant");
  fuzzy::Fait f2("niveau_physique", true, false, 0, "décrit le niveau en physique de l'étudiant");

  std::vector<std::shared_ptr<fuzzy::Fait> > vfp;
  std::vector<std::shared_ptr<fuzzy::Fait> > vfc;
  vfp.push_back(std::make_shared<fuzzy::Fait>(f1));
  vfc.push_back(std::make_shared<fuzzy::Fait>(f2));

  fuzzy::BaseFaits bf(vfp);

  fuzzy::Regle r1("R1", vfp, vfc, true, 0.9); 
  fuzzy::Regle r2("R2", vfc, vfp, true, 0.3);

  std::vector<std::shared_ptr<fuzzy::Regle> > vr;
  vr.push_back(std::make_shared<fuzzy::Regle>(r1));
  vr.push_back(std::make_shared<fuzzy::Regle>(r2));

  fuzzy::BaseRegles br(vr);
  
  
}
