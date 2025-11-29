#include <stdio.h>
#include <string.h>

struct Employee {
    int EmployeeID;
    char Name[30];
    char Designation[30];
    double Salary;
};

void inputRecords (struct Employee* employees, int n);
void displayRecords(struct Employee* employees, int n);
void findHighestSalary(struct Employee* employees, int n);
void searchEmployee(struct Employee* employees, int n);

int main () {
    int n;
    printf("Enter the number of employees of the company: ");
    scanf("%d", &n);
    struct Employee employees[n];
    inputRecords (employees, n);
    displayRecords(employees, n);
    findHighestSalary(employees, n);
    searchEmployee(employees, n);
    return 0;
}
void inputRecords (struct Employee* employees, int n) {
    printf("...Inputting Employee's Details...\n");
    for (int i=0; i<n; i++) {
        printf("Enter Employee number %d's ID: ", i+1);
        scanf("%d", &employees[i].EmployeeID);
        printf("Enter Employee number %d's Name: ", i+1);
        scanf("%s", employees[i].Name);
        printf("Enter Employee number %d's Designation: ", i+1);
        scanf("%s", employees[i].Designation);
        printf("Enter Employee number %d's Salary: ", i+1);
        scanf("%lf", &employees[i].Salary);
    }
    return;
}

void displayRecords(struct Employee* employees, int n) {
    printf("...Displaying Employee's Records...\n");
    printf("S.no\tEmployee ID\tEmployee Name\tDesignation\tSalary\n");
    for (int i=0; i<n; i++) {
        printf("%d  \t%d\t\t%s\t\t%s\t\t%lf\n", i+1, employees[i].EmployeeID, employees[i].Name, employees[i].Designation, employees[i].Salary);
    }
    return;
}

void findHighestSalary(struct Employee* employees, int n) {
    int highest = 0; //storing the index of the first employee
    for (int i=1; i<n; i++) {
        if (employees[i].Salary>employees[highest].Salary) highest = i; //storing the index of the employee with the highest salary
    }
    printf("The employee with the highest salary has:\nEmployee ID: %d\nName: %s\nDesignation: %s\nSalary: %lf\n", employees[highest].EmployeeID, employees[highest].Name, employees[highest].Designation, employees[highest].Salary);
    return;
}


void searchEmployee(struct Employee* employees, int n) {
    int choice;
    printf("Do you wish to search employees by ID or by Name?\nTo search by ID enter 1\nTo search by Name enter 2\n");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            int ID;
            int found=0;
            printf("Enter the employee ID: ");
            scanf("%d", &ID);
            printf("...Searching...\n");
            for (int i=0; i<n; i++) {
                if (employees[i].EmployeeID == ID) {
                    printf("Employee Name: %s\nEmployee ID: %d\nDesignation: %s\nSalary: %lf\n", employees[i].Name, employees[i].EmployeeID, employees[i].Designation, employees[i].Salary);
                    found = 1;
                    break;
                }
            }
            if (found == 0) printf("No employee found with this ID\n");
            break;
        case 2:
            char name[30];
            int found = 0;
            printf("Enter the employee name: ");
            scanf("%s", name);
            printf("...Searching...\n");
            for (int i=0; i<n; i++) {
                if (strcmp(employees[i].Name, name)==0) {
                    printf("Employee ID: %d\nEmployee Name: %s\nDesignation: %s\nSalary: %lf\n", employees[i].EmployeeID, employees[i].Name, employees[i].Designation, employees[i].Salary);
                    found = 1;
                    break;
                }
            }
            if (found == 0) printf("No employee found with this name\n");
            break;
        default:
            printf("Enter a valid choice\n");
    }
}