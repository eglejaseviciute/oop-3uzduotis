#include "funkcijos.h"
#include "myLib.h"


double skaiciuotiVidurki(const vector<int>& namuDarbai) {
    double suma = 0;
    for (int nd : namuDarbai) {
        suma += nd;
    }
    return suma / namuDarbai.size();
}


double skaiciuotiMediana(vector<int> namuDarbai) {
    sort(namuDarbai.begin(), namuDarbai.end());
    int dydis = namuDarbai.size();
    if (dydis % 2 == 0) {
        return (namuDarbai[dydis / 2 - 1] + namuDarbai[dydis / 2]) / 2.0;
    } else {
        return namuDarbai[dydis / 2];
    }
}


void nuskaitytiDuomenisIsFailo(string &failoPavadinimas, std::vector<Studentas> &studentai) {
    while (true) { // Ciklas, kad vartotojas galetu pakartotinai ivesti failo pavadinima
        ifstream failas(failoPavadinimas);
        if (!failas) {
            cout << "Klaida! Nepavyko atidaryti failo: " << failoPavadinimas << endl;
            cout << "Prašome įvesti teisingą failo pavadinimą: ";
            cin >> failoPavadinimas;
            continue;
        }

        // Praleidziame pirma eilute (antraste)
        string line;
        std::getline(failas, line);

        while (std::getline(failas, line)) {
            cout << "Nuskaityta eilutė: " << line << endl;
            Studentas studentas;
            stringstream ss(line);

            // Nuskaitome varda ir pavarde
            ss >> studentas.vardas >> studentas.pavarde;
            studentas.rezultatai.namuDarbai.clear();

            // Nuskaitome namu darbus
            string ndInput;
            int nd;
            int ndIndex = 0;

            while (ss >> ndInput) {
                try {
                    nd = stoi(ndInput);
                    if (nd < 0 || nd > 10) {
                        throw std::invalid_argument("Neteisingas diapazonas");
                    }
                    studentas.rezultatai.namuDarbai.push_back(nd);
                    ndIndex++;
                } catch (const std::exception&) {
                    // Klaida su namu darbo rezultatu
                    cout << "Klaida! Netinkamas simbolis ar skaicius studentui(-ei): " 
                         << studentas.vardas << " " << studentas.pavarde 
                         << " (klaida: '" 
                         << ndInput << "')." << endl;

                    cout << "Iveskite tinkama rezultata (skaicius nuo 0 iki 10) studentui(-ei): "
                         << studentas.vardas << " " << studentas.pavarde << ": ";

                    while (true) {
                        cin >> nd;
                        if (cin.fail() || nd < 0 || nd > 10) {
                            cout << "Klaida! Iveskite skaiciu tarp 0 ir 10: ";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        } else {
                            studentas.rezultatai.namuDarbai.push_back(nd);
                            break;
                        }
                    }
                }
            }

    
            if (!studentas.rezultatai.namuDarbai.empty()) {
                // Nuskaitome paskutini namu darba kaip egzamino rezultata
                int egzaminas = studentas.rezultatai.namuDarbai.back();
                studentas.rezultatai.namuDarbai.pop_back(); // Pasaliname paskutini elementa is namu darbu

                // Tikriname, ar egzaminas tinkamas
                if (egzaminas < 0 || egzaminas > 10) {
                    cout << "Klaida! Egzamino rezultatas studentui " << studentas.vardas 
                         << " " << studentas.pavarde << " už neteisingą diapazoną." << endl;
                } else {
                    studentas.rezultatai.egzaminas = egzaminas;
                }
            }

            // Pridedame studenta i sarasa
            if (!studentas.rezultatai.namuDarbai.empty()) {
                studentai.push_back(studentas);
            }
        }

        failas.close();
        break;
    }
}


bool lygintiPagalVarda(const Studentas &a, const Studentas &b) {
    if (a.vardas == b.vardas) {
        return a.pavarde < b.pavarde;
    }
    return a.vardas < b.vardas;
}
