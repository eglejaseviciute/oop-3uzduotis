#ifndef STUDENTAS_H
#define STUDENTAS_H


#include "zmogus.h"
#include "myLib.h"


// Studentas klase, kuri paveldi is Zmogus klases
class Studentas : public Zmogus {
private:
    vector<int> namuDarbai_;
    int egzaminas_;

public:
    // Konstruktorius
    Studentas(const string& vardas = "", const string& pavarde = "") 
        : Zmogus(vardas, pavarde), egzaminas_(0) {}

    // Copy konstruktorius (Rule of Three - 1)
    Studentas(const Studentas& other) 
        : Zmogus(other.vardas_, other.pavarde_), 
          namuDarbai_(other.namuDarbai_), 
          egzaminas_(other.egzaminas_) {}

    // Copy assignment operatorius (Rule of Three - 2)
    Studentas& operator=(const Studentas& other) {
        if (this != &other) {
            Zmogus::operator=(other);
            namuDarbai_ = other.namuDarbai_;
            egzaminas_ = other.egzaminas_;
        }
        return *this;
    }

    // Destruktorius (Rule of Three - 3)
    ~Studentas() {
        namuDarbai_.clear();
    }

    // Getteriai
    inline const vector<int>& namuDarbai() const { return namuDarbai_; }
    inline int egzaminas() const { return egzaminas_; }

    // Setteriai
    void setEgzaminas(int egz) { egzaminas_ = egz; }
    void addNamuDarbas(int pazymys) { namuDarbai_.push_back(pazymys); }
    void clearNamuDarbai() { namuDarbai_.clear(); }
    void setNamuDarbai(const vector<int>& namuDarbai) { namuDarbai_ = namuDarbai; }

    // Metodai
    void ivestiStudenta(bool atsitiktiniai, int namuDarbaiKiekis);
    double skaiciuotiGalutiniBala(bool naudotiVidurki) const;

    // Virtuali funkcija is Zmogus klases
    void spausdintiInformacija() const override {
        cout << "Studentas: " << vardas_ << " " << pavarde_ << "\n";
    }

    // Ivesties ir isvesties operatoriai
    friend istream& operator>>(istream& is, Studentas& studentas);
    friend ostream& operator<<(ostream& os, const Studentas& studentas);
};


#endif // STUDENTAS_H
