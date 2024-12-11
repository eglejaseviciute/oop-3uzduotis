#ifndef STUDENTAS_H
#define STUDENTAS_H


#include "zmogus.h"
#include "myLib.h"


/**
 * @brief Studentų valdymo klasė
 * 
 * Ši klasė paveldi iš Zmogus klasės ir prideda specifines studento savybes,
 * tokias kaip namų darbų rezultatai ir egzamino balas.
 */
class Studentas : public Zmogus {
private:
    vector<int> namuDarbai_;   /**< Studento namų darbų rezultatų sąrašas */
    int egzaminas_;            /**< Studento egzamino rezultatas */

public:
    /**
     * @brief Konstruktorius su numatytosiomis reikšmėmis
     * 
     * Sukuria Studentas objektą su pasirinktiniais vardo, pavardės parametrais.
     * Inicializuoja egzamino balą į 0.
     * 
     * @param vardas Studento vardas (numatytoji reikšmė - tuščias string)
     * @param pavarde Studento pavardė (numatytoji reikšmė - tuščias string)
     */
    Studentas(const string& vardas = "", const string& pavarde = "") 
        : Zmogus(vardas, pavarde), egzaminas_(0) {}

    /**
     * @brief Copy konstruktorius
     * 
     * Sukuria naują Studentas objektą pagal jau egzistuojantį.
     * Dalis Rule of Three principo realizacijos.
     * 
     * @param other Kopijuojamas Studentas objektas
     */
    Studentas(const Studentas& other) 
        : Zmogus(other.vardas_, other.pavarde_), 
          namuDarbai_(other.namuDarbai_), 
          egzaminas_(other.egzaminas_) {}

    /**
     * @brief Priskyrimo operatorius
     * 
     * Leidžia priskirti vieno Studentas objekto reikšmes kitam.
     * Dalis Rule of Three principo realizacijos.
     * 
     * @param other Priskiriamas Studentas objektas
     * @return Nuoroda į pakeistą objektą
     */
    Studentas& operator=(const Studentas& other) {
        if (this != &other) {
            Zmogus::operator=(other);
            namuDarbai_ = other.namuDarbai_;
            egzaminas_ = other.egzaminas_;
        }
        return *this;
    }

    /**
     * @brief Destruktorius
     * 
     * Atlaisvina resursus ir išvalo namų darbų vektorių.
     * Dalis Rule of Three principo realizacijos.
     */
    ~Studentas() {
        namuDarbai_.clear();
    }

    // Getteriai
    /**
     * @brief Grąžina studento namų darbų rezultatus
     * @return Namų darbų rezultatų vektorius
     */
    inline const vector<int>& namuDarbai() const { return namuDarbai_; }

    /**
     * @brief Grąžina studento egzamino balą
     * @return Egzamino balas
     */
    inline int egzaminas() const { return egzaminas_; }

    // Setteriai
    /**
     * @brief Nustato studento egzamino balą
     * @param egz Naujas egzamino balas
     */
    void setEgzaminas(int egz) { egzaminas_ = egz; }

    /**
     * @brief Prideda naują namų darbų pažymį
     * @param pazymys Naujas pažymys
     */
    void addNamuDarbas(int pazymys) { namuDarbai_.push_back(pazymys); }

    /**
     * @brief Išvalo visus namų darbų pažymius
     */
    void clearNamuDarbai() { namuDarbai_.clear(); }

    /**
     * @brief Nustato visus namų darbų pažymius
     * @param namuDarbai Naujas namų darbų pažymių vektorius
     */
    void setNamuDarbai(const vector<int>& namuDarbai) { namuDarbai_ = namuDarbai; }

    // Metodai
    /**
     * @brief Įveda studento duomenis
     * 
     * Leidžia įvesti studento duomenis rankiniu būdu arba generuoti atsitiktinius.
     * 
     * @param atsitiktiniai Ar generuoti atsitiktinius duomenis
     * @param namuDarbaiKiekis Atsitiktinių namų darbų kiekis (jei generuojami)
     */
    void ivestiStudenta(bool atsitiktiniai, int namuDarbaiKiekis);

    /**
     * @brief Apskaičiuoja studento galutinius balus
     * 
     * Skaičiuoja galutinius balus pagal pasirinktą skaičiavimo metodą
     * (vidurkis arba mediana).
     * 
     * @param naudotiVidurki Ar naudoti vidurkį (true), ar medianą (false)
     * @return Galutinis studento balas
     */
    double skaiciuotiGalutiniBala(bool naudotiVidurki) const;

    /**
     * @brief Virtuali funkcija informacijos spausdinimui
     * 
     * Realizuoja bazinės Zmogus klasės abstraktų metodą.
     * Atspausdina studento vardą ir pavardę.
     */
    void spausdintiInformacija() const override {
        cout << "Studentas: " << vardas_ << " " << pavarde_ << "\n";
    }

    // Įvesties ir išvesties operatoriai
    /**
     * @brief Įvesties operatorius studento duomenų nuskaitymui
     * 
     * Leidžia nuskaityti studento duomenis iš įvesties srauto
     * (konsoles arba failo).
     * 
     * @param is Įvesties srautas
     * @param studentas Studentas objektas, kuriam bus priskirti nuskaityti duomenys
     * @return Nuoroda į įvesties srautą
     */
    friend istream& operator>>(istream& is, Studentas& studentas);

    /**
     * @brief Išvesties operatorius studento duomenų spausdinimui
     * 
     * Atspausdina studento vardą, pavardę ir galutinius balus.
     * 
     * @param os Išvesties srautas
     * @param studentas Studentas objektas, kurio duomenys bus spausdinami
     * @return Nuoroda į išvesties srautą
     */
    friend ostream& operator<<(ostream& os, const Studentas& studentas);
};


#endif // STUDENTAS_H
