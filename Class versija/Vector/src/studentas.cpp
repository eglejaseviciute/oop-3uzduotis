#include "studentas.h"
#include "myLib.h"
#include "funkcijos.h"


Studentas::Studentas(const std::string& vardas, const std::string& pavarde)
    : vardas_(vardas), pavarde_(pavarde) {}



// Funkcija ivedanti studento duomenis
void Studentas::ivestiStudenta(bool atsitiktiniai, int namuDarbaiKiekis) {
    std::cout << "Iveskite studento varda: ";
    std::cin >> vardas_;
    std::cout << "Iveskite studento pavarde: ";
    std::cin >> pavarde_;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (atsitiktiniai) {
        // Assuming generuotiRezultatus is modified to work with the new class
        generuotiRezultatus(*this, namuDarbaiKiekis);
    } else {
        std::string input;
        int rezultatas;
        bool bentVienasRezultatas = false;

        std::cout << "Iveskite namu darbu rezultatus (du kartus paspauskite ENTER, kai noresite baigti):" << std::endl;

        while (true) {
            std::getline(std::cin, input);

            if (input.empty()) {
                if (bentVienasRezultatas) break;
                std::cout << "Turite ivesti bent viena namu darbu rezultata!" << std::endl;
                continue;
            }

            try {
                rezultatas = std::stoi(input);
                if (rezultatas < 0 || rezultatas > 10) {
                    std::cout << "Klaida! Namu darbu rezultatas turi buti tarp 0 ir 10. Iveskite teigiama skaiciu: ";
                } else {
                    rezultatai_.addNamuDarbas(rezultatas);
                    bentVienasRezultatas = true;
                }
            } catch (const std::invalid_argument&) {
                std::cout << "Klaida! Prasome ivesti tinkama skaiciu: ";
            } catch (const std::out_of_range&) {
                std::cout << "Klaida! Skaicius per didelis. Bandykite dar karta: ";
            }
        }

        std::cout << "Iveskite egzamino rezultata: ";
        while (true) {
            std::getline(std::cin, input);
            if (input.empty()) {
                std::cout << "Klaida! Prasome ivesti egzamino rezultata: ";
            } else {
                try {
                    int egz = std::stoi(input);
                    if (egz < 0 || egz > 10) {
                        std::cout << "Klaida! Egzamino rezultatas turi buti tarp 0 ir 10. Iveskite tinkama skaiciu: ";
                    } else {
                        rezultatai_.setEgzaminas(egz);
                        break;
                    }
                } catch (const std::invalid_argument&) {
                    std::cout << "Klaida! Prasome ivesti tinkama skaiciu: ";
                } catch (const std::out_of_range&) {
                    std::cout << "Klaida! Skaicius per didelis. Bandykite dar karta: ";
                }
            }
        }
        std::cout << std::endl;
    }
}


// Funkcija spausdinanti studento duomenis
void Studentas::spausdintiStudenta(bool naudotiVidurki) const {
    double galutinis = skaiciuotiGalutiniBala(naudotiVidurki);
    std::cout << std::left << std::setw(18) << vardas_
              << std::setw(18) << pavarde_
              << std::left << std::setw(15) << std::fixed 
              << std::setprecision(2) << galutinis << std::endl;
}


// Funkcija skaiciuojanti galutini bala
double Studentas::skaiciuotiGalutiniBala(bool naudotiVidurki) const {
    double namuDarbuRezultatas = naudotiVidurki ? 
        skaiciuotiVidurki(rezultatai_.namuDarbai()) : 
        skaiciuotiMediana(rezultatai_.namuDarbai());
    return 0.4 * namuDarbuRezultatas + 0.6 * rezultatai_.egzaminas();
}



// Funkcija rasanti studentus i faila
double rasytiStudentusIFaila(const std::vector<Studentas>& studentai,
                            const std::string& failoPavadinimas, 
                            bool naudotiVidurki) {
    auto start = std::chrono::high_resolution_clock::now();
    std::ofstream failas(failoPavadinimas);
    if (!failas) {
        throw std::runtime_error("Nepavyko atidaryti failo: " + failoPavadinimas);
    }

    failas << std::left << std::setw(18) << "Vardas" << std::setw(18) << "Pavarde" 
           << (naudotiVidurki ? "Galutinis (Vid.)" : "Galutinis (Med.)") << std::endl;
    failas << std::string(60, '-') << std::endl;

    for (const auto& studentas : studentai) {
        double galutinis = studentas.skaiciuotiGalutiniBala(naudotiVidurki);
        failas << std::left << std::setw(18) << studentas.vardas()
               << std::setw(18) << studentas.pavarde()
               << std::fixed << std::setprecision(2) << galutinis << std::endl;
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
