#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>//used this header instead of error.h ... because that header file was not being compiled on windows

#define INITIAL_CAPACITY 4 // starting capacity for lines array

#define MAX_LINE 1024 // maximum input line length

// Structure to hold the buffer of lines
typedef struct {
    char **lines; // dynamic array of pointers to strings
    size_t size; // current number of lines stored
    size_t capacity;  // current allocated capacity
} LinesBuffer;

// ensureCapacity dynamically grows the pointer array when needed.
// Instead of allocating a huge fixed array, we expand only when required.
void ensureCapacity(LinesBuffer *buf, size_t minCapacity) {

    if (buf->capacity >= minCapacity) return;

    size_t newCapacity = buf->capacity * 2;
    if (newCapacity < minCapacity) newCapacity = minCapacity;

    // realloc adjusts the memory block size without losing existing data.
    char **newLines = realloc(buf->lines, newCapacity * sizeof(char *));
    if (!newLines) {
        perror("realloc failed");
        exit(EXIT_FAILURE);
    }
    buf->lines = newLines;
    buf->capacity = newCapacity;
}

// Insert a new line at given index
void insertLine(LinesBuffer *buf, size_t index, const char *text) {

    if (index > buf->size) {
        fprintf(stderr, "Invalid index\n");
        return;
    }
    ensureCapacity(buf, buf->size + 1);
    // Shift pointers to make room
    memmove(&buf->lines[index + 1], &buf->lines[index], (buf->size - index) * sizeof(char *));
    // Allocate exact memory for new string
    buf->lines[index] = malloc(strlen(text) + 1);

    if (!buf->lines[index]) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    strcpy(buf->lines[index], text);
    buf->size++;
}

// Delete a line at given index
void deleteLine(LinesBuffer *buf, size_t index) {

    if (index >= buf->size) {
        fprintf(stderr, "Invalid index\n");
        return;
    }

    free(buf->lines[index]); // free memory of that line
    // Shift remaining pointers left
    memmove(&buf->lines[index], &buf->lines[index + 1], (buf->size - index - 1) * sizeof(char *));
    buf->size--;
}

// Print all lines in buffer
void printAllLines(const LinesBuffer *buf) {

    if (buf->size == 0) {
        printf("Buffer is empty.\n");
        return;
    }

    for (size_t i = 0; i < buf->size; i++) {
        printf("%zu: %s\n", i, buf->lines[i]);
    }
}

// Free all allocated memory
void freeAll(LinesBuffer *buf) {

    for (size_t i = 0; i < buf->size; i++) {
        free(buf->lines[i]);
    }

    free(buf->lines);
    buf->lines = NULL;
    buf->size = 0;
    buf->capacity = 0;
}

// Shrink capacity to exactly match size
// reduces capacity to match the actual number of lines, ensuring no unused memory remains allocated.
void shrinkToFit(LinesBuffer *buf) {
    if (buf->capacity == buf->size) return;

    char **newLines = realloc(buf->lines, buf->size * sizeof(char *));

    if (!newLines && buf->size > 0) {
        perror("realloc failed");
        exit(EXIT_FAILURE);
    }
    buf->lines = newLines;
    buf->capacity = buf->size;
}

// Save buffer contents to a file
void saveToFile(const LinesBuffer *buf, const char *filename) {
    FILE *fptr = fopen(filename, "w");

    if (!fptr) {
        perror("Cannot open file for writing");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < buf->size; i++) {
        fprintf(fptr, "%s\n", buf->lines[i]);
    }
    fclose(fptr);
}

// Load buffer contents from a file
void loadFromFile(LinesBuffer *buf, const char *filename) {
    FILE *fptr = fopen(filename, "r");

    if (!fptr) {
        perror("Cannot open file for reading");
        exit(EXIT_FAILURE);
    }
    // Free old lines
    for (size_t i = 0; i < buf->size; i++) free(buf->lines[i]);
    buf->size = 0;
    char line[MAX_LINE];
    // Read each line and insert into buffer
    while (fgets(line, sizeof(line), fptr)) {
        line[strcspn(line, "\n")] = '\0'; // remove newline
        insertLine(buf, buf->size, line);
    }
    fclose(fptr);
}

// Main program with menu-driven interface
int main() {
    LinesBuffer buf;
    buf.lines = malloc(INITIAL_CAPACITY * sizeof(char *));

    if (!buf.lines) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    buf.size = 0;
    buf.capacity = INITIAL_CAPACITY;

    int choice;
    char text[MAX_LINE], filename[256];
    size_t index;

    do {
        printf("\n--- Minimal Text Editor Menu ---\n");
        printf("1. Insert Line\n");
        printf("2. Delete Line\n");
        printf("3. Print All Lines\n");
        printf("4. Shrink To Fit\n");
        printf("5. Save To File\n");
        printf("6. Load From File\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) break;
        getchar(); // consume newline

        switch (choice) {
            case 1: // Insert line
                printf("Enter index (0..%zu): ", buf.size);
                scanf("%zu", &index); getchar();
                printf("Enter text: ");
                fgets(text, sizeof(text), stdin);
                text[strcspn(text, "\n")] = '\0';
                insertLine(&buf, index, text);
                break;

            case 2: // Delete line
                if (buf.size == 0) { printf("Buffer empty.\n"); break; }
                printf("Enter index to delete (0..%zu): ", buf.size - 1);
                scanf("%zu", &index); getchar();
                deleteLine(&buf, index);
                break;

            case 3: // Print all lines
                printAllLines(&buf);
                break;

            case 4: // Shrink capacity
                shrinkToFit(&buf);
                printf("Shrunk capacity to %zu\n", buf.capacity);
                break;

            case 5: // Save to file
                printf("Enter filename: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                saveToFile(&buf, filename);
                break;

            case 6: // Load from file
                printf("Enter filename: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                loadFromFile(&buf, filename);
                break;

            case 7: // Exit program
                freeAll(&buf);
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice.\n");
        }
        
    } while (choice != 7);

    return 0;
}