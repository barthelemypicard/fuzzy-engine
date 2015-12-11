#include <iostream>
#include <vector>
#include <cmath>

#include "StructDonnees.hpp"
#include "MoteurInference.hpp"
#include "Parser.hpp"
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
		R1 : A et B et C -> D
		R2 : A et B 	 -> E
		R3 : C et E 	 -> F
		R4 : E et B 	 -> C
	*/	
/*	
	std::vector<float> AB;
	std::vector<float> B = {0.0, 0.005, 0.005, 0.01, 0.1, 0.3, 0.4, 0.6, 0.8, 0.9, 1.0};
	std::vector<float> TB;
	for (auto& b : B) {
		AB.push_back(std::sqrt(b));
		TB.push_back(b*b);
	}

	typedef std::pair<std::shared_ptr<fuzzy::Fait>, std::shared_ptr<fuzzy::LingVar> > FACT;
	typedef std::shared_ptr<fuzzy::Fait> fait_ptr;

	std::shared_ptr<fuzzy::Fait> 	pA = std::make_shared<fuzzy::Fait>("A");
	std::shared_ptr<fuzzy::Fait> 	pB = std::make_shared<fuzzy::Fait>("B");
	std::shared_ptr<fuzzy::Fait> 	pC = std::make_shared<fuzzy::Fait>("C");
	std::shared_ptr<fuzzy::Fait> 	pD = std::make_shared<fuzzy::Fait>("D");
	std::shared_ptr<fuzzy::Fait> 	pE = std::make_shared<fuzzy::Fait>("E");
	std::shared_ptr<fuzzy::Fait> 	pF = std::make_shared<fuzzy::Fait>("F");
	std::shared_ptr<fuzzy::Fait> 	pG = std::make_shared<fuzzy::Fait>("G");

	fait_ptr pR1_A = std::make_shared<fuzzy::Fait>("A");
	fait_ptr pR1_B = std::make_shared<fuzzy::Fait>("B");
	fait_ptr pR1_C = std::make_shared<fuzzy::Fait>("C");
	fait_ptr pR1_D = std::make_shared<fuzzy::Fait>("D");
	std::shared_ptr<fuzzy::Regle> 	pR1 = std::make_shared<fuzzy::Regle>(fuzzy::Regle("R1", {pR1_A, pR1_B, pR1_C}, {pR1_D}, false, 1.0));
	fait_ptr pR2_A = std::make_shared<fuzzy::Fait>("A");
	fait_ptr pR2_B = std::make_shared<fuzzy::Fait>("B");
	fait_ptr pR2_E = std::make_shared<fuzzy::Fait>("E");
	std::shared_ptr<fuzzy::Regle> 	pR2 = std::make_shared<fuzzy::Regle>(fuzzy::Regle("R2", {pR2_A, pR2_B}, {pR2_E}, false, 1.0));
	fait_ptr pR3_C = std::make_shared<fuzzy::Fait>("C");
	fait_ptr pR3_E = std::make_shared<fuzzy::Fait>("E");
	fait_ptr pR3_F = std::make_shared<fuzzy::Fait>("F");
	std::shared_ptr<fuzzy::Regle> 	pR3 = std::make_shared<fuzzy::Regle>(fuzzy::Regle("R3", {pR3_C, pR3_E}, {pR3_F}, false, 1.0));
	fait_ptr pR4_E = std::make_shared<fuzzy::Fait>("E");
	fait_ptr pR4_B = std::make_shared<fuzzy::Fait>("B");
	fait_ptr pR4_C = std::make_shared<fuzzy::Fait>("C");
	std::shared_ptr<fuzzy::Regle> 	pR4 = std::make_shared<fuzzy::Regle>(fuzzy::Regle("R4", {pR4_E, pR4_B}, {pR4_C}, false, 1.0));
	
	pA->nom = "A"; pA->eval = true;
	pA->prem.push_back(pR1); pA->prem.push_back(pR2);
	pB->nom = "B"; pB->eval = true;
	pB->prem.push_back(pR1); pB->prem.push_back(pR2); pB->prem.push_back(pR4);
	pC->nom = "C"; pC->eval = false;
	pC->prem.push_back(pR2); pC->prem.push_back(pR2);
	pC->concl.push_back(pR4);
	pD->nom = "D"; pD->eval = false;
	//pD->prem.push_back(pR3); 
	pD->concl.push_back(pR1);
	pE->nom = "E"; pE->eval = false;
	pE->prem.push_back(pR3); pE->prem.push_back(pR4);
	pE->concl.push_back(pR2);
	pF->nom = "F"; pF->eval = false;
	//pF->prem.push_back(pR4); 
	pF->concl.push_back(pR3);
	//pG->nom = "G"; pG->eval = false;
	//pG->prem.push_back(pR3);
	//pG->concl.push_back(pR4);

	pR2_A->value = fuzzy::LingVar("TB", "", fuzzy::MoteurInference::liste_notes, TB);
	pR2_B->value = fuzzy::LingVar("B", "", fuzzy::MoteurInference::liste_notes, B);
	pR2_E->value = fuzzy::LingVar("B", "", fuzzy::MoteurInference::liste_notes, B);
	pA->value = fuzzy::LingVar("TB", "", fuzzy::MoteurInference::liste_notes, B);
	pB->value = fuzzy::LingVar("B", "", fuzzy::MoteurInference::liste_notes, TB);

	std::shared_ptr<fuzzy::BaseFaits> 	base_faits(new fuzzy::BaseFaits({pA, pB, pE}));
	std::shared_ptr<fuzzy::BaseRegles>	base_regles(new fuzzy::BaseRegles({pR2}));

	std::cout << "Launching engine... ";
	fuzzy::MoteurInference engine(base_faits, base_regles, 3);
	std::cout << "Done." << std::endl;
	std::cout << "Evaluating missing vars." << std::endl;
	engine.evaluerFaitsManquants();

	std::cout << "E.value = { ";
	for (auto& note : fuzzy::MoteurInference::liste_notes) {
		std::cout << pE->value.getMembershipValue(note) << " ";
	}
	std::cout << "}" << std::endl;
	*/

	
  fuzzy::BaseFaits listeFaits;//ensemble des faits évaluables selon le fichier regles.txt
  
  fuzzy::BaseRegles regles;//ensemble des règles du fichier regles.txt

  listeFaits=fuzzy::Parser::parseFaits_firstPass("regles.txt", 70); 
               //ensemble des faits évaluables selon le fichier regles.txt
               //Attention ici les fait de la base ne sont pas reliés à des règles
  
  regles=fuzzy::Parser::parseRegles("regles.txt", 70);
               //ensemble des règles du fichier regles.txt
               //Création de faits de référence pour regles
	//std::shared_ptr<fuzzy::BaseFaits> base_faits(new fuzzy::Parser::parseFaits_firstPass("regles.txt", 70);
}
