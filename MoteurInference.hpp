#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <memory>

#include "StructDonnees.hpp"

namespace fuzzy {
	typedef std::vector<std::vector<float> > Imp_Mat;

	class MoteurInference {
	private:
		std::shared_ptr<BaseFaits> 	base_faits;
		std::shared_ptr<BaseRegles> 	base_regles;
		int 				norme;
		
	public:
		static std::vector<float> liste_notes;

		MoteurInference(std::shared_ptr<BaseFaits> bf, 
				std::shared_ptr<BaseRegles> br, int n);
		~MoteurInference();
		std::vector<float> lingVarToArray(LingVar lg);
		Imp_Mat computeImpMat(std::vector<float> A, std::vector<float> B, int norme);
		std::vector<float> conclPourPremice(std::vector<float> fait, Imp_Mat im);
		float evalCoeff(std::shared_ptr<Regle> rgl);
		void evaluerFaitsManquants();
		bool evaluerFait(std::shared_ptr<Fait> fait_courant, std::list<std::shared_ptr<Fait> > prec_faits);
		void construireLingVars(std::map<std::string, LingVar> tables);
	};
}
