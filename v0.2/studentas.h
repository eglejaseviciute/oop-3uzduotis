#ifndef STUDENTAS_H
#define STUDENTAS_H


#include "rezultatai.h"
#include "myLib.h"

struct Studentas {
    string vardas;
    string pavarde;
    Rezultatai rezultatai;
};

void ivestiStudenta(Studentas &studentas, bool atsitiktiniai, int namuDarbaiKiekis);
void spausdintiStudenta(const Studentas &studentas, bool naudotiVidurki);
bool lygintiPagalVarda(const Studentas &a, const Studentas &b);

#endif // STUDENTAS_H
