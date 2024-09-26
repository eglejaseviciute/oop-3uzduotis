#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H


#include "studentas.h"
#include "myLib.h"


double skaiciuotiVidurki(const vector<int>& namuDarbai);
double skaiciuotiMediana(vector<int> namuDarbai);
void generuotiRezultatus(Studentas &studentas, int namuDarbaiKiekis);
void ivestiStudenta(Studentas &studentas, bool atsitiktiniai, int namuDarbaiKiekis);
void spausdintiStudenta(const Studentas &studentas, bool naudotiVidurki);
void nuskaitytiDuomenisIsFailo(string &failoPavadinimas, vector<Studentas> &studentai);
bool lygintiPagalVarda(const Studentas &a, const Studentas &b);


#endif // FUNKCIJOS_H
