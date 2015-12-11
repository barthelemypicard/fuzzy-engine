#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <memory>

namespace fuzzy {

  typedef std::string Objet;
  typedef int Operateur;
        
  /* ----- Classe LingVar -----
     LingVar représente une variable linguistique floue.
     Celle-ci pouvant être représentée par différent types de données
     (vecteur, trapéze, gaussienne, etc.), l'accès à la valeur d'appartenance
     se fera via une méthode et non un attribut. Mais on n'implémentera que le type "vecteur"
  */
  class LingVar {
  public:
    std::string 	name;
    std::string 	description;
  private:	
    std::vector<float> 	vec_keys;	
    std::vector<float> 	vec_values;

  public:
    LingVar();
    LingVar(std::string n, std::string d);
    LingVar(std::string n, std::string d, std::vector<float> vk, std::vector<float> vv);
    ~LingVar();
    float getMembershipValue(float var_val);
  };

  //////////////////////REGLES///////////////////////////////////


  /* ----- Classe Regle -----
     contient une associations de faits premisses, d'opérateur de logique floue et de faits conclusion
  */
  class Fait;
  class Regle {
  public:
    std::string nom;
    std::vector<std::shared_ptr<Fait> > prem;
    std::vector<std::shared_ptr<Fait> >	concl;
    std::vector<Operateur> operateurs;
    bool flou;
    float coeff;

    Regle(std::string n, std::vector<std::shared_ptr<Fait> > p, std::vector<std::shared_ptr<Fait> > c, bool f, float cf);
    ~Regle();
  };



  /* ----- Classe BaseRegles -----
     contient l'association d'un objet (string) et de la variable linguistique qui lui est associée.l'ensemble des règles
  */
  class BaseRegles {
  private:
    std::map<std::string, std::shared_ptr<Regle> > 	data;

  public: 
    BaseRegles();
    BaseRegles(std::vector<std::shared_ptr<Regle> > regles);
    BaseRegles(const BaseRegles& br);
    BaseRegles& operator=(const BaseRegles& br);
    BaseRegles(BaseRegles&& br);
    BaseRegles& operator=(BaseRegles&& br);
    ~BaseRegles();
    
    bool addRegle(std::shared_ptr<Regle> r);
    void addRegles(std::vector<std::shared_ptr<Regle> > regles);
    void rmRegle(std::string regle);
    std::shared_ptr<Regle> get(const std::string& nom) const;
    std::shared_ptr<Regle> operator()(const std::string& nom) const;
    std::map<std::string, std::shared_ptr<Regle> > getData() const; 
    // std::ostream& operator<<(std::ostream& os, const BaseRegles& br);	
  };


  ///////////////////FAITS////////////////////////////


  /* ----- Classe Fait -----
     contient l'association d'un objet (string) et de la variable linguistique qui lui est associée.
     Le fait peut etre évalué ou non
  */
  class Fait {
  public:
    std::string 				nom;
    bool 					flou;
    std::vector<std::shared_ptr<Regle> >        prem;
    std::vector<std::shared_ptr<Regle> >        concl;
    std::vector<std::shared_ptr<Regle> > 	metaprem;
    bool 					eval;
    float 					coeff;
    std::string 			        texte;

    LingVar                                     value;

    bool evaluate();
    Fait(const std::string n, bool f=true, bool e=false, float c=0, std::string t="default text");
    ~Fait();
  };



  /* ----- Classe BaseFaits -----
     contient l'ensemble des faits
  */
  class BaseFaits {
  private:
  public: 
    std::map<std::string, std::shared_ptr<Fait> > data;

    BaseFaits();
    BaseFaits(std::vector<std::shared_ptr<Fait> > faits);
    BaseFaits(const BaseFaits& bf);
    BaseFaits& operator=(const BaseFaits& bf);
    BaseFaits(BaseFaits&& bf);
    BaseFaits& operator=(BaseFaits&& bf);
    ~BaseFaits();

    void addFaits(std::vector<std::shared_ptr<Fait> > faits);
    void rmFait(std::string fait);
    std::shared_ptr<Fait> get(const std::string& fait) const;
    std::shared_ptr<Fait> operator()(const std::string& fait) const;
    std::map<std::string, std::shared_ptr<Fait> > getData() const; 
    // // std::ostream& operator<<(std::ostream& os, const BaseFaits& c);	
  };
}


 
