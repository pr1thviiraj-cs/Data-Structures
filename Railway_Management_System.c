#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 5     
#define COLS 4     
#define FILENAME "reservation.txt" 
int seats[ROWS][COLS]; 

                            

void loadData();
void saveData();
void displaySeats();
void bookSeat();
void cancelSeat();

int main() {
    int choice;
    loadData(); 

    do {
        printf("\n===== RAILWAY RESERVATION SYSTEM =====\n");
        printf("1. Display Seat Layout\n"); 
        printf("2. Book a Seat\n");
        printf("3. Cancel a Seat\n"); 
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displaySeats();
                break;
            case 2:
                bookSeat();
                break;
            case 3:
                cancelSeat();
                break;
            case 4:
                saveData();
                printf("Exiting... Data saved successfully.\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 4);

    return 0;
}



void loadData() {
    FILE *fp = fopen(FILENAME, "r"); 
    if (fp == NULL) {
        printf("No previous data found. Initializing empty seat layout.\n");
        memset(seats, 0, sizeof(seats)); 
        return;
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            fscanf(fp, "%d", &seats[i][j]);
        }
    }

    fclose(fp);
}

                                

void saveData() {
    FILE *fp = fopen(FILENAME, "w");
    if (fp == NULL) {
        printf("Error saving data!\n");
        return;
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            fprintf(fp, "%d ", seats[i][j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}

                                

void displaySeats() {
    printf("\nSeat Layout (1 = Booked, 0 = Available):\n\n");
    
    
    printf("   "); 
    for (int j = 0; j < COLS; j++) {
        printf(" C%d", j + 1);
    }
    printf("\n");
    

    for (int i = 0; i < ROWS; i++) {
        printf("R%d ", i + 1); 
        for (int j = 0; j < COLS; j++) {
            printf(" %d ", seats[i][j]); 
        }
        printf("\n"); 
    } 
}

                                

void bookSeat() {
    int row, col;
    displaySeats();
    printf("\nEnter row (1-%d): ", ROWS);
    scanf("%d", &row);
    printf("Enter column (1-%d): ", COLS);
    scanf("%d", &col);

    if (row < 1 || row > ROWS || col < 1 || col > COLS) {
        printf("Invalid seat position!\n");
        return;
    }

    if (seats[row - 1][col - 1] == 1) {
        printf("Seat already booked!\n");
    } else {
        seats[row - 1][col - 1] = 1;
        printf("Seat booked successfully!\n");
        saveData(); 
    }
}

                                    

void cancelSeat() {
    int row, col;
    displaySeats();
    printf("\nEnter row (1-%d): ", ROWS);
    scanf("%d", &row);
    printf("Enter column (1-%d): ", COLS);
    scanf("%d", &col);

    if (row < 1 || row > ROWS || col < 1 || col > COLS) {
        printf("Invalid seat position!\n");
        return;
    }

    if (seats[row - 1][col - 1] == 0) {
        printf("Seat is already available (not booked).\n");
    } else {
        seats[row - 1][col - 1] = 0;
        printf("Booking cancelled successfully.\n");
        saveData(); 
    }
} 

 // RAILWAY MANAGEMENT & RESERVATION SYSTEM--(Book/Cancel Seats Using 2D-Arrays)
