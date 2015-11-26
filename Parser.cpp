#include "Parser.hpp"
#include "StructDonnees.hpp"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>

fuzzy::BaseRegles fuzzy::Parser::parseRegles(const std::string filename){
  std::ifstream fichier(filename);
  if(fichier){
    fuzzy::BaseRegles br;
    std::vector<fuzzy::Regle> tr;

    std::string prem, varLing;
    std::string nom;
    std::vector< std::pair<std::string, std::string> > premisses;
    std::pair<std::string, std::string> conclusion;
    bool est_floue;
    float coeff;

    while(getline(fichier, nom)){
      fichier.ignore();
      while(fichier>>
      fichier>>;
      fichier>>prem;
      fichier>>varLing;
      tr.pushBack(Regle(temp, premisses, conclusion, est_floue, coeff));
    }
    br.addRegles(tr);


    
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
  return br;
}

fuzzy::BaseFaits fuzzy::Parser::parseFaits(const fuzzy::BaseRegles& br){

  return BaseFaits bf();
}

