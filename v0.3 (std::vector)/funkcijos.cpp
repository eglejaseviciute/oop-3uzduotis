#include "funkcijos.h"
#include "myLib.h"
#include "studentas.h"


map<string, VeikimoGreicioMatavimai> veikimoGreicioRezultatai;


// Funkcija skaiciuojanti vidurki
double skaiciuotiVidurki(const vector<int>& namuDarbai) {
    if (namuDarbai.empty()) return 0;
    double suma = 0.0;
    for (int nd : namuDarbai) {
        suma += nd;
    }
    return suma / namuDarbai.size();
}


// Funkcija skaiciuojanti mediana
double skaiciuotiMediana(vector<int> namuDarbai) {
    if (namuDarbai.empty()) return 0;
    sort(namuDarbai.begin(), namuDarbai.end());
    int dydis = namuDarbai.size();
    if (dydis % 2 == 0) {
        return (namuDarbai[dydis / 2 - 1] + namuDarbai[dydis / 2]) / 2.0;
    } else {
        return namuDarbai[dydis / 2];
    }
}


// Funkcija gaunanti tinkama simboli is vartotojo
char gautiTinkamaSymboli(const string &pranesimas, const string &tinkamisymboliai) {
    string ivestis;
    while (true) {
        cout << pranesimas;
        cin >> ivestis;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (ivestis.length() == 1 && tinkamisymboliai.find(ivestis[0]) != string::npos) {
            return ivestis[0];
        }
        cout << "Klaida! Iveskite viena is siu simboliu: " << tinkamisymboliai << endl;
    }
}


// Funkcija generuojanti atsitiktinius rezultatus studentui
void generuotiRezultatus(Studentas &studentas, int namuDarbaiKiekis) {
    for (int i = 0; i < namuDarbaiKiekis; ++i) {
        studentas.rezultatai.namuDarbai.push_back(rand() % 11); 
    }
    studentas.rezultatai.egzaminas = rand() % 11;
}


// Funkcija skaiciuojanti galutini bala
double skaiciuotiGalutiniBala(const Studentas &studentas, bool naudotiVidurki) {
    double namuDarbuRezultatas = naudotiVidurki ? 
        skaiciuotiVidurki(studentas.rezultatai.namuDarbai) : 
        skaiciuotiMediana(studentas.rezultatai.namuDarbai);
    return 0.4 * namuDarbuRezultatas + 0.6 * studentas.rezultatai.egzaminas;
}


