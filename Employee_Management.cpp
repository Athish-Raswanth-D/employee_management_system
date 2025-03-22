#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
using namespace std;

class Department;

class Employee {
protected:
    int id;
    string name;
    string designation;
    double salary;
    Department* dept;

public:
    Employee(int i, string n, string d, double s) : id(i), name(n), designation(d), salary(s), dept(nullptr) {
        cout << "Employee " << name << " registered (Constructor).\n";
    }

    virtual ~Employee() {
        cout << "Employee " << name << " resigned (Destructor).\n";
    }

    int getId() const { return id; }
    string getName() const { return name; }
    double getSalary() const { return salary; }
    void setDept(Department* d) { dept = d; }

    virtual double calculateSalary() const { return salary; }
    virtual void display() const {
        cout << "ID: " << id << ", Name: " << name << ", Designation: " << designation << ", Salary: " << salary << endl;
    }
    virtual string getReportFormat() const { return "CSV"; }
};

class Department {
private:
    string deptName;
    vector<Employee*> employees;

public:
    Department(string name) : deptName(name) {}
    void addEmployee(Employee* emp) { employees.push_back(emp); emp->setDept(this); }
    string getDeptName() const { return deptName; }
};

class Attendance {
private:
    string checkIn;
    string checkOut;
    double hoursWorked;

public:
    Attendance(string in, string out, double hours) : checkIn(in), checkOut(out), hoursWorked(hours) {}
    double getHours() const { return hoursWorked; }
    void display() const {
        cout << "Check-In: " << checkIn << ", Check-Out: " << checkOut << ", Hours: " << hoursWorked << endl;
    }
};

class Payroll {
private:
    double basicPay;
    double deductions;
    double netSalary;

public:
    Payroll(double basic, double ded) : basicPay(basic), deductions(ded) {
        netSalary = basicPay - deductions;
    }
    double getNetSalary() const { return netSalary; }
    void display() const {
        cout << "Basic Pay: " << basicPay << ", Deductions: " << deductions << ", Net Salary: " << netSalary << endl;
    }
};

class Manager : public Employee {
private:
    double bonus;

public:
    Manager(int i, string n, double s, double b) : Employee(i, n, "Manager", s), bonus(b) {}
    double calculateSalary() const override {
        return salary + bonus;
    }
    void display() const override {
        cout << "ID: " << id << ", Name: " << name << ", Designation: " << designation << ", Salary: " << calculateSalary() << " (Manager)\n";
    }
};

class Intern : public Employee {
public:
    Intern(int i, string n, double s) : Employee(i, n, "Intern", s) {}
    double calculateSalary() const override {
        return salary * 0.8;
    }
};

class EmployeeSystem {
private:
    vector<Employee*> employees;
    vector<Attendance*> attendanceRecords;
    vector<Payroll*> payrollRecords;

    void saveToFile() const {
        ofstream file("employees.txt");
        if (file.is_open()) {
            for (const auto* emp : employees) {
                file << emp->getId() << "," << emp->getName() << "," << emp->getSalary() << "\n";
            }
            file.close();
        } else {
            throw runtime_error("Unable to open file for saving!");
        }
    }

public:
    void addEmployee(Employee* emp) {
        employees.push_back(emp);
        saveToFile();
    }

    void recordAttendance(int id, string in, string out, double hours) {
        attendanceRecords.push_back(new Attendance(in, out, hours));
    }

    void processPayroll(int id, double basic, double deductions) {
        payrollRecords.push_back(new Payroll(basic, deductions));
    }

    void displayEmployee(int id, bool isAdmin) const {
        for (const auto* emp : employees) {
            if (emp->getId() == id) {
                emp->display();
                if (isAdmin) cout << "Admin view: Salary details visible.\n";
                return;
            }
        }
        throw runtime_error("Employee not found!");
    }

    void generateReport() const {
        for (const auto* emp : employees) {
            cout << "Report in " << emp->getReportFormat() << " format: ";
            emp->display();
        }
    }

    ~EmployeeSystem() {
        for (auto* emp : employees) delete emp;
        for (auto* att : attendanceRecords) delete att;
        for (auto* pay : payrollRecords) delete pay;
    }
};

class Leave {
public:
    virtual bool approveLeave(int days) {
        if (days > 10) throw runtime_error("Leave exceeds limit!");
        return true;
    }
};

class AutoLeave : public Leave {
public:
    bool approveLeave(int days) override {
        return days <= 5;
    }
};

int main() {
    EmployeeSystem system;
    Department itDept("IT");

    try {
        Employee* emp1 = new Manager(1, "Alice", 70000, 10000);
        Employee* emp2 = new Intern(2, "Bob", 20000);
        system.addEmployee(emp1);
        system.addEmployee(emp2);
        itDept.addEmployee(emp1);

        system.recordAttendance(1, "09:00", "17:00", 8);
        Leave manualLeave;
        AutoLeave autoLeave;
        cout << "Manual Leave Approval (8 days): " << (manualLeave.approveLeave(8) ? "Approved" : "Denied") << endl;
        cout << "Auto Leave Approval (3 days): " << (autoLeave.approveLeave(3) ? "Approved" : "Denied") << endl;

        system.processPayroll(1, 70000, 5000);

        system.displayEmployee(1, true);
        system.generateReport();

        manualLeave.approveLeave(15);
    } catch (const runtime_error& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}