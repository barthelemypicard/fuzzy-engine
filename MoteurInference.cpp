#include <iostream>
#include <vector>
#include <list>
#include <math.h>

#include "StructDonnees.hpp"
#include "MoteurInference.hpp"

namespace fuzzy {
	MoteurInference::MoteurInference(std::shared_ptr<BaseFaits> bf, std::shared_ptr<BaseRegles> br, int n) : base_faits(bf), base_regles(br), norme(n) {}

	MoteurInference::~MoteurInference() {}

	std::vector<float> MoteurInference::liste_notes = {0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 
											12.0, 14.0, 16.0, 18.0, 20.0};
	std::vector<float> MoteurInference::lingVarToArray(LingVar lg) {
		std::vector<float> result;
		for (auto& note : liste_notes) {
			result.push_back(lg.getMembershipValue(note));
		}
		
		return result;
	}

	Imp_Mat MoteurInference::computeImpMat(std::vector<float> A, std::vector<float> B, int norme) {
		if (A.size() != B.size()) {
			std::cout << "Cannot compute Immplication Matrix." << std::endl;
			return Imp_Mat();
		}
		float un = 1.0;
		float zero = 0.0; 
		Imp_Mat result;
		for (auto& itA : A) {
			std::vector<float> inter;
			for (auto& itB : B) {
			switch (norme) {
				case 1: inter.push_back((itA != 1.0 || itB == 1.0) ? un : zero);
				break;
				case 2: inter.push_back((itA <= itB) ? un : zero);
				break;
				case 3: inter.push_back((itA <= itB) ? un : itB);
				break;
				case 4: inter.push_back(std::min(un, itB/itA));
				break;
				case 5: inter.push_back(std::min(un, un - itA + itB));
				break;
				default : std::cout << "Norme non supportée" << std::endl; 
			}
			}
			result.push_back(inter);
		}
		
		return result;
	}

	std::vector<float> MoteurInference::conclPourPremice(std::vector<float> fait, Imp_Mat im) {
		std::vector<float> result;
		Imp_Mat tmp_mat;
		auto itFait = fait.begin();
		for (auto& itL : im) {
			std::vector<float> inter;
			for (auto& itC : itL) {
				inter.push_back(std::min(itC, *itFait));
			}
			tmp_mat.push_back(inter);
			result.push_back(0.0);
			itFait++;
		}
		for (auto &itL : tmp_mat) {
			auto itRes = result.begin();
			for (auto& itC : itL) {
				*itRes = std::max(*itRes, itC);
				itRes++;
			}
		}
		
		return result;
	}

	float MoteurInference::evalCoeff(std::shared_ptr<Regle> rgl) {
		float result = 1.0;
		for (auto& prem : rgl->prem) {
			result *= prem->coeff;
		}
		result *= rgl->coeff;
		return result;
	}

	void MoteurInference::evaluerFaitsManquants() {
		std::map<std::string, bool>  	faits_flags;

		// Vérifier la possibilité d'itérer sur la base de faits ainsi que la présence de pointeurs
		// On liste les faits que n'ont pas encore été évalués
		for (auto& fait_map : base_faits->getData()) {
			std::shared_ptr<Fait> fait = fait_map.second;
			if (fait->eval == 0) 
				faits_flags.insert(std::pair<std::string, bool>(fait->nom, false));
		}

		// Tant que tous les faits n'ont pas été évalués et que 
		// l'on n'est pas bloqué dans l'évolutation
		bool blocked = false;
		while (!blocked) {
			// On parcourt à chaque fois la liste des faits à évaluer (on la parcourt à chaque
			// fois car l'évaluation d'un fait à un endroit de la liste peut débloquer la situation
			// pour un autre fait de la list):
			std::cout << "----- Iteration du while -----" << std::endl;
			blocked = true;
			for (auto& fflag : faits_flags) {
				if (base_faits->get(fflag.first)->eval == 0) {
					std::list<std::shared_ptr<Fait> > prec_faits;
					std::cout << "Evaluation du fait " << fflag.first << std::endl;
					evaluerFait(base_faits->get(fflag.first), prec_faits);
				}
			}
			std::cout << "-x-x- Fin de l'évaluation -x-x-" << std::endl;
			for (auto fflag = faits_flags.begin(); fflag != faits_flags.end(); ++fflag) { 
				if (base_faits->get(fflag->first)->eval != 0 && !(fflag->second)) {
					std::cout << fflag->first << " a été évalué." << std::endl;
					fflag->second = true;
					blocked = false;
				} 
			}
			std::cout << std::endl << std::endl;
		}
	}

