#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for storing login information
typedef struct {
    char username[7];
    int password[7];
    char max_Password_Length[30];
} login;

// Define a structure for storing accommodation details
typedef struct acc {
    // Payload

    // Reference to the next node
    struct acc* next; // Pointer to reference the next node in the linked list

    // Accommodation properties
    int id;
    char owner_Name[30];
    char owner_Surname[30];
    int year_Built;
    float monthly_Rental;
    char owner_Email[30];
    int type;                // Type of accommodation (1 for hotel, 2 for motel, 3 for cabin)
    int num_Bedrooms;        // Number of bedrooms
    int pets_Allowed;        // 1 if pets are allowed, 0 if not allowed
    int duration;            // Duration of stay
    int choice_Type_acc;     // User choice for type of accommodation
    int choice_Average_Stay; // User choice for average stay type
} acc;

// Function prototypes
void add_acc(acc** top);
void addNodeAtEnd(acc** top);
void addNodeAtPos(acc** top, int pos);
int listLength(acc* top);
void deleteAtTheStart(acc** top);
void deleteAtTheEnd(acc** top);
void deleteAtPost(acc** top, int pos);
void display_accs(acc* top);
void searchById(acc* top, int id);
void deleteById(acc** top, int id);
void saveFile(acc* root);
void loadFile(acc** root);
void printaccReport(acc** top);

int main() {
    acc* headPtr = NULL;
    int choice;
    int position;

    // Load existing data from file
    loadFile(&headPtr);

    printf("1. Add accommodation\n");
    printf("2. Add accommodation at the end of the list\n");
    printf("3. Add accommodation at a certain position in the list\n");
    printf("4. Delete accommodation at the start of the list\n");
    printf("5. Delete accommodation at the end of the list\n");
    printf("6. Delete accommodation from a certain position in the list\n");
    printf("7. Display all accommodations\n");
    printf("8. Display accommodation by ID\n");
    printf("9. Delete accommodation by ID\n");
    printf("-1. Exit\n");
    scanf("%d", &choice);

    while (choice != -1) {
        if (choice == 1) {
            add_acc(&headPtr);
        }
        else if (choice == 2) {
            if (headPtr == NULL) {
                add_acc(&headPtr);
            }
            else {
                addNodeAtEnd(&headPtr);
            }
        }
        else if (choice == 3) {
            printf("Please enter the position in the list where you wish to add the accommodation\n");
            printf("Note the first node is position 1\n");
            scanf("%d", &position);
            if (headPtr == NULL) {
                add_acc(&headPtr);
            }
            else if (position < 1 || position > listLength(headPtr) + 1) {
                printf("Invalid position selected\n");
            }
            else if (position == 1) {
                add_acc(&headPtr);
            }
            else if (position == listLength(headPtr) + 1) {
                addNodeAtEnd(&headPtr);
            }
            else {
                addNodeAtPos(&headPtr, position);
            }
        }
        else if (choice == 4) {
            if (headPtr == NULL)
                printf("Not possible to delete from an empty list\n");
            else
                deleteAtTheStart(&headPtr);
        }
        else if (choice == 5) {
            if (headPtr == NULL)
                printf("Not possible to delete from an empty list\n");
            else if (listLength(headPtr) == 1)
                deleteAtTheStart(&headPtr);
            else
                deleteAtTheEnd(&headPtr);
        }
        else if (choice == 6) {
            printf("Please enter the position in the list where you wish to delete the node\n");
            printf("Note the first node is position 1\n");
            scanf("%d", &position);
            if (headPtr == NULL) {
                printf("Not possible to delete from an empty list\n");
            }
            else if (position < 1 || position > listLength(headPtr)) {
                printf("Invalid position selected\n");
            }
            else if (position == 1) {
                deleteAtTheStart(&headPtr);
            }
            else if (position == listLength(headPtr)) {
                deleteAtTheEnd(&headPtr);
            }
            else {
                deleteAtPost(&headPtr, position);
            }
        }
        else if (choice == 7) {
            display_accs(headPtr);
        }
        else if (choice == 8) {
            int id;
            printf("Please enter the ID of the accommodation you want to search for: ");
            scanf("%d", &id);
            searchById(headPtr, id);
        }
        else if (choice == 9) {
            int id;
            printf("Please enter the ID of the accommodation you want to DELETE: ");
            scanf("%d", &id);
            deleteById(&headPtr, id);
        }
        printf("1. Add accommodation\n");
        printf("2. Add accommodation at the end of the list\n");
        printf("3. Add accommodation at a certain position in the list\n");
        printf("4. Delete accommodation at the start of the list\n");
        printf("5. Delete accommodation at the end of the list\n");
        printf("6. Delete accommodation from a certain position in the list\n");
        printf("7. Display all accommodations\n");
        printf("8. Display accommodation by ID\n");
        printf("9. Delete accommodation by ID\n");
        printf("-1. Exit and save all accommodation details\n");
        scanf("%d", &choice);
    }

    // Save all accommodations to a file before exiting
    saveFile(headPtr);
    return 0;
}

