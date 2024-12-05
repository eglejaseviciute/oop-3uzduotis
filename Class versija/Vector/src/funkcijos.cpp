#include "funkcijos.h"
#include "myLib.h"
#include "studentas.h"
#include "strategijos.h"


map<string, VeikimoGreicioMatavimai> veikimoGreicioRezultatai;


// Funkcija skaiciuojanti vidurki
double skaiciuotiVidurki(const vector<int>& namuDarbai) {
    if (namuDarbai.empty()) return 0;
    return accumulate(namuDarbai.begin(), namuDarbai.end(), 0.0) / namuDarbai.size();
}


// Funkcija skaiciuojanti mediana
double skaiciuotiMediana(vector<int> namuDarbai) {
    if (namuDarbai.empty()) return 0;
    sort(namuDarbai.begin(), namuDarbai.end());
    int dydis = namuDarbai.size();
    if (dydis % 2 == 0) {
        return (namuDarbai[dydis / 2 - 1] + namuDarbai[dydis / 2]) / 2.0;
    }
    return namuDarbai[dydis / 2];
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
    studentas.clearNamuDarbai();
    
    for (int i = 0; i < namuDarbaiKiekis; ++i) {
        studentas.addNamuDarbas(rand() % 11);
    }
    studentas.setEgzaminas(rand() % 11);
    
}


// Funkcija nuskaitanti duomenis is failo
double nuskaitytiDuomenisIsFailo(const string& failoPavadinimas, vector<Studentas>& studentai) {
    auto start = std::chrono::high_resolution_clock::now();

    ifstream failas(failoPavadinimas);
    if (!failas) {
        throw runtime_error("Klaida! Nepavyko atidaryti failo: " + failoPavadinimas);
    }

    string line;
    getline(failas, line); // Praleidziame pirma eilute (antraste)

    int lineNumber = 1;
    while (getline(failas, line)) {
        lineNumber++;
        stringstream ss(line);
        try {
            Studentas studentas;
            ss >> studentas; // naudojamas operatorius>> studento duomenims nuskaityti
            studentai.push_back(studentas);
        } catch (const runtime_error& e) {
            cout << "Klaida eiluteje " << lineNumber << ": " << e.what() << endl;
        }
    }

    failas.close();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    double readingTime = diff.count();

    veikimoGreicioRezultatai[failoPavadinimas].setSkaitymoLaikas(readingTime);

    return readingTime;
}


bool lygintiPagalPavarde(const Studentas& a, const Studentas& b) {
    return a.pavarde() < b.pavarde();
}


bool lygintiPagalVarda(const Studentas& a, const Studentas& b) {
    return a.vardas() < b.vardas();
}


bool lygintiPagalVardaIrPavarde(const Studentas& a, const Studentas& b) {
    return (a.vardas() + a.pavarde()) < (b.vardas() + b.pavarde());
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
    
    veikimoGreicioRezultatai[fileName].setKurimoLaikas(creationTime);
    
    return creationTime;
}


// Funkcija rasanti studentus i faila
double rasytiStudentusIFaila(const vector<Studentas>& studentai,
                            const string& failoPavadinimas,
                            bool naudotiVidurki) {
    auto start = std::chrono::high_resolution_clock::now();
    ofstream outputFile(failoPavadinimas); 

    if (!outputFile) {
        throw runtime_error("Nepavyko atidaryti failo: " + failoPavadinimas);
    }

    outputFile << left << setw(18) << "Vardas" << setw(18) << "Pavarde"
              << (naudotiVidurki ? "Galutinis (Vid.)" : "Galutinis (Med.)") << endl;
    outputFile << string(60, '-') << endl;

    for (const auto& studentas : studentai) {
        outputFile << studentas;  // operator<<
        double galutinis = studentas.skaiciuotiGalutiniBala(naudotiVidurki);
        outputFile << fixed << setprecision(2) << galutinis << endl; 
    }

    outputFile.close();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    return diff.count();
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
        cout << studentas; // operator<<
        cout << setw(25) << &studentas;
        double galutinis = studentas.skaiciuotiGalutiniBala(naudotiVidurki);
        cout << fixed << setprecision(2) << galutinis << endl;
    }
}


