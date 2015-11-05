#include <iostream>
#include <vector>
#include <map>

#include "StructDonnees.hpp"


namespace fuzzy {
	LingVar::LingVar() {
		std::cout << "Initialisation vide de LingVar." << std::endl;
	}
	LingVar::LingVar(std::string n, std::string d, VarType vt) : name(n), description(d), var_type(vt) {}
	LingVar::LingVar(std::string n, std::string d, std::vector<float> vk, std::vector<float> vv) : name(n), description(d), vec_keys(vk), vec_values(vv) {
		var_type 	= VarType::VECTOR;
	}
	LingVar::~LingVar() {}

	float LingVar::getMembershipValue(float var_val) {
		float result = 0.0;
		switch (var_type) {
			case VECTOR: {	if (vec_keys.size() == 0 || vec_keys.size() != vec_values.size()) {
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
								break;
			}

			default: 		std::cout << "Cas non implémenté" << std::endl;
		}

		return result;
	}

	
	Regle::Regle(std::string n, std::vector<std::pair<std::string, std::string> > p, std::pair<std::string, std::string> c, bool f, float cf) : nom(n), flou(f), coeff(cf) {
	}
	Regle::~Regle() {}


	BaseRegles::BaseRegles() {}
	BaseRegles::BaseRegles(std::vector<Regle> regles) {
		for (auto& it: regles) {
			data.insert(std::pair<std::string, Regle>(it.nom, it));
		}
	}
	BaseRegles::~BaseRegles() {}
	void BaseRegles::addRegles(std::vector<Regle> regles) {
		for (auto& it: regles) {
			data.insert(std::pair<std::string, Regle>(it.nom, it));
		}
	}
	void BaseRegles::rmRegle(std::string regle) {
		data.erase(regle);
	}
	Regle BaseRegles::get(const std::string& nom) const {
		return data.at(nom);
	}
	Regle BaseRegles::operator()(const std::string& nom) const {
		return get(nom);
	}


	Fait::Fait() {}
	Fait::~Fait() {}
}
