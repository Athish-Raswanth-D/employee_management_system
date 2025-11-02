import java.io.*;
import java.util.*;

class EmployeeManagement {
    
    static Scanner sc = new Scanner(System.in);

    static void addEmployee() {
        try {
            FileWriter fw = new FileWriter("employees.txt", true);

            System.out.print("Enter Name: ");
            String name = sc.next();
            System.out.print("Enter ID: ");
            long id = sc.nextLong();
            System.out.print("Enter Designation: ");
            String designation = sc.next();
            System.out.print("Enter Experience: ");
            int exp = sc.nextInt();
            System.out.print("Enter Age: ");
            int age = sc.nextInt();

            fw.write(name + "," + id + "," + designation + "," + exp + "," + age + "\n");
            fw.close();
            System.out.println("Employee added successfully!");

        } catch (Exception e) {
            System.out.println("Error writing to file");
        }
    }

    static void displayEmployees() {
        try {
            File file = new File("employees.txt");
            Scanner fileReader = new Scanner(file);

            System.out.println("\n--- Employee List ---");
            while (fileReader.hasNextLine()) {
                String line = fileReader.nextLine();
                System.out.println(line);
            }
            fileReader.close();
        } catch (Exception e) {
            System.out.println("No employees found.");
        }
    }

    static void searchEmployee() {
        System.out.print("Enter Employee ID to search: ");
        long searchId = sc.nextLong();
        boolean found = false;

        try {
            File file = new File("employees.txt");
            Scanner fileReader = new Scanner(file);

            while (fileReader.hasNextLine()) {
                String line = fileReader.nextLine();
                String[] data = line.split(",");

                long id = Long.parseLong(data[1]);

                if (id == searchId) {
                    System.out.println("Employee Found!");
                    System.out.println("Name: " + data[0]);
                    System.out.println("ID: " + data[1]);
                    System.out.println("Designation: " + data[2]);
                    System.out.println("Experience: " + data[3]);
                    System.out.println("Age: " + data[4]);
                    found = true;
                    break;
                }
            }
            fileReader.close();

            if (!found) {
                System.out.println("Employee not found.");
            }

        } catch (Exception e) {
            System.out.println("File not found.");
        }
    }

    public static void main(String[] args) {
        
        while (true) {
            System.out.println("\n--- Employee Management ---");
            System.out.println("1. Add Employee");
            System.out.println("2. Display Employees");
            System.out.println("3. Search Employee");
            System.out.println("4. Exit");
            System.out.print("Enter choice: ");
            
            int choice = sc.nextInt();

            switch (choice) {
                case 1: addEmployee(); break;
                case 2: displayEmployees(); break;
                case 3: searchEmployee(); break;
                case 4: 
                    System.out.println("Bye");
                    return;
                default: 
                    System.out.println("Invalid choice!");
            }
        }
    }
}
