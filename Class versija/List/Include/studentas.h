#ifndef STUDENTAS_H
#define STUDENTAS_H


#include "myLib.h"


// Studentas klase: reprezentuoja individualu studenta
class Studentas {
private:
    string vardas_;
    string pavarde_;
    list<int> namuDarbai_;
    int egzaminas_;

public:
    // Konstruktorius
    Studentas(const string& vardas = "", const string& pavarde = "") 
        : vardas_(vardas), pavarde_(pavarde), egzaminas_(0) {}

    // Copy konstruktorius (Rule of Three - 1)
    Studentas(const Studentas& other) 
        : vardas_(other.vardas_), 
          pavarde_(other.pavarde_), 
          namuDarbai_(other.namuDarbai_), 
          egzaminas_(other.egzaminas_) {}

    // Copy assignment operatorius (Rule of Three - 2)
    Studentas& operator=(const Studentas& other) {
        if (this != &other) {
            vardas_ = other.vardas_;
            pavarde_ = other.pavarde_;
            namuDarbai_ = other.namuDarbai_;
            egzaminas_ = other.egzaminas_;
        }
        return *this;
    }

    // Destruktorius (Rule of Three - 3)
    ~Studentas() {
        vardas_.clear();
        pavarde_.clear();
        namuDarbai_.clear();
    }


    // Getteriai, leidzia saugiai pasiekti studento duomenis
    inline string vardas() const { return vardas_; }
    inline string pavarde() const { return pavarde_; }
    inline const list<int>& namuDarbai() const { return namuDarbai_; }
    inline int egzaminas() const { return egzaminas_; }
    
    // Setteriai, leidzia keisti studento duomenis
    void setVardas(const string& vardas) { vardas_ = vardas; }
    void setPavarde(const string& pavarde) { pavarde_ = pavarde; }
    void setEgzaminas(int egz) { egzaminas_ = egz; }
    void addNamuDarbas(int pazymys) { namuDarbai_.push_back(pazymys); }
    void clearNamuDarbai() { namuDarbai_.clear(); }
    void setNamuDarbai(const list<int>& namuDarbai) { namuDarbai_ = namuDarbai; }
    
    // Metodai
    void ivestiStudenta(bool atsitiktiniai, int namuDarbaiKiekis);
    double skaiciuotiGalutiniBala(bool naudotiVidurki) const;

    // Ivesties operatorius
    friend istream& operator>>(istream& is, Studentas& studentas);

    // Isvesties operatorius 
    friend ostream& operator<<(ostream& os, const Studentas& studentas);
};


#endif // STUDENTAS_H
