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
    int egzaminas;
};

int main() {
    Studentas studentas;

    // Ivedame studento varda ir pavarde:
    cout << "Iveskite studento varda: ";
    cin >> studentas.vardas;
    cout << "Iveskite studento pavarde: ";
    cin >> studentas.pavarde;

    // Ivedame namu darbu rezultatus ir tikriname klaidas
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

    // Ivedame egzamino rezultata
    cout << "Iveskite egzamino rezultata: ";
    while (!(cin >> studentas.egzaminas)) {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Klaida! Prasome ivesti skaiciu: ";
    }

    // Pridedame tuscia eilute po ivedimu
    cout << endl;

    // Spausdiname ivestus studento duomenis
    cout << "Studentas: " << studentas.vardas << " " << studentas.pavarde << endl;

    // Spausdiname namu darbu rezultatus
    cout << "Namu darbu rezultatai: ";
    for (int nd : studentas.namuDarbai) {
        cout << nd << " ";
    }
    cout << endl;

    // Spausdiname egzamino rezultata
    cout << "Egzamino rezultatas: " << studentas.egzaminas << endl;

    return 0;
}
