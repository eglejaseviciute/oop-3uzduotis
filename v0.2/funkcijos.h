#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H


#include "myLib.h"
#include "studentas.h"


double skaiciuotiVidurki(const vector<int>& namuDarbai);
double skaiciuotiMediana(vector<int> namuDarbai);
void generuotiRezultatus(Studentas &studentas, int namuDarbaiKiekis);
void nuskaitytiDuomenisIsFailo(string &failoPavadinimas, vector<Studentas> &studentai);
bool lygintiPagalPavarde(const Studentas &a, const Studentas &b);
bool lygintiPagalVarda(const Studentas &a, const Studentas &b);
bool lygintiPagalVardaIrPavarde(const Studentas &a, const Studentas &b);
double skaiciuotiGalutiniBala(const Studentas &studentas, bool naudotiVidurki);
void generuotiFailus(int studentuKiekis, int namuDarbaiKiekis, const string &filePrefix);
void procesarArchivosBucle();
void rodytiRezultatus(const vector<Studentas>& studentai, bool naudotiVidurki);


#endif // FUNKCIJOS_H
