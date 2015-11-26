#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <memory>

namespace fuzzy {
	typedef std::string Objet;

	enum VarType : int {
		VECTOR,
		TRAPEZE,
		GAUSSIAN
	};
	
	/* ----- Classe LingVar -----
	LingVar représente une variable linguistique floue.
	Celle-ci pouvant être représentée par différent types de données
	(vecteur, trapéze, gaussienne, etc.), l'accès à la valeur d'appartenance
	se fera via une méthode et non un attribut. 
	*/
	class LingVar {
	public:
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

	class Fait;
	class Regle {
	public:
		std::string 																nom;
		std::vector<std::pair<Fait, std::shared_ptr<LingVar> > > 	prem;
		std::pair<std::shared_ptr<Fait>, std::shared_ptr<LingVar> >	concl;
		bool 																			flou;
		float 																		coeff;

		Regle(std::string n, std::vector<std::pair<std::string, std::string> > p, std::pair<std::string, std::string> c, bool f, float cf);
		~Regle();
	};

	
	class BaseRegles {
	private:
		std::map<std::string, Regle> 	data;

	public: 
		BaseRegles();
		BaseRegles(std::vector<Regle> regles);
		~BaseRegles();

		void 	addRegles(std::vector<Regle> regles);
		void 	rmRegle(std::string regle);
		Regle get(const std::string& nom) const;
		Regle operator()(const std::string& nom) const;
	};


	class Fait {
	public:
		std::string 				nom;
		bool 					flou;
		std::vector<std::shared_ptr<Regle> > 	prem;
		std::vector<std::shared_ptr<Regle> > 	concl;
		std::vector<std::shared_ptr<Regle> > 	metaprem;
		bool 					eval;
		float 					coeff;
		std::string 			        texte;

		Fait();
		~Fait();
	};
}
