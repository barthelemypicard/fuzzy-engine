#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <memory>

#include "StructDonnees.hpp"

namespace fuzzy {
	
	class MoteurInference {
	private:
		std::shared_ptr<BaseFaits> 	base_faits;
		std::shared_ptr<BaseRegles> 	base_regles;
		
	public:
		MoteurInference(std::shared_ptr<BaseFaits> bf, 
				std::shared_ptr<BaseRegles> br);
		~MoteurInference();
		void evaluerFaitsManquants();
		bool evaluerFait(Fait fait_courant, std::list<Fait> prec_faits);
	};
}
