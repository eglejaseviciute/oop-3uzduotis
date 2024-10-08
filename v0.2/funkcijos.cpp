#include "funkcijos.h"
#include "myLib.h"


double skaiciuotiVidurki(const vector<int>& namuDarbai) {
    double suma = 0.0;
    for (int nd : namuDarbai) {
        suma += nd;
    }
    return suma / namuDarbai.size();
}


double skaiciuotiMediana(vector<int> namuDarbai) {
    std::sort(namuDarbai.begin(), namuDarbai.end());
    int dydis = namuDarbai.size();
    if (dydis % 2 == 0) {
        return (namuDarbai[dydis / 2 - 1] + namuDarbai[dydis / 2]) / 2.0;
    } else {
        return namuDarbai[dydis / 2];
    }
}


void generuotiRezultatus(Studentas &studentas, int namuDarbaiKiekis) {
    for (int i = 0; i < namuDarbaiKiekis; ++i) {
        studentas.rezultatai.namuDarbai.push_back(rand() % 11); 
    }
    studentas.rezultatai.egzaminas = rand() % 11;
}


void nuskaitytiDuomenisIsFailo(string &failoPavadinimas, vector<Studentas> &studentai) {
    while (true) {
        std::ifstream failas(failoPavadinimas);
        if (!failas) {
            cout << "Klaida! Nepavyko atidaryti failo: " << failoPavadinimas << endl;
            cout << "Prasome ivesti teisinga failo pavadinima: ";
            cin >> failoPavadinimas; 
            continue; 
        }

        string line;
        std::getline(failas, line);

        int lineNumber = 1;
        while (std::getline(failas, line)) {
            lineNumber++;
            Studentas studentas;
            std::stringstream ss(line);

            if (!(ss >> studentas.vardas >> studentas.pavarde)) {
                cout << "Klaida eiluteje " << lineNumber << "! Nepavyko nuskaityti vardo ir pavardes." << endl;
                continue;
            }

            studentas.rezultatai.namuDarbai.clear();

            string input;
            int nd;
            bool egzaminasNuskaitytas = false;

            while (ss >> input) {
                try {
                    nd = std::stoi(input);
                    if (nd < 0 || nd > 10) {
                        throw std::out_of_range("Rezultatas ne intervale [0, 10]");
                    }
                    if (!egzaminasNuskaitytas) {
                        studentas.rezultatai.namuDarbai.push_back(nd);
                    } else {
                        cout << "Klaida eiluteje " << lineNumber << "! Po egzamino rezultato aptikti papildomi duomenys." << endl;
                        break;
                    }
                } catch (const std::invalid_argument&) {
                    cout << "Klaida eiluteje " << lineNumber << "! Netinkamas simbolis '" << input << "' studentui(-ei): " 
                         << studentas.vardas << " " << studentas.pavarde << "." << endl;
                    cout << "Iveskite tinkama rezultata (skaicius nuo 0 iki 10): ";
                    while (!(cin >> nd) || nd < 0 || nd > 10) {
                        cout << "Klaida! Iveskite skaiciu tarp 0 ir 10: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    studentas.rezultatai.namuDarbai.push_back(nd);
                } catch (const std::out_of_range&) {
                    cout << "Klaida eiluteje " << lineNumber << "! Rezultatas '" << input << "' ne intervale [0, 10] studentui(-ei): " 
                         << studentas.vardas << " " << studentas.pavarde << "." << endl;
                    cout << "Iveskite tinkama rezultata (skaicius nuo 0 iki 10): ";
                    while (!(cin >> nd) || nd < 0 || nd > 10) {
                        cout << "Klaida! Iveskite skaiciu tarp 0 ir 10: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    studentas.rezultatai.namuDarbai.push_back(nd);
                }
            }

            if (studentas.rezultatai.namuDarbai.empty()) {
                cout << "Klaida eiluteje " << lineNumber << "! Nerasta nama darbu rezultatu studentui(-ei): " 
                     << studentas.vardas << " " << studentas.pavarde << "." << endl;
                continue;
            }

            studentas.rezultatai.egzaminas = studentas.rezultatai.namuDarbai.back();
            studentas.rezultatai.namuDarbai.pop_back();

            if (studentas.rezultatai.namuDarbai.empty()) {
                cout << "Klaida eiluteje " << lineNumber << "! Nerasta namu darbu rezultatu studentui(-ei): " 
                     << studentas.vardas << " " << studentas.pavarde << " (tik egzamino rezultatas)." << endl;
                continue;
            }

            studentai.push_back(studentas);
        }

        failas.close();
        break; 
    }
}


bool lygintiPagalGalutiniBalaAscending(const Studentas &a, const Studentas &b) {
    return skaiciuotiGalutiniBala(a, true) < skaiciuotiGalutiniBala(b, true);
}


bool lygintiPagalGalutiniBalaDescending(const Studentas &a, const Studentas &b) {
    return skaiciuotiGalutiniBala(a, true) > skaiciuotiGalutiniBala(b, true);
}


bool lygintiPagalPavarde(const Studentas &a, const Studentas &b) {
    return a.pavarde < b.pavarde;
}


bool lygintiPagalVarda(const Studentas &a, const Studentas &b) {
    return a.vardas < b.vardas;
}


bool lygintiPagalVardaIrPavarde(const Studentas &a, const Studentas &b) {
    return (a.vardas + a.pavarde) < (b.vardas + b.pavarde);
}


double skaiciuotiGalutiniBala(const Studentas &studentas, bool naudotiVidurki) {
    double namuDarbuRezultatas = naudotiVidurki ? 
        skaiciuotiVidurki(studentas.rezultatai.namuDarbai) : 
        skaiciuotiMediana(studentas.rezultatai.namuDarbai);
    return 0.4 * namuDarbuRezultatas + 0.6 * studentas.rezultatai.egzaminas;
}


void generuotiFailus(int studentuKiekis, int namuDarbaiKiekis, const string &filePrefix) {
    std::ofstream failas(filePrefix + std::to_string(studentuKiekis) + ".txt");
    if (!failas) {
        cout << "Klaida! Nepavyko sukurti failo." << endl;
        return;
    }

    
    failas << left << setw(20) << "Vardas" << setw(20) << "Pavarde";
    for (int i = 1; i <= namuDarbaiKiekis; ++i) {
        failas << "ND" << setw(8) << i;
    }
    failas << "Egz." << endl;

    
    for (int i = 1; i <= studentuKiekis; ++i) {
        failas << left << setw(20) << "Vardas" + std::to_string(i) 
               << setw(20) << "Pavarde" + std::to_string(i);
        
        for (int j = 0; j < namuDarbaiKiekis; ++j) {
            failas << setw(10) << (rand() % 11);
        }
        failas << (rand() % 11) << endl;
    }

    failas.close();
    cout << "Failas " << filePrefix + std::to_string(studentuKiekis) + ".txt buvo sukurtas." << endl;
}


void rodytiRezultatus(const vector<Studentas>& studentai, bool naudotiVidurki) {
    cout << left << setw(18) << "Vardas"
         << setw(18) << "Pavarde"
         << (naudotiVidurki ? "Galutinis (Vid.)" : "Galutinis (Med.)") << endl;
    cout << string(60, '-') << endl;

    for (const auto& studentas : studentai) {
        double galutinis = skaiciuotiGalutiniBala(studentas, naudotiVidurki);
        cout << left << setw(18) << studentas.vardas
             << setw(18) << studentas.pavarde
             << fixed << setprecision(2) << galutinis << endl;
    }
}
