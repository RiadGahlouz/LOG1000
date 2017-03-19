#include <iostream>
#include <vector>
using namespace std;

/* FORWARD DECLARATION */
class Local;
class LocalCours;
class LocalProf;
class LocalLabo;
class LocalEntretien;
class BureauDirecteur;
class SalleDeBain;

class VisiteurDeLocaux {
public:
	virtual double visiter(const LocalCours& local) const = 0;
	virtual double visiter(const LocalProf& local) const = 0;
	virtual double visiter(const LocalLabo& local) const = 0;
	virtual double visiter(const LocalEntretien& local) const = 0;
	virtual double visiter(const BureauDirecteur& local) const = 0;
	virtual double visiter(const SalleDeBain& local) const = 0;
};

class Visitable {
public:
	virtual double accepter(const VisiteurDeLocaux& visiteur) = 0;
};

class Local : public Visitable{
public:
	Local(int superficie) : superficie_(superficie) {}
	virtual ~Local(){};
	int getSuperficie() const { return superficie_; }


private:
	int superficie_;
};

class LocalCours : public Local {
public:
	LocalCours(int superficie, int nombreDePlaces): Local(superficie), nombreDePlaces_(nombreDePlaces) {}
	~LocalCours(){};
	int getNombreDePlaces() const { return nombreDePlaces_; }

	virtual double accepter(const VisiteurDeLocaux& visiteur) {
		return visiteur.visiter(*this);
	}
private:
	int nombreDePlaces_;
};

class LocalProf : public Local {
public:
	LocalProf(int superficie): Local(superficie){}
	~LocalProf(){};
	virtual double accepter(const VisiteurDeLocaux& visiteur) {
		return visiteur.visiter(*this);
	}
};

class LocalLabo : public Local {
public:
	LocalLabo(int superficie, int nombreDeBechers) :Local(superficie), nombreDeBechers_(nombreDeBechers) {}
	~LocalLabo(){};

	int getNombreDeBechers() const { return nombreDeBechers_; }
	virtual double accepter(const VisiteurDeLocaux& visiteur) {
		return visiteur.visiter(*this);
	}
private:
	int nombreDeBechers_;

};

class BureauDirecteur : public Local {
public:
	BureauDirecteur(int superficie):Local(superficie){}
	~BureauDirecteur(){};
	virtual double accepter(const VisiteurDeLocaux& visiteur) {
		return visiteur.visiter(*this);
	}
};

class LocalEntretien : public Local {
public:
	LocalEntretien(int superficie, int nombreDeBalais) :Local(superficie), nombreDeBalais_(nombreDeBalais) {}
	~LocalEntretien(){};

	int getNombreDeBalais() const { return nombreDeBalais_; }
	virtual double accepter(const VisiteurDeLocaux& visiteur) {
		return visiteur.visiter(*this);
	}
private:
	int nombreDeBalais_;
};

class SalleDeBain : public Local {
public:
	SalleDeBain(int superficie, int nombreDeBols) :Local(superficie), nombreDeBols_(nombreDeBols) {}
	~SalleDeBain(){};

	int getNombreDeBols() const { return nombreDeBols_; }
	virtual double accepter(const VisiteurDeLocaux& visiteur) {
		return visiteur.visiter(*this);
	}
private:
	int nombreDeBols_;
};




//Calcule le cout d'entretien des locaux
class Inspecteur : public VisiteurDeLocaux {
public:
	virtual double visiter(const LocalCours& local) const {
		return local.getNombreDePlaces() * 10;//cout de 10$ par places
	}
	virtual double visiter(const LocalProf& local) const {
		return local.getSuperficie() * 10;//cout de 10$ par m2
	}
	virtual double visiter(const LocalLabo& local) const {
		return local.getNombreDeBechers() * 100;//les bechers contiennent de l'uranium :P
	}
	virtual double visiter(const LocalEntretien& local) const {
		return  local.getNombreDeBalais() * 5 + 100;//5$ par balais + 100$ pour produits m�nagers
	}
	virtual double visiter(const BureauDirecteur& local) const {
		return local.getSuperficie() * 20;//cout de 20$ par m2
	}
	virtual double visiter(const SalleDeBain& local) const {
		return local.getNombreDeBols() * 15;//cout de 15 $ par bols
	}
};

class Concierge : public VisiteurDeLocaux {
public:
	virtual double visiter(const LocalCours& local) const {
		return local.getNombreDePlaces() * 0.5 + local.getSuperficie();//30 secondes par si�ge
	}
	virtual double visiter(const LocalProf& local) const {
		return local.getSuperficie();//1 minute par m^2 (plusieurs passages)
	}
	virtual double visiter(const LocalLabo& local) const {
		return local.getSuperficie() * 2;//Le labo doit �tre tr�s propre
	}
	virtual double visiter(const LocalEntretien& local)const {
		return  local.getNombreDeBalais() * 0.1 ;//Nettoyer les balais
	}
	virtual double visiter(const BureauDirecteur& local)const {
		return local.getSuperficie() * 2 + 10 ;//Bureau tr�s propre sinon on se fait virer et 10 minutes pour faire augmenter osn salaire :)
	}
	virtual double visiter(const SalleDeBain& local)const {
		return local.getNombreDeBols() * 5 + local.getSuperficie() *2;//5 Minutes par bol et 2 minutes par m^2 de sol
	}
};

int main() {
	LocalCours localCours(100,50);
	LocalProf localProf(10);
	LocalLabo localLabo(50,30);
	LocalEntretien localEntretien(10,5);
	BureauDirecteur bureauDirecteur(25);
	SalleDeBain salleDeBain(60,10);

	Concierge concierge;
	Inspecteur inspecteur;

	double tempsDeNettoyage = 0, //Concierge
	coutEntretient = 0; //Inspecteur

	tempsDeNettoyage += concierge.visiter(localCours);
	coutEntretient += inspecteur.visiter(localCours);

	tempsDeNettoyage += concierge.visiter(localProf);
	coutEntretient += inspecteur.visiter(localProf);

	tempsDeNettoyage += concierge.visiter(localLabo);
	coutEntretient += inspecteur.visiter(localLabo);

	tempsDeNettoyage += concierge.visiter(localEntretien);
	coutEntretient += inspecteur.visiter(localEntretien);

	tempsDeNettoyage += concierge.visiter(bureauDirecteur);
	coutEntretient += inspecteur.visiter(bureauDirecteur);

	tempsDeNettoyage += concierge.visiter(salleDeBain);
	coutEntretient += inspecteur.visiter(salleDeBain);

	std::cout << "Le cout d'entretien de tous les locaux: "<<coutEntretient<<" $" << std::endl;
	std::cout << "Le temps de nettoyage de tous les locaux: "<<tempsDeNettoyage<<" Minutes" << std::endl;

}
