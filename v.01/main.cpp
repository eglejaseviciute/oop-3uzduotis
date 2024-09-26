#include "funkcijos.h"
#include "myLib.h"


int main() {
    srand(static_cast<unsigned>(time(0))); // Atsitiktiniu skaiciu generatorius

    char pasirinkimas;
    while (true) {
        cout << "Ar norite nuskaityti duomenis is failo (f) ar juos ivesti patys (i)? (iveskite f arba i): ";
        cin >> pasirinkimas;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (pasirinkimas == 'f' || pasirinkimas == 'i') {
            break;
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
            nuskaitytiDuomenisIsFailo(failoPavadinimas, studentai);
        } else if (pasirinkimas == 'i') {
            // Ivedimas rankiniu budu
            int studentuSkaicius;
            while (true) {
                cout << "Kiek studentu norite ivesti? ";
                cin >> studentuSkaicius;
                if (cin.fail() || studentuSkaicius <= 0) {
                    cout << "Klaida! Prasome ivesti teigiama skaiciu." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                } else {
                    break;
                }
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            for (int i = 0; i < studentuSkaicius; ++i) {
                cout << endl;
                cout << "Iveskite " << i + 1 << "-ojo studento duomenis:" << endl;

                
                char atsitiktiniuPasirinkimas;
                while (true) { 
                    cout << "Ar norite generuoti atsitiktinius balus (t - TAIP, n - NE)? ";
                    string ivestis;
                    cin >> ivestis;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    if (ivestis.length() == 1 && (ivestis[0] == 't' || ivestis[0] == 'n')) {
                        atsitiktiniuPasirinkimas = ivestis[0];
                        break;
                    } else {
                        cout << "Klaida! Prašome įvesti tik vieną simbolį: 't' arba 'n'!" << endl;
                    }
                }

                bool atsitiktiniai = (atsitiktiniuPasirinkimas == 't');
                int namuDarbaiKiekis = 0;
                if (atsitiktiniai) {
                    // Jei generuojami atsitiktiniai balai, reikia nurodyti kiek namu darbu generuoti
                    cout << "Kiek namu darbu rezultatu norite generuoti? ";
                    while (true) {
                        cin >> namuDarbaiKiekis;
                        if (cin.fail() || namuDarbaiKiekis < 1) {
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
            break;
        } else {
            cout << "Klaida! Prašome įvesti 'v' arba 'm'!" << endl;
        }
    }

    bool naudotiVidurki = (metodoPasirinkimas == 'v');

    // Surusiuojame studentus pagal vardus
    sort(studentai.begin(), studentai.end(), lygintiPagalVarda);

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
