#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"header.h"
// #include"main.c"

int Teacher(const char* password) {
    const char* TeacherPass = "coep123";
    if (strcmp(password, TeacherPass) == 0)
        return 1;
    else
    	    return 0;
}

void displayMenu() {
    printf("\n \nMenu:\n");

    printf("1. Display your Timetable\n");
    printf("2. Display class Schedule\n");
    printf("3. Display free slots for the class\n");
    printf("4. Schedule a class\n");
    printf("5. Cancel a lecture\n");
    printf("6. Exit\n");
}

int main() {
    // Read data from CSV file and populate the timetable
    FILE* file = fopen("database.csv", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }
    
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        Class classData;
        sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]", 
               classData.classroom, classData.day, classData.time,
               classData.faculty, classData.subject, classData.class_name);
        insertClass(classData);
    }
    
    fclose(file);

    char username[20];
    char class_name[20];
    char weekday[20];
    char password[20];
    char subject[20];
    char time_slot[20];
    int role = 1;

    printf("Login Page\n");
    printf("==========\n");
    
    if (role == 1) {
	    printf("Username (Name_Surname) : ");
        scanf("%s", username);
        printf("Password: ");
        scanf("%s", password);

        if (Teacher(password)) {
            printf("Teacher login successful. Welcome, %s!\n", username);
            int choice;
            int exitFlag = 0;

            while (!exitFlag) {
                displayMenu();
                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch (choice) {
                    case 1:
                        display_schedule_for_faculty(username);
                        break;
                    case 2:
                        char class_name[20];
                        printf("Enter the class name : ");
                        scanf("%s", class_name);
                        printf("\n");
                        display_schedule_for_class(class_name);
                        break;
                    case 3:
                        printf("Enter the class name : ");
                        scanf("%s", class_name);
                        printf("\n");
                        printf("Enter the day : ");
                        scanf("%s", weekday);
                        printf("\n");
                        display_free_slots_for_class(weekday,class_name);
                        break;
                    case 4:
                        printf("Enter the subject : ");
                        scanf("%s", subject);
                        printf("Enter the class name : ");
                        scanf("%s", class_name);
                        printf("\n");
                        Schedule_new_lecture(username, class_name, subject);
                        printf("Class Scheduled Sucessfully !!! :) \n");
                        break;
                    case 5:
                        printf("Enter the time slot of the lecture you want to cancel in 24-hour format : ");
                        scanf("%s", time_slot);
                        printf("\n");
                        printf("Enter the day : ");
                        scanf("%s", weekday);
                        printf("\n");
                        cancel_lecture(username, time_slot, weekday);
                        break;
                    case 6:
                        printf("Exiting...\n");
                        exitFlag = 1;
                        break;
                    default:
                        printf("Invalid choice. Please try again.\n");
                        break;
                }
            }
        }
        else printf("Invalid teacher credentials. Login failed.\n");
    }
    else printf("Invalid role selection. Login failed.\n");
    return 0;
}
