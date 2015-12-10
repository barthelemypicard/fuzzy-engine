#include "Parser.hpp"
#include "StructDonnees.hpp"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>

// fuzzy::BaseRegles fuzzy::Parser::parseRegles(const std::string filename, fuzzy::BaseFaits& bf){
//   std::ifstream fichier(filename);
//   if(fichier){
//     std::string tmp;
//     fuzzy::BaseRegles br;
//     fuzzy::Regle r;
//     while(getline(fichier, r.nom)){//boucle sur les regles
//     //   fichier.ignore();
//     //   fichier>>tmp;//lecture de l'opérateur
//     //   do{
//     // 	fichier>>tmp;//lecture du fait
//     // 	for(auto& i : bf.data){ //recherche du fait dans la base de faits
//     // 	  if(i.first==tmp){
//     // 	    (r.prem).push_back(make_shared(i))
//     // 	    break;
//     // 	  }
//     // 	}

//     // 	if(tmp!=""){//retour écran en cas d'erreur
//     // 	  std::cout<<"extaction fait: "<<tmp<<"impossible"<<std::endl;
//     // 	}
//     // 	fichier>>tmp;//lecture de la variable linguistique
//     // 	fichier>>tmp;//lecture de l'opérateur suivant
//     //   }while(tmp!="Alors");
//     //   std::cout<<std::endl;
//     // }
//     return br;
//   }
//   else{
//     std::cout<<"Parsing des regles: ouverture fichier impossible"<<std::endl;
//     return fuzzy::BaseRegles();
//   }
// }

// fuzzy::BaseFaits fuzzy::Parser::parseFaits_firstPass(std::string filename){
//   fuzzy::BaseFaits bf;
//   std::vector<fuzzy::Fait> vf;
//   std::string tmp;

//   std::ifstream fichier(filename);
//   if(fichier){
//     while(getline(fichier, tmp)){//boucle sur les regles
//     //   fichier.ignore();
//     //   std::cout<<"Regle: "<<tmp<<std::endl;
//     //   fichier>>tmp;//lecture de l'opérateur
//     //   do{
//     // 	fichier>>tmp;//lecture du fait
//     // 	for(auto& i : vf){ //ajout s'il n'est pas présent dans la base
//     // 	  if(i.nom==tmp){
//     // 	    tmp="";
//     // 	    break;
//     // 	  }
//     // 	}
//     // 	if(tmp!=""){
//     // 	  vf.push_back(fuzzy::Fait(tmp, true, false, 0, "default text"));
//     // 	  std::cout<<"extaction fait: "<<tmp<std::endl;
//     // 	}
//     // 	fichier>>tmp;//lecture de la variable linguistique
//     // 	vf.back().value=LingVar("TB", "niveau scolaire", 
//     // 	fichier>>tmp;//lecture de l'opérateur suivant
//     //   }while(tmp!="Certitude");
//     //   std::cout<<std::endl;
//     // }
//     // bf.addFaits(vf);
//     return bf;
//   }
//   else{
//     std::cout<<"Parsing des faits premiere passe: ouverture fichier impossible"<<std::endl;
//     return fuzzy::BaseFaits();
//   }
// }

// fuzzy::BaseFaits fuzzy::Parser::ParseFaits_secondPass(fuzzy::BaseRegles br, fuzzy::BaseFaits bf_1){
//   return fuzzy::BaseFaits();
// }

