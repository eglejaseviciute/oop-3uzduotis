#include "studentas.h"
#include "myLib.h"
#include "funkcijos.h"


Studentas::Studentas(const string& vardas, const string& pavarde)
    : vardas_(vardas), pavarde_(pavarde) {}



// Funkcija ivedanti studento duomenis
void Studentas::ivestiStudenta(bool atsitiktiniai, int namuDarbaiKiekis) {
    cout << "Iveskite studento varda: ";
    cin >> vardas_;
    cout << "Iveskite studento pavarde: ";
    cin >> pavarde_;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (atsitiktiniai) {
        // Assuming generuotiRezultatus is modified to work with the new class
        generuotiRezultatus(*this, namuDarbaiKiekis);
    } else {
        string input;
        int rezultatas;
        bool bentVienasRezultatas = false;

        cout << "Iveskite namu darbu rezultatus (du kartus paspauskite ENTER, kai noresite baigti):" << endl;

        while (true) {
            getline(cin, input);

            if (input.empty()) {
                if (bentVienasRezultatas) break;
                cout << "Turite ivesti bent viena namu darbu rezultata!" << endl;
                continue;
            }

            try {
                rezultatas = stoi(input);
                if (rezultatas < 0 || rezultatas > 10) {
                    cout << "Klaida! Namu darbu rezultatas turi buti tarp 0 ir 10. Iveskite teigiama skaiciu: ";
                } else {
                    rezultatai_.addNamuDarbas(rezultatas);
                    bentVienasRezultatas = true;
                }
            } catch (const std::invalid_argument&) {
                cout << "Klaida! Prasome ivesti tinkama skaiciu: ";
            } catch (const std::out_of_range&) {
                cout << "Klaida! Skaicius per didelis. Bandykite dar karta: ";
            }
        }

        cout << "Iveskite egzamino rezultata: ";
        while (true) {
            getline(std::cin, input);
            if (input.empty()) {
                cout << "Klaida! Prasome ivesti egzamino rezultata: ";
            } else {
                try {
                    int egz = stoi(input);
                    if (egz < 0 || egz > 10) {
                        cout << "Klaida! Egzamino rezultatas turi buti tarp 0 ir 10. Iveskite tinkama skaiciu: ";
                    } else {
                        rezultatai_.setEgzaminas(egz);
                        break;
                    }
                } catch (const invalid_argument&) {
                    cout << "Klaida! Prasome ivesti tinkama skaiciu: ";
                } catch (const out_of_range&) {
                    cout << "Klaida! Skaicius per didelis. Bandykite dar karta: ";
                }
            }
        }
        cout << endl;
    }
}


// Funkcija spausdinanti studento duomenis
void Studentas::spausdintiStudenta(bool naudotiVidurki) const {
    double galutinis = skaiciuotiGalutiniBala(naudotiVidurki);
    cout << sleft << setw(18) << vardas_
              << setw(18) << pavarde_
              << left << setw(15) << fixed
              << setprecision(2) << galutinis << endl;
}


// Funkcija skaiciuojanti galutini bala
double Studentas::skaiciuotiGalutiniBala(bool naudotiVidurki) const {
    double namuDarbuRezultatas = naudotiVidurki ? 
        skaiciuotiVidurki(rezultatai_.namuDarbai()) : 
        skaiciuotiMediana(rezultatai_.namuDarbai());
    return 0.4 * namuDarbuRezultatas + 0.6 * rezultatai_.egzaminas();
}



// Funkcija rasanti studentus i faila
double rasytiStudentusIFaila(const vector<Studentas>& studentai,
                            const string& failoPavadinimas,
                            bool naudotiVidurki) {
    auto start = std::chrono::high_resolution_clock::now();
    ofstream failas(failoPavadinimas);
    if (!failas) {
        throw runtime_error("Nepavyko atidaryti failo: " + failoPavadinimas);
    }

    failas << left << setw(18) << "Vardas" << setw(18) << "Pavarde"
           << (naudotiVidurki ? "Galutinis (Vid.)" : "Galutinis (Med.)") << endl;
    failas << string(60, '-') << endl;

    for (const auto& studentas : studentai) {
        double galutinis = studentas.skaiciuotiGalutiniBala(naudotiVidurki);
        failas << left << setw(18) << studentas.vardas()
               << setw(18) << studentas.pavarde()
               << fixed << setprecision(2) << galutinis << endl;
    }

    failas.close();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    return diff.count();
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
