#include "myLib.h"
#include "studentas.h"
#include "funkcijos.h"


// Pagrindinė funkcija
int main() {
    srand(static_cast<unsigned>(time(0)));

    char pasirinkimas;

    while (true) {
        pasirinkimas = gautiTinkamaSymboli("Ar norite generuoti failus (g), nuskaityti duomenis iš failo (f), juos ivesti patys (i), ar atlikti greicio analize penkiems failams iš karto (p)? ", "'g', 'f', 'i', 'p'!");

        try {
            if (pasirinkimas == 'g') {
                int namuDarbaiKiekis;
                while (true) {
                    cout << "Kiek namu darbu rezultatu norite generuoti? ";
                    if (cin >> namuDarbaiKiekis && namuDarbaiKiekis > 0) {
                        break;
                    } else {
                        cout << "Klaida! Iveskite teigiama skaiciu!" << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }

                string ivestis;
                while (true) {
                    cout << "Kiek studentu norite generuoti? (ivesti 1000, 10000, 100000, 1000000, 10000000 arba 'visi'): ";
                    cin >> ivestis;

                    if (ivestis == "visi") {
                        int dydžiai[] = {1000, 10000, 100000, 1000000, 10000000};
                        for (int dydis : dydžiai) {
                            generuotiFailus(dydis, namuDarbaiKiekis, "studentai_");
                        }
                        break;
                    } else {
                        try {
                            int studentuKiekis = stoi(ivestis);
                            if (studentuKiekis > 0) {
                                generuotiFailus(studentuKiekis, namuDarbaiKiekis, "studentai_");
                                break;
                            } else {
                                cout << "Klaida! Iveskite teigiama skaiciu." << endl;
                            }
                        } catch (const invalid_argument&) {
                            cout << "Klaida! Iveskite tinkama skaiciu arba 'visi'!" << endl;
                        } catch (const out_of_range&) {
                            cout << "Klaida! Skaicius per didelis. Bandykite dar karta." << endl;
                        }
                    }
                }
                continue;
            } else if (pasirinkimas == 'f') {
                failuApdorojimoCiklas();
                break;
            } else if (pasirinkimas == 'i') {
                vector<Studentas> studentai;
                int studentuSkaicius;
                while (true) {
                    cout << "Kiek studentu norite ivesti? ";
                    cin >> studentuSkaicius;
                    if (cin.fail() || studentuSkaicius <= 0) {
                        cout << "Klaida! Prasome ivesti teigiama skaiciu!" << endl;
                        cin.clear(); 
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                    } else {
                        break; 
                    }
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

                for (int i = 0; i < studentuSkaicius; ++i) {
                    cout << endl;
                    cout << "Iveskite " << i + 1 << "-ojo studento duomenis:" << endl;

                    char atsitiktiniuPasirinkimas = gautiTinkamaSymboli("Ar norite generuoti atsitiktinius balus? (Iveskite 't' - TAIP arba 'n' - NE): ", "'t' arba 'n'!");

                    bool atsitiktiniai = (atsitiktiniuPasirinkimas == 't');
                    int namuDarbaiKiekis = 0;
                    if (atsitiktiniai) {
                        cout << "Kiek namu darbu rezultatu norite generuoti? ";
                        while (true) {
                            cin >> namuDarbaiKiekis;
                            if (cin.fail() || namuDarbaiKiekis < 1) {
                                cout << "Klaida! Iveskite teigiama skaiciu: ";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            } else {
                                break;
                            }
                        }
                    }

                    Studentas studentas;
                    ivestiStudenta(studentas, atsitiktiniai, namuDarbaiKiekis);
                    studentai.push_back(studentas);
                }

                char metodoPasirinkimas = gautiTinkamaSymboli("Ar norite skaiciuoti galutini bala pagal vidurki (v) ar mediana (m)? ", "'v' arba 'm'!");
                bool naudotiVidurki = (metodoPasirinkimas == 'v');

                sort(studentai.begin(), studentai.end(), lygintiPagalVardaIrPavarde);

                rodytiRezultatus(studentai, naudotiVidurki);
                break;
            } else if (pasirinkimas == 'p') {
                atliktiGreicioAnalize();
                break;   
            } else {
                cout << "Klaida! Prasome ivesti 'g', 'f', 'i' arba 'p'!" << endl;
                continue;
            }
        } catch (const std::exception& e) {
            cout << "Ivyko klaida: " << e.what() << endl;
        }

        char grizti = gautiTinkamaSymboli("Ar norite grizti i pagrindini meniu? (Iveskite 't' - TAIP arba 'n' - NE): ", "'t' arba 'n'!");
        if (grizti != 't' && grizti != 'T') {
            break;
        }
    }
    return 0;
}
