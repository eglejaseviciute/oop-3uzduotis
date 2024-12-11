#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H


#include "myLib.h"
#include "studentas.h"


/**
 * @brief Klasė, skirta matuoti ir saugoti veikimo greičio duomenis.
 * 
 * Ši klasė kaupia laikus įvairiems veiksmams: failo kūrimui, skaitymui, rūšiavimui ir rezultatų rašymui.
 */
class VeikimoGreicioMatavimai {
private:
    double kurimoLaikas_; ///< Laikas, skirtas failo sukūrimui
    double skaitymoLaikas_; ///< Laikas, skirtas duomenų nuskaitymui iš failo
    double rusiavimoLaikas_; ///< Laikas, skirtas studentų rūšiavimui
    double rasymoLaikasVargsiukai_; ///< Laikas, skirtas rašyti vargsiukų duomenis į failą
    double rasymoLaikasGalvociai_; ///< Laikas, skirtas rašyti galvočių duomenis į failą

public:
    /**
     * @brief Konstruktorius, inicializuojantis laikus nuliais.
     */
    VeikimoGreicioMatavimai() :
        kurimoLaikas_(0.0),
        skaitymoLaikas_(0.0),
        rusiavimoLaikas_(0.0),
        rasymoLaikasVargsiukai_(0.0),
        rasymoLaikasGalvociai_(0.0) {}

    /**
     * @brief Geteris, grąžinantis failo kūrimo laiką.
     * @return Kurimo laikas (sekundėmis)
     */
    double getKurimoLaikas() const { return kurimoLaikas_; }

    /**
     * @brief Geteris, grąžinantis failo nuskaitymo laiką.
     * @return Skaitymo laikas (sekundėmis)
     */
    double getSkaitymoLaikas() const { return skaitymoLaikas_; }

    /**
     * @brief Geteris, grąžinantis rūšiavimo laiką.
     * @return Rūšiavimo laikas (sekundėmis)
     */
    double getRusiavimoLaikas() const { return rusiavimoLaikas_; }

    /**
     * @brief Geteris, grąžinantis vargšiukų rezultatų rašymo laiką.
     * @return Vargšiukų rašymo laikas (sekundėmis)
     */
    double getRasymoLaikasVargsiukai() const { return rasymoLaikasVargsiukai_; }

    /**
     * @brief Geteris, grąžinantis galvočių rezultatų rašymo laiką.
     * @return Galvočių rašymo laikas (sekundėmis)
     */
    double getRasymoLaikasGalvociai() const { return rasymoLaikasGalvociai_; }

    /**
     * @brief Seteris, nustatantis failo kūrimo laiką.
     * @param laikas Laiko reikšmė (sekundėmis)
     */
    void setKurimoLaikas(double laikas) { kurimoLaikas_ = laikas; }

    /**
     * @brief Seteris, nustatantis failo nuskaitymo laiką.
     * @param laikas Laiko reikšmė (sekundėmis)
     */
    void setSkaitymoLaikas(double laikas) { skaitymoLaikas_ = laikas; }

    /**
     * @brief Seteris, nustatantis rūšiavimo laiką.
     * @param laikas Laiko reikšmė (sekundėmis)
     */
    void setRusiavimoLaikas(double laikas) { rusiavimoLaikas_ = laikas; }

    /**
     * @brief Seteris, nustatantis vargšiukų rezultatų rašymo laiką.
     * @param laikas Laiko reikšmė (sekundėmis)
     */
    void setRasymoLaikasVargsiukai(double laikas) { rasymoLaikasVargsiukai_ = laikas; }

    /**
     * @brief Seteris, nustatantis galvočių rezultatų rašymo laiką.
     * @param laikas Laiko reikšmė (sekundėmis)
     */
    void setRasymoLaikasGalvociai(double laikas) { rasymoLaikasGalvociai_ = laikas; }
};

/**
 * @brief Funkcija, apskaičiuojanti namų darbų vidurkį.
 * 
 * @param namuDarbai Vektorius su studento namų darbų rezultatais
 * @return Vidurkis
 */
double skaiciuotiVidurki(const vector<int>& namuDarbai);

/**
 * @brief Funkcija, apskaičiuojanti namų darbų medianą.
 * 
 * @param namuDarbai Vektorius su studento namų darbų rezultatais
 * @return Mediana
 */
double skaiciuotiMediana(vector<int> namuDarbai);

