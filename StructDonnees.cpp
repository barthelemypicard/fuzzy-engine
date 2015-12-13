#include <iostream>
#include <vector>
#include <map>
#include "StructDonnees.hpp"


namespace fuzzy {

  ///////LINGVAR////////
  LingVar::LingVar() {
    std::cout << "Initialisation vide de LingVar." << std::endl;
  }
  LingVar::LingVar(std::string n, std::string d) : name(n), description(d) {}

  LingVar::LingVar(std::string n, std::string d, std::vector<float> vk, std::vector<float> vv) 
    : name(n), description(d), vec_keys(vk), vec_values(vv) {}

  LingVar::~LingVar() {}

  float LingVar::getMembershipValue(float var_val) {
    float result = 0.0;
    if (vec_keys.size() == 0 || vec_keys.size() != vec_values.size()) {
      std::cout << "Failed to evaluate LingVar : " << ((vec_keys.size() == 0) ? "Not initialized" : "vec_keys and vec_values have difference size") << std::endl;
      // std::cout << "Vecteurs non initiliasés, vides, ou de tailles différentes";
      return result;
    }
    result = vec_values[0]; 
    auto val_it = vec_values.rbegin();
    for (auto key_it = vec_keys.rbegin(); key_it != vec_keys.rend(); key_it++) {
      if (var_val >= *key_it) {
	result = *val_it;
	break;
      }
      val_it++;
    }
    return result;
  }

  ////////REGLES/////////
  Regle::Regle(std::string n, std::vector<std::shared_ptr<Fait> > p, std::vector<std::shared_ptr<Fait> >  c, bool f, float cf) 
    : nom(n), prem(p), concl(c), flou(f), coeff(cf) {} //constructeur ave argumets

  Regle::~Regle() {} //destructeur par défaut

  ///////BaseRegles/////////
  BaseRegles::BaseRegles() {} //constructeur pa défaut

  BaseRegles::BaseRegles(const BaseRegles& br) : data(br.getData()) {}//constucteur par recopie

  BaseRegles& BaseRegles::operator=(const BaseRegles& br) { //surcharge de l'opérateur =
    data = br.getData();
    return *this;
  }

  BaseRegles::BaseRegles(BaseRegles&& br) : data(br.getData()) {} //constructeur par copie de référence

  BaseRegles& BaseRegles::operator=(BaseRegles&& br) { ////surcharge de l'opérateur = par référence
    data = br.getData();
    return *this;
  }
  BaseRegles::~BaseRegles() {} //destructeur par défaut

  void BaseRegles::rmRegle(std::string regle) {
    data.erase(regle);
  }


  BaseRegles::BaseRegles(std::vector<std::shared_ptr<Regle> > regles) { //constructeur par tableau de règles
    for (auto& it: regles) {
      data.insert(std::pair<std::string, std::shared_ptr<Regle> >(it->nom, it));
    }
  }



  void BaseRegles::addRegles(std::vector<std::shared_ptr<Regle> > regles) {
    for (auto& it: regles) {
      data.insert(std::pair<std::string, std::shared_ptr<Regle> >(it->nom, it));
    }
  }

  std::shared_ptr<Regle> BaseRegles::get(const std::string& nom) const {
    return data.at(nom);
  }
  std::shared_ptr<Regle> BaseRegles::operator()(const std::string& nom) const {
    return get(nom);
  }
  std::map<std::string, std::shared_ptr<Regle> > BaseRegles::getData() const {
    return data;
  }
  
  
  void BaseRegles::addRegle(std::shared_ptr<Regle> r){
    data.insert(std::pair<std::string, std::shared_ptr<Regle> >(r->nom, r));
  }
  
  bool Fait::evaluate(){
    eval = true;
    return true;
  }

  //// Faits//////
  Fait::Fait(const std::string n, bool f, bool e, float c, std::string t) : nom(n), flou(f), eval(e), coeff(c), texte(t) {}
  Fait::~Fait() {}

  
  ///BaseFaits////
  BaseFaits::BaseFaits() {}

  BaseFaits::BaseFaits(std::vector<std::shared_ptr<Fait> > faits) {
    for (auto& it: faits) {
      data.insert(std::pair<std::string, std::shared_ptr<Fait> >(it->nom, it));
    }
  }

  BaseFaits::~BaseFaits() {}

  void BaseFaits::addFaits(std::vector<std::shared_ptr<Fait> > faits) {
    for (auto& it: faits) {
      data.insert(std::pair<std::string, std::shared_ptr<Fait> >(it->nom, it));
    }
  }

  void BaseFaits::rmFait(std::string fait) {
    data.erase(fait);
  }

  std::shared_ptr<Fait> BaseFaits::get(const std::string& nom) const {
    return data.at(nom);
  }

  std::shared_ptr<Fait> BaseFaits::operator()(const std::string& nom) const {
    return get(nom);
  }

 
  BaseFaits::BaseFaits(const BaseFaits& bf) : data(bf.getData()) {}

  BaseFaits& BaseFaits::operator=(const BaseFaits& bf) {
    data = bf.getData();
    return *this;
  }

  BaseFaits::BaseFaits(BaseFaits&& bf) : data(bf.getData()) {}

  BaseFaits& BaseFaits::operator=(BaseFaits&& bf) {
    data = bf.getData();
    return *this;
  }

  std::map<std::string, std::shared_ptr<Fait> > BaseFaits::getData() const {
    return data;
  }



  // std::ostream& operator<<(std::ostream& os, const BaseRegles& br) {
  //   for (auto& it: br.data) {
  //     os << it->second.nom << ": Si ";
			
  //     for (auto& it_vec: it->second->prem) {
  // 	// os << "(" << it_vec.first->nom << ", ";
  // 	// os << it_vec.second->name << ")" << " et ";
  //     }
  //     os << " alors ";
  //     // os << "(" << it.second.concl.first->nom; 
  //     // os << ", " << it.second.concl.second->name;
  //     os << ")" << std::endl;
  //     os << "Flou: " << it.second.flou ? "true" : "false";
  //     os << std::endl;
  //     os << "Coeff: " << it.second.coeff << std::endl << std::endl; 
  //   }

  //   return os; 
  // }	
  // std::ostream& operator<<(std::ostream& os, const BaseFaits& c);
  
}