// Funkcija greicio rezultatu rodymui
void rodytiGreicioAnalizesRezultatus(const string& failoPavadinimas) {
    const auto& rezultatai = veikimoGreicioRezultatai[failoPavadinimas];
    cout << fixed << setprecision(8);
    cout << "\nGreicio analizes rezultatai failui: " << failoPavadinimas << endl;
    cout << "- Failo skaitymo laikas: " << rezultatai.getSkaitymoLaikas() << " sekundziu" << endl;
    cout << "- Rusiavimo i dvi grupes laikas: " << rezultatai.getRusiavimoLaikas() << " sekundziu" << endl;
    cout << "- Rasymo laikas (vargsiukai): " << rezultatai.getRasymoLaikasVargsiukai() << " sekundziu" << endl;
    cout << "- Rasymo laikas (galvociai): " << rezultatai.getRasymoLaikasGalvociai() << " sekundziu" << endl;
    
    double bendrasLaikas = rezultatai.getSkaitymoLaikas() + rezultatai.getRusiavimoLaikas() +
                          rezultatai.getRasymoLaikasVargsiukai() + rezultatai.getRasymoLaikasGalvociai();
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
            testiApdorojima = gautiTinkamaSymboli("\nAr norite nuskaityti kita faila? (Iveskite 't' - TAIP arba 'n' - NE): ", "'t' arba 'n'!");
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

        char strategijaPasirinkimas = gautiTinkamaSymboli(
            "\nPasirinkite rusiavimo strategija:\n"
            "* 1 - strategija (du nauji konteineriai)\n"
            "* 2 - strategija (vienas naujas konteineris)\n"
            "* 3 - strategija (optimizuota)\n"
            "* 4 - palyginti visas strategijas\n"
            "(Iveskite '1', '2', '3' arba '4'): ",
            "'1', '2', '3' arba '4'!\n");

        
        if (strategijaPasirinkimas == '4') {
            vector<Studentas> studentaiKopija = studentai;
            palygintiStrategijas(studentaiKopija, naudotiVidurki);
            
            testiApdorojima = gautiTinkamaSymboli(
                "\nAr norite nuskaityti kita faila?\n"
                "(Iveskite 't' - TAIP arba 'n' - NE): ",
                "'t' arba 'n'!\n");
            continue;
        }

        
        char rusiavimoPasirinkimas = gautiTinkamaSymboli(
            "\nKaip norite surusiuoti studentus?\n"
            "* 1 - pagal galutini bala didejimo tvarka\n"
            "* 2 - pagal galutini bala mazejimo tvarka\n"
            "* 3 - pagal varda\n"
            "* 4 - pagal pavarde\n"
            "* 5 - pagal varda ir pavarde\n"
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
        double rusiavimoLaikas = 0.0;
        vector<Studentas> studentaiKopija = studentai;
        
        switch(strategijaPasirinkimas) {
            case '1':
                rusiavimoLaikas = rusiuotiStudentusStrategija1(studentai, vargsiukai, galvociai, naudotiVidurki);
                break;
            case '2':
                rusiavimoLaikas = rusiuotiStudentusStrategija2(studentaiKopija, vargsiukai, naudotiVidurki);
                galvociai = studentaiKopija;
                break;
            case '3':
                rusiavimoLaikas = rusiuotiStudentusStrategija3(studentaiKopija, vargsiukai, naudotiVidurki);
                galvociai = studentaiKopija;
                break;
        }

        veikimoGreicioRezultatai[failoPavadinimas].setRusiavimoLaikas(rusiavimoLaikas);

        string vargsiukaiFailoPavadinimas = "vargsiukai_" + failoPavadinimas;
        string galvociaiFailoPavadinimas = "galvociai_" + failoPavadinimas;

        double rasymoLaikasVargsiukai = rasytiStudentusIFaila(vargsiukai, vargsiukaiFailoPavadinimas, naudotiVidurki);
        double rasymoLaikasGalvociai = rasytiStudentusIFaila(galvociai, galvociaiFailoPavadinimas, naudotiVidurki);

        veikimoGreicioRezultatai[failoPavadinimas].setRasymoLaikasVargsiukai(rasymoLaikasVargsiukai);
        veikimoGreicioRezultatai[failoPavadinimas].setRasymoLaikasGalvociai(rasymoLaikasGalvociai);

        cout << "\nStudentai buvo surusiuoti ir irasyti i failus '"
             << vargsiukaiFailoPavadinimas << "' ir '"
             << galvociaiFailoPavadinimas << "'." << endl;

        apdorotiFailai.push_back(failoPavadinimas);

        testiApdorojima = gautiTinkamaSymboli(
            "\nAr norite nuskaityti kita faila?\n"
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
        
        bendrasLaikas += rezultatai.getSkaitymoLaikas() + rezultatai.getRusiavimoLaikas() + rezultatai.getRasymoLaikasVargsiukai() + rezultatai.getRasymoLaikasGalvociai();
    }

    cout << fixed << setprecision(8);
    double vidutinisLaikas = bendrasLaikas / apdorotiFailai.size();
    cout << "Vidutinis laikas visiems apdorotiems failams: " << vidutinisLaikas << " sekundziu" << endl;
    }
}


void RuleOfThreeDemonstravimas () {
    Studentas a;
    cin >> a;
    Studentas b;
    b = a;
    Studentas c(b);
    cout << a << "\n" << b << "\n" << c << endl;
}
