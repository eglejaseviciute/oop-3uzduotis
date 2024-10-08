#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

#include <vector>
#include <string>
#include "studentas.h"

double skaiciuotiVidurki(const std::vector<int>& namuDarbai);
double skaiciuotiMediana(std::vector<int> namuDarbai);
void generuotiRezultatus(Studentas &studentas, int namuDarbaiKiekis);
void nuskaitytiDuomenisIsFailo(std::string &failoPavadinimas, std::vector<Studentas> &studentai);
void generuotiFailus(int studentuKiekis, int namuDarbaiKiekis, const std::string &filePrefix);

#endif // FUNKCIJOS_H
