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
#include <cctype>

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
            } catch (const std::out_of_range&) {
                cout << "Klaida! Skaičius per didelis. Bandykite dar kartą: ";
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
                } catch (const std::out_of_range&) {
                    cout << "Klaida! Skaičius per didelis. Bandykite dar kartą: ";
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


void nuskaitytiDuomenisIsFailo(string &failoPavadinimas, vector<Studentas> &studentai) {
    while (true) { // Ciklas, kad vartotojas galėtų pakartotinai įvesti failo pavadinimą
        std::ifstream failas(failoPavadinimas);
        if (!failas) {
            cout << "Klaida! Nepavyko atidaryti failo: " << failoPavadinimas << endl;
            cout << "Prašome įvesti teisingą failo pavadinimą: ";
            cin >> failoPavadinimas; // Vartotojas gali įvesti naują failo pavadinimą
            continue; // Grįžtame prie failo atidarymo
        }

        // Praleidžiame pirmą eilutę (antraštę)
        string line;
        std::getline(failas, line);

        while (std::getline(failas, line)) {
            cout << "Nuskaityta eilutė: " << line << endl; // Debug
            Studentas studentas;
            std::stringstream ss(line);

            // Nuskaitome vardą ir pavardę
            ss >> studentas.vardas >> studentas.pavarde;

            // Išvalome vektorių
            studentas.rezultatai.namuDarbai.clear();

            // Nuskaitome namų darbus
            string ndInput;
            int nd;
            int ndIndex = 0; // Indeksas, kuriame saugosime namų darbo poziciją

            while (ss >> ndInput) {
                try {
                    nd = std::stoi(ndInput);
                    if (nd < 0 || nd > 10) {
                        throw std::invalid_argument("Neteisingas diapazonas");
                    }
                    studentas.rezultatai.namuDarbai.push_back(nd);
                    ndIndex++; // Padidiname indeksą tik sėkmingai nuskaitytam namų darbui
                } catch (const std::exception&) {
                    // Klaida su namų darbo rezultatu
                    cout << "Klaida! Netinkamas simbolis ar skaicius studentui(-ei): " 
                         << studentas.vardas << " " << studentas.pavarde 
                         << " (klaida: '" 
                         << ndInput << "')." << endl;

                    // Prašome vartotojo įvesti tinkamą namų darbo įvestį
                    cout << "Iveskite tinkama rezultata (skaicius nuo 0 iki 10) studentui(-ei): "
                         << studentas.vardas << " " << studentas.pavarde << ": ";

                    while (true) {
                        cin >> nd;
                        if (cin.fail() || nd < 0 || nd > 10) {
                            cout << "Klaida! Iveskite skaiciu tarp 0 ir 10: ";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        } else {
                            studentas.rezultatai.namuDarbai.push_back(nd);
                            break; // Išeiname iš ciklo
                        }
                    }
                }
            }

            // Dabar paskutinis rezultatas visada bus egzamino rezultatas
            if (!studentas.rezultatai.namuDarbai.empty()) {
                // Nuskaitome paskutinį namų darbą kaip egzamino rezultatą
                int egzaminas = studentas.rezultatai.namuDarbai.back();
                studentas.rezultatai.namuDarbai.pop_back(); // Pašaliname paskutinį elementą iš namų darbų

                // Tikriname, ar egzaminas tinkamas
                if (egzaminas < 0 || egzaminas > 10) {
                    cout << "Klaida! Egzamino rezultatas studentui " << studentas.vardas 
                         << " " << studentas.pavarde << " už neteisingą diapazoną." << endl;
                } else {
                    studentas.rezultatai.egzaminas = egzaminas;
                }
            }

            // Pridedame studentą į sąrašą
            if (!studentas.rezultatai.namuDarbai.empty()) {
                studentai.push_back(studentas);
            }
        }

        failas.close();
        break; // Jei failas sėkmingai perskaitytas, išeiname iš ciklo
    }
}



// Lyginimo funkcija, kuri naudoja varda ir pavarde rusiavimui
bool lygintiPagalVarda(const Studentas &a, const Studentas &b) {
    if (a.vardas == b.vardas) {
        return a.pavarde < b.pavarde;
    }
    return a.vardas < b.vardas;
}



int main() {
    srand(static_cast<unsigned>(time(0))); // Atsitiktinių skaičių generatorius

    char pasirinkimas;
    while (true) {
        cout << "Ar norite nuskaityti duomenis is failo (f) ar juos ivesti patys (i)? (iveskite f arba i): ";
        cin >> pasirinkimas;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Išvalykite įvesties srautą

        if (pasirinkimas == 'f' || pasirinkimas == 'i') {
            break; // Išeiname iš ciklo, jei pasirinkimas tinkamas
        } else {
            cout << "Klaida! Prašome įvesti 'f' arba 'i'!" << endl;
        }
    }

    vector<Studentas> studentai;

    try {
        if (pasirinkimas == 'f') {
            // Nuskaitymas is failo
            string failoPavadinimas;
            cout << "Iveskite failo pavadinima (pvz., studentai.txt): ";
            getline(cin, failoPavadinimas);
            nuskaitytiDuomenisIsFailo(failoPavadinimas, studentai); // Sioje funkcijoje nuskaitomi duomenys is failo
        } else if (pasirinkimas == 'i') {
            // Ivedimas rankiniu budu
            int studentuSkaicius;
            while (true) { // Ciklas, skirtas validuoti studentu skaiciu
                cout << "Kiek studentu norite ivesti? ";
                cin >> studentuSkaicius;
                if (cin.fail() || studentuSkaicius <= 0) {
                    cout << "Klaida! Prasome ivesti teigiama skaiciu." << endl;
                    cin.clear(); // Išvalome klaidos vėliavą
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Išvalykite srautą
                } else {
                    break; // Išeiname iš ciklo, kai gautas tinkamas įvestis
                }
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Išvalykite srautą po skaičiaus ivedimo

            for (int i = 0; i < studentuSkaicius; ++i) {
                cout << endl;
                cout << "Iveskite " << i + 1 << "-ojo studento duomenis:" << endl;

                // Ar generuoti atsitiktinius rezultatus?
                char atsitiktiniuPasirinkimas;
                while (true) { // Ciklas, skirtas validuoti atsitiktiniu pasirinkima
                    cout << "Ar norite generuoti atsitiktinius balus (t - TAIP, n - NE)? ";
                    string ivestis; // Naudojame string, kad galėtume patikrinti įvesties ilgį
                    cin >> ivestis;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Išvalykite srautą po pasirinkimo

                    // Tikriname, ar įvestis yra vieno simbolio ilgio ir ar tai 't' arba 'n'
                    if (ivestis.length() == 1 && (ivestis[0] == 't' || ivestis[0] == 'n')) {
                        atsitiktiniuPasirinkimas = ivestis[0]; // Priskiriame teisingą pasirinkimą
                        break; // Išeiname iš ciklo, jei pasirinkimas teisingas
                    } else {
                        cout << "Klaida! Prašome įvesti tik vieną simbolį: 't' arba 'n'!" << endl;
                    }
                }

                bool atsitiktiniai = (atsitiktiniuPasirinkimas == 't');
                int namuDarbaiKiekis = 0;
                if (atsitiktiniai) {
                    // Jei generuojami atsitiktiniai balai, reikia nurodyti kiek namu darbu
                    cout << "Kiek namu darbu rezultatu norite generuoti? ";
                    while (true) {
                        cin >> namuDarbaiKiekis;
                        if (cin.fail() || namuDarbaiKiekis < 1) { // Šaliname 10 viršutinę ribą
                            cout << "Klaida! Iveskite teigiama skaiciu: ";
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
        }
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    // Galutiniu balu skaiciavimas pagal vidurki arba mediana
    char metodoPasirinkimas;
    while (true) {
        cout << "Ar norite skaiciuoti galutini bala pagal vidurki (v) ar mediana (m)? (iveskite v arba m): ";
        cin >> metodoPasirinkimas;

        if (metodoPasirinkimas == 'v' || metodoPasirinkimas == 'm') {
            break; // Išeiname iš ciklo, jei pasirinkimas tinkamas
        } else {
            cout << "Klaida! Prašome įvesti 'v' arba 'm'!" << endl;
        }
    }

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

