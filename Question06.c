#include <stdio.h>
#include <stdlib.h>
struct StudentRecord {
    int StudentID;
    char FullName[100];
    char Batch[15];
    char MembershipType[5];
    char RegistrationDate[11];
    char InterestIn[5];
};

#define MAX_RECORDS 1000

void loadDatabase(const char* student);

int main () {
    FILE *student = fopen("members.dat", "r");
    if (student==NULL) {
        printf("Error to open the file\n");
        return 1;
    }
    loadDatabase(student);
    fclose(student);
}

void loadDatabase(const char* student) {
    struct StudentRecord students[MAX_RECORDS];
    int count=0;
    while ((count < MAX_RECORDS) && (fscanf(student, "%d %s %s %s %s %s", &students[count].StudentID, students[count].FullName, students[count].Batch, students[count].MembershipType, students[count].RegistrationDate, students[count].InterestIn)) != EOF) {
        count++;
    }
}