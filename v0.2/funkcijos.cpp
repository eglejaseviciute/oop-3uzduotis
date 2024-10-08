#include "funkcijos.h"
#include "myLib.h"

double skaiciuotiVidurki(const vector<int>& namuDarbai) {
    double suma = 0.0;
    for (int nd : namuDarbai) {
        suma += nd;
    }
    return suma / namuDarbai.size();
}

double skaiciuotiMediana(vector<int> namuDarbai) {
    std::sort(namuDarbai.begin(), namuDarbai.end());
    int dydis = namuDarbai.size();
    if (dydis % 2 == 0) {
        return (namuDarbai[dydis / 2 - 1] + namuDarbai[dydis / 2]) / 2.0;
    } else {
        return namuDarbai[dydis / 2];
    }
}

void generuotiRezultatus(Studentas &studentas, int namuDarbaiKiekis) {
    for (int i = 0; i < namuDarbaiKiekis; ++i) {
        studentas.rezultatai.namuDarbai.push_back(rand() % 11);
    }
    studentas.rezultatai.egzaminas = rand() % 11;
}

void nuskaitytiDuomenisIsFailo(string &failoPavadinimas, vector<Studentas> &studentai) {
    while (true) {
        std::ifstream failas(failoPavadinimas);
        if (!failas) {
            cout << "Klaida! Nepavyko atidaryti failo: " << failoPavadinimas << endl;
            cout << "Prasome ivesti teisinga failo pavadinima: ";
            cin >> failoPavadinimas; 
            continue; 
        }

        string line;
        std::getline(failas, line);

        while (std::getline(failas, line)) {
            cout << "Nuskaityta eilute: " << line << endl; 
            Studentas studentas;
            std::stringstream ss(line);

            ss >> studentas.vardas >> studentas.pavarde;
            studentas.rezultatai.namuDarbai.clear();

            string ndInput;
            int nd;
            int ndIndex = 0; 

            while (ss >> ndInput) {
                try {
                    nd = std::stoi(ndInput);
                    if (nd < 0 || nd > 10) {
                        throw std::invalid_argument("Neteisingas diapazonas");
                    }
                    studentas.rezultatai.namuDarbai.push_back(nd);
                    ndIndex++;
                } catch (const std::exception&) {
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
                int egzaminas = studentas.rezultatai.namuDarbai.back();
                studentas.rezultatai.namuDarbai.pop_back(); 

                if (egzaminas < 0 || egzaminas > 10) {
                    cout << "Klaida! Egzamino rezultatas studentui " << studentas.vardas 
                         << " " << studentas.pavarde << " uz neteisinga diapazona." << endl;
                } else {
                    studentas.rezultatai.egzaminas = egzaminas;
                }
            }

            if (!studentas.rezultatai.namuDarbai.empty()) {
                studentai.push_back(studentas);
            }
        }

        failas.close();
        break; 
    }
}

void generuotiFailus(int studentuKiekis, int namuDarbaiKiekis, const string &filePrefix) {
    std::ofstream failas(filePrefix + std::to_string(studentuKiekis) + ".txt");
    if (!failas) {
        cout << "Klaida! Nepavyko sukurti failo." << endl;
        return;
    }

    for (int i = 1; i <= studentuKiekis; ++i) {
        failas << "Vardas" << i << " Pavarde" << i << " ";
        for (int j = 0; j < namuDarbaiKiekis; ++j) {
            failas << (rand() % 11) << " ";
        }
        failas << (rand() % 11) << endl;
    }

    failas.close();
    cout << "Failas " << filePrefix + std::to_string(studentuKiekis) + ".txt buvo sukurtas." << endl;
}
