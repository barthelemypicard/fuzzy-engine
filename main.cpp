#include <iostream>
#include <vector>
#include <cmath>

#include "StructDonnees.hpp"
#include "MoteurInference.hpp"
#include "Parser.hpp"
// #include "BaseRegles.hpp"


int main(int argc, char* argv[]) {
	std::cout << "Start" << std::endl;	

	fuzzy::BaseFaits listeFaits;//ensemble des faits évaluables selon le fichier regles.txt  
	fuzzy::BaseRegles regles;//ensemble des règles du fichier regles.txt

	listeFaits = fuzzy::Parser::parseFaits_firstPass("regles.txt", 70); 
	regles = fuzzy::Parser::parseRegles("regles.txt", 70);
	fuzzy::Parser::parseFaits_secondPass(listeFaits, regles);
	fuzzy::Parser::parseFaits_bulletin("bulletin.txt", listeFaits);


	std::shared_ptr<fuzzy::BaseFaits> base_faits = std::make_shared<fuzzy::BaseFaits>(listeFaits);
	std::shared_ptr<fuzzy::BaseRegles> base_regles = std::make_shared<fuzzy::BaseRegles>(regles);

	std::string fact = "resultat_biolo";
	std::cout << fact << " : " << ((base_faits->get(fact)->value.name)) << std::endl;;
	std::cout << fact << " : " << ((base_faits->get(fact)->eval) ? "évalué" : "non évalué") <<  std::endl;
	std::cout << fact <<".value = { ";
	for (auto& note : fuzzy::MoteurInference::liste_notes) {
		std::cout << base_faits->get(fact)->value.getMembershipValue(note) << " ";
	}
	std::cout << "}" << std::endl;

	std::cout << "Initialisation of LingVars" << std::endl;
	std::vector<float> AB;
	std::vector<float> B = {0.0, 0.005, 0.005, 0.01, 0.1, 0.3, 0.4, 0.6, 0.8, 0.9, 1.0};
	std::vector<float> TB;
	std::vector<float> T = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0};
	for (auto& b : B) {
		AB.push_back(std::sqrt(b));
		TB.push_back(b*b);
	}
	fuzzy::LingVar lv_AB("AB", "", fuzzy::MoteurInference::liste_notes, AB);
	fuzzy::LingVar lv_B("B", "", fuzzy::MoteurInference::liste_notes, B);
	fuzzy::LingVar lv_TB("TB", "", fuzzy::MoteurInference::liste_notes, TB);
	fuzzy::LingVar lv_T("T", "", fuzzy::MoteurInference::liste_notes, T);
	std::map<std::string, fuzzy::LingVar> table;
	table.insert(std::pair<std::string, fuzzy::LingVar>(lv_AB.name, lv_AB));	
	table.insert(std::pair<std::string, fuzzy::LingVar>(lv_B.name, lv_B));	
	table.insert(std::pair<std::string, fuzzy::LingVar>(lv_TB.name, lv_TB));	
	table.insert(std::pair<std::string, fuzzy::LingVar>(lv_T.name, lv_T));	

	std::cout << std::endl << "---------------------" << std::endl << std::endl;
	std::cout << std::endl << "Launching engine... ";
	fuzzy::MoteurInference engine(base_faits, base_regles, 3);
	std::cout << "Done." << std::endl;
	
	engine.construireLingVars(table);
	std::cout << fact <<".value = { ";
	for (auto& note : fuzzy::MoteurInference::liste_notes) {
		std::cout << base_faits->get(fact)->value.getMembershipValue(note) << " ";
	}
	std::cout << "}" << std::endl;
	
	engine.evaluerFaitsManquants();

	fact = "niveau_biolo";
	std::cout << fact <<".value = { ";
	for (auto& note : fuzzy::MoteurInference::liste_notes) {
		std::cout << base_faits->get(fact)->value.getMembershipValue(note) << " ";
	}
	std::cout << "}" << std::endl;

	// Boucle pour demander à l'utilisateur des faits à afficher
	std::string in_str = "";
	while (in_str != "q") {
		std::cout << "Entrer un fait ('q' pour quitter) : ";
		std::cin >> in_str;
		if (in_str != "q") {
			std::cout << "---------------------------------" << std::endl;
			std::cout << "Fait : " << in_str << std::endl;
			try {
				std::cout << "Evalué : " << (base_faits->get(in_str)->eval ? "Oui" : "Non") << std::endl;
				std::cout << "Valeur : " << (base_faits->get(in_str)->value.name) << " = { ";
				for (auto& note : fuzzy::MoteurInference::liste_notes) {
					std::cout << base_faits->get(in_str)->value.getMembershipValue(note) << " ";
				}
				std::cout << "}" << std::endl;
				std::cout << "Certitude : " << base_faits->get(in_str)->coeff << std::endl;
			} catch (const std::out_of_range& oor) {
				std::cout << "Ce fait n'existe pas." << std::endl;
			}
			std::cout << "---------------------------------" << std::endl << std::endl;
		}
	}
}

