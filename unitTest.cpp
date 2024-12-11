#include <iostream>
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "/Users/eglejaseviciute/Desktop/v1.5 (vector) class (paprastas)/studentas.h"

using namespace std;

// Test default constructor
TEST(DefaultConstructor, BasicAssertions) {
    Studentas s;
    EXPECT_EQ(s.egzaminas(), 0);
    EXPECT_TRUE(s.namuDarbai().empty());
}

// Test parameterized constructor
TEST(ParameterizedConstructor, BasicAssertions) {
    Studentas s("Jonas", "Jonaitis");
    
    // Check if exam score is 0
    EXPECT_EQ(s.egzaminas(), 0);
    
    // Check if homework grades list is empty
    EXPECT_EQ(s.namuDarbai().size(), 0);
    
    // Test if the name and surname are correctly set
    EXPECT_EQ(s.vardas(), "Jonas");
    EXPECT_EQ(s.pavarde(), "Jonaitis");
}

// Test adding homework grades
TEST(AddHomeworkGrades, AddsGradeCorrectly) {
    Studentas student;
    student.addNamuDarbas(8);
    EXPECT_EQ(student.namuDarbai().size(), 1);
    EXPECT_EQ(student.namuDarbai()[0], 8);
}

// Test setting homework grades
TEST(SetHomeworkGrades, SetsGradesCorrectly) {
    Studentas student;
    vector<int> newGrades = {10, 8, 9};
    student.setNamuDarbai(newGrades);
    EXPECT_EQ(student.namuDarbai().size(), 3);
    EXPECT_EQ(student.namuDarbai()[1], 8);
}

// Test clearing homework grades
TEST(ClearHomeworkGrades, ClearsGradesCorrectly) {
    Studentas student;
    student.addNamuDarbas(8);
    student.clearNamuDarbai();
    EXPECT_TRUE(student.namuDarbai().empty());
}

// Test copy constructor
TEST(CopyConstructor, CopiesCorrectly) {
    Studentas original("Jonas", "Jonaitis");
    original.setEgzaminas(8);
    original.addNamuDarbas(7);
    original.addNamuDarbas(9);
    
    // Create a copy using the copy constructor
    Studentas copy = original;
    
    // Check if the copy has the same data
    EXPECT_EQ(copy.vardas(), original.vardas());
    EXPECT_EQ(copy.pavarde(), original.pavarde());
    EXPECT_EQ(copy.egzaminas(), original.egzaminas());
    EXPECT_EQ(copy.namuDarbai(), original.namuDarbai());
}

// Test copy assignment operator
TEST(CopyAssignmentOperator, AssignsCorrectly) {
    Studentas original("Jonas", "Jonaitis");
    original.setEgzaminas(10);
    original.addNamuDarbas(8);
    original.addNamuDarbas(9);
    
    // Create an empty student object
    Studentas assigned;
    
    // Use the copy assignment operator
    assigned = original;
    
    // Check if the assigned object has the same data
    EXPECT_EQ(assigned.vardas(), original.vardas());
    EXPECT_EQ(assigned.pavarde(), original.pavarde());
    EXPECT_EQ(assigned.egzaminas(), original.egzaminas());
    EXPECT_EQ(assigned.namuDarbai(), original.namuDarbai());
}

// Main function to run all the tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
