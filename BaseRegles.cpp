
#include <iostream>
#include <vector>
#include "StructDonnees.hpp"
#include "BaseRegles.hpp"

namespace fuzzy {
	Regle::Regle(std::string n, std::vector<std::pair<std::string, std::string>> p, std::pair<std::string, std::string> c, bool f, float cf) : nom(n), flou(f), coeff(cf) {
	}
	Regle::~Regle() {}
}
