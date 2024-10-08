#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H


#include "myLib.h"
#include "studentas.h"


double skaiciuotiVidurki(const vector<int>& namuDarbai);
double skaiciuotiMediana(vector<int> namuDarbai);
void nuskaitytiDuomenisIsFailo(string &failoPavadinimas, vector<Studentas> &studentai);
bool lygintiPagalVarda(const Studentas &a, const Studentas &b);
void generuotiFailus(int studentuKiekis, int namuDarbaiKiekis, const string &filePrefix);
void rodytiRezultatus(const vector<Studentas>& studentai, bool naudotiVidurki);


#endif // FUNKCIJOS_H
