#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Student {
    int rollNo;
    char name[50];
    float marks;
};

/* -------- Function Declarations -------- */

void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

/* -------- Add Student -------- */

void addStudent() {
    Student s;
    ofstream file("students.dat", ios::binary | ios::app);

    cout << "\nEnter Roll Number: ";
    cin >> s.rollNo;

    cout << "Enter Name: ";
    cin.ignore();
    cin.getline(s.name, 50);

    cout << "Enter Marks: ";
    cin >> s.marks;

    file.write(reinterpret_cast<char*>(&s), sizeof(s));
    file.close();

    cout << "\nStudent Added Successfully!\n";
}

/* -------- Display All -------- */

void displayStudents() {
    Student s;
    ifstream file("students.dat", ios::binary);

    cout << "\n----- Student Records -----\n";

    while (file.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        cout << "\nRoll No: " << s.rollNo;
        cout << "\nName: " << s.name;
        cout << "\nMarks: " << s.marks;
        cout << "\n--------------------------";
    }

    file.close();
}

/* -------- Search Student -------- */

void searchStudent() {
    Student s;
    int roll;
    bool found = false;

    cout << "\nEnter Roll Number to Search: ";
    cin >> roll;

    ifstream file("students.dat", ios::binary);

    while (file.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.rollNo == roll) {
            cout << "\nStudent Found!";
            cout << "\nName: " << s.name;
            cout << "\nMarks: " << s.marks << endl;
            found = true;
            break;
        }
    }

    if (!found)
        cout << "\nStudent Not Found!\n";

    file.close();
}

/* -------- Update Student -------- */

void updateStudent() {
    Student s;
    int roll;
    bool found = false;

    cout << "\nEnter Roll Number to Update: ";
    cin >> roll;

    fstream file("students.dat", ios::binary | ios::in | ios::out);

    while (file.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.rollNo == roll) {
            cout << "\nEnter New Name: ";
            cin.ignore();
            cin.getline(s.name, 50);

            cout << "Enter New Marks: ";
            cin >> s.marks;

            file.seekp(file.tellg() - streampos(sizeof(s)));
            file.write(reinterpret_cast<char*>(&s), sizeof(s));

            cout << "\nRecord Updated Successfully!\n";
            found = true;
            break;
        }
    }

    if (!found)
        cout << "\nStudent Not Found!\n";

    file.close();
}

/* -------- Delete Student -------- */

void deleteStudent() {
    Student s;
    int roll;
    bool found = false;

    cout << "\nEnter Roll Number to Delete: ";
    cin >> roll;

    ifstream inFile("students.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary);

    while (inFile.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.rollNo == roll) {
            found = true;
            continue;  // Skip writing this record
        }
        outFile.write(reinterpret_cast<char*>(&s), sizeof(s));
    }

    inFile.close();
    outFile.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        cout << "\nStudent Deleted Successfully!\n";
    else
        cout << "\nStudent Not Found!\n";
}

/* -------- Main Function -------- */

int main() {
    int choice;

    do {
        cout << "\n\n===== STUDENT MANAGEMENT SYSTEM =====";
        cout << "\n1. Add Student";
        cout << "\n2. Display All Students";
        cout << "\n3. Search Student";
        cout << "\n4. Update Student";
        cout << "\n5. Delete Student";
        cout << "\n6. Exit";
        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addStudent();
            break;
        case 2:
            displayStudents();
            break;
        case 3:
            searchStudent();
            break;
        case 4:
            updateStudent();
            break;
        case 5:
            deleteStudent();
            break;
        case 6:
            cout << "\nThank You!\n";
            break;
        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 6);

    return 0;
}
