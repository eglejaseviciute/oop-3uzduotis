#ifndef STUDENTAS_H
#define STUDENTAS_H

#include "rezultatai.h"
#include "myLib.h"


// Studentas klase: reprezentuoja individualu studenta
class Studentas {
private:
    std::string vardas_;
    std::string pavarde_;
    Rezultatai rezultatai_;

public:
    // Konstruktoriai
    // Numatytasis konstruktorius
    Studentas() = default;
    // Konstruktorius su vardu ir pavarde
    Studentas(const std::string& vardas, const std::string& pavarde);


    // Destruktorius, automatiškai atlaisvina klasės išteklius
    ~Studentas() = default;

    // Getteriai, leidzia saugiai pasiekti studento duomenis
    inline std::string vardas() const { return vardas_; }
    inline std::string pavarde() const { return pavarde_; }
    inline const Rezultatai& rezultatai() const { return rezultatai_; }
    
    // Setteriai, leidzia keisti studento duomenis
    void setVardas(const std::string& vardas) { vardas_ = vardas; }
    void setPavarde(const std::string& pavarde) { pavarde_ = pavarde; }
    void setRezultatai(const Rezultatai& rezultatai) { rezultatai_ = rezultatai; }
    
    // Metodai
    void ivestiStudenta(bool atsitiktiniai, int namuDarbaiKiekis);
    void spausdintiStudenta(bool naudotiVidurki) const;
    double skaiciuotiGalutiniBala(bool naudotiVidurki) const;

};


// Rusiavimo funkcijos
bool lygintiPagalPavarde(const Studentas& a, const Studentas& b);
bool lygintiPagalVarda(const Studentas& a, const Studentas& b);
bool lygintiPagalVardaIrPavarde(const Studentas& a, const Studentas& b);


// Failo rasymo funkcija
double rasytiStudentusIFaila(const std::vector<Studentas>& studentai, 
                            const std::string& failoPavadinimas, 
                            bool naudotiVidurki);


// Rusiavimo klases
class RusiuotiPagalGalutiniBalaDidejanciai {
private:
    bool naudotiVidurki;
public:
    RusiuotiPagalGalutiniBalaDidejanciai(bool naudotiVid) : naudotiVidurki(naudotiVid) {}
    bool operator()(const Studentas& a, const Studentas& b) const {
        return a.skaiciuotiGalutiniBala(naudotiVidurki) < b.skaiciuotiGalutiniBala(naudotiVidurki);
    }
};

class RusiuotiPagalGalutiniBalaMazejanciai {
private:
    bool naudotiVidurki;
public:
    RusiuotiPagalGalutiniBalaMazejanciai(bool naudotiVid) : naudotiVidurki(naudotiVid) {}
    bool operator()(const Studentas& a, const Studentas& b) const {
        return a.skaiciuotiGalutiniBala(naudotiVidurki) > b.skaiciuotiGalutiniBala(naudotiVidurki);
    }
};


#endif // STUDENTAS_H