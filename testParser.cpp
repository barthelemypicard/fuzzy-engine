#include "Parser.hpp"
#include "StructDonnees.hpp"
#include <vector>
#include <string>
#include <iostream>

int main( int argc, const char* argv[] )
{
  /////Test d'instanciation des fait, regle et base associée.////

  // fuzzy::Fait f1("niveau_math", true, false, 0, "décrit le niveau en math de l'étudiant");
  // fuzzy::Fait f2("niveau_physique", true, false, 0, "décrit le niveau en physique de l'étudiant");

  // std::vector<std::shared_ptr<fuzzy::Fait> > vfp;
  // std::vector<std::shared_ptr<fuzzy::Fait> > vfc;
  // vfp.push_back(std::make_shared<fuzzy::Fait>(f1));
  // vfc.push_back(std::make_shared<fuzzy::Fait>(f2));

  // fuzzy::BaseFaits bf(vfp);

  // fuzzy::Regle r1("R1", vfp, vfc, true, 0.9); 
  // fuzzy::Regle r2("R2", vfc, vfp, true, 0.3);

  // std::vector<std::shared_ptr<fuzzy::Regle> > vr;
  // vr.push_back(std::make_shared<fuzzy::Regle>(r1));
  // vr.push_back(std::make_shared<fuzzy::Regle>(r2));

  // fuzzy::BaseRegles br(vr);
  

  ////Test parser////
  fuzzy::BaseFaits listeFaits;//ensemble des faits évaluables selon le fichier regles.txt
  fuzzy::BaseRegles regles;//ensemble des règles du fichier regles.txt
  
  
  listeFaits=fuzzy::Parser::parseFaits_firstPass("regles.txt", 70); 
               //ensemble des faits évaluables selon le fichier regles.txt
               //Attention ici les fait de la base ne sont pas reliés à des règles
  
  regles=fuzzy::Parser::parseRegles("regles.txt", 70);
               //ensemble des règles du fichier regles.txt
               //Création de faits de référence pour regles

  fuzzy::Parser::parseFaits_secondPass(listeFaits, regles);
               //remplissages des prémisses et conclusions des faits de listeFait 
               //avec les regles de regles
  fuzzy::Parser::parseFaits_bulletin("bulletin.txt", listeFaits);
}
