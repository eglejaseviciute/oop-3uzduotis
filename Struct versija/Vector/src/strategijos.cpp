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
        return skaiciuotiGalutiniBala(s, naudotiVidurki) >= 5.0;
    }
};


class VargsiukuTikrintojas {
private:
    bool naudotiVidurki;
public:
    VargsiukuTikrintojas(bool naudotiVid) : naudotiVidurki(naudotiVid) {}
    
    bool operator()(const Studentas& s) const {
        return skaiciuotiGalutiniBala(s, naudotiVidurki) < 5.0;
    }
};


class PazymioSkaiciuokle {
private:
    bool naudotiVidurki;
public:
    PazymioSkaiciuokle(bool naudotiVid) : naudotiVidurki(naudotiVid) {}
    
    pair<Studentas, double> operator()(const Studentas& s) const {
        return make_pair(s, skaiciuotiGalutiniBala(s, naudotiVidurki));
    }
};


class IndeksuSkirstytojas {
private:
    const vector<Studentas>& studentai;
    bool naudotiVidurki;
public:
    IndeksuSkirstytojas(const vector<Studentas>& stud, bool naudotiVid) 
        : studentai(stud), naudotiVidurki(naudotiVid) {}
    
    bool operator()(size_t i) const {
        return skaiciuotiGalutiniBala(studentai[i], naudotiVidurki) >= 5.0;
    }
};


// Strategija 1: Du nauji konteineriai
double rusiuotiStudentusStrategija1(const vector<Studentas>& studentai, 
                                   vector<Studentas>& vargsiukai, 
                                   vector<Studentas>& galvociai, 
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
double rusiuotiStudentusStrategija2(vector<Studentas>& studentai, 
                                   vector<Studentas>& vargsiukai, 
                                   bool naudotiVidurki) {
    auto pradzia = std::chrono::high_resolution_clock::now();
    
    vargsiukai.clear();
    vector<Studentas> galvociai;
    
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
double rusiuotiStudentusStrategija3(vector<Studentas>& studentai, 
                                     vector<Studentas>& vargsiukai, 
                                     bool naudotiVidurki) {
    auto pradzia = std::chrono::high_resolution_clock::now();
    
    vargsiukai.clear();
    
    // Sukuriame indeksu vektoriu rusiavimui
    vector<size_t> indeksai(studentai.size());
    iota(indeksai.begin(), indeksai.end(), 0);
    
    // Suskirstome indeksus pagal studentu pazymius
    IndeksuSkirstytojas skirstytojas(studentai, naudotiVidurki);
    auto skirstymoTaskas = stable_partition(indeksai.begin(), indeksai.end(), skirstytojas);
    
    // Rezervuojame vieta vargsiukams
    vargsiukai.reserve(distance(skirstymoTaskas, indeksai.end()));
    
    // Kopijuojame vargsiukus naudodami indeksus
    for (auto it = skirstymoTaskas; it != indeksai.end(); ++it) {
        vargsiukai.push_back(studentai[*it]);
    }
    
    // Pasaliname vargsiukus is pradinio konteinerio
    VargsiukuTikrintojas vargsiukuTikr(naudotiVidurki);
    auto naujasPabaiga = remove_if(studentai.begin(), studentai.end(), vargsiukuTikr);
    studentai.erase(naujasPabaiga, studentai.end());
    
    auto pabaiga = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(pabaiga - pradzia).count();
}


void testuotiStrategija(const string& strategijaPavadinimas,
                       vector<Studentas>& studentai,
                       bool naudotiVidurki) {
    vector<Studentas> vargsiukai, galvociai;
    vector<Studentas> studentaiKopija = studentai;
    double laikas;
    
    cout << "\nTestavimas: " << strategijaPavadinimas << endl;
    cout << "Studentu skaicius: " << studentai.size() << endl;
    
    if (strategijaPavadinimas == "1 Strategija (du nauji konteineriai)") {
        laikas = rusiuotiStudentusStrategija1(studentaiKopija, vargsiukai, galvociai, naudotiVidurki);
        cout << "Atmintis: " << (vargsiukai.size() + galvociai.size()) * sizeof(Studentas) / 1024.0 
             << " KB" << endl;
    }
    else if (strategijaPavadinimas == "2 Strategija (vienas naujas konteineris)") {
        laikas = rusiuotiStudentusStrategija2(studentaiKopija, vargsiukai, naudotiVidurki);
        cout << "Atmintis: " << vargsiukai.size() * sizeof(Studentas) / 1024.0 
             << " KB" << endl;
    }
    else {
        laikas = rusiuotiStudentusStrategija3(studentaiKopija, vargsiukai, naudotiVidurki);
        cout << "Atmintis: " << vargsiukai.size() * sizeof(Studentas) / 1024.0 
             << " KB" << endl;
    }
    
    cout << "Rusiavimo laikas: " << laikas << " s" << endl;
}


void palygintiStrategijas(vector<Studentas>& studentai, bool naudotiVidurki) {
    cout << "\nStrategiju palyginimas su " << studentai.size() << " studentu:\n";
    
    vector<string> strategijos;
    strategijos.push_back("1 Strategija (du nauji konteineriai)");
    strategijos.push_back("2 Strategija (vienas naujas konteineris)");
    strategijos.push_back("3 Strategija (optimizuota)");
    
    for (const auto& strategija : strategijos) {
        testuotiStrategija(strategija, studentai, naudotiVidurki);
    }
}
