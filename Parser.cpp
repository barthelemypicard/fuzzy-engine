#include "Parser.hpp"
#include "StructDonnees.hpp"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>

std::vector<fuzzy::Regle> fuzzy::Parser::parse(std::string filename){
  std::ifstream fichier("regles.txt");
  if(fichier){
    std::string nom;
    std::string prem_p1, prem_p2;
    std::vector< std::pair<std::string, std::string> > premisses;
    std::pair<std::string, std::string> conclusion;
    bool est_floue;
    float coeff;
    
    std::getline(fichier,nom);
    fichier>>prem_p1;
    while(prem_p1!="Alors"){
      fichier>>prem_p1;
      fichier>>prem_p2;
      premisses.push_back(std::pair<std::string, std::string>(prem_p1, prem_p2));
    }
    fichier>>prem_p1;
    fichier>>prem_p2;
    conclusion= std::pair<std::string, std::string>(prem_p1, prem_p2);
    fichier>>prem_p1;
    fichier>>coeff;
    est_floue=true;

    tableau_regles.push_back(Regle(nom, premisses, conclusion, est_floue, coeff));
  }
  else{
    std::cout<<"Erreur: fichier impossible à ouvrir"<<std::endl;
  }
  return tableau_regles;
}