/**
 * @brief Funkcija, gaunanti tinkamą simbolį iš vartotojo.
 * 
 * @param pranesimas Pranešimas, kuris bus rodomas vartotojui
 * @param tinkamiSymboliai Galimi simboliai
 * @return Tinkamas simbolis
 */
char gautiTinkamaSymboli(const string &pranesimas, const string &tinkamiSymboliai);

/**
 * @brief Funkcija, generuojanti atsitiktinius rezultatus studentui.
 * 
 * @param studentas Studentas, kuriam bus sugeneruoti rezultatai
 * @param namuDarbaiKiekis Namų darbų skaičius
 */
void generuotiRezultatus(Studentas &studentas, int namuDarbaiKiekis);

/**
 * @brief Funkcija, nuskaityti studentų duomenis iš failo.
 * 
 * @param failoPavadinimas Failo pavadinimas
 * @param studentai Vektorius, kuriame bus saugomi studentai
 * @return Skaitymo laikas (sekundėmis)
 */
double nuskaitytiDuomenisIsFailo(const string& failoPavadinimas, vector<Studentas>& studentai);

/**
 * @brief Funkcija, lyginanti studentus pagal pavardę.
 * 
 * @param a Pirmas studentas
 * @param b Antras studentas
 * @return Ar pirmo studento pavardė yra anksčiau pagal abėcėlę nei antro
 */
bool lygintiPagalPavarde(const Studentas& a, const Studentas& b);

/**
 * @brief Funkcija, lyginanti studentus pagal vardą.
 * 
 * @param a Pirmas studentas
 * @param b Antras studentas
 * @return Ar pirmo studento vardas yra anksčiau pagal abėcėlę nei antro
 */
bool lygintiPagalVarda(const Studentas& a, const Studentas& b);

/**
 * @brief Funkcija, lyginanti studentus pagal vardą ir pavardę.
 * 
 * @param a Pirmas studentas
 * @param b Antras studentas
 * @return Ar pirmo studento vardas ir pavardė yra anksčiau pagal abėcėlę nei antro
 */
bool lygintiPagalVardaIrPavarde(const Studentas& a, const Studentas& b);

/**
 * @brief Funkcija, generuojanti failą su studentų duomenimis.
 * 
 * @param studentuKiekis Studentų kiekis
 * @param namuDarbaiKiekis Namų darbų kiekis
 * @param filePrefix Failo pavadinimo prefiksas
 * @return Failo kūrimo laikas (sekundėmis)
 */
double generuotiFailus(int studentuKiekis, int namuDarbaiKiekis, const string &filePrefix);

/**
 * @brief Funkcija, rašanti studentų duomenis į failą.
 * 
 * @param studentai Studentų vektorius
 * @param failoPavadinimas Failo pavadinimas
 * @param naudotiVidurki Ar naudoti vidurkį galutiniam balui apskaičiuoti
 * @return Rašymo laikas (sekundėmis)
 */
double rasytiStudentusIFaila(const vector<Studentas>& studentai, const string& failoPavadinimas, bool naudotiVidurki);

/**
 * @brief Funkcija, rodanti studentų rezultatus ekrane.
 * 
 * @param studentai Studentų vektorius
 * @param naudotiVidurki Ar naudoti vidurkį galutiniam balui apskaičiuoti
 */
void rodytiRezultatus(const vector<Studentas>& studentai, bool naudotiVidurki);


/**
 * @brief Rodo greičio analizės rezultatus pagal pateiktą failo pavadinimą.
 *
 * Tai funkcija, kuri atlieka greičio analizę ir išveda rezultatus apie failo apdorojimo laiko etapus,
 * tokius kaip failo skaitymo laikas, rūšiavimo laikas, rašymo laikas vargšiukams ir galvočiams, bei bendras laikas.
 *
 * @param failoPavadinimas Failo pavadinimas, kurio greičio analizė bus atliekama.
 */
void rodytiGreicioAnalizesRezultatus(const std::string& failoPavadinimas);

/**
 * @brief Atlieka failų apdorojimo ciklą.
 *
 * Funkcija leidžia vartotojui pasirinkti failus, kuriuos nori apdoroti. Ji tikrina, ar failas jau buvo apdorotas,
 * tuomet nuskaito duomenis iš failo, tada pasirenkiamad galutinio balo skaičiavimo metodas ir studentai surūšiuojami pagal pasirinktą
 * strategiją. Po apdorojimo rezultatai įrašomi į atskirus failus "vargsiukai" ir "galvociai".
 */
