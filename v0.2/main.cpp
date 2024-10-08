#include "myLib.h"
#include "studentas.h"
#include "funkcijos.h"

int main() {
    srand(static_cast<unsigned>(time(0)));

    vector<Studentas> studentai;
    char pasirinkimas;

    while (true) {
        studentai.clear();

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
        } else if (pasirinkimas == 'f' || pasirinkimas == 'i') {
            break;
        } else {
            cout << "Klaida! Prasome ivesti 'g', 'f' arba 'i'!" << endl;
        }
    }
    try {
        if (pasirinkimas == 'f') {
            string failoPavadinimas;
            cout << "Iveskite failo pavadinima (pvz., studentai.txt): ";
            getline(cin, failoPavadinimas);
            nuskaitytiDuomenisIsFailo(failoPavadinimas, studentai);

            
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

            
            char outputPasirinkimas;
            while (true) {
                cout << "Ar norite matyti rezultatus ekrane (e) ar surusiuosti studentus i dvi kategorijas ir irasyti i failus (f)? (iveskite e arba f): ";
                cin >> outputPasirinkimas;

                if (outputPasirinkimas == 'e' || outputPasirinkimas == 'f') {
                    break;
                } else {
                    cout << "Klaida! Prasome ivesti 'e' arba 'f'!" << endl;
                }
            }

            if (outputPasirinkimas == 'e') {
                
                std::sort(studentai.begin(), studentai.end(), lygintiPagalVardaIrPavarde);
                
                rodytiRezultatus(studentai, naudotiVidurki);
            } else {
                char sortingPreference;
                cout << "Kaip norite surusiuoti studentus? (1 - Pagal galutini bala didejimo tvarka, 2 - Pagal galutini bala mazejimo tvarka, 3 - Pagal varda, 4 - Pagal pavarde, 5 - Pagal varda ir pavarde): ";
                cin >> sortingPreference;

                if (sortingPreference == '1') {
                    std::sort(studentai.begin(), studentai.end(), lygintiPagalGalutiniBalaAscending);
                } else if (sortingPreference == '2') {
                    std::sort(studentai.begin(), studentai.end(), lygintiPagalGalutiniBalaDescending);
                } else if (sortingPreference == '3') {
                    std::sort(studentai.begin(), studentai.end(), lygintiPagalVarda);
                } else if (sortingPreference == '4') {
                    std::sort(studentai.begin(), studentai.end(), lygintiPagalPavarde);
                } else if (sortingPreference == '5') {
                    std::sort(studentai.begin(), studentai.end(), lygintiPagalVardaIrPavarde);
                }

                vector<Studentas> vargsiukai, galvociai;
                rusiuotiStudentus(studentai, vargsiukai, galvociai, naudotiVidurki);

                rasytiStudentusIFaila(vargsiukai, "vargsiukai.txt", naudotiVidurki);
                rasytiStudentusIFaila(galvociai, "galvociai.txt", naudotiVidurki);

                cout << "Studentai buvo surusiuoti ir irasyti i failus 'vargsiukai.txt' ir 'galvociai.txt'." << endl;
            }

        } else if (pasirinkimas == 'i') {
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
        }
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    return 0;
}