// Function to save accommodation details to a file
void saveFile(acc* root) {
    FILE* file = fopen("acc.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }
    for (acc* node = root; node != NULL; node = node->next) {
        fprintf(file, "%d,%s,%s,%d,%.2f,%s,%d,%d,%d,%d,%d,%d,%d,%d\n",
            node->id, node->owner_Name, node->owner_Surname, node->year_Built,
            node->monthly_Rental, node->owner_Email, node->type, node->num_Bedrooms,
            node->pets_Allowed, node->duration, node->choice_Type_acc,
            node->choice_Average_Stay);
    }
    fclose(file);
}

// Function to load accommodation data from a file
void loadFile(acc** top) {
    FILE* fp;
    char line[256];

    fp = fopen("acc.txt", "r");
    if (fp == NULL) {
        perror("File error");
        return;
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        acc* new_node = (acc*)malloc(sizeof(acc));
        if (new_node == NULL) {
            perror("Memory allocation error");
            return;
        }

        // Initialize variables to 0 before calling sscanf
        memset(new_node, 0, sizeof(acc));

        sscanf(line, "%d,%[^,],%[^,],%d,%f,%[^,],%d,%d,%d,%d,%d,%d,%d,%d",
            &new_node->id, new_node->owner_Name, new_node->owner_Surname, &new_node->year_Built,
            &new_node->monthly_Rental, new_node->owner_Email, &new_node->type, &new_node->num_Bedrooms,
            &new_node->pets_Allowed, &new_node->duration, &new_node->choice_Type_acc,
            &new_node->choice_Average_Stay);

        if (*top == NULL) {
            new_node->next = NULL;
        }
        else {
            new_node->next = *top;
        }

        *top = new_node;
    }

    fclose(fp);
}

// Function to add accommodation at the beginning of the list
void add_acc(acc** top) {
    acc* newNode = (acc*)malloc(sizeof(acc));
    if (newNode == NULL) {
        printf("Error: Memory allocation failed.\n");
        return;
    }

    // Input accommodation details
    printf("Property Identification Number: ");
    scanf("%d", &newNode->id);
    printf("Owner First Name: ");
    scanf("%s", newNode->owner_Name);
    printf("Owner Last Name: ");
    scanf("%s", newNode->owner_Surname);
    printf("Year built: ");
    scanf("%d", &newNode->year_Built);
    printf("Monthly rental: ");
    scanf("%f", &newNode->monthly_Rental);
    printf("Owner email address: ");
    scanf("%s", newNode->owner_Email);
    printf("Accommodation type (1 for hotel, 2 for motel, 3 for cabin): ");
    scanf("%d", &newNode->type);
    printf("Number of bedrooms: ");
    scanf("%d", &newNode->num_Bedrooms);
    printf("Are pets allowed? (1 for Yes, 0 for No): ");
    scanf("%d", &newNode->pets_Allowed);
    printf("Average duration of stay (in days): ");
    scanf("%d", &newNode->duration);
    printf("Choice for accommodation type: ");
    scanf("%d", &newNode->choice_Type_acc);
    printf("Choice for average stay type: ");
    scanf("%d", &newNode->choice_Average_Stay);

    if (*top == NULL) {
        newNode->next = NULL;
    }
    else {
        newNode->next = *top;
    }

    *top = newNode;
}

// Function to add accommodation at the end of the list
void addNodeAtEnd(acc** top) {
    acc* newNode = (acc*)malloc(sizeof(acc));
    if (newNode == NULL) {
        printf("Error: Memory allocation failed.\n");
        return;
    }

    // Input accommodation details
    printf("Property Identification Number: ");
    scanf("%d", &newNode->id);
    printf("Owner First Name: ");
    scanf("%s", newNode->owner_Name);
    printf("Owner Last Name: ");
    scanf("%s", newNode->owner_Surname);
    printf("Year built: ");
    scanf("%d", &newNode->year_Built);
    printf("Monthly rental: ");
    scanf("%f", &newNode->monthly_Rental);
    printf("Owner email address: ");
    scanf("%s", newNode->owner_Email);
    printf("Accommodation type (1 for hotel, 2 for motel, 3 for cabin): ");
    scanf("%d", &newNode->type);
    printf("Number of bedrooms: ");
    scanf("%d", &newNode->num_Bedrooms);
    printf("Are pets allowed? (1 for Yes, 0 for No): ");
    scanf("%d", &newNode->pets_Allowed);
    printf("Average duration of stay (in days): ");
    scanf("%d", &newNode->duration);
    printf("Choice for accommodation type: ");
    scanf("%d", &newNode->choice_Type_acc);
    printf("Choice for average stay type: ");
    scanf("%d", &newNode->choice_Average_Stay);

    newNode->next = NULL;

    if (*top == NULL) {
        *top = newNode;
    }
    else {
        acc* temp = *top;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Function to add accommodation at a specific position in the list
void addNodeAtPos(acc** top, int pos) {
    if (pos < 1) {
        printf("Invalid position selected\n");
        return;
    }

    acc* newNode = (acc*)malloc(sizeof(acc));
    if (newNode == NULL) {
        printf("Error: Memory allocation failed.\n");
        return;
    }

    // Input accommodation details
    printf("Property Identification Number: ");
    scanf("%d", &newNode->id);
    printf("Owner First Name: ");
    scanf("%s", newNode->owner_Name);
    printf("Owner Last Name: ");
    scanf("%s", newNode->owner_Surname);
    printf("Year built: ");
    scanf("%d", &newNode->year_Built);
    printf("Monthly rental: ");
    scanf("%f", &newNode->monthly_Rental);
    printf("Owner email address: ");
    scanf("%s", newNode->owner_Email);
    printf("Accommodation type (1 for hotel, 2 for motel, 3 for cabin): ");
    scanf("%d", &newNode->type);
    printf("Number of bedrooms: ");
    scanf("%d", &newNode->num_Bedrooms);
    printf("Are pets allowed? (1 for Yes, 0 for No): ");
    scanf("%d", &newNode->pets_Allowed);
    printf("Average duration of stay (in days): ");
    scanf("%d", &newNode->duration);
    printf("Choice for accommodation type: ");
    scanf("%d", &newNode->choice_Type_acc);
    printf("Choice for average stay type: ");
    scanf("%d", &newNode->choice_Average_Stay);

    if (*top == NULL || pos == 1) {
        newNode->next = *top;
        *top = newNode;
    }
    else {
        acc* temp = *top;
        int currentPos = 1;
        while (temp != NULL && currentPos < pos - 1) {
            temp = temp->next;
            currentPos++;
        }
        if (temp == NULL) {
            printf("Invalid position selected\n");
            free(newNode);
        }
        else {
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }
}

// Function to get the length of the accommodation list
int listLength(acc* top) {
    int count = 0;
    acc* temp = top;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

// Function to delete the first accommodation in the list
void deleteAtTheStart(acc** top) {
    if (*top == NULL) {
        printf("List is empty.\n");
        return;
    }
    acc* temp = *top;
    *top = temp->next;
    free(temp);
}

// Function to delete the last accommodation in the list
void deleteAtTheEnd(acc** top) {
    if (*top == NULL) {
        printf("List is empty.\n");
        return;
    }
    if ((*top)->next == NULL) {
        free(*top);
        *top = NULL;
        return;
    }
    acc* temp = *top;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    free(temp->next);
    temp->next = NULL;
}

// Function to delete accommodation at a specific position in the list
void deleteAtPost(acc** top, int pos) {
    if (*top == NULL) {
        printf("List is empty.\n");
        return;
    }
    if (pos < 1 || pos > listLength(*top)) {
        printf("Invalid position selected\n");
        return;
    }
    if (pos == 1) {
        deleteAtTheStart(top);
        return;
    }
    acc* temp = *top;
    int currentPos = 1;
    while (temp != NULL && currentPos < pos - 1) {
        temp = temp->next;
        currentPos++;
    }
    if (temp == NULL || temp->next == NULL) {
        printf("Invalid position selected\n");
        return;
    }
    acc* toDelete = temp->next;
    temp->next = toDelete->next;
    free(toDelete);
}

// Function to display all accommodations in the list
void display_accs(acc* top) {
    acc* temp = top;
    while (temp != NULL) {
        printf("Property Identification Number: %d\n", temp->id);
        printf("Owner First Name: %s\n", temp->owner_Name);
        printf("Owner Last Name: %s\n", temp->owner_Surname);
        printf("Year built: %d\n", temp->year_Built);
        printf("Monthly rental: %.2f\n", temp->monthly_Rental);
        printf("Owner email address: %s\n", temp->owner_Email);
        printf("Accommodation type: %d\n", temp->type);
        printf("Number of bedrooms: %d\n", temp->num_Bedrooms);
        printf("Pets Allowed: %d\n", temp->pets_Allowed);
        printf("Duration: %d\n", temp->duration);
        printf("Choice for accommodation type: %d\n", temp->choice_Type_acc);
        printf("Choice for average stay type: %d\n", temp->choice_Average_Stay);
        printf("\n");
        temp = temp->next;
    }
}

// Function to search for accommodation by ID
void searchById(acc* top, int id) {
    acc* temp = top;
    while (temp != NULL) {
        if (temp->id == id) {
            printf("Accommodation found:\n");
            printf("Property Identification Number: %d\n", temp->id);
            printf("Owner First Name: %s\n", temp->owner_Name);
            printf("Owner Last Name: %s\n", temp->owner_Surname);
            printf("Year built: %d\n", temp->year_Built);
            printf("Monthly rental: %.2f\n", temp->monthly_Rental);
            printf("Owner email address: %s\n", temp->owner_Email);
            printf("Accommodation type: %d\n", temp->type);
            printf("Number of bedrooms: %d\n", temp->num_Bedrooms);
            printf("Pets Allowed: %d\n", temp->pets_Allowed);
            printf("Duration: %d\n", temp->duration);
            printf("Choice for accommodation type: %d\n", temp->choice_Type_acc);
            printf("Choice for average stay type: %d\n", temp->choice_Average_Stay);
            return;
        }
        temp = temp->next;
    }
    printf("Accommodation with ID %d not found.\n", id);
}

// Function to delete accommodation by ID
void deleteById(acc** top, int id) {
    if (*top == NULL) {
        printf("List is empty.\n");
        return;
    }
    acc* temp = *top;
    acc* prev = NULL;

    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Accommodation not found.\n");
        return;
    }

    if (prev == NULL) {
        *top = temp->next;
    }
    else {
        prev->next = temp->next;
    }

    free(temp);
}

// Function to print accommodation report
void printaccReport(acc** top) {
    FILE* report = fopen("acc_report.txt", "w");
    if (report == NULL) {
        perror("Error opening report file");
        return;
    }

    acc* temp = *top;
    while (temp != NULL) {
        fprintf(report, "Property Identification Number: %d\n", temp->id);
        fprintf(report, "Owner First Name: %s\n", temp->owner_Name);
        fprintf(report, "Owner Last Name: %s\n", temp->owner_Surname);
        fprintf(report, "Year built: %d\n", temp->year_Built);
        fprintf(report, "Monthly rental: %.2f\n", temp->monthly_Rental);
        fprintf(report, "Owner email address: %s\n", temp->owner_Email);
        fprintf(report, "Accommodation type: %d\n", temp->type);
        fprintf(report, "Number of bedrooms: %d\n", temp->num_Bedrooms);
        fprintf(report, "Pets Allowed: %d\n", temp->pets_Allowed);
        fprintf(report, "Duration: %d\n", temp->duration);
        fprintf(report, "Choice for accommodation type: %d\n", temp->choice_Type_acc);
        fprintf(report, "Choice for average stay type: %d\n", temp->choice_Average_Stay);
        fprintf(report, "\n");
        temp = temp->next;
    }

    fclose(report);
}