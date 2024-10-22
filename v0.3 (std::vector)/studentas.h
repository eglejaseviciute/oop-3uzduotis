#ifndef STUDENTAS_H
#define STUDENTAS_H


#include "myLib.h"
#include "rezultatai.h"


struct Studentas {
    string vardas;
    string pavarde;
    Rezultatai rezultatai;
};


void ivestiStudenta(Studentas &studentas, bool atsitiktiniai, int namuDarbaiKiekis);
void spausdintiStudenta(const Studentas &studentas, bool naudotiVidurki);
void rusiuotiStudentus(const vector<Studentas> &studentai, vector<Studentas> &vargsiukai, vector<Studentas> &galvociai, bool naudotiVidurki);
void rasytiStudentusIFaila(const vector<Studentas> &studentai, const string &failoPavadinimas, bool naudotiVidurki);


#endif // STUDENTAS_H
