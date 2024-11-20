#ifndef STRATEGIJOS_H
#define STRATEGIJOS_H


#include "myLib.h"
#include "studentas.h"


// Strategiju funkciju deklaracijos

double rusiuotiStudentusStrategija1(const list<Studentas>& studentai, 
                                   list<Studentas>& vargsiukai, 
                                   list<Studentas>& galvociai, 
                                   bool naudotiVidurki);

double rusiuotiStudentusStrategija2(list<Studentas>& studentai, 
                                   list<Studentas>& vargsiukai, 
                                   bool naudotiVidurki);

double rusiuotiStudentusStrategija3(list<Studentas>& studentai, 
                                   list<Studentas>& vargsiukai, 
                                   bool naudotiVidurki);

// Testavimo ir palyginimo funkciju deklaracijos
void testuotiStrategija(const string& strategijaPavadinimas,
                       list<Studentas>& studentai,
                       bool naudotiVidurki);

void palygintiStrategijas(list<Studentas>& studentai, bool naudotiVidurki);


#endif // STRATEGIJOS_H
