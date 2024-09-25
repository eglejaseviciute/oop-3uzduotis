#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
#include <algorithm>

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

// Funkcija, kuri iveda studento duomenis
void ivestiStudenta(Studentas &studentas) {
    cout << "Iveskite studento varda: ";
    cin >> studentas.vardas;
    cout << "Iveskite studento pavarde: ";
    cin >> studentas.pavarde;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string input;
    int rezultatas;
    bool bentVienasRezultatas = false;

    cout << "Iveskite namu darbu rezultatus (du kartus paspauskite ENTER, kad baigtumete):" << endl;
    
    while (true) {
        std::getline(cin, input); // Naudojame getline, kad gautume visą eilutę

        // Patikriname, ar įvesta tuščia eilutė
        if (input.empty()) {
            if (bentVienasRezultatas) {
                break; // Baigti, jei bent vienas rezultatas buvo įvestas
            } else {
                cout << "Turite ivesti bent viena namu darbu rezultata!" << endl;
                continue; // Toliau laukti įvesties
            }
        }

        try {
            rezultatas = std::stoi(input);
            if (rezultatas < 0) {
                cout << "Klaida! Namu darbu rezultatas negali buti neigiamas. Iveskite teigiama skaiciu: ";
            } else {
                studentas.namuDarbai.push_back(rezultatas);
                bentVienasRezultatas = true;
            }
        } catch (const std::invalid_argument&) {
            cout << "Klaida! Prasome ivesti tinkama skaiciu: ";
        }
    }

    cout << "Iveskite egzamino rezultata: ";
    while (!(cin >> studentas.egzaminas) || studentas.egzaminas < 0 || studentas.egzaminas > 10) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Klaida! Prasome ivesti tinkama egzamino rezultata (0-10): ";
    }
    cout << endl;
}

// Funkcija, kuri spausdina studento duomenis kartu su galutiniu balu
void spausdintiStudenta(const Studentas &studentas, bool naudotiVidurki) {
    double galutinis;
    if (naudotiVidurki) {
        double vidurkis = skaiciuotiVidurki(studentas.namuDarbai);
        galutinis = 0.4 * vidurkis + 0.6 * studentas.egzaminas;
    } else {
        double mediana = skaiciuotiMediana(studentas.namuDarbai);
        galutinis = 0.4 * mediana + 0.6 * studentas.egzaminas;
    }
    
    // Spausdiname studento varda, pavarde ir galutini bala
    cout << std::left << std::setw(12) << studentas.vardas
         << std::setw(12) << studentas.pavarde
         << std::fixed << std::setprecision(2) << galutinis << endl;
}

int main() {
    int studentuSkaicius;
    cout << "Kiek studentu norite ivesti? ";
    cin >> studentuSkaicius;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<Studentas> studentai(studentuSkaicius);
    for (int i = 0; i < studentuSkaicius; ++i) {
        cout << "Iveskite " << i + 1 << "-ojo studento duomenis:" << endl;
        ivestiStudenta(studentai[i]);
    }

    // Paklausiame, ar naudoti vidurki ar mediana
    char pasirinkimas;
    cout << "Ar norite skaiciuoti galutini bala naudodami vidurki (v) ar mediana (m)? (iveskite v arba m): ";
    cin >> pasirinkimas;
    bool naudotiVidurki = (pasirinkimas == 'v');

    // Spausdiname antrastes
    cout << std::left << std::setw(12) << "Vardas"
         << std::setw(12) << "Pavarde"
         << (naudotiVidurki ? "Galutinis (Vid.)" : "Galutinis (Med.)") << endl;
    cout << "------------------------------------------------------" << endl;

    // Spausdiname studentu rezultatus
    for (const auto& studentas : studentai) {
        spausdintiStudenta(studentas, naudotiVidurki);
    }

    return 0;
}
