#include "funkcijos.h"
#include "myLib.h"
#include "studentas.h"


// Funkciju objektai skirtingoms operacijoms
class GalvociuTikrintojas {
private:
    bool naudotiVidurki;
public:
    GalvociuTikrintojas(bool naudotiVid) : naudotiVidurki(naudotiVid) {}
    
    bool operator()(const Studentas& s) const {
        return s.skaiciuotiGalutiniBala(naudotiVidurki) >= 5.0;
    }
};


class VargsiukuTikrintojas {
private:
    bool naudotiVidurki;
public:
    VargsiukuTikrintojas(bool naudotiVid) : naudotiVidurki(naudotiVid) {}
    
    bool operator()(const Studentas& s) const {
        return s.skaiciuotiGalutiniBala(naudotiVidurki) < 5.0;
    }
};


// Strategija 1: Du nauji konteineriai
double rusiuotiStudentusStrategija1(const list<Studentas>& studentai, 
                                   list<Studentas>& vargsiukai, 
                                   list<Studentas>& galvociai, 
                                   bool naudotiVidurki) {
    auto pradzia = std::chrono::high_resolution_clock::now();
    
    vargsiukai.clear();
    galvociai.clear();
    
    VargsiukuTikrintojas vargsiukuTikr(naudotiVidurki);
    GalvociuTikrintojas galvociuTikr(naudotiVidurki);
    
    for (const auto& studentas : studentai) {
        if (vargsiukuTikr(studentas)) {
            vargsiukai.push_back(studentas);
        } else {
            galvociai.push_back(studentas);
        }
    }
    
    auto pabaiga = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(pabaiga - pradzia).count();
}


// Strategija 2: Vienas naujas konteineris
double rusiuotiStudentusStrategija2(list<Studentas>& studentai, 
                                   list<Studentas>& vargsiukai, 
                                   bool naudotiVidurki) {
    auto pradzia = std::chrono::high_resolution_clock::now();
    
    vargsiukai.clear();
    list<Studentas> galvociai;
    
    GalvociuTikrintojas tikrintojas(naudotiVidurki);
    
    for (const auto& studentas : studentai) {
        if (tikrintojas(studentas)) {
            galvociai.push_back(studentas);
        } else {
            vargsiukai.push_back(studentas);
        }
    }
    
    studentai = move(galvociai);
    
    auto pabaiga = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(pabaiga - pradzia).count();
}


// Strategija 3: Optimizuota
double rusiuotiStudentusStrategija3(list<Studentas>& studentai, 
                                   list<Studentas>& vargsiukai, 
                                   bool naudotiVidurki) {
    auto pradzia = std::chrono::high_resolution_clock::now();
    
    vargsiukai.clear();
    
    // Naudojame stable_partition tiesiai su studentu sarasu
    GalvociuTikrintojas tikrintojas(naudotiVidurki);
    auto skirstymoTaskas = stable_partition(studentai.begin(), studentai.end(), tikrintojas);
    
    // Perkeliame vargsiukus i ju sarasa
    vargsiukai.splice(vargsiukai.end(), studentai, skirstymoTaskas, studentai.end());
    
    auto pabaiga = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(pabaiga - pradzia).count();
}


void testuotiStrategija(const string& strategijaPavadinimas,
                       list<Studentas>& studentai,
                       bool naudotiVidurki) {
    list<Studentas> vargsiukai, galvociai;
    list<Studentas> studentaiKopija = studentai;
    double laikas;
    
    cout << "\nTestavimas: " << strategijaPavadinimas << endl;
    cout << "Studentu skaicius: " << distance(studentai.begin(), studentai.end()) << endl;
    
    if (strategijaPavadinimas == "1 Strategija (du nauji konteineriai)") {
        laikas = rusiuotiStudentusStrategija1(studentaiKopija, vargsiukai, galvociai, naudotiVidurki);
        cout << "Atmintis: " << (distance(vargsiukai.begin(), vargsiukai.end()) + 
                                distance(galvociai.begin(), galvociai.end())) * sizeof(Studentas) / 1024.0 
             << " KB" << endl;
    }
    else if (strategijaPavadinimas == "2 Strategija (vienas naujas konteineris)") {
        laikas = rusiuotiStudentusStrategija2(studentaiKopija, vargsiukai, naudotiVidurki);
        cout << "Atmintis: " << distance(vargsiukai.begin(), vargsiukai.end()) * sizeof(Studentas) / 1024.0 
             << " KB" << endl;
    }
    else {
        laikas = rusiuotiStudentusStrategija3(studentaiKopija, vargsiukai, naudotiVidurki);
        cout << "Atmintis: " << distance(vargsiukai.begin(), vargsiukai.end()) * sizeof(Studentas) / 1024.0 
             << " KB" << endl;
    }
    
    cout << "Rusiavimo laikas: " << laikas << " s" << endl;
}


void palygintiStrategijas(list<Studentas>& studentai, bool naudotiVidurki) {
    cout << "\nStrategiju palyginimas su " << distance(studentai.begin(), studentai.end()) << " studentu:\n";
    
    list<string> strategijos;
    strategijos.push_back("1 Strategija (du nauji konteineriai)");
    strategijos.push_back("2 Strategija (vienas naujas konteineris)");
    strategijos.push_back("3 Strategija (optimizuota)");
    
    for (const auto& strategija : strategijos) {
        testuotiStrategija(strategija, studentai, naudotiVidurki);
    }
}