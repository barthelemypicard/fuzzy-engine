#pragma once

#include <iostream>
#include <vector>


namespace fuzzy {
	typedef std::string Objet;

	/* ----- Classe LingVar -----
	LingVar représente une variable linguistique floue.
	Celle-ci pouvant être représentée par différent types de données
	(vecteur, trapéze, gaussienne, etc.), l'accès à la valeur d'appartenance
	se fera via une méthode et non un attribut. 
	*/
	class LingVar {
	public:
	enum VarType : int {
		VECTOR,
		TRAPEZE,
		GAUSSIAN
	};
		std::string 	name;
		std::string 	description;
		VarType 			var_type;
	private:	
		std::vector<float> 	vec_keys;	
		std::vector<float> 	vec_values;

	public:
		LingVar();
		LingVar(std::string n, std::string d, VarType vt);
		LingVar(std::string n, std::string d, std::vector<float> vk, std::vector<float> vv);
		~LingVar();
		float getMembershipValue(float var_val);
	};


}
