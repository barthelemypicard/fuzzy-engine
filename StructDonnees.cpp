#include <iostream>
#include <vector>

#include "StructDonnees.hpp"


namespace fuzzy {
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
								for (auto key_it = vec_keys.rbegin(); key_it != (vec_keys.rend()--); key_it++) {
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
}
