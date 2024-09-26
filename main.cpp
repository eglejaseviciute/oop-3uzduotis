#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>

using std::endl;
using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::numeric_limits;
using std::streamsize;
using std::left;
using std::right;
using std::setw;
using std::setprecision;
using std::fixed;
using std::getline;


// Struktura, skirta namu darbu ir egzamino rezultatams saugoti
struct Rezultatai {
    vector<int> namuDarbai;
    int egzaminas;
};


// Struktura, skirta studento duomenims saugoti
struct Studentas {
    string vardas;
    string pavarde;
    Rezultatai rezultatai; // Naudojame Rezultatai struktura
};


// Funkcija, kuri skaiciuoja vidurki is namu darbu rezultatu
double skaiciuotiVidurki(const vector<int>& namuDarbai) {
    double suma = 0;
    for (int nd : namuDarbai) {
        suma += nd;
    }
    return suma / namuDarbai.size();
}


// Funkcija, kuri skaiciuoja mediana is namu darbu rezultatu
double skaiciuotiMediana(vector<int> namuDarbai) {
    std::sort(namuDarbai.begin(), namuDarbai.end());
    int dydis = namuDarbai.size();
    if (dydis % 2 == 0) {
        return (namuDarbai[dydis / 2 - 1] + namuDarbai[dydis / 2]) / 2.0;
    } else {
        return namuDarbai[dydis / 2];
    }
}


// Funkcija, kuri generuoja atsitiktinius rezultatus
void generuotiRezultatus(Studentas &studentas, int namuDarbaiKiekis) {
    for (int i = 0; i < namuDarbaiKiekis; ++i) {
        studentas.rezultatai.namuDarbai.push_back(rand() % 11); // Generuojame atsitiktini namu darbu rezultatus nuo 0 iki 10
    }
    studentas.rezultatai.egzaminas = rand() % 11; // Generuojame atsitiktini egzamino rezultata nuo 0 iki 10
}


// Funkcija, kuri iveda studento duomenis
void ivestiStudenta(Studentas &studentas, bool atsitiktiniai, int namuDarbaiKiekis) {
    cout << "Iveskite studento varda: ";
    cin >> studentas.vardas;
    cout << "Iveskite studento pavarde: ";
    cin >> studentas.pavarde;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (atsitiktiniai) {
        generuotiRezultatus(studentas, namuDarbaiKiekis);
    } else {
        string input;
        int rezultatas;
        bool bentVienasRezultatas = false;

        cout << "Iveskite namu darbu rezultatus (du kartus paspauskite ENTER, kai noresite baigti):" << endl;

        while (true) {
            getline(cin, input);

            if (input.empty()) {
                if (bentVienasRezultatas) {
                    break;
                } else {
                    cout << "Turite ivesti bent viena namu darbu rezultata!" << endl;
                    continue;
                }
            }

            try {
                rezultatas = std::stoi(input);
                if (rezultatas < 0 || rezultatas > 10) {
                    cout << "Klaida! Namu darbu rezultatas turi buti tarp 0 ir 10. Iveskite teigiama skaiciu: ";
                } else {
                    studentas.rezultatai.namuDarbai.push_back(rezultatas);
                    bentVienasRezultatas = true;
                }
            } catch (const std::invalid_argument&) {
                cout << "Klaida! Prasome ivesti tinkama skaiciu: ";
            }
        }

        cout << "Iveskite egzamino rezultata: ";
        while (true) {
            std::getline(cin, input);
            if (input.empty()) {
                cout << "Klaida! Prasome ivesti egzamino rezultata: ";
            } else {
                try {
                    studentas.rezultatai.egzaminas = std::stoi(input);
                    if (studentas.rezultatai.egzaminas < 0 || studentas.rezultatai.egzaminas > 10) {
                        cout << "Klaida! Egzamino rezultatas turi buti tarp 0 ir 10. Iveskite tinkama skaiciu: ";
                    } else {
                        break;
                    }
                } catch (const std::invalid_argument&) {
                    cout << "Klaida! Prasome ivesti tinkama skaiciu: ";
                }
            }
        }
        cout << endl;
    }
}


// Funkcija, kuri spausdina studento duomenis kartu su galutiniu balu
void spausdintiStudenta(const Studentas &studentas, bool naudotiVidurki) {
    double galutinis;
    if (naudotiVidurki) {
        double vidurkis = skaiciuotiVidurki(studentas.rezultatai.namuDarbai);
        galutinis = 0.4 * vidurkis + 0.6 * studentas.rezultatai.egzaminas;
    } else {
        double mediana = skaiciuotiMediana(studentas.rezultatai.namuDarbai);
        galutinis = 0.4 * mediana + 0.6 * studentas.rezultatai.egzaminas;
    }

    cout << left << setw(18) << studentas.vardas
         << setw(18) << studentas.pavarde
         << left << setw(15) << fixed << setprecision(2) << galutinis << endl;
}


