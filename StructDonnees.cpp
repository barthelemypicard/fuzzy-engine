#include <iostream>
#include <vector>
#include <map>
#include "StructDonnees.hpp"


namespace fuzzy {
  LingVar::LingVar() {
    std::cout << "Initialisation vide de LingVar." << std::endl;
  }
  LingVar::LingVar(std::string n, std::string d) : name(n), description(d) {}
  LingVar::LingVar(std::string n, std::string d, std::vector<float> vk, std::vector<float> vv) : name(n), description(d), vec_keys(vk), vec_values(vv) {}
  LingVar::~LingVar() {}

  float LingVar::getMembershipValue(float var_val) {
    float result = 0.0;
    if (vec_keys.size() == 0 || vec_keys.size() != vec_values.size()) {
      std::cout << "Vecteurs non initiliasés, vides, ou de tailles différentes";
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

	
  Regle::Regle(std::string n, std::vector<std::shared_ptr<Fait> > p, std::vector<std::shared_ptr<Fait> >  c, bool f, float cf) : nom(n), flou(f), coeff(cf) {
  }
  Regle::~Regle() {}


  BaseRegles::BaseRegles() {}
  BaseRegles::BaseRegles(std::vector<std::shared_ptr<Regle> > regles) {
    for (auto& it: regles) {
      data.insert(std::pair<std::string, std::shared_ptr<Regle> >(it->nom, it));
    }
  }
  BaseRegles::BaseRegles(const BaseRegles& br) {
    data = br.getData();
  }
  BaseRegles& BaseRegles::operator=(const BaseRegles& br) {
    data = br.getData();
    return *this;
  }
  BaseRegles::~BaseRegles() {}
  void BaseRegles::addRegles(std::vector<std::shared_ptr<Regle> > regles) {
    for (auto& it: regles) {
      data.insert(std::pair<std::string, std::shared_ptr<Regle> >(it->nom, it));
    }
  }
  void BaseRegles::rmRegle(std::string regle) {
    data.erase(regle);
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
  
  
  bool BaseRegles::addRegle(std::shared_ptr<Regle> r){
    data.insert(std::pair<std::string, std::shared_ptr<Regle> >(r->nom, r));
  }
  
  bool Fait::evaluate(){
    //à implémenter!!
    return true;
  }
  Fait::Fait(std::string n, bool f, bool e, float c, std::string t) : nom(n), flou(f), eval(e), coeff(c), texte(t) {}
  Fait::~Fait() {}


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


}
