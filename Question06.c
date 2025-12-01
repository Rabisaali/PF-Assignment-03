#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "members.dat"

typedef struct {
    int studentID;
    char fullName[100];
    char batch[20];             // CS, SE, Cyber Security, AI
    char membershipType[10];    // IEEE / ACM
    char registrationDate[11];  // YYYY-MM-DD
    char dateOfBirth[11];       // YYYY-MM-DD
    char interest[10];          // IEEE / ACM / Both
} Student;

Student *students = NULL;
int count = 0;

/* ---------- File Handling ---------- */
void loadDatabase() {
    FILE *fp = fopen(FILENAME, "rb");
    if (!fp) return;
    Student s;
    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        students = realloc(students, (count + 1) * sizeof(Student));
        students[count++] = s;
    }
    fclose(fp);
}

void saveDatabase() {
    FILE *fp = fopen(FILENAME, "wb");
    if (!fp) { printf("Error saving file.\n"); return; }
    fwrite(students, sizeof(Student), count, fp);
    fclose(fp);
}

/* ---------- Helpers ---------- */
int findStudent(int id) {
    for (int i = 0; i < count; i++)
        if (students[i].studentID == id) return i;
    return -1;
}

void consumeNewline() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

/* ---------- Operations ---------- */
void addStudent() {
    Student s;
    printf("Enter Student ID: ");
    scanf("%d", &s.studentID);
    consumeNewline();
    if (findStudent(s.studentID) != -1) { printf("Duplicate ID!\n"); return; }

    printf("Full Name: "); scanf(" %[^\n]", s.fullName);
    printf("Batch (CS/SE/Cyber Security/AI): "); scanf(" %[^\n]", s.batch);
    printf("Membership Type (IEEE/ACM): "); scanf(" %[^\n]", s.membershipType);
    printf("Registration Date (YYYY-MM-DD): "); scanf("%10s", s.registrationDate);
    printf("Date of Birth (YYYY-MM-DD): "); scanf("%10s", s.dateOfBirth);
    printf("Interest (IEEE/ACM/Both): "); scanf("%9s", s.interest);

    students = realloc(students, (count + 1) * sizeof(Student));
    students[count++] = s;
    saveDatabase();
    printf("Student added!\n");
}

void updateStudent() {
    int id; printf("Enter ID to update: "); scanf("%d", &id);
    consumeNewline();
    int idx = findStudent(id);
    if (idx == -1) { printf("Not found!\n"); return; }

    int choice; printf("Update 1.Batch 2.Membership: "); scanf("%d", &choice);
    consumeNewline();
    if (choice == 1) {
        printf("New Batch: "); scanf(" %[^\n]", students[idx].batch);
    } else if (choice == 2) {
        printf("New Membership: "); scanf(" %[^\n]", students[idx].membershipType);
    } else {
        printf("Invalid choice.\n"); return;
    }
    saveDatabase();
    printf("Updated!\n");
}

void deleteStudent() {
    int id; printf("Enter ID to delete: "); scanf("%d", &id);
    int idx = findStudent(id);
    if (idx == -1) { printf("Not found!\n"); return; }

    for (int i = idx; i < count - 1; i++) students[i] = students[i+1];
    count--;
    students = (count > 0) ? realloc(students, count * sizeof(Student)) : NULL;
    saveDatabase();
    printf("Deleted!\n");
}

void viewAll() {
    if (count == 0) { printf("No registrations.\n"); return; }
    for (int i = 0; i < count; i++) {
        Student s = students[i];
        printf("%d | %s | %s | %s | %s | %s | %s\n",
               s.studentID, s.fullName, s.batch, s.membershipType,
               s.registrationDate, s.dateOfBirth, s.interest);
    }
}

void batchReport() {
    char batch[20];
    printf("Enter batch (CS/SE/Cyber Security/AI): ");
    scanf(" %[^\n]", batch);

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].batch, batch) == 0) {
            printf("%d | %s | %s | %s\n",
                   students[i].studentID,
                   students[i].fullName,
                   students[i].membershipType,
                   students[i].interest);
            found = 1;
        }
    }
    if (!found) printf("No students found in batch %s.\n", batch);
}

/* ---------- Menu ---------- */
int main() {
    loadDatabase();
    int choice;
    do {
        printf("\n1.Add 2.Update 3.Delete 4.ViewAll 5.BatchReport 6.Exit\nChoice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1: addStudent(); break;
            case 2: updateStudent(); break;
            case 3: deleteStudent(); break;
            case 4: viewAll(); break;
            case 5: batchReport(); break;
            case 6: saveDatabase(); break;
            default: printf("Invalid!\n");
        }
    } while(choice != 6);
    free(students);
    return 0;
}