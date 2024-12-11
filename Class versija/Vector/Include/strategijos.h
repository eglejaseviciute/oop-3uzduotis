#ifndef STRATEGIJOS_H
#define STRATEGIJOS_H


#include "myLib.h"
#include "studentas.h"


/**
 * @brief Studentų rūšiavimo strategijų modulis
 * 
 * Šis modulis pateikia skirtingas strategijas studentų paskirstymui į 
 * "galvočius" (turinčius įvertinimą >= 5.0) ir "vargšiukus" (turinčius įvertinimą < 5.0).
 */

/**
 * @brief Pirma strategija: Studentų rūšiavimas naudojant du naujus konteinerius
 * 
 * Ši funkcija skirsto studentus į du atskirus konteinerius: 
 * "vargšiukus" ir "galvočius", priklausomai nuo jų galutinio balo.
 * 
 * @param studentai Pradinis studentų vektorius
 * @param vargsiukai Išvestinis vektorius žemesnių pažymių studentams
 * @param galvociai Išvestinis vektorius aukštesnių pažymių studentams
 * @param naudotiVidurki Parametras, nurodantis skaičiuoti galutinį balą su vidurkiu arba medianu
 * @return double Funkcijos vykdymo laikas sekundėmis
 * 
 */
double rusiuotiStudentusStrategija1(const vector<Studentas>& studentai, 
                                   vector<Studentas>& vargsiukai, 
                                   vector<Studentas>& galvociai, 
                                   bool naudotiVidurki);

/**
 * @brief Antra strategija: Studentų rūšiavimas naudojant vieną naują konteinerį
 * 
 * Ši funkcija skirsto studentus į "vargšiukus" ir pašalina "galvočius" 
 * iš pradinio konteinerio.
 * 
 * @param studentai Pradinis/galutinis studentų vektorius (bus modifikuotas)
 * @param vargsiukai Išvestinis vektorius žemesnių pažymių studentams
 * @param naudotiVidurki Parametras, nurodantis skaičiuoti galutinį balą su vidurkiu arba medianu
 * @return double Funkcijos vykdymo laikas sekundėmis
 * 
 */
double rusiuotiStudentusStrategija2(vector<Studentas>& studentai, 
                                   vector<Studentas>& vargsiukai, 
                                   bool naudotiVidurki);

/**
 * @brief Trečia strategija: Optimizuotas studentų rūšiavimas
 * 
 * Ši funkcija naudoja indeksų vektorių ir stabilų rūšiavimą 
 * efektyvesniam studentų paskirstymui.
 * 
 * @param studentai Pradinis/galutinis studentų vektorius (bus modifikuotas)
 * @param vargsiukai Išvestinis vektorius žemesnių pažymių studentams
 * @param naudotiVidurki Parametras, nurodantis skaičiuoti galutinį balą su vidurkiu arba medianu
 * @return double Funkcijos vykdymo laikas sekundėmis
 * 
 */
double rusiuotiStudentusStrategija3(vector<Studentas>& studentai, 
                                   vector<Studentas>& vargsiukai, 
                                   bool naudotiVidurki);

/**
 * @brief Strategijos testavimo funkcija
 * 
 * Ši funkcija atlieka vienos strategijos testavimą, išmatuoja 
 * vykdymo laiką ir atspausdina rezultatus.
 * 
 * @param strategijaPavadinimas Testuojamos strategijos pavadinimas
 * @param studentai Studentų vektorius testavimui
 * @param naudotiVidurki Parametras, nurodantis skaičiavimo metodą
 */
void testuotiStrategija(const string& strategijaPavadinimas,
                       vector<Studentas>& studentai,
                       bool naudotiVidurki);

/**
 * @brief Strategijų palyginimo funkcija
 * 
 * Ši funkcija atlieka visų trijų strategijų testavimą ir 
 * palyginimą, išvedant kiekvienos strategijos rezultatus.
 * 
 * @param studentai Studentų vektorius testams
 * @param naudotiVidurki Parametras, nurodantis skaičiavimo metodą
 */
void palygintiStrategijas(vector<Studentas>& studentai, 
                         bool naudotiVidurki);


#endif // STRATEGIJOS_H
