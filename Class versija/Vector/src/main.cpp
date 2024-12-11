#include "myLib.h"
#include "studentas.h"
#include "funkcijos.h"
#include "strategijos.h"


/**
 * @file main.cpp
 * @brief Studentų duomenų tvarkymo ir analizės programos pagrindinis failas
 * 
 * Šis failas pateikia pagrindinę programos sąsają, kuri leidžia vartotojui:
 * - Generuoti studentų duomenų failus
 * - Skaityti duomenis iš failų
 * - Įvesti duomenis rankiniu būdu
 * - Atlikti programos našumo analizę
 * - Demonstruoti objektinio programavimo principus
 */

/**
 * @brief Pagrindinė programos funkcija, valdanti vartotojo sąsają ir programos logiką
 * 
 * Funkcija pateikia meniu, kuriame vartotojas gali pasirinkti įvairias
 * programos funkcijas. Galimi pasirinkimai:
 * - 'g': Generuoti studentų duomenų failus
 * - 'f': Nuskaityti duomenis iš failo
 * - 'i': Įvesti duomenis rankiniu būdu
 * - 'a': Atlikti veikimo greičio analizę
 * - 'p': Parodyti 'Rule of Three' principą
 * - 'z': Demonstruoti abstrakčios 'Zmogus' klasės veikimą
 * 
 * Programa palaiko pakartotinius pasirinkimus ir leidžia vartotojui
 * tęsti darbą arba užbaigti programą.
 * 
 * @return int Programos užbaigimo būsenos kodas (0 - sėkmingas užbaigimas)
 * 
 * @note Programai pradėjus veikti pateikiami pasirinkimai
 *       pagal kuriuos yra vykdomos skirtingos funkcijos.
 *       Kiekvienas pasirinkimas apdorojamas pagal atitinkamą funkciją,
 *       o klaidų atvejais pateikiama klaidos žinutė.
 *       Po kiekvieno pasirinkimo vartotojui leidžiama grįžti į pagrindinį meniu.
 */
int main() {
    // Atsitiktinių skaičių generatoriaus inicializavimas
    srand(static_cast<unsigned>(time(0)));

    // Kintamieji valdyti vartotojo pasirinkimams ir programos būsenai
    char pasirinkimas;
    bool testi = true;

    // Pagrindinis programos ciklas
    while (testi) {
        try {
            // Vartotojo pasirinkimo gavimas su išsamiu meniu
            pasirinkimas = gautiTinkamaSymboli(
            "Pasirinkite:\n"
            "* generuoti failus (g)\n"
            "* nuskaityti duomenis is failo (f)\n"
            "* juos ivesti patiems (i)\n"
            "* atlikti veikimo greicio analize (a)\n"
            "* pademonstruoti 'Rule of three' veikima (p)\n"
            "* pademonstruoti abstraccios klases 'Zmogus' veikima (z)\n"
            "(Iveskite 'g', 'f', 'i', 'a', 'p' arba 'z'!): ",
            "'g', 'f', 'i', 'a', 'p' arba 'z'!\n");

            // Apdoroti skirtingus vartotojo pasirinkimus
            if(pasirinkimas == 'p') {
                RuleOfThreeDemonstravimas(); // Demonstracijos funkcija, rodanti 'Rule of Three' principo veikimą
            } 
            else if(pasirinkimas == 'z') {
                abstrakciosKlasesZmogusDemonstravimas(); // Demonstracijos funkcija, rodanti abstrakčios 'Žmogus' klasės veikimą
            } 
            else if(pasirinkimas == 'a') {
                greicioAnalize(); // Atlikti veikimo greičio analizę
            }
            else if (pasirinkimas == 'g') {
                // Failo generavimo pasirinkimas
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

                // Studentų skaičiaus pasirinkimas generavimui
                string ivestis;
                while (true) {
                    cout << "\nKiek studentu norite generuoti? (ivesti 1000, 10000, 100000, 1000000, 10000000 arba 'visi'): ";
                    cin >> ivestis;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    // Generuoti visus iš anksto nustatytus dydžius
                    if (ivestis == "visi") {
                        int dydziai[] = {1000, 10000, 100000, 1000000, 10000000};
                        for (int dydis : dydziai) {
                            generuotiFailus(dydis, namuDarbaiKiekis, "studentai_");
                        }
                        break;
                    }
                    
                    try {
                        // Bandyti konvertuoti įvestį į studentų skaičių
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
                // Failų apdorojimo funkcija
                failuApdorojimoCiklas(); // Failų apdorojimo funkcija
            }
            else if (pasirinkimas == 'i') {
                // Rankinis studentų duomenų įvedimas
                vector<Studentas> studentai;
                int studentuSkaicius;
                
                // Gauti norimą studentų skaičių
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

                // Įvesti kiekvieno studento duomenis
                for (int i = 0; i < studentuSkaicius; ++i) {
                    cout << "\nIveskite " << i + 1 << "-ojo studento duomenis:" << endl;
                    
                    // Pasirinkti, ar generuoti atsitiktinius balus
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

                    // Sukurti ir įtraukti studentą į sąrašą
                    Studentas studentas;
                    studentas.ivestiStudenta(atsitiktiniai, namuDarbaiKiekis);
                    studentai.push_back(studentas);
                }

                // Pasirinkti galutinio balo skaičiavimo metodą
                char metodoPasirinkimas = gautiTinkamaSymboli(
                "\nAr norite skaiciuoti studento galutini bala pagal:\n"
                "* vidurki (v),\n"
                "* mediana (m)?\n"
                "(Iveskite 'v' arba 'm'!): ",
                "'v' arba 'm'!\n");
                bool naudotiVidurki = (metodoPasirinkimas == 'v');

                // Rūšiuoti studentus ir rodyti rezultatus
                sort(studentai.begin(), studentai.end(), lygintiPagalVardaIrPavarde); // Studentų rūšiavimas pagal vardą ir pavardę
                rodytiRezultatus(studentai, naudotiVidurki); // Studentų rezultatų rodymas
            }
        }
        catch (const exception& e) {
            // Klaidos apdorojimas
            cout << "Ivyko klaida: " << e.what() << endl;
        }

        // Klausti vartotojo, ar nori tęsti darbą
        char griztiPasirinkimas = gautiTinkamaSymboli(
            "\nAr norite grizti i pagrindini meniu? (Iveskite 't' - TAIP arba 'n' - NE): ",
            "'t' arba 'n'!\n"
        );
        testi = (griztiPasirinkimas == 't' || griztiPasirinkimas == 'T');
    }

    return 0;
}
