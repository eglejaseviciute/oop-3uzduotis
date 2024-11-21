#include "myLib.h"
#include "studentas.h"
#include "funkcijos.h"
#include "strategijos.h"


// Pagrindinė funkcija
int main() {
    srand(static_cast<unsigned>(time(0)));

    char pasirinkimas;
    bool testi = true;

    while (testi) {
        try {
            pasirinkimas = gautiTinkamaSymboli(
            "Pasirinkite:\n"
            "* generuoti failus (g)\n"
            "* nuskaityti duomenis iš failo (f)\n"
            "* juos ivesti patiems (i)\n"
            "* atlikti veikimo greicio analize (a)\n"
            "(Iveskite 'g', 'f', 'i' arba 'a'!): ",
            "'g', 'f', 'i' arba 'a'!\n");

            if(pasirinkimas == 'a') {
                greicioAnalize();
            }
            else if (pasirinkimas == 'g') {
                int namuDarbaiKiekis;
                while (true) {
                    cout << "\nKiek namu darbu rezultatu norite generuoti? ";
                    if (cin >> namuDarbaiKiekis && namuDarbaiKiekis > 0) {
                        break;
                    }
                    cout << "\nKlaida! Iveskite teigiama skaiciu!" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                string ivestis;
                while (true) {
                    cout << "\nKiek studentu norite generuoti? (ivesti 1000, 10000, 100000, 1000000, 10000000 arba 'visi'): ";
                    cin >> ivestis;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    if (ivestis == "visi") {
                        int dydziai[] = {1000, 10000, 100000, 1000000, 10000000};
                        for (int dydis : dydziai) {
                            generuotiFailus(dydis, namuDarbaiKiekis, "studentai_");
                        }
                        break;
                    }
                    
                    try {
                        int studentuKiekis = stoi(ivestis);
                        if (studentuKiekis > 0) {
                            generuotiFailus(studentuKiekis, namuDarbaiKiekis, "studentai_");
                            break;
                        }
                        cout << "\nKlaida! Iveskite teigiama skaiciu." << endl;
                    }
                    catch (const invalid_argument&) {
                        cout << "\nKlaida! Iveskite tinkama skaiciu arba 'visi'!" << endl;
                    }
                    catch (const out_of_range&) {
                        cout << "\nKlaida! Skaicius per didelis. Bandykite dar karta." << endl;
                    }
                }
            }
            else if (pasirinkimas == 'f') {
                failuApdorojimoCiklas();
            }
            else if (pasirinkimas == 'i') {
                list<Studentas> studentai;
                int studentuSkaicius;
                
                while (true) {
                    cout << "\nKiek studentu norite ivesti? ";
                    if (cin >> studentuSkaicius && studentuSkaicius > 0) {
                        break;
                    }
                    cout << "\nKlaida! Prasome ivesti teigiama skaiciu!" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                for (int i = 0; i < studentuSkaicius; ++i) {
                    cout << "\nIveskite " << i + 1 << "-ojo studento duomenis:" << endl;
                    
                    char atsitiktiniuPasirinkimas = gautiTinkamaSymboli(
                        "Ar norite generuoti atsitiktinius balus? (Iveskite 't' - TAIP arba 'n' - NE): ",
                        "'t' arba 'n'!\n"
                    );

                    bool atsitiktiniai = (atsitiktiniuPasirinkimas == 't');
                    int namuDarbaiKiekis = 0;
                    
                    if (atsitiktiniai) {
                        while (true) {
                            cout << "\nKiek namu darbu rezultatu norite generuoti? ";
                            if (cin >> namuDarbaiKiekis && namuDarbaiKiekis > 0) {
                                break;
                            }
                            cout << "\nKlaida! Iveskite teigiama skaiciu!";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                    }

                    Studentas studentas;
                    ivestiStudenta(studentas, atsitiktiniai, namuDarbaiKiekis);
                    studentai.push_back(studentas);
                }

                char metodoPasirinkimas = gautiTinkamaSymboli(
                "\nAr norite skaiciuoti studento galutini bala pagal:\n"
                "* vidurki (v),\n"
                "* mediana (m)?\n"
                "(Iveskite 'v' arba 'm'!): ",
                "'v' arba 'm'!\n");
                bool naudotiVidurki = (metodoPasirinkimas == 'v');

                studentai.sort(lygintiPagalVardaIrPavarde);
                rodytiRezultatus(studentai, naudotiVidurki);
            }
        }
        catch (const exception& e) {
            cout << "Ivyko klaida: " << e.what() << endl;
        }

        char griztiPasirinkimas = gautiTinkamaSymboli(
            "\nAr norite grizti i pagrindini meniu? (Iveskite 't' - TAIP arba 'n' - NE): ",
            "'t' arba 'n'!\n"
        );
        testi = (griztiPasirinkimas == 't' || griztiPasirinkimas == 'T');
    }

    return 0;
}
