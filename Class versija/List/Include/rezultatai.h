#ifndef REZULTATAI_H
#define REZULTATAI_H

#include "myLib.h"


// Rezultatai klase: skirta saugoti studento akademinius pasiekimus
class Rezultatai {
private:
    list<int> namuDarbai_;
    int egzaminas_;

public:
    // Konstruktorius, inicijuojantis egzamino pazymi i 0
    Rezultatai() : egzaminas_(0) {}
    
    // Destruktorius, automatiškai atlaisvina klasės išteklius
    ~Rezultatai() = default;

    // Getteriai, leidzia saugiai pasiekti privacius duomenis
    inline const list<int>& namuDarbai() const { return namuDarbai_; }
    inline int egzaminas() const { return egzaminas_; }
    
    // Setteriai, leidzia keisti ir prideti rezultatus
    void setEgzaminas(int egz) { egzaminas_ = egz; }
    void addNamuDarbas(int pazymys) { namuDarbai_.push_back(pazymys); }
    void clearNamuDarbai() { namuDarbai_.clear(); }
    void setNamuDarbai(const list<int>& namuDarbai) { namuDarbai_ = namuDarbai; }

    // Leidzia Studentas klasei prieiti prie privaciu nariu
    friend class Studentas;
};


#endif // REZULTATAI_H