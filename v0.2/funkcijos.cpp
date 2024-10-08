#include "funkcijos.h"
#include "myLib.h"
#include "studentas.h"


map<string, VeikimoGreicioMatavimai> veikimoGreicioRezultatai;


// Funkcija skaiciuojanti vidurki
double skaiciuotiVidurki(const vector<int>& namuDarbai) {
    if (namuDarbai.empty()) return 0;
    double suma = 0;
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
    cout << "Failas " << fileName << " buvo sukurtas." << endl;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    double creationTime = diff.count();
    
    veikimoGreicioRezultatai[fileName].kurimoLaikas = creationTime;
    
    return creationTime;
}


// Funkcija rezultatu rodymui ekrane
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


// Funkcija nasumo rezultatu rodymui
void rodytiGreicioAnalizesRezultatus(const string& failoPavadinimas) {
    auto& rezultatai = veikimoGreicioRezultatai[failoPavadinimas];
    cout << "\nGreicio analizes rezultatai failui: " << failoPavadinimas << endl;
    cout << "Failo kurimo laikas: " << rezultatai.kurimoLaikas << " sekundziu" << endl;
    cout << "Failo skaitymo laikas: " << rezultatai.skaitymoLaikas << " sekundziu" << endl;
    cout << "Rusiavimo i dvi grupes laikas: " << rezultatai.rusiavimoLaikas << " sekundziu" << endl;
    cout << "Rasymo laikas (vargsiukai): " << rezultatai.rasymoLaikasVargsiukai << " sekundziu" << endl;
    cout << "Rasymo laikas (galvociai): " << rezultatai.rasymoLaikasGalvociai << " sekundziu" << endl;
    
    double bendrasLaikas = rezultatai.kurimoLaikas + rezultatai.skaitymoLaikas + rezultatai.rusiavimoLaikas + 
                           rezultatai.rasymoLaikasVargsiukai + rezultatai.rasymoLaikasGalvociai;
    cout << "Bendras laikas: " << bendrasLaikas << " sekundziu" << endl;
}


