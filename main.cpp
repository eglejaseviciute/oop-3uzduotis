#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip> // Naudojama rezultatu formatavimui

using std::endl;
using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::numeric_limits;
using std::streamsize;

// Struktura, skirta studento duomenims saugoti
struct Studentas {
    string vardas;
    string pavarde;
    vector<int> namuDarbai;
    int egzaminas;
};

// Funkcija, kuri skaiciuoja vidurki is namu darbu rezultatu
double skaiciuotiVidurki(const vector<int>& namuDarbai) {
    double suma = 0;
    for (int nd : namuDarbai) {
        suma += nd;
    }
    return suma / namuDarbai.size();
}

// Funkcija, kuri iveda studento duomenis
void ivestiStudenta(Studentas &studentas) {
    cout << "Iveskite studento varda: ";
    cin >> studentas.vardas;
    cout << "Iveskite studento pavarde: ";
    cin >> studentas.pavarde;

    // Ivedame namu darbu rezultatus ir tikriname, ar buvo ivesta bent viena reiksme
    string input;
    int rezultatas;
    bool bentVienasRezultatas = false;
    cout << "Iveskite namu darbu rezultatus (iveskite *, kai noresite baigti):" << endl;
    while (true) {
        cin >> input;

        if (input == "*") {
            if (bentVienasRezultatas) {
                break; // Jei buvo ivestas bent vienas rezultatas, baigiame ivesti
            } else {
                cout << "Turite ivesti bent viena namu darbu rezultata!" << endl;
            }
        } else {
            try {
                rezultatas = std::stoi(input); // Konvertuojame ivesta string i int
                if (rezultatas < 0) {
                    cout << "Klaida! Namu darbu rezultatas negali buti neigiamas. Iveskite teigiama skaiciu: ";
                } else {
                    studentas.namuDarbai.push_back(rezultatas); // Pridedame rezultata i vektoriu
                    bentVienasRezultatas = true;
                }
            } catch (const std::invalid_argument&) {
                cout << "Klaida! Prasome ivesti tinkama skaiciu arba * baigti: ";
            }
        }
    }

    // Ivedame egzamino rezultata ir tikriname, ar tai yra skaicius nuo 0 iki 10
    cout << "Iveskite egzamino rezultata: ";
    while (!(cin >> studentas.egzaminas) || studentas.egzaminas < 0 || studentas.egzaminas > 10) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Klaida! Prasome ivesti tinkama egzamino rezultata (0-10): ";
    }
    cout << endl;
}

// Funkcija, kuri spausdina studento duomenis kartu su galutiniu balu
void spausdintiStudenta(const Studentas &studentas) {
    double vidurkis = skaiciuotiVidurki(studentas.namuDarbai); // Skaiciuojame vidurki
    double galutinis = 0.4 * vidurkis + 0.6 * studentas.egzaminas; // Skaiciuojame galutini bala

    // Spausdiname studento duomenis su formatuotais stulpeliais
    cout << std::left << std::setw(12) << studentas.vardas 
         << std::setw(12) << studentas.pavarde 
         << std::fixed << std::setprecision(2) << galutinis << endl;
}

int main() {
    int studentuSkaicius;
    cout << "Kiek studentu norite ivesti? ";
    cin >> studentuSkaicius;

    vector<Studentas> studentai(studentuSkaicius);

    // Ivedame studentu duomenis
    for (int i = 0; i < studentuSkaicius; ++i) {
        cout << "Iveskite " << i + 1 << "-ojo studento duomenis:" << endl;
        ivestiStudenta(studentai[i]);
    }

    // Spausdiname rezultatus su antrastemis
    cout << std::left << std::setw(12) << "Vardas" 
         << std::setw(12) << "Pavarde" 
         << "Galutinis (Vid.)" << endl;
    cout << "———————————————————————————————————-------------------" << endl;

    // Spausdiname visu studentu duomenis
    for (const auto& studentas : studentai) {
        spausdintiStudenta(studentas);
    }

    return 0;
}
