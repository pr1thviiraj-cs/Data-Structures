#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DAYS 30
#define MAX_TANKS 10
#define OVERFLOW_THRESHOLD 95.0
#define SHORTAGE_THRESHOLD 20.0


typedef struct {
    int day;
    float waterLevel;
    char status[20];
} DailyRecord;


typedef struct {
    char tankName[50];
    float capacity;
    DailyRecord records[MAX_DAYS];
    int recordCount;
} WaterTank;

// Function declarations
void displayMenu();
void addDailyLevel(WaterTank *tank);
void displayDailyLevels(WaterTank *tank);
void detectOverflowCondition(WaterTank *tank);
void showAverageUsage(WaterTank *tank);
void initializeTank(WaterTank *tank);
void checkStatus(float level, char *status);

int main() {
    WaterTank tanks[MAX_TANKS];
    int tankCount = 0;
    int choice, tankIndex;
    
    printf("\n========================================\n");
    printf("  SMART WATER TANK MONITORING SYSTEM\n");
    printf("========================================\n");
    
    while(1) {
        displayMenu();
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                
                if(tankCount < MAX_TANKS) {
                    printf("\nEnter tank name (e.g., Hostel-A, House-1): ");
                    scanf("%s", tanks[tankCount].tankName);
                    printf("Enter tank capacity (in liters): ");
                    scanf("%f", &tanks[tankCount].capacity);
                    initializeTank(&tanks[tankCount]);
                    tankCount++;
                    printf("\n✓ Tank created successfully!\n");
                } else {
                    printf("\n✗ Maximum tank limit reached!\n");
                }
                break;
                
            case 2:
                
                if(tankCount == 0) {
                    printf("\n✗ No tanks available. Please create a tank first.\n");
                    break;
                }
                printf("\nAvailable Tanks:\n");
                for(int i = 0; i < tankCount; i++) {
                    printf("%d. %s (Capacity: %.2f L)\n", i+1, tanks[i].tankName, tanks[i].capacity);
                }
                printf("Select tank number: ");
                scanf("%d", &tankIndex);
                
                if(tankIndex > 0 && tankIndex <= tankCount) {
                    addDailyLevel(&tanks[tankIndex-1]);
                } else {
                    printf("\n✗ Invalid tank selection!\n");
                }
                break;
                
            case 3:
                
                if(tankCount == 0) {
                    printf("\n✗ No tanks available.\n");
                    break;
                }
                printf("\nSelect tank number (1-%d): ", tankCount);
                scanf("%d", &tankIndex);
                
                if(tankIndex > 0 && tankIndex <= tankCount) {
                    displayDailyLevels(&tanks[tankIndex-1]);
                } else {
                    printf("\n✗ Invalid tank selection!\n");
                }
                break;
                
            case 4:
                
                if(tankCount == 0) {
                    printf("\n✗ No tanks available.\n");
                    break;
                }
                printf("\nSelect tank number (1-%d): ", tankCount);
                scanf("%d", &tankIndex);
                
                if(tankIndex > 0 && tankIndex <= tankCount) {
                    detectOverflowCondition(&tanks[tankIndex-1]);
                } else {
                    printf("\n✗ Invalid tank selection!\n");
                }
                break;
                
            case 5:
                
                if(tankCount == 0) {
                    printf("\n✗ No tanks available.\n");
                    break;
                }
                printf("\nSelect tank number (1-%d): ", tankCount);
                scanf("%d", &tankIndex);
                
                if(tankIndex > 0 && tankIndex <= tankCount) {
                    showAverageUsage(&tanks[tankIndex-1]);
                } else {
                    printf("\n✗ Invalid tank selection!\n");
                }
                break;
                
            case 6:
                printf("\n✓ Exiting system. Thank you!\n");
                exit(0);
                
            default:
                printf("\n✗ Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}

// Function menu
void displayMenu() {
    printf("\n========================================\n");
    printf("              MAIN MENU\n");
    printf("========================================\n");
    printf("1. Create New Water Tank\n");
    printf("2. Add Daily Water Level\n");
    printf("3. Display Daily Water Levels\n");
    printf("4. Detect Overflow/Shortage Condition\n");
    printf("5. Show Average Water Usage\n");
    printf("6. Exit\n");
    printf("========================================\n");
}

// Initialization of tank
void initializeTank(WaterTank *tank) {
    tank->recordCount = 0;
    for(int i = 0; i < MAX_DAYS; i++) {
        tank->records[i].day = 0;
        tank->records[i].waterLevel = 0.0;
        strcpy(tank->records[i].status, "");
    }
}

// Function Water Level Stats
void checkStatus(float level, char *status) {
    if(level >= OVERFLOW_THRESHOLD) {
        strcpy(status, "OVERFLOW RISK!");
    } else if(level <= SHORTAGE_THRESHOLD) {
        strcpy(status, "SHORTAGE!");
    } else {
        strcpy(status, "NORMAL");
    }
}



void addDailyLevel(WaterTank *tank) {
    if(tank->recordCount >= MAX_DAYS) {
        printf("\n✗ Maximum record limit reached for this tank!\n");
        return;
    }
    
    int day;
    float currentLevel, percentage;
    
    printf("\n--- Add Daily Water Level ---\n");
    printf("Tank: %s (Capacity: %.2f L)\n", tank->tankName, tank->capacity);
    printf("Enter day number: ");
    scanf("%d", &day);
    printf("Enter current water level (in liters): ");
    scanf("%f", &currentLevel);
    
    
    percentage = (currentLevel / tank->capacity) * 100.0;
    
   
    tank->records[tank->recordCount].day = day;
    tank->records[tank->recordCount].waterLevel = percentage;
    checkStatus(percentage, tank->records[tank->recordCount].status);
    
    printf("\n✓ Record added successfully!\n");
    printf("   Day: %d | Level: %.2f%% | Status: %s\n", 
           day, percentage, tank->records[tank->recordCount].status);
    
    tank->recordCount++;
}


void displayDailyLevels(WaterTank *tank) {
    if(tank->recordCount == 0) {
        printf("\n✗ No records available for tank: %s\n", tank->tankName);
        return;
    }
    
    printf("\n========================================\n");
    printf("  DAILY WATER LEVELS - %s\n", tank->tankName);
    printf("========================================\n");
    printf("Day\t| Water Level\t| Status\n");
    printf("--------|---------------|------------------\n");
    
    for(int i = 0; i < tank->recordCount; i++) {
        printf("%d\t| %.2f%%\t\t| %s\n", 
               tank->records[i].day,
               tank->records[i].waterLevel,
               tank->records[i].status);
    }
    printf("========================================\n");
}


void detectOverflowCondition(WaterTank *tank) {
    if(tank->recordCount == 0) {
        printf("\n✗ No records available for analysis.\n");
        return;
    }
    
    int overflowCount = 0;
    int shortageCount = 0;
    
    printf("\n========================================\n");
    printf("  OVERFLOW/SHORTAGE DETECTION - %s\n", tank->tankName);
    printf("========================================\n");
    
    for(int i = 0; i < tank->recordCount; i++) {
        if(tank->records[i].waterLevel >= OVERFLOW_THRESHOLD) {
            printf("⚠ Day %d: OVERFLOW RISK - %.2f%%\n", 
                   tank->records[i].day, tank->records[i].waterLevel);
            overflowCount++;
        }
        if(tank->records[i].waterLevel <= SHORTAGE_THRESHOLD) {
            printf("⚠ Day %d: SHORTAGE - %.2f%%\n", 
                   tank->records[i].day, tank->records[i].waterLevel);
            shortageCount++;
        }
    }
    
    if(overflowCount == 0 && shortageCount == 0) {
        printf("✓ No overflow or shortage detected!\n");
    } else {
        printf("\nSummary:\n");
        printf("- Overflow incidents: %d\n", overflowCount);
        printf("- Shortage incidents: %d\n", shortageCount);
    }
    printf("========================================\n");
}


void showAverageUsage(WaterTank *tank) {
    if(tank->recordCount == 0) {
        printf("\n✗ No records available for calculation.\n");
        return;
    }
    
    float totalLevel = 0.0;
    float maxLevel = tank->records[0].waterLevel;
    float minLevel = tank->records[0].waterLevel;
    
    
    for(int i = 0; i < tank->recordCount; i++) {
        totalLevel += tank->records[i].waterLevel;
        
        if(tank->records[i].waterLevel > maxLevel) {
            maxLevel = tank->records[i].waterLevel;
        }
        if(tank->records[i].waterLevel < minLevel) {
            minLevel = tank->records[i].waterLevel;
        }
    }
    
    float average = totalLevel / tank->recordCount;
    
    printf("\n========================================\n");
    printf("  WATER USAGE STATISTICS - %s\n", tank->tankName);
    printf("========================================\n");
    printf("Tank Capacity: %.2f liters\n", tank->capacity);
    printf("Total Records: %d days\n", tank->recordCount);
    printf("----------------------------------------\n");
    printf("Average Water Level: %.2f%%\n", average);
    printf("Maximum Water Level: %.2f%%\n", maxLevel);
    printf("Minimum Water Level: %.2f%%\n", minLevel);
    printf("----------------------------------------\n");
    
   
    if(average >= 70.0) {
        printf("💧 Status: Good water availability\n");
    } else if(average >= 40.0) {
        printf("⚠ Status: Moderate - Monitor regularly\n");
    } else {
        printf("⚠ Status: Low - Consider refilling\n");
    }
    printf("========================================\n");
}
