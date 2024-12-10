#include "studentas.h"
#include "myLib.h"
#include "funkcijos.h"


istream& operator>>(istream& is, Studentas& studentas) {
    studentas.clearNamuDarbai();

    // Aptinkama, ar ivestis vyksta per konsole, ar is failo
    bool isConsoleInput = (&is == &cin);

    if (isConsoleInput) {
        // Konsoles ivedimo logika
        cout << "\n";
        cout << "Iveskite studento varda: ";
        cin >> studentas.vardas_;
    
        cout << "Iveskite studento pavarde: ";
        cin >> studentas.pavarde_;

        is.ignore(numeric_limits<streamsize>::max(), '\n');

        string input;
        int rezultatas;
        bool bentVienasRezultatas = false;

        cout << "Iveskite namu darbu rezultatus (du kartus paspauskite ENTER, kai noresite baigti):" << endl;

        while (true) {
            getline(is, input);

            if (input.empty()) {
                if (bentVienasRezultatas) break;
                cout << "Turite ivesti bent viena namu darbu rezultata!" << endl;
                continue;
            }

            try {
                rezultatas = stoi(input); // Konvertuojama i sveikaji skaiciu
                if (rezultatas < 0 || rezultatas > 10) {
                    cout << "Klaida! Namu darbu rezultatas turi buti tarp 0 ir 10. Iveskite teigiama skaiciu: ";
                    continue;
                } 
                studentas.addNamuDarbas(rezultatas);
                bentVienasRezultatas = true;
            } catch (const invalid_argument&) {
                cout << "Klaida! Prasome ivesti tinkama skaiciu: ";
                continue;
            } catch (const out_of_range&) {
                cout << "Klaida! Skaicius per didelis. Bandykite dar karta: ";
                continue;
            }
        }

        cout << "Iveskite egzamino rezultata: ";
        while (true) {
            getline(is, input);
            if (input.empty()) {
                cout << "Klaida! Prasome ivesti egzamino rezultata: ";
                continue;
            }

            try {
                int egz = stoi(input); // Konvertuojamas egzamino rezultatas
                if (egz < 0 || egz > 10) {
                    cout << "Klaida! Egzamino rezultatas turi buti tarp 0 ir 10. Iveskite tinkama skaiciu: ";
                    continue;
                }
                studentas.setEgzaminas(egz);
                break;
            } catch (const invalid_argument&) {
                cout << "Klaida! Prasome ivesti tinkama skaiciu: ";
            } catch (const out_of_range&) {
                cout << "Klaida! Skaicius per didelis. Bandykite dar karta: ";
            }
        }
    } else {
        // Failo ivesties logika
        string vardas, pavarde;
        list<int> namuDarbai;
        string input;
        int nd;
        bool egzaminasNuskaitytas = false;

        if (!(is >> vardas >> pavarde)) {
            throw runtime_error("Nepavyko nuskaityti vardo ir pavardes.");
        }

        studentas.setVardas(vardas);
        studentas.setPavarde(pavarde);

        while (is >> input) {
            try {
                nd = stoi(input); // Bandome konvertuoti i skaiciu
                if (nd < 0 || nd > 10) {
                    throw out_of_range("Rezultatas ne intervale [0, 10]");
                }
                if (!egzaminasNuskaitytas) {
                    namuDarbai.push_back(nd);
                } else {
                    throw runtime_error("Po egzamino rezultato aptikti papildomi duomenys.");
                }
            } catch (const invalid_argument&) {
                // Klaida, jei ivestas netinkamas simbolis
                cout << "Netinkamas simbolis '" << input << "' studentui(-ei): "
                     << studentas.vardas() << " " << studentas.pavarde() << "." << endl;
                cout << "Iveskite tinkama rezultata (skaicius nuo 0 iki 10): ";

                while (!(cin >> nd) || nd < 0 || nd > 10) {
                    cout << "Klaida! Iveskite skaiciu tarp 0 ir 10: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                namuDarbai.push_back(nd); // Irasome pataisyta rezultata
            } catch (const out_of_range&) {
                // Klaida, jei rezultatas ne leistiname intervale
                cout << "Rezultatas '" << input << "' ne intervale [0, 10] studentui(-ei): "
                    << studentas.vardas() << " " << studentas.pavarde() << "." << endl;
                cout << "Iveskite tinkama rezultata (skaicius nuo 0 iki 10): ";
                while (!(cin >> nd) || nd < 0 || nd > 10) {
                    cout << "Klaida! Iveskite skaiciu tarp 0 iki 10: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                namuDarbai.push_back(nd); // Irasome pataisyta rezultata
            } catch (const runtime_error& e) {
                cout << "Klaida: " << e.what() << " (" << studentas.vardas() << " " << studentas.pavarde() << ")." << endl;
                break;
            }
        }

        if (namuDarbai.empty()) {
            throw runtime_error("Nerasta namu darbu rezultatu.");
        }

        // Egzamino rezultatas - paskutinis elementas namu darbu sarase
        studentas.setEgzaminas(namuDarbai.back());
        namuDarbai.pop_back();// Pasaliname egzamino rezultata is namu darbu saraso
        studentas.setNamuDarbai(namuDarbai);

        if (namuDarbai.empty()) {
            throw runtime_error("Namu darbu rezultatu nera, rastas tik egzamino rezultatas.");
        }
    }
    return is;
}


ostream& operator<<(ostream& os, const Studentas& studentas) {
    double galutinis = studentas.skaiciuotiGalutiniBala("v");
    os << left << setw(18) << studentas.vardas()
       << setw(22) << studentas.pavarde()
       << fixed << setprecision(2) << galutinis << endl;

    return os;
}


// Funkcija ivedanti studento duomenis
void Studentas::ivestiStudenta(bool atsitiktiniai, int namuDarbaiKiekis) {
    if (atsitiktiniai) {
        // Naudojama funkcija generuoti rezultatus
        cout << "Iveskite studento varda: ";
        cin >> vardas_;
    
        cout << "Iveskite studento pavarde: ";
        cin >> pavarde_;
        generuotiRezultatus(*this, namuDarbaiKiekis);
    } else {
        // Naudojamas operator>> rankiniams duomenims
        cin >> *this;
    }
}


// Funkcija skaiciuojanti galutini bala
double Studentas::skaiciuotiGalutiniBala(bool naudotiVidurki) const {
    double namuDarbuRezultatas = naudotiVidurki ? 
        skaiciuotiVidurki(namuDarbai_) : 
        skaiciuotiMediana(namuDarbai_);
    return 0.4 * namuDarbuRezultatas + 0.6 * egzaminas_;
}
