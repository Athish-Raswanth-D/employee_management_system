#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

#define MAX_EMPLOYEES 1000

struct Employee {
    string name;
    long int id;
    string designation;
    int experience;
    int age;
};

int empCount = 0;
Employee emp[MAX_EMPLOYEES];

void saveToFile() {
    ofstream file("employees.txt");
    for (int i = 0; i < empCount; ++i) {
        file << emp[i].name << "," << emp[i].id << "," << emp[i].designation << ","
             << emp[i].experience << "," << emp[i].age << "\n";
    }
    file.close();
}

void loadFromFile() {
    ifstream file("employees.txt");
    string line;
    empCount = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, emp[empCount].name, ',');
        ss >> emp[empCount].id;
        ss.ignore();
        getline(ss, emp[empCount].designation, ',');
        ss >> emp[empCount].experience;
        ss.ignore();
        ss >> emp[empCount].age;
        empCount++;
    }
    file.close();
}

void build() {
    cout << "Build employee table for TechNova Pvt Ltd\n";
    cout << "Enter number of employees to register: ";
    cin >> empCount;
    if (empCount > MAX_EMPLOYEES) empCount = MAX_EMPLOYEES;

    for (int i = 0; i < empCount; ++i) {
        cout << "Name: "; cin >> emp[i].name;
        cout << "Employee ID: "; cin >> emp[i].id;
        cout << "Designation: "; cin >> emp[i].designation;
        cout << "Experience (years): "; cin >> emp[i].experience;
        cout << "Age: "; cin >> emp[i].age;
    }

    saveToFile();
}

void insert() {
    if (empCount < MAX_EMPLOYEES) {
        cout << "Name: "; cin >> emp[empCount].name;
        cout << "Employee ID: "; cin >> emp[empCount].id;
        cout << "Designation: "; cin >> emp[empCount].designation;
        cout << "Experience (years): "; cin >> emp[empCount].experience;
        cout << "Age: "; cin >> emp[empCount].age;
        empCount++;
        saveToFile();
    } else {
        cout << "Employee limit reached (Max: " << MAX_EMPLOYEES << ")\n";
    }
}

void deleteEmployee() {
    long int id;
    cout << "Enter Employee ID to delete: ";
    cin >> id;

    for (int i = 0; i < empCount; ++i) {
        if (emp[i].id == id) {
            for (int j = i; j < empCount - 1; ++j) {
                emp[j] = emp[j + 1];
            }
            empCount--;
            saveToFile();
            cout << "Record deleted successfully.\n";
            return;
        }
    }
    cout << "Employee ID not found.\n";
}

void search() {
    long int id;
    cout << "Enter Employee ID to search: ";
    cin >> id;

    for (int i = 0; i < empCount; ++i) {
        if (emp[i].id == id) {
            cout << "Name: " << emp[i].name << "\n";
            cout << "ID: " << emp[i].id << "\n";
            cout << "Designation: " << emp[i].designation << "\n";
            cout << "Experience: " << emp[i].experience << " years\n";
            cout << "Age: " << emp[i].age << " years\n";
            return;
        }
    }
    cout << "Employee not found.\n";
}

void menu() {
    int choice;
    loadFromFile();
    do {
        cout << "\n--- Employee Management System ---\n";
        cout << "1. Build Employee Table\n";
        cout << "2. Insert New Employee\n";
        cout << "3. Delete Employee\n";
        cout << "4. Search Employee\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: build(); break;
            case 2: insert(); break;
            case 3: deleteEmployee(); break;
            case 4: search(); break;
            case 5: cout << "Exiting system. Goodbye!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);
}

int main() {
    menu();
    return 0;
}
