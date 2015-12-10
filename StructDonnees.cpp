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


	Regle::Regle() {}	
	Regle::Regle(std::string n, std::vector<std::pair<std::string, std::string> > p, std::pair<std::string, std::string> c, bool f, float cf) : nom(n), flou(f), coeff(cf) {
	}
	Regle::~Regle() {}


	BaseRegles::BaseRegles() {}
	BaseRegles::BaseRegles(std::vector<Regle> regles) {
		for (auto& it: regles) {
			data.insert(std::pair<std::string, Regle>(it.nom, it));
		}
	}
	BaseRegles::BaseRegles(const BaseRegles& br) : data(br.getData()) {}
	BaseRegles& BaseRegles::operator=(const BaseRegles& br) {
		data = br.getData();
		return *this;
	}
	BaseRegles::BaseRegles(BaseRegles&& br) : data(br.getData()) {}
	BaseRegles& BaseRegles::operator=(BaseRegles&& br) {
		data = br.getData();
		return *this;
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
	std::map<std::string, Regle> BaseRegles::getData() const {
		return data;
	}

	
	Fait::Fait() {}
	Fait::Fait(std::string n, bool f, bool e, float c, std::string t) : nom(n), flou(f), eval(e), coeff(c), texte(t) {}
	Fait::~Fait() {}
	void Fait::setEval(bool e) { std::cout << eval; eval = e; std::cout << eval << std::endl;}
	void Fait::setCoeff(float c) { coeff = c; }

	BaseFaits::BaseFaits() {}
	BaseFaits::BaseFaits(std::vector<Fait> faits) {
		for (auto& it: faits) {
			data.insert(std::pair<std::string, Fait>(it.nom, it));
		}
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
	BaseFaits::~BaseFaits() {}
	void BaseFaits::addFaits(std::vector<Fait> faits) {
		for (auto& it: faits) {
			data.insert(std::pair<std::string, Fait>(it.nom, it));
		}
	}
	void BaseFaits::rmFait(std::string fait) {
		data.erase(fait);
	}
	Fait BaseFaits::get(const std::string& nom) {
		return data.at(nom);
	}
	Fait BaseFaits::operator()(const std::string& nom) {
		return get(nom);
	}
	std::map<std::string, Fait> BaseFaits::getData() const {
		return data;
	}



	std::ostream& operator<<(std::ostream& os, const BaseRegles& br) {
		for (auto& it: br.data) {
			os << it.second.nom << ": Si ";
			
			for (auto& it_vec: it.second.prem) {
				// os << "(" << it_vec.first->nom << ", ";
				// os << it_vec.second->name << ")" << " et ";
			}
			os << " alors ";
			// os << "(" << it.second.concl.first->nom; 
			// os << ", " << it.second.concl.second->name;
			os << ")" << std::endl;
			os << "Flou: " << (it.second.flou ? "true" : "false");
			os << std::endl;
			os << "Coeff: " << it.second.coeff << std::endl << std::endl; 
		}

		return os; 
	}	
	std::ostream& operator<<(std::ostream& os, const BaseFaits& c);



	
}
