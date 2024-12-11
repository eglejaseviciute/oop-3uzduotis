#ifndef ZMOGUS_H
#define ZMOGUS_H


#include "myLib.h"


/**
 * @brief Abstrakti bazinė Zmogus klasė
 * 
 * Ši klasė yra abstrakti bazinė klasė, skirta saugoti bendrus duomenis.
 * Ji naudojama kaip pagrindinė klasė, iš kurios bus paveldimos kitos konkrečios klasės.
 */
class Zmogus {
protected:
    string vardas_;     /**< Žmogaus vardas */
    string pavarde_;    /**< Žmogaus pavardė */

public:
    /**
     * @brief Konstruktorius su numatytosiomis reikšmėmis
     * 
     * Sukuria Zmogus objektą su pasirinktiniais vardo ir pavardės parametrais.
     * 
     * @param vardas Žmogaus vardas (numatytoji reikšmė - tuščias string)
     * @param pavarde Žmogaus pavardė (numatytoji reikšmė - tuščias string)
     */
    Zmogus(const string& vardas = "", const string& pavarde = "") 
        : vardas_(vardas), pavarde_(pavarde) {}

    /**
     * @brief Virtualusis destruktorius
     * 
     * Atlaisvina resursus ir išvalo vardo bei pavardės string'us.
     */
    virtual ~Zmogus() {
        vardas_.clear();
        pavarde_.clear();
    }

    /**
     * @brief Abstrakti virtuali funkcija informacijos spausdinimui
     * 
     * Ši funkcija turi būti realizuota išvestinėse klasėse.
     * Skirta atspausdinti specifinę informaciją apie objektą.
     */
    virtual void spausdintiInformacija() const = 0;

    // Getteriai
    /**
     * @brief Grąžina žmogaus vardą
     * @return Žmogaus vardas
     */
    inline string vardas() const { return vardas_; }

    /**
     * @brief Grąžina žmogaus pavardę
     * @return Žmogaus pavardė
     */
    inline string pavarde() const { return pavarde_; }

    // Setteriai
    /**
     * @brief Nustato žmogaus vardą
     * @param vardas Naujas vardas
     */
    void setVardas(const string& vardas) { vardas_ = vardas; }

    /**
     * @brief Nustato žmogaus pavardę
     * @param pavarde Nauja pavardė
     */
    void setPavarde(const string& pavarde) { pavarde_ = pavarde; }
};


#endif // ZMOGUS_H