	bool MoteurInference::evaluerFait(std::shared_ptr<Fait> fait_courant, std::list<std::shared_ptr<Fait> > prec_faits) {
		bool evaluable = true;
		bool success = false;
		std::list<std::shared_ptr<Regle> > regles_a_eval;

		std::cout << "___Fait : " << fait_courant->nom;
		std::cout << ", faits passés : [ ";
		for (auto& f : prec_faits)
			std::cout << f->nom << " ";
		std::cout << "]" << std::endl;
		// Parmi les régles pour lesquelles le fait figure en conclusion, 
		// on élimine celles qui contiennent des boucles
		for (auto& concl_rgl : base_faits->get(fait_courant->nom)->concl) {
			bool add_rgl = true;
			for (auto& prem_rgl : concl_rgl->prem) {
				for (auto& pf : prec_faits) {
					add_rgl = add_rgl && (prem_rgl->nom != pf->nom);
				}
			}
			if (add_rgl) {
				//std::cout << "On doit évaluer " << concl_rgl->nom << std::endl;
				regles_a_eval.push_back(concl_rgl);
			}
		}

		// On tente d'évaluer les régles selectionnées. Si un des faits en prémices
		// n'a pas été évalué, on tente de l'évaluer récurcivement. SI cela est 
		// fructueux, on évalue la règle, sinon on abandonne.
		for (auto& rgl : regles_a_eval) {
			success = true;
			for (auto& pre : rgl->prem) {
				if (base_faits->get(pre->nom)->eval == 0) {
					std::cout << "______Fait inconnu : " << pre->nom << std::endl;
					std::list<std::shared_ptr<Fait> > next_faits(prec_faits);
					next_faits.push_back(fait_courant);
					success = success && evaluerFait(pre, next_faits);
				} 
			}
			if (success) {
				// Fonctionnera juste pour le "et"
				std::vector<float> current_concl(liste_notes.size(), 1.0);
				for (auto& pre : rgl->prem) {
					std::vector<float> A = lingVarToArray(pre->value);
					std::vector<float> B = lingVarToArray(base_faits->get(pre->nom)->value);
					Imp_Mat AtoB = computeImpMat(A, B, norme);
					std::vector<float> R = conclPourPremice(B, AtoB);
					current_concl = std::min(current_concl, R);
				}
				std::cout << "______success" << std::endl;
				if (base_faits->get(fait_courant->nom)->eval) {
					//Le fait a déjà été évalué dans la boucle donc on le modifiei
					auto vrai_fait = base_faits->get(fait_courant->nom);
					vrai_fait->value = LingVar("eval", "", liste_notes, std::max(lingVarToArray(vrai_fait->value), current_concl));
					vrai_fait->coeff = std::max(vrai_fait->coeff, evalCoeff(rgl));
				} else {
					base_faits->get(fait_courant->nom)->value = LingVar("eval", "", liste_notes, current_concl);
					base_faits->get(fait_courant->nom)->coeff = evalCoeff(rgl);
					base_faits->get(fait_courant->nom)->evaluate();
				}
				std::cout << base_faits->get(fait_courant->nom)->eval << std::endl;
				// On évalue la régle sans oublier de fusionner les résultats 
			}
		}

		return success;
	}
	
	
	void MoteurInference::construireLingVars(std::map<std::string, LingVar> tables) {
		for (auto& fait : base_faits->getData()) {
			if (base_faits->get(fait.first)->eval) {
				auto fait_courant = base_faits->get(fait.first);
				// std::cout << fait_courant->nom << " : " << fait_courant->value.name << std::endl;
				try {
					fait_courant->value = tables.at(fait_courant->value.name);
				} catch (const std::out_of_range& oor) {
					std::cout << "The element " << fait.first << " does not exist in the table." << std::endl;
				}
			}
		}
		for (auto& regle : base_regles->getData()) {
			for (auto& prem : base_regles->get(regle.first)->prem) {
				try {
					prem->value = tables.at(prem->value.name);
				} catch (const std::out_of_range& oor) {
					std::cout << "The element " << prem->value.name << " does not exist in the table." << std::endl;
				}
			}
			for (auto& concl : base_regles->get(regle.first)->concl) {
				try {
					concl->value = tables.at(concl->value.name);
				} catch (const std::out_of_range& oor) {
					std::cout << "The element " << concl->value.name << " does not exist in the table." << std::endl;
				}
			}
		}
	}
}