// Funkcija failu apdorojimo ciklui
void failuApdorojimoCiklas() {
    string failoPavadinimas;
    char testiApdorojima = 't';
    vector<string> apdorotiFailai;

    while (testiApdorojima == 't' || testiApdorojima == 'T') {
        vector<Studentas> studentai;

        cout << "Iveskite failo pavadinima (pvz., studentai.txt): ";
        getline(cin, failoPavadinimas);
        
        try {
            nuskaitytiDuomenisIsFailo(failoPavadinimas, studentai);
        } catch (const runtime_error& e) {
            cout << e.what() << " Bandykite dar karta." << endl;
            continue;
        }
        
        char metodoPasirinkimas = gautiTinkamaSymboli("Ar norite skaiciuoti galutini bala pagal vidurki (v) ar mediana (m)? ", "'v' arba 'm'!");
        bool naudotiVidurki = (metodoPasirinkimas == 'v');

        char isvestiesPasirinkimas = gautiTinkamaSymboli("Ar norite matyti rezultatus ekrane (e) ar surusiuoti studentus i dvi kategorijas ir irasyti i failus (f)? ", "'e' arba 'f'!");

        if (isvestiesPasirinkimas == 'e') {
            sort(studentai.begin(), studentai.end(), lygintiPagalVardaIrPavarde);
            rodytiRezultatus(studentai, naudotiVidurki);
        } else {
            char rusiavimoPasirinkimas = gautiTinkamaSymboli("Kaip norite surusiuoti studentus? (1 - Pagal galutini bala didejimo tvarka, 2 - Pagal galutini bala mazejimo tvarka, 3 - Pagal varda, 4 - Pagal pavarde, 5 - Pagal varda ir pavarde): ", "'1', '2', '3', '4' arba '5'!");

            if (rusiavimoPasirinkimas == '1') {
                sort(studentai.begin(), studentai.end(), RusiuotiPagalGalutiniBalaDidejanciai(naudotiVidurki));
            } else if (rusiavimoPasirinkimas == '2') {
                sort(studentai.begin(), studentai.end(), RusiuotiPagalGalutiniBalaMazejanciai(naudotiVidurki));
            } else if (rusiavimoPasirinkimas == '3') {
                sort(studentai.begin(), studentai.end(), lygintiPagalVarda);
            } else if (rusiavimoPasirinkimas == '4') {
                sort(studentai.begin(), studentai.end(), lygintiPagalPavarde);
            } else if (rusiavimoPasirinkimas == '5') {
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

            cout << "Studentai buvo surusiuoti ir irasyti i failus '" << vargsiukaiFailoPavadinimas << "' ir '" << galvociaiFailoPavadinimas << "'." << endl;

            apdorotiFailai.push_back(failoPavadinimas);
        }

        testiApdorojima = gautiTinkamaSymboli("Ar norite nuskaityti kita faila? (Iveskite 't' - TAIP arba 'n' - NE): ", "'t' arba 'n'!");
    }

    if (!apdorotiFailai.empty()) {
        char rodytiRezultatus = gautiTinkamaSymboli("Ar norite matyti greicio analizes rezultatus apdorotiems failams? (Iveskite 't' - TAIP arba 'n' - NE): ", "'t' arba 'n'!");

        if (rodytiRezultatus == 't' || rodytiRezultatus == 'T') {
            cout << "\nRezultatai visiems apdorotiems failams:\n" << endl;
            double bendrasLaikas = 0.0;
            for (const auto& failoPav : apdorotiFailai) {
                rodytiGreicioAnalizesRezultatus(failoPav);
                cout << endl;
                auto& rezultatai = veikimoGreicioRezultatai[failoPav];
                bendrasLaikas += rezultatai.kurimoLaikas + rezultatai.skaitymoLaikas + rezultatai.rusiavimoLaikas + 
                                 rezultatai.rasymoLaikasVargsiukai + rezultatai.rasymoLaikasGalvociai;
            }
            double vidutinisLaikas = bendrasLaikas / apdorotiFailai.size();
            cout << "Vidutinis laikas visiems apdorotiems failams: " << vidutinisLaikas << " sekundziu" << endl;
        }
    }
}


// Funkcija greicio analizei atlikti
void atliktiGreicioAnalize() {
    vector<int> dydziai;
    dydziai.push_back(1000);
    dydziai.push_back(10000);
    dydziai.push_back(100000);
    dydziai.push_back(1000000);
    dydziai.push_back(10000000);
    int namuDarbaiKiekis = 5;
    double bendrasLaikas = 0;

    for (int dydis : dydziai) {
        cout << "\nTestavimas " << dydis << " irasu:\n";

        string failoPavadinimas = "studentai_" + to_string(dydis) + ".txt";

        try {
            double kurmoLaikas = generuotiFailus(dydis, namuDarbaiKiekis, "studentai_");
            cout << "Failo sukurimo laikas: " << kurmoLaikas << " sekundziu\n";

            vector<Studentas> studentai;
            double skaitymoLaikas = nuskaitytiDuomenisIsFailo(failoPavadinimas, studentai);
            cout << "Failo skaitymo laikas: " << skaitymoLaikas << " sekundziu\n";

            vector<Studentas> vargsiukai, galvociai;
            double rusiavimoLaikas = rusiuotiStudentus(studentai, vargsiukai, galvociai, true);
            cout << "Rusiavimo i dvi grupes laikas: " << rusiavimoLaikas << " sekundziu\n";

            double rasymoLaikasVargsiukai = rasytiStudentusIFaila(vargsiukai, "vargsiukai_" + failoPavadinimas, true);
            double rasymoLaikasGalvociai = rasytiStudentusIFaila(galvociai, "galvociai_" + failoPavadinimas, true);
            cout << "Rasymo laikas (vargsiukai): " << rasymoLaikasVargsiukai << " sekundziu\n";
            cout << "Rasymo laikas (galvociai): " << rasymoLaikasGalvociai << " sekundziu\n";

            double bendrasFailoLaikas = kurmoLaikas + skaitymoLaikas + rusiavimoLaikas + rasymoLaikasVargsiukai + rasymoLaikasGalvociai;
            cout << "Bendras laikas " << dydis << " irasams: " << bendrasFailoLaikas << " sekundziu\n";

            bendrasLaikas += bendrasFailoLaikas;
        } catch (const exception& e) {
            cout << "Klaida apdorojant " << dydis << " irasu: " << e.what() << endl;
        }
    }

    cout << "\nVidutinis testo laikas: " << bendrasLaikas / dydziai.size() << " sekundziu\n";
}
