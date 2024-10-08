#include "studentas.h"
#include "funkcijos.h"


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
                cout << "Klaida! Skaicius per didelis. Bandykite dar karta: ";
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
                    cout << "Klaida! Skaicius per didelis. Bandykite dar karta: ";
                }
            }
        }
        cout << endl;
    }
}


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


void rusiuotiStudentus(const vector<Studentas> &studentai, vector<Studentas> &vargsiukai, vector<Studentas> &galvociai, bool naudotiVidurki) {
    for (const auto &studentas : studentai) {
        double galutinis = skaiciuotiGalutiniBala(studentas, naudotiVidurki);
        if (galutinis < 5.0) {
            vargsiukai.push_back(studentas);
        } else {
            galvociai.push_back(studentas);
        }
    }
}


void rasytiStudentusIFaila(const vector<Studentas> &studentai, const string &failoPavadinimas, bool naudotiVidurki) {
    std::ofstream failas(failoPavadinimas);
    if (!failas) {
        throw std::runtime_error("Nepavyko atidaryti failo: " + failoPavadinimas);
    }

    failas << left << setw(18) << "Vardas" << setw(18) << "Pavarde" 
           << (naudotiVidurki ? "Galutinis (Vid.)" : "Galutinis (Med.)") << endl;
    failas << string(60, '-') << endl;

    for (const auto &studentas : studentai) {
        double galutinis = skaiciuotiGalutiniBala(studentas, naudotiVidurki);
        failas << left << setw(18) << studentas.vardas
               << setw(18) << studentas.pavarde
               << fixed << setprecision(2) << galutinis << endl;
    }

    failas.close();
}
