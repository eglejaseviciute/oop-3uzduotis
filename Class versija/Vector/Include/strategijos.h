#ifndef STRATEGIJOS_H
#define STRATEGIJOS_H


#include "myLib.h"
#include "studentas.h"


// Strategiju funkciju deklaracijos
double rusiuotiStudentusStrategija1(const vector<Studentas>& studentai, 
                                   vector<Studentas>& vargsiukai, 
                                   vector<Studentas>& galvociai, 
                                   bool naudotiVidurki);

double rusiuotiStudentusStrategija2(vector<Studentas>& studentai, 
                                   vector<Studentas>& vargsiukai, 
                                   bool naudotiVidurki);

double rusiuotiStudentusStrategija3(vector<Studentas>& studentai, 
                                   vector<Studentas>& vargsiukai, 
                                   bool naudotiVidurki);

// Testavimo ir palyginimo funkciju deklaracijos
void testuotiStrategija(const string& strategijaPavadinimas,
                       vector<Studentas>& studentai,
                       bool naudotiVidurki);

void palygintiStrategijas(vector<Studentas>& studentai, 
                         bool naudotiVidurki);


#endif // STRATEGIJOS_H