// Funkcija, kuri nuskaito studentu duomenis is failo
void nuskaitytiDuomenisIsFailo(const string &failoPavadinimas, vector<Studentas> &studentai) {
    std::ifstream failas(failoPavadinimas);
    if (!failas) {
        cout << "Klaida! Nepavyko atidaryti failo." << endl;
        return;
    }

    // Praleidziame pirma eilute (antraste)
    string line;
    std::getline(failas, line);

    while (std::getline(failas, line)) {
        Studentas studentas;
        std::stringstream ss(line);  

        ss >> studentas.vardas >> studentas.pavarde;

        // Isvalome vektoriu, kad butu svarus
        studentas.rezultatai.namuDarbai.clear(); 

        int nd;
        while (ss >> nd) {
            // Paskutine reiksme turetu buti egzamino rezultatas
            studentas.rezultatai.namuDarbai.push_back(nd);
        }

        // Patikriname, ar yra bent vienas namu darbas ir ar yra teisingas egzamino rezultatas
        if (!studentas.rezultatai.namuDarbai.empty()) {
            studentas.rezultatai.egzaminas = studentas.rezultatai.namuDarbai.back(); // Paskutine reiksme - egzamino rezultatas
            studentas.rezultatai.namuDarbai.pop_back(); // Pasalinti egzamino rezultata is namu darbu
            studentai.push_back(studentas);
        }
    }

    failas.close();
}


// Lyginimo funkcija, kuri naudoja varda ir pavarde rusiavimui
bool lygintiPagalVarda(const Studentas &a, const Studentas &b) {
    if (a.vardas == b.vardas) {
        return a.pavarde < b.pavarde;
    }
    return a.vardas < b.vardas;
}


int main() {
    srand(static_cast<unsigned>(time(0))); // Atsitiktiniu skaiciu generatorius

    char pasirinkimas;
    cout << "Ar norite nuskaityti duomenis is failo (f) ar juos ivesti patys (i)? (iveskite f arba i): ";
    cin >> pasirinkimas;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Isvalykite ivesties srauta

    vector<Studentas> studentai;

    if (pasirinkimas == 'f') {
        // Nuskaitymas is failo
        string failoPavadinimas;
        cout << "Iveskite failo pavadinima (pvz., studentai.txt): ";
        getline(cin, failoPavadinimas);
        nuskaitytiDuomenisIsFailo(failoPavadinimas, studentai); // Sioje funkcijoje nuskaitomi duomenys is failo
    } else if (pasirinkimas == 'i') {
        // Ivedimas rankiniu budu
        int studentuSkaicius;
        cout << "Kiek studentu norite ivesti? ";
        cin >> studentuSkaicius;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Isvalykite srauta po skaiciaus ivedimo

        for (int i = 0; i < studentuSkaicius; ++i) {
            cout << endl;
            cout << "Iveskite " << i + 1 << "-ojo studento duomenis:" << endl;

            // Ar generuoti atsitiktinius rezultatus?
            char atsitiktiniuPasirinkimas;
            cout << "Ar norite generuoti atsitiktinius balus (t - TAIP, n - NE)? ";
            cin >> atsitiktiniuPasirinkimas;
            bool atsitiktiniai = (atsitiktiniuPasirinkimas == 't');
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Isvalykite srauta po pasirinkimo

            int namuDarbaiKiekis = 0;
            if (atsitiktiniai) {
            // Jei generuojami atsitiktiniai balai, reikia nurodyti kiek namu darbu
                cout << "Kiek namu darbu rezultatu norite generuoti (nuo 1 iki 10)? ";
                while (true) {
                    cin >> namuDarbaiKiekis;
                    if (cin.fail() || namuDarbaiKiekis < 1 || namuDarbaiKiekis > 10) {
                        cout << "Klaida! Iveskite skaiciu tarp 1 ir 10: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                     } else {
                        break;
                    }
                }
            }


            // Ivedame studento duomenis
            Studentas studentas;
            ivestiStudenta(studentas, atsitiktiniai, namuDarbaiKiekis);
            studentai.push_back(studentas);
        }
    } else {
        // Klaida, jei pasirinkimas neteisingas
        cout << "Klaida! Pasirinkite teisinga pasirinkima." << endl;
        return 1;
    }

    // Galutiniu balu skaiciavimas pagal vidurki arba mediana
    char metodoPasirinkimas;
    cout << "Ar norite skaiciuoti galutini bala pagal vidurki (v) ar mediana (m)? (iveskite v arba m): ";
    cin >> metodoPasirinkimas;

    bool naudotiVidurki = (metodoPasirinkimas == 'v');

    // Surusiuojame studentus pagal vardus
    std::sort(studentai.begin(), studentai.end(), lygintiPagalVarda);

    // Spausdiname antraste
    cout << endl;
    cout << left << setw(18) << "Vardas"
         << setw(18) << "Pavarde"
         << (naudotiVidurki ? "Galutinis (Vid.)" : "Galutinis (Med.)") << endl;
    cout << "--------------------------------------------------------------" << endl;

    // Spausdiname kiekvieno studento duomenis
    for (const auto &studentas : studentai) {
        spausdintiStudenta(studentas, naudotiVidurki);
    }

    return 0;
}