// Funkcija nuskaitanti duomenis is failo
double nuskaitytiDuomenisIsFailo(const string& failoPavadinimas, vector<Studentas>& studentai) {
    auto start = std::chrono::high_resolution_clock::now();
    while (true) {
        ifstream failas(failoPavadinimas);
        if (!failas) {
            throw runtime_error("Klaida! Nepavyko atidaryti failo: " + failoPavadinimas);
        }

        string line;
        getline(failas, line);

        int lineNumber = 1;
        while (getline(failas, line)) {
            lineNumber++;
            Studentas studentas;
            stringstream ss(line);

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
                    nd = stoi(input);
                    if (nd < 0 || nd > 10) {
                        throw out_of_range("Rezultatas ne intervale [0, 10]");
                    }
                    if (!egzaminasNuskaitytas) {
                        studentas.rezultatai.namuDarbai.push_back(nd);
                    } else {
                        cout << "Klaida eiluteje " << lineNumber << "! Po egzamino rezultato aptikti papildomi duomenys." << endl;
                        break;
                    }
                } catch (const invalid_argument&) {
                    cout << "Klaida eiluteje " << lineNumber << "! Netinkamas simbolis '" << input << "' studentui(-ei): " 
                         << studentas.vardas << " " << studentas.pavarde << "." << endl;
                    cout << "Iveskite tinkama rezultata (skaicius nuo 0 iki 10): ";
                    while (!(cin >> nd) || nd < 0 || nd > 10) {
                        cout << "Klaida! Iveskite skaiciu tarp 0 ir 10: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    studentas.rezultatai.namuDarbai.push_back(nd);
                } catch (const out_of_range&) {
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
                cout << "Klaida eiluteje " << lineNumber << "! Nerasta namu darbu rezultatu studentui(-ei): " 
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
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    double readingTime = diff.count();
    
    veikimoGreicioRezultatai[failoPavadinimas].skaitymoLaikas = readingTime;
    
    return readingTime;
}


// Struktura rusiavimui pagal galutini bala didejimo tvarka
struct RusiuotiPagalGalutiniBalaDidejanciai {
    bool naudotiVidurki;
    RusiuotiPagalGalutiniBalaDidejanciai(bool naudotiVid) : naudotiVidurki(naudotiVid) {}
    bool operator()(const Studentas &a, const Studentas &b) const {
        return skaiciuotiGalutiniBala(a, naudotiVidurki) < skaiciuotiGalutiniBala(b, naudotiVidurki);
    }
};


// Struktura rusiavimui pagal galutini bala mazejimo tvarka
struct RusiuotiPagalGalutiniBalaMazejanciai {
    bool naudotiVidurki;
    RusiuotiPagalGalutiniBalaMazejanciai(bool naudotiVid) : naudotiVidurki(naudotiVid) {}
    bool operator()(const Studentas &a, const Studentas &b) const {
        return skaiciuotiGalutiniBala(a, naudotiVidurki) > skaiciuotiGalutiniBala(b, naudotiVidurki);
    }
};


// Funkcija lyginanti studentus pagal pavarde
bool lygintiPagalPavarde(const Studentas &a, const Studentas &b) {
    return a.pavarde < b.pavarde;
}


// Funkcija lyginanti studentus pagal varda
bool lygintiPagalVarda(const Studentas &a, const Studentas &b) {
    return a.vardas < b.vardas;
}


// Funkcija lyginanti studentus pagal varda ir pavarde
bool lygintiPagalVardaIrPavarde(const Studentas &a, const Studentas &b) {
    return (a.vardas + a.pavarde) < (b.vardas + b.pavarde);
}


// Funkcija generuojanti failus
double generuotiFailus(int studentuKiekis, int namuDarbaiKiekis, const string &filePrefix) {
    auto start = std::chrono::high_resolution_clock::now();
    string fileName = filePrefix + to_string(studentuKiekis) + ".txt";
    ofstream failas(fileName);
    if (!failas) {
        throw runtime_error("Klaida! Nepavyko sukurti failo: " + fileName);
    }

    failas << left << setw(20) << "Vardas" << setw(20) << "Pavarde";
    for (int i = 1; i <= namuDarbaiKiekis; ++i) {
        failas << "ND" << setw(8) << i;
    }
    failas << "Egz." << endl;

    for (int i = 1; i <= studentuKiekis; ++i) {
        failas << left << setw(20) << "Vardas" + to_string(i) 
               << setw(20) << "Pavarde" + to_string(i);
        
        for (int j = 0; j < namuDarbaiKiekis; ++j) {
            failas << setw(10) << (rand() % 11);
        }
        failas << (rand() % 11) << endl;
    }

    failas.close();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    double creationTime = diff.count();
    
    cout << "\nFailas " << fileName << " buvo sukurtas." << endl;
    cout << "Failo kurimo laikas: " << creationTime << " sekundziu" << endl;
    
    veikimoGreicioRezultatai[fileName].kurimoLaikas = creationTime;
    
    return creationTime;
}


// Funkcija rezultatu rodymui ekrane
void rodytiRezultatus(const vector<Studentas>& studentai, bool naudotiVidurki) {
    cout << "\n" << endl;
    cout << left << setw(18) << "Vardas"
         << setw(22) << "Pavarde"
         << setw(25) << "Adresas atmintyje"
         << (naudotiVidurki ? "Galutinis (Vid.)" : "Galutinis (Med.)") << endl;
    cout << string(83, '-') << endl;

    for (const auto& studentas : studentai) {
        double galutinis = skaiciuotiGalutiniBala(studentas, naudotiVidurki);
        cout << left << setw(18) << studentas.vardas
             << setw(22) << studentas.pavarde
             << setw(25) << &studentas  // adresas atmintyje
             << fixed << setprecision(2) << galutinis << endl;
    }
}


// Funkcija greicio rezultatu rodymui
void rodytiGreicioAnalizesRezultatus(const string& failoPavadinimas) {
    auto& rezultatai = veikimoGreicioRezultatai[failoPavadinimas];
    cout << "\nGreicio analizes rezultatai failui: " << failoPavadinimas << endl;
    cout << "- Failo skaitymo laikas: " << rezultatai.skaitymoLaikas << " sekundziu" << endl;
    cout << "- Rusiavimo i dvi grupes laikas: " << rezultatai.rusiavimoLaikas << " sekundziu" << endl;
    cout << "- Rasymo laikas (vargsiukai): " << rezultatai.rasymoLaikasVargsiukai << " sekundziu" << endl;
    cout << "- Rasymo laikas (galvociai): " << rezultatai.rasymoLaikasGalvociai << " sekundziu" << endl;
    
    double bendrasLaikas = rezultatai.skaitymoLaikas + rezultatai.rusiavimoLaikas + 
                           rezultatai.rasymoLaikasVargsiukai + rezultatai.rasymoLaikasGalvociai;
    cout << "Bendras laikas: " << bendrasLaikas << " sekundziu" << endl;
}


// Funkcija failu apdorojimo ciklui
void failuApdorojimoCiklas() {
    string failoPavadinimas;
    char testiApdorojima = 't';
    vector<string> apdorotiFailai;

    while (tolower(testiApdorojima) == 't') {
        vector<Studentas> studentai;

        cout << "\nIveskite failo pavadinima (pvz., studentai.txt): ";
        getline(cin, failoPavadinimas);
        
        // Tikrinama ar failas jau buvo apdorotas
        if (find(apdorotiFailai.begin(), apdorotiFailai.end(), failoPavadinimas) != apdorotiFailai.end()) {
            cout << "\nSis failas jau buvo apdorotas! Pasirinkite kita faila." << endl;
            continue;
        }

        try {
            nuskaitytiDuomenisIsFailo(failoPavadinimas, studentai);
            apdorotiFailai.push_back(failoPavadinimas); // Pridedame i apdorotu failu sarasa
        } catch (const runtime_error& e) {
            cout << e.what() << " Bandykite dar karta." << endl;
            continue;
        }
        
        if (studentai.empty()) {
            cout << "Nera studentu duomenu faile!" << endl;
            continue;
        }

        char metodoPasirinkimas;
        do {
            metodoPasirinkimas = gautiTinkamaSymboli(
            "\nAr norite skaiciuoti studento galutini bala pagal:\n"
            "* vidurki (v),\n"
            "* mediana (m)?\n"
            "(Iveskite 'v' arba 'm'!): ",
            "'v' arba 'm'!\n");
        } while (tolower(metodoPasirinkimas) != 'v' && tolower(metodoPasirinkimas) != 'm');

        bool naudotiVidurki = (tolower(metodoPasirinkimas) == 'v');

        try {
            sort(studentai.begin(), studentai.end(), lygintiPagalVardaIrPavarde);
            rodytiRezultatus(studentai, naudotiVidurki);
        } catch (const exception& e) {
            cout << "Ivyko klaida apdorojant duomenis: " << e.what() << endl;
            continue;
        }

        do {
            testiApdorojima = gautiTinkamaSymboli("\nAr norite nuskaityti kita faila? (Iveskite 't' - TAIP arba 'n' - NE)", "'t' arba 'n'!");
        } while (tolower(testiApdorojima) != 't' && tolower(testiApdorojima) != 'n');
    }
}


// Funkcija greicio analizei atlikti
void greicioAnalize() {
    string failoPavadinimas;
    char testiApdorojima = 't';
    vector<string> apdorotiFailai;

    while (testiApdorojima == 't' || testiApdorojima == 'T') {
        vector<Studentas> studentai;

        cout << "\nIveskite failo pavadinima (pvz., studentai.txt): ";
        getline(cin, failoPavadinimas);
        
        try {
            nuskaitytiDuomenisIsFailo(failoPavadinimas, studentai);
        } catch (const runtime_error& e) {
            cout << e.what() << " Bandykite dar karta." << endl;
            continue;
        }
            char metodoPasirinkimas = gautiTinkamaSymboli(
                "\nAr norite skaiciuoti studento galutini bala pagal:\n"
                "* vidurki (v),\n"
                "* mediana (m)?\n"
                "(Iveskite 'v' arba 'm'!): ",
                "'v' arba 'm'!\n");
            bool naudotiVidurki = (metodoPasirinkimas == 'v');

            cout << "\nStudentai bus surusiuoti i dvi kategorijas ir irasyti i failus!" << endl;

            char rusiavimoPasirinkimas = gautiTinkamaSymboli(
                "\nKaip norite surusiuoti studentus?\n"
                "* 1 - pagal galutini bala didejimo tvarka\n"
                "* 2 - pagal galutini bala mazejimo tvarka\n"
                "* 3 - pagal varda\n"
                "* 4 - pagal pavarde\n"
                "* 5 - pagal varda ir pavarde)\n"
                "(Iveskite '1', '2', '3', '4' arba '5'!): ",
                "'1', '2', '3', '4' arba '5'!\n");

            if (rusiavimoPasirinkimas == '1') {
                sort(studentai.begin(), studentai.end(), RusiuotiPagalGalutiniBalaDidejanciai(naudotiVidurki));
            } else if (rusiavimoPasirinkimas == '2') {
                sort(studentai.begin(), studentai.end(), RusiuotiPagalGalutiniBalaMazejanciai(naudotiVidurki));
            } else if (rusiavimoPasirinkimas == '3') {
                sort(studentai.begin(), studentai.end(), lygintiPagalVarda);
            } else if (rusiavimoPasirinkimas == '4') {
                sort(studentai.begin(), studentai.end(), lygintiPagalPavarde);
            } else {
                sort(studentai.begin(), studentai.end(), lygintiPagalVardaIrPavarde);
            }


            vector<Studentas> vargsiukai, galvociai;
            
            double rusiavimoLaikas = rusiuotiStudentus(studentai, vargsiukai, galvociai, naudotiVidurki);
            veikimoGreicioRezultatai[failoPavadinimas].rusiavimoLaikas = rusiavimoLaikas;

            string vargsiukaiFailoPavadinimas = "vargsiukai_" + failoPavadinimas;
            string galvociaiFailoPavadinimas = "galvociai_" + failoPavadinimas;

            double rasymoLaikasVargsiukai = rasytiStudentusIFaila(vargsiukai, vargsiukaiFailoPavadinimas, naudotiVidurki);
            double rasymoLaikasGalvociai = rasytiStudentusIFaila(galvociai, galvociaiFailoPavadinimas, naudotiVidurki);

            veikimoGreicioRezultatai[failoPavadinimas].rasymoLaikasVargsiukai = rasymoLaikasVargsiukai;
            veikimoGreicioRezultatai[failoPavadinimas].rasymoLaikasGalvociai = rasymoLaikasGalvociai;

            cout << "\nStudentai buvo surusiuoti ir irasyti i failus '" 
                 << vargsiukaiFailoPavadinimas << "' ir '" 
                 << galvociaiFailoPavadinimas << "'.\n" << endl;

            apdorotiFailai.push_back(failoPavadinimas);

        testiApdorojima = gautiTinkamaSymboli(
            "Ar norite nuskaityti kita faila?\n"
            "(Iveskite 't' - TAIP arba 'n' - NE): ",
            "'t' arba 'n'!\n");
    }


    if (!apdorotiFailai.empty()) {
        cout << "\nRezultatai visiems apdorotiems failams:" << endl;
        double bendrasLaikas = 0.0;
        for (const auto& failoPav : apdorotiFailai) {
            rodytiGreicioAnalizesRezultatus(failoPav);
            cout << endl;
            auto& rezultatai = veikimoGreicioRezultatai[failoPav];
            bendrasLaikas += rezultatai.kurimoLaikas + rezultatai.skaitymoLaikas + 
                            rezultatai.rusiavimoLaikas + rezultatai.rasymoLaikasVargsiukai + 
                            rezultatai.rasymoLaikasGalvociai;
        }
        double vidutinisLaikas = bendrasLaikas / apdorotiFailai.size();
        cout << "Vidutinis laikas visiems apdorotiems failams: " << vidutinisLaikas << " sekundziu" << endl;
    }
}
