#include "Parser.hpp"
#include "StructDonnees.hpp"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>

void fuzzy::Parser::parseFaits_secondPass(fuzzy::BaseFaits& bf, const fuzzy::BaseRegles& br){
  //itérer sur les regles:
  for( auto it : br.getData()){ //itération sur la map de regles
    for( auto it2 : (it.second)->prem){ //itération sur les premisses de la règle courante
      (bf.get(it2->nom)->prem).push_back(it.second);//ajout de la règle dans le tableau des premisses du fait
    }
    for( auto it2 : (it.second)->concl){ //itération sur les conclusions de la règle courante
      (bf.get(it2->nom)->concl).push_back(it.second);//ajout de la règle dans le tableau des conclusions du fait
    }
  }
}

fuzzy::BaseFaits fuzzy::Parser::parseFaits_firstPass(std::string filename, int n){
  fuzzy::BaseFaits bf;
  std::vector<std::shared_ptr<fuzzy::Fait> > vf;
  std::string tmp;

  std::ifstream fichier(filename);
  if(fichier){
    
    int i=1;
    do{//boucle sur les regles
       getline(fichier, tmp);
       std::cout<<i<<std::endl;
       i++;
      std::cout<<"nom: "<<tmp<<std::endl;
      fichier>>tmp;//lecture de l'opérateur
      std::cout<<"Opéateur: "<<tmp<<std::endl;
       do{
       	fichier>>tmp;//lecture du fait
       	std::cout<<"Fait: "<<tmp<<std::endl;
       	for(auto& i : vf){ //ajout s'il n'est pas présent dans la base
       	  if(i->nom==tmp){
      	    tmp="";
      	    break;
      	  }
      	}
      	if(tmp!=""){
      	  vf.push_back(std::make_shared<fuzzy::Fait>(fuzzy::Fait(tmp, true, false, 0, "default text")));
      	  std::cout<<"ajout fait: "<<tmp<<std::endl;
      	}
      	else{
      	  std::cout<<"Fait déjà présent"<<std::endl;
      	}
       	fichier>>tmp;//lecture de la variable linguistique
       	std::cout<<"variable linguistique associée: "<<tmp<<std::endl;
       	vf.back()->value=LingVar(tmp,"description par defaut");
       	fichier>>tmp;//lecture de l'opérateur suivant
       	std::cout<<"opérateur: "<<tmp<<std::endl; 
       }while(tmp!="Certitude");
       fichier>>tmp;//récupération de la valeur de la certitude
       std::cout<<"valeur de certitude: "<<tmp<<std::endl;
       getline(fichier, tmp);
       getline(fichier, tmp);
    }while(i<n+1);
    bf.addFaits(vf);
    return bf;
  }
  else{
    std::cout<<"Parsing des faits premiere passe: ouverture fichier impossible"<<std::endl;
    return fuzzy::BaseFaits();
  }
}




fuzzy::BaseRegles fuzzy::Parser::parseRegles(std::string filename, int n){
  std::ifstream fichier(filename);
  std::vector<std::shared_ptr<fuzzy::Regle> > vr;
  std::string tmp;
  int i=1;
  while(i<n+1){
    getline(fichier, tmp);
    std::vector<std::shared_ptr<fuzzy::Fait> > v;//inutile mais nécessaire...
    fuzzy::Regle r(tmp, v, v, true, (float)0.0);
    std::cout<<"Regle: "<<tmp<<std::endl;
    fichier>>tmp;
    std::cout<<"Premisses:"<<std::endl;
    while(tmp!="Alors"){
      fichier>>tmp;
      fuzzy::Fait f(tmp, true, false, 0, "default text");
      std::cout<<tmp<<std::endl;
      fichier>>tmp;
      f.value=fuzzy::LingVar(tmp, "default description");
      std::cout<<tmp<<std::endl;
      r.prem.push_back(std::make_shared<fuzzy::Fait>(f));
      fichier>>tmp;
    }
    std::cout<<"Conclusions:"<<std::endl;
    while(tmp!="Certitude"){
      fichier>>tmp;
      std::cout<<tmp<<std::endl;
      fuzzy::Fait f(tmp, true, false, 0, "default text");
      fichier>>tmp;
      std::cout<<tmp<<std::endl;
      f.value=fuzzy::LingVar(tmp, "default description");
      r.concl.push_back(std::make_shared<fuzzy::Fait>(f));
      fichier>>tmp;
    }
    fichier>>tmp;
    r.coeff=std::stof(tmp);
    std::cout<<"Coeff: "<<tmp<<std::endl;
    getline(fichier, tmp);
    getline(fichier, tmp);
    i++;
    vr.push_back(std::make_shared<fuzzy::Regle>(r));
  }
  return fuzzy::BaseRegles(vr);
}

void fuzzy::Parser::parseFaits_bulletin(const std::string filename, fuzzy::BaseFaits& bf){
  std::ifstream fichier(filename);
  std::string tmp="init";
  if(fichier){
    while(fichier>>tmp){ //on boucle sur les lignes jusqu'à la fin du fichier
      try{
	std::shared_ptr<fuzzy::Fait> p=bf.get(tmp);
	std::cout<<"Fait déja présent"<<std::endl;
	p->eval=true;
	fichier>>tmp;
	p->value=fuzzy::LingVar("TB", "default description");
	fichier>>tmp;
	p->coeff=stof(tmp);
	std::cout<<"evaluation faite"<<std::endl;
      }
      catch(const std::out_of_range& oor){
	std::vector<std::shared_ptr<fuzzy::Fait> >v;
	fuzzy::Fait f(tmp, true, true, 0, "default text");
	fichier>>tmp;
	f.value=fuzzy::LingVar(tmp, "default description");
	fichier>>tmp;
	f.coeff=stof(tmp);
	v.push_back(std::make_shared<fuzzy::Fait>(f));
	bf.addFaits(v);
	std::cout<<"Fait ajouté à la base"<<std::endl<<"evaluation faite"<<std::endl;
      }
    }
  }
  else{
    std::cout<<"Ouverture fichier bulletin impossible!"<<std::endl;
  }
}


