#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

#include "myLib.h"
#include "studentas.h"


class VeikimoGreicioMatavimai {
private:
    double kurimoLaikas_;
    double skaitymoLaikas_;
    double rusiavimoLaikas_;
    double rasymoLaikasVargsiukai_;
    double rasymoLaikasGalvociai_;

public:
    // Konstruktorius
    VeikimoGreicioMatavimai() : 
        kurimoLaikas_(0.0), 
        skaitymoLaikas_(0.0), 
        rusiavimoLaikas_(0.0),
        rasymoLaikasVargsiukai_(0.0),
        rasymoLaikasGalvociai_(0.0) {}

    // Geteriai
    double getKurimoLaikas() const { return kurimoLaikas_; }
    double getSkaitymoLaikas() const { return skaitymoLaikas_; }
    double getRusiavimoLaikas() const { return rusiavimoLaikas_; }
    double getRasymoLaikasVargsiukai() const { return rasymoLaikasVargsiukai_; }
    double getRasymoLaikasGalvociai() const { return rasymoLaikasGalvociai_; }

    // Seteriai
    void setKurimoLaikas(double laikas) { kurimoLaikas_ = laikas; }
    void setSkaitymoLaikas(double laikas) { skaitymoLaikas_ = laikas; }
    void setRusiavimoLaikas(double laikas) { rusiavimoLaikas_ = laikas; }
    void setRasymoLaikasVargsiukai(double laikas) { rasymoLaikasVargsiukai_ = laikas; }
    void setRasymoLaikasGalvociai(double laikas) { rasymoLaikasGalvociai_ = laikas; }
};


double skaiciuotiVidurki(const list<int>& namuDarbai);
double skaiciuotiMediana(const list<int>& namuDarbai);
char gautiTinkamaSymboli(const string &pranesimas, const string &tinkamisymboliai);
void generuotiRezultatus(Studentas &studentas, int namuDarbaiKiekis);
double nuskaitytiDuomenisIsFailo(const string& failoPavadinimas, list<Studentas>& studentai);
double generuotiFailus(int studentuKiekis, int namuDarbaiKiekis, const string &filePrefix);
void rodytiRezultatus(const list<Studentas>& studentai, bool naudotiVidurki);
void rodytiGreicioAnalizesRezultatus(const string& failoPavadinimas);
void failuApdorojimoCiklas();
void greicioAnalize();


#endif // FUNKCIJOS_H
