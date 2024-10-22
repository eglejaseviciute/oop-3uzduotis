#ifndef STUDENTAS_H
#define STUDENTAS_H


#include "rezultatai.h"
#include "myLib.h"


// Strukturos aprasymas studentui
struct Studentas {
    string vardas;
    string pavarde;
    Rezultatai rezultatai;
};


void ivestiStudenta(Studentas &studentas, bool atsitiktiniai, int namuDarbaiKiekis);
void spausdintiStudenta(const Studentas &studentas, bool naudotiVidurki);
double rusiuotiStudentus(const vector<Studentas> &studentai, vector<Studentas> &vargsiukai, vector<Studentas> &galvociai, bool naudotiVidurki);
double rasytiStudentusIFaila(const vector<Studentas> &studentai, const string &failoPavadinimas, bool naudotiVidurki);


#endif // STUDENTAS_H
