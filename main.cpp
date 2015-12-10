#include <iostream>
#include <vector>

#include "StructDonnees.hpp"
#include "MoteurInference.hpp"
// #include "BaseRegles.hpp"

int main(int argc, char* argv[]) {
	std::cout << "Start" << std::endl;
/*
	std::vector<float> vk = {0.0, 2.0, 4.0, 6.0, 8.0, 10.0,
									 12.0, 14.0, 16.0, 18.0, 20.0};
	std::vector<float> vv = {0.001, 0.005, 0.005, 0.01, 0.1, 0.3, 0.4, 0.6, 0.8, 0.9, 1.0};

	fuzzy::LingVar lv("temp", "température.", vk, vv);
	std::cout << lv.name << " : " << lv.description <<   std::endl;
	std::cout << lv.getMembershipValue(-10.0) << ", " 
				 << lv.getMembershipValue(0.0)   << ", "
				 << lv.getMembershipValue(6.0)   << ", "
				 << lv.getMembershipValue(13.0)   << ", "
				 << lv.getMembershipValue(16.5)   << ", "
				 << lv.getMembershipValue(20.0)   << ", "
				 << lv.getMembershipValue(60.0)   << std::endl;

	std::vector<std::pair<std::string, std::string>> tp = {{"resultat_biolo", "TB"}, {"resultat_chimie", "B"}};
	std::pair<std::string, std::string> tc = {"niveau_biolo", "TB"};
	fuzzy::Regle rgl("R1", tp, tc, true, 1.0);
	std::cout << rgl.nom << std::endl;
	fuzzy::Regle rgl2("R2", tp, tc, true, 0.5);
	fuzzy::Regle rgl3("R1", tp, tc, true, 0.75);
	std::vector<fuzzy::Regle> brgl;
	brgl.push_back(rgl);
	brgl.push_back(rgl2);
	brgl.push_back(rgl3);
	fuzzy::BaseRegles br(brgl);
	std::cout << br.get(rgl2.nom).coeff << ", " << br(rgl3.nom).coeff << std::endl;

	std::cout << "-----------" << std::endl;
	std::cout << br << std::endl;
*/	
	/* ----- Premier test du moteur -----
	A, B, C connus
		R1 : A et B -> D
		R2 : A et C -> E
		R3 : C et D -> F
		R4 : F et B -> G
	*/
	std::shared_ptr<fuzzy::Fait> 	pA = std::make_shared<fuzzy::Fait>();
	std::shared_ptr<fuzzy::Fait> 	pB = std::make_shared<fuzzy::Fait>();
	std::shared_ptr<fuzzy::Fait> 	pC = std::make_shared<fuzzy::Fait>();
	std::shared_ptr<fuzzy::Fait> 	pD = std::make_shared<fuzzy::Fait>();
	std::shared_ptr<fuzzy::Fait> 	pE = std::make_shared<fuzzy::Fait>();
	std::shared_ptr<fuzzy::Fait> 	pF = std::make_shared<fuzzy::Fait>();
	std::shared_ptr<fuzzy::Fait> 	pG = std::make_shared<fuzzy::Fait>();

	std::shared_ptr<fuzzy::Regle> 	pR1 = std::make_shared<fuzzy::Regle>();
	std::shared_ptr<fuzzy::Regle> 	pR2 = std::make_shared<fuzzy::Regle>();
	std::shared_ptr<fuzzy::Regle> 	pR3 = std::make_shared<fuzzy::Regle>();
	std::shared_ptr<fuzzy::Regle> 	pR4 = std::make_shared<fuzzy::Regle>();
	
	pA->nom = "A"; pA->eval = true;
	pA->prem.push_back(pR1); pA->prem.push_back(pR2);
	pB->nom = "B"; pB->eval = true;
	pB->prem.push_back(pR1); pB->prem.push_back(pR4);
	pC->nom = "C"; pC->eval = true;
	pC->prem.push_back(pR2); pC->prem.push_back(pR3);
	pD->nom = "D"; pD->eval = false;
	pD->prem.push_back(pR3); 
	pD->concl.push_back(pR1);
	pE->nom = "E"; pE->eval = false;
	pE->concl.push_back(pR2);
	pF->nom = "F"; pF->eval = false;
	pF->prem.push_back(pR4); 
	pF->concl.push_back(pR3);
	pG->nom = "G"; pG->eval = false;
	pG->concl.push_back(pR4);

	typedef std::pair<std::shared_ptr<fuzzy::Fait>, std::shared_ptr<fuzzy::LingVar> > FACT;
	pR1->nom = "R1"; 				pR1->concl = FACT(pD, 0);
	pR1->prem.push_back(FACT(pA, 0)); 	pR1->prem.push_back(FACT(pB, 0));
	pR2->nom = "R2"; 				pR2->concl = FACT(pE, 0);
	pR2->prem.push_back(FACT(pA, 0)); 	pR2->prem.push_back(FACT(pC, 0));
	pR3->nom = "R3"; 				pR3->concl = FACT(pF, 0);
	pR3->prem.push_back(FACT(pC, 0)); 	pR3->prem.push_back(FACT(pD, 0));
	pR4->nom = "R4"; 				pR4->concl = FACT(pG, 0);
	pR4->prem.push_back(FACT(pF, 0)); 	pR4->prem.push_back(FACT(pB, 0));

	std::shared_ptr<fuzzy::BaseFaits> 	base_faits(new fuzzy::BaseFaits({*pA, *pB, *pG, *pF, *pE, *pC, *pD}));
	std::shared_ptr<fuzzy::BaseRegles>	base_regles(new fuzzy::BaseRegles({*pR1, *pR2, *pR3, *pR4}));

	std::cout << "Launching engine... ";
	fuzzy::MoteurInference engine(base_faits, base_regles);
	std::cout << "Done." << std::endl;
	std::cout << "Evaluating missing vars." << std::endl;
	engine.evaluerFaitsManquants();
}
