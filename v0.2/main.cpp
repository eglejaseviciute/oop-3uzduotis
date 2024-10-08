
#include "myLib.h"
#include "studentas.h"
#include "funkcijos.h"


int main() {
    srand(static_cast<unsigned>(time(0))); 

    char pasirinkimas;

    while (true) {
        cout << "\nAr norite generuoti failus (g) ar nuskaityti duomenis is failo (f), ar juos ivesti patys (i)? (iveskite g arba f, arba i): ";
        cin >> pasirinkimas;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (pasirinkimas == 'g') {
            int namuDarbaiKiekis;
            while (true) {
                cout << "Kiek namu darbu rezultatu norite generuoti? ";
                if (cin >> namuDarbaiKiekis && namuDarbaiKiekis > 0) {
                    break;
                } else {
                    cout << "Klaida! Iveskite teigiama skaiciu." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            string input;
            while (true) {
                cout << "Kiek studentu norite generuoti? (ivesti 1000, 10000, 100000, 1000000, 10000000 arba 'visi'): ";
                cin >> input;

                if (input == "visi") {
                    int sizes[] = {1000, 10000, 100000, 1000000, 10000000};
                    for (int size : sizes) {
                        generuotiFailus(size, namuDarbaiKiekis, "studentai_");
                    }
                    break;
                } else {
                    try {
                        int studentuKiekis = std::stoi(input);
                        if (studentuKiekis > 0) {
                            generuotiFailus(studentuKiekis, namuDarbaiKiekis, "studentai_");
                            break;
                        } else {
                            cout << "Klaida! Iveskite teigiama skaiciu." << endl;
                        }
                    } catch (const std::invalid_argument&) {
                        cout << "Klaida! Iveskite tinkama skaiciu arba 'visi'." << endl;
                    } catch (const std::out_of_range&) {
                        cout << "Klaida! Skaicius per didelis. Bandykite dar karta." << endl;
                    }
                }
            }
            continue; 
        } else if (pasirinkimas == 'f') {
            procesarArchivosBucle();
            break;
        } else if (pasirinkimas == 'i') {
            vector<Studentas> studentai;
            int studentuSkaicius;
            while (true) {
                cout << "Kiek studentu norite ivesti? ";
                cin >> studentuSkaicius;
                if (cin.fail() || studentuSkaicius <= 0) {
                    cout << "Klaida! Prasome ivesti teigiama skaiciu." << endl;
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

                char atsitiktiniuPasirinkimas;
                while (true) {
                    cout << "Ar norite generuoti atsitiktinius balus (t - TAIP, n - NE)? ";
                    string ivestis; 
                    cin >> ivestis;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

                    if (ivestis.length() == 1 && (ivestis[0] == 't' || ivestis[0] == 'n')) {
                        atsitiktiniuPasirinkimas = ivestis[0]; 
                        break; 
                    } else {
                        cout << "Klaida! Prasome ivesti tik viena simboli: 't' arba 'n'!" << endl;
                    }
                }

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

    
            std::sort(studentai.begin(), studentai.end(), lygintiPagalVardaIrPavarde);

    
            rodytiRezultatus(studentai, naudotiVidurki);
            break;
        } else {
            cout << "Klaida! Prasome ivesti 'g', 'f' arba 'i'!" << endl;
        }
    }

    return 0;
}