void failuApdorojimoCiklas();

/**
 * @brief Atlieka greičio analizę.
 *
 * Ši funkcija leidžia vartotojui įvesti failo pavadinimą ir atlikti greičio analizę, tikrinant apdorojimo
 * laikus pagal skirtingas rūšiavimo strategijas, taip pat įrašant rezultatus į atskirus failus.
 * 
 * @note Pasirinkimas apdoroti kelis failus ir įrašyti juos į naujus failus.
 */
void greicioAnalize();

/**
 * @brief Demonstracija, kaip veikia "Rule of Three" principas.
 *
 * Tai demonstracinė funkcija, kuri rodo, kaip veikia "Rule of Three" principas C++, kur yra naudojami konstruktoriai,
 * destruktoriai ir operatoriai priskyrimui.
 */
void RuleOfThreeDemonstravimas();

/**
 * @brief Demonstracija, kaip naudojamos abstrakčios klasės.
 *
 * Demonstracija, kaip abstrakčių klasių objektai gali būti naudojami per rodykles. Ši funkcija parodo, kaip sukurti
 * rodykles į abstrakčias klases ir kaip pasiekti paveldėtas funkcijas.
 */
void abstrakciosKlasesZmogusDemonstravimas();

/**
 * @brief Rūšiavimo klasė, skirta studentams rūšiuoti pagal galutinį balą didėjančia tvarka.
 *
 * Ši klasė naudojama studentų sąrašui rūšiuoti pagal jų galutinį balą (vidurkį arba medianą) didėjančia tvarka.
 */
class RusiuotiPagalGalutiniBalaDidejanciai {
private:
    bool naudotiVidurki; ///< Nurodo, ar turėtų būti naudojamas vidurkis galutinio balo skaičiavimui.
public:
    /**
     * @brief Konstruktoras, nustatantis, ar bus naudojamas vidurkis.
     *
     * @param naudotiVid Nustato, ar naudoti vidurkį galutinio balo skaičiavimui.
     */
    RusiuotiPagalGalutiniBalaDidejanciai(bool naudotiVid) : naudotiVidurki(naudotiVid) {}

    /**
     * @brief Operatorius, leidžiantis palyginti du studentus pagal galutinį balą didėjančia tvarka.
     *
     * @param a Pirmas studentas.
     * @param b Antras studentas.
     * @return true, jei pirmas studentas turi mažesnį galutinį balą nei antras.
     * @return false, jei pirmas studentas turi didesnį galutinį balą nei antras.
     */
    bool operator()(const Studentas& a, const Studentas& b) const {
        return a.skaiciuotiGalutiniBala(naudotiVidurki) < b.skaiciuotiGalutiniBala(naudotiVidurki);
    }
};

/**
 * @brief Rūšiavimo klasė, skirta studentams rūšiuoti pagal galutinį balą mažėjimo tvarka.
 *
 * Ši klasė naudojama studentų sąrašui rūšiuoti pagal jų galutinį balą (vidurkį arba medianą) mažėjimo tvarka.
 */
class RusiuotiPagalGalutiniBalaMazejanciai {
private:
    bool naudotiVidurki; ///< Nurodo, ar turėtų būti naudojamas vidurkis galutinio balo skaičiavimui.
public:
    /**
     * @brief Konstruktoras, nustatantis, ar bus naudojamas vidurkis.
     *
     * @param naudotiVid Nustato, ar naudoti vidurkį galutinio balo skaičiavimui.
     */
    RusiuotiPagalGalutiniBalaMazejanciai(bool naudotiVid) : naudotiVidurki(naudotiVid) {}

    /**
     * @brief Operatorius, leidžiantis palyginti du studentus pagal galutinį balą mažėjimo tvarka.
     *
     * @param a Pirmas studentas.
     * @param b Antras studentas.
     * @return true, jei pirmas studentas turi didesnį galutinį balą nei antras.
     * @return false, jei pirmas studentas turi mažesnį galutinį balą nei antras.
     */
    bool operator()(const Studentas& a, const Studentas& b) const {
        return a.skaiciuotiGalutiniBala(naudotiVidurki) > b.skaiciuotiGalutiniBala(naudotiVidurki);
    }
};


#endif // FUNKCIJOS_H
