#include <stdio.h>
#include <string.h>

struct book {
    int ID;
    int popularity_score;
    int last_used;
};

void ADD(struct book* b, int ID, int* popularity_score, int* number_of_books, int capacity, int timer);
int ACCESS(struct book* b, int ID, int number_of_books, int timer);

int main () {
    printf("\n...Welcome to Libarary Shelf System...\n");
    int capacity, Q;
    printf("Enter the capacity and the number of operations: ");
    scanf("%d %d", &capacity, &Q);
    struct book b[capacity];
    int number_of_books = 0;
    int timer=1;
    while (Q>0) {
        char Operation[7];
        scanf("%s", Operation);
        if (strcmp(Operation, "ADD")==0) {
            int ID, popularity_score;
            scanf("%d %d", &ID, &popularity_score);
            ADD(b, ID, &popularity_score, &number_of_books, capacity, timer);
        }
        else if (strcmp(Operation, "ACCESS")==0) {
            int ID;
            scanf("%d", &ID);
            int score = ACCESS(b, ID, number_of_books, timer);
            printf("%d\n", score);
        }
        timer++;
        Q--;
    }
    return 0;   
}

void ADD(struct book* b, int ID, int* popularity_score, int* number_of_books, int capacity, int timer) {
    for (int i=0; i<*number_of_books; i++) {
        if (ID==b[i].ID) {
            b[i].popularity_score += (*popularity_score);
            b[i].last_used=timer;
            return;
        }
    }
    if ((*number_of_books)<capacity) {
        int index = (*number_of_books);
        b[index].ID = ID;
        b[index].popularity_score = (*popularity_score);
        b[index].last_used = timer;
        (*number_of_books)++;
        return;
    }
    else {
        int least_recently_accessed=0;
        for (int i=1; i < (*number_of_books); i++) {
            if (b[i].last_used < b[least_recently_accessed].last_used) {
                least_recently_accessed=i;
            }
        }
        b[least_recently_accessed].ID=ID;
        b[least_recently_accessed].popularity_score=(*popularity_score);
        b[least_recently_accessed].last_used=timer;
    }
}

int ACCESS(struct book* b, int ID, int number_of_books, int timer) {
    for (int i = 0; i < number_of_books; i++) {
        if (b[i].ID == ID) {
            b[i].last_used = timer;
            return (b[i].popularity_score);
        }
    }
    return -1;
}
