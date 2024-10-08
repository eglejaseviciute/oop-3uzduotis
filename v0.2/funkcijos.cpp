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


double skaiciuotiGalutiniBala(const Studentas &studentas, bool naudotiVidurki) {
    double namuDarbuRezultatas = naudotiVidurki ? 
        skaiciuotiVidurki(studentas.rezultatai.namuDarbai) : 
        skaiciuotiMediana(studentas.rezultatai.namuDarbai);
    return 0.4 * namuDarbuRezultatas + 0.6 * studentas.rezultatai.egzaminas;
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


struct SortByFinalScoreAsc {
    bool naudotiVidurki;
    SortByFinalScoreAsc(bool useAverage) : naudotiVidurki(useAverage) {}
    bool operator()(const Studentas &a, const Studentas &b) const {
        return skaiciuotiGalutiniBala(a, naudotiVidurki) < skaiciuotiGalutiniBala(b, naudotiVidurki);
    }
};


struct SortByFinalScoreDesc {
    bool naudotiVidurki;
    SortByFinalScoreDesc(bool useAverage) : naudotiVidurki(useAverage) {}
    bool operator()(const Studentas &a, const Studentas &b) const {
        return skaiciuotiGalutiniBala(a, naudotiVidurki) > skaiciuotiGalutiniBala(b, naudotiVidurki);
    }
};

void procesarArchivosBucle() {
    string failoPavadinimas;
    char continueProcessing = 'y';

    while (continueProcessing == 'y' || continueProcessing == 'Y') {
        vector<Studentas> studentai;

        cout << "Iveskite failo pavadinima (pvz., studentai.txt): ";
        getline(cin, failoPavadinimas);
        nuskaitytiDuomenisIsFailo(failoPavadinimas, studentai);

       
        char metodoPasirinkimas;
        while (true) {
            cout << "Ar norite skaiciuoti galutini bala pagal vidurki (v) ar mediana (m)? (iveskite v arba m): ";
            cin >> metodoPasirinkimas;

            if (metodoPasirinkimas == 'v' || metodoPasirinkimas == 'm') {
                break; 
            } else {
                cout << "Klaida! Prasome ivesti 'v' arba 'm'!" << endl;
            }
        }

        bool naudotiVidurki = (metodoPasirinkimas == 'v');

        
        char outputPasirinkimas;
        while (true) {
            cout << "Ar norite matyti rezultatus ekrane (e) ar surusiuosti studentus i dvi kategorijas ir irasyti i failus (f)? (iveskite e arba f): ";
            cin >> outputPasirinkimas;

            if (outputPasirinkimas == 'e' || outputPasirinkimas == 'f') {
                break;
            } else {
                cout << "Klaida! Prasome ivesti 'e' arba 'f'!" << endl;
            }
        }

        if (outputPasirinkimas == 'e') {
           
            std::sort(studentai.begin(), studentai.end(), lygintiPagalVardaIrPavarde);
            
            rodytiRezultatus(studentai, naudotiVidurki);
        } else {
            
            char sortingPreference;
            cout << "Kaip norite surusiuoti studentus? (1 - Pagal galutini bala didejimo tvarka, 2 - Pagal galutini bala mazejimo tvarka, 3 - Pagal varda, 4 - Pagal pavarde, 5 - Pagal varda ir pavarde): ";
            cin >> sortingPreference;

            if (sortingPreference == '1') {
                std::sort(studentai.begin(), studentai.end(), SortByFinalScoreAsc(naudotiVidurki));
            } else if (sortingPreference == '2') {
                std::sort(studentai.begin(), studentai.end(), SortByFinalScoreDesc(naudotiVidurki));
            } else if (sortingPreference == '3') {
                std::sort(studentai.begin(), studentai.end(), lygintiPagalVarda);
            } else if (sortingPreference == '4') {
                std::sort(studentai.begin(), studentai.end(), lygintiPagalPavarde);
            } else if (sortingPreference == '5') {
                std::sort(studentai.begin(), studentai.end(), lygintiPagalVardaIrPavarde);
            }

            
            vector<Studentas> vargsiukai, galvociai;
            rusiuotiStudentus(studentai, vargsiukai, galvociai, naudotiVidurki);

            string vargsiukaiFilename = "vargsiukai_" + failoPavadinimas;
            string galvociaiFilename = "galvociai_" + failoPavadinimas;

            rasytiStudentusIFaila(vargsiukai, vargsiukaiFilename, naudotiVidurki);
            rasytiStudentusIFaila(galvociai, galvociaiFilename, naudotiVidurki);

            cout << "Studentai buvo surusiuoti ir irasyti i failus '" << vargsiukaiFilename << "' ir '" << galvociaiFilename << "'." << endl;
        }

        
        cout << "Ar norite apdoroti kita faila? (y/n): ";
        cin >> continueProcessing;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}
