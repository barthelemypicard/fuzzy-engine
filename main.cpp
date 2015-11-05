#include <iostream>
#include <vector>

#include "StructDonnees.hpp"
// #include "BaseRegles.hpp"

int main(int argc, char* argv[]) {
	std::cout << "Start" << std::endl;

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
}
