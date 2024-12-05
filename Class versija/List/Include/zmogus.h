#ifndef ZMOGUS_H
#define ZMOGUS_H


#include "myLib.h"


// Abstrakti bazine Zmogus klase
class Zmogus {
protected:
    string vardas_;
    string pavarde_;

public:
    // Konstruktorius
    Zmogus(const string& vardas = "", const string& pavarde = "") 
        : vardas_(vardas), pavarde_(pavarde) {}

     // Destruktorius   
    virtual ~Zmogus() {
        vardas_.clear();
        pavarde_.clear();
    }

    // Virtuali funkcija (daro klase abstrakcia)
    virtual void spausdintiInformacija() const = 0;

    // Getteriai ir setteriai
    inline string vardas() const { return vardas_; }
    inline string pavarde() const { return pavarde_; }
    void setVardas(const string& vardas) { vardas_ = vardas; }
    void setPavarde(const string& pavarde) { pavarde_ = pavarde; }
};


#endif // ZMOGUS_H
