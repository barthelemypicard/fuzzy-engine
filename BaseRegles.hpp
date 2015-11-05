#pragma once

#include <iostream>
#include <vector>
#include "StructDonnees.hpp"

namespace fuzzy {
	class Regle {
	public:
		std::string 										nom;
		std::vector<std::pair<Objet, LingVar>> 	prem;
		std::pair<Objet, LingVar> 						concl;
		bool 													flou;
		float 												coeff;

		Regle(std::string n, std::vector<std::pair<std::string, std::string>> p, std::pair<std::string, std::string> c, bool f, float cf);
		~Regle();
	};

}
