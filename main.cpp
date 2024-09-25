#include <iostream>
#include <vector>
#include <string>
#include <limits> // Naudojama cin klaidu tvarkymui

using std::endl;
using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::numeric_limits;
using std::streamsize;

struct Studentas {
    string vardas;
    string pavarde;
    vector<int> namuDarbai;
    int egzaminas = -1; // Pradžioje nustatome, kad egzaminas neįvestas
};

void ivestiStudenta(Studentas &studentas) {
    // Ivedame studento varda ir pavarde:
    cout << "Iveskite studento varda: ";
    cin >> studentas.vardas;
    cout << "Iveskite studento pavarde: ";
    cin >> studentas.pavarde;

    // Ivedame namu darbu rezultatus ir tikriname klaidas:
    cout << "Iveskite namu darbu rezultatus (iveskite -1, kai noresite baigti):" << endl;
    int rezultatas;
    while (true) {
        cin >> rezultatas;

        // Patikriname, ar ivesta reiksme yra skaicius
        if (cin.fail()) {
            cin.clear(); // Isvalome klaidos busena
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Praleidziame neteisinga ivesti
            cout << "Klaida! Prasome ivesti skaiciu: ";
        } else if (rezultatas == -1) {
            // Baigiame ivesti, kai irasoma -1
            break;
        } else {
            studentas.namuDarbai.push_back(rezultatas); // Pridedame rezultata i vektoriu
        }
    }

    // Ivedame egzamino rezultata arba nustatome -1, jei neįvesta
    cout << "Iveskite egzamino rezultata (jei neturi, iveskite -1): ";
    while (!(cin >> studentas.egzaminas)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Klaida! Prasome ivesti skaiciu: ";
    }
    cout << endl;
}

void spausdintiStudenta(const Studentas &studentas) {
    // Spausdiname ivestus studento duomenis:
    cout << "Studentas: " << studentas.vardas << " " << studentas.pavarde << endl;

    // Spausdiname namu darbu rezultatus arba pranesima, kad ju nera:
    if (studentas.namuDarbai.empty()) {
        cout << "Namu darbu rezultatai: Nera" << endl;
    } else {
        cout << "Namu darbu rezultatai: ";
        for (int nd : studentas.namuDarbai) {
            cout << nd << " ";
        }
        cout << endl;
    }

    // Spausdiname egzamino rezultata arba pranesima, kad egzamino nera:
    if (studentas.egzaminas == -1) {
        cout << "Egzamino rezultatas: Nera" << endl;
    } else {
        cout << "Egzamino rezultatas: " << studentas.egzaminas << endl;
    }
}

int main() {
    int studentuSkaicius;
    cout << "Kiek studentu norite ivesti? ";
    cin >> studentuSkaicius;

    vector<Studentas> studentai(studentuSkaicius);

    for (int i = 0; i < studentuSkaicius; ++i) {
        cout << "Iveskite " << i+1 << "-ojo studento duomenis:" << endl;
        ivestiStudenta(studentai[i]);
    }

    for (int i = 0; i < studentuSkaicius; ++i) {
        cout << i+1 << "-ojo studento duomenys:" << endl;
        spausdintiStudenta(studentai[i]);
    }

    return 0;
}
