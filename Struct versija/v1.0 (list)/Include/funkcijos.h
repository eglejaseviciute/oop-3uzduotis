#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H


#include "myLib.h"
#include "studentas.h"


// Strukturos aprasymas veikimo greicio analizes matavimams
struct VeikimoGreicioMatavimai {
    double kurimoLaikas = 0.0;
    double skaitymoLaikas = 0.0;
    double rusiavimoLaikas = 0.0;
    double rasymoLaikasVargsiukai = 0.0;
    double rasymoLaikasGalvociai = 0.0;
};


double skaiciuotiVidurki(const list<int>& namuDarbai);
double skaiciuotiMediana(const list<int>& namuDarbai);
char gautiTinkamaSymboli(const string &pranesimas, const string &tinkamisymboliai);
void generuotiRezultatus(Studentas &studentas, int namuDarbaiKiekis);
double skaiciuotiGalutiniBala(const Studentas &studentas, bool naudotiVidurki);
double nuskaitytiDuomenisIsFailo(const string& failoPavadinimas, list<Studentas>& studentai);
bool lygintiPagalPavarde(const Studentas &a, const Studentas &b);
bool lygintiPagalVarda(const Studentas &a, const Studentas &b);
bool lygintiPagalVardaIrPavarde(const Studentas &a, const Studentas &b);
double generuotiFailus(int studentuKiekis, int namuDarbaiKiekis, const string &filePrefix);
void rodytiRezultatus(const list<Studentas>& studentai, bool naudotiVidurki);
void rodytiGreicioAnalizesRezultatus(const string& failoPavadinimas);
void failuApdorojimoCiklas();
void greicioAnalize();


#endif // FUNKCIJOS_H
