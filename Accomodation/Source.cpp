#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[30];
    char password[30];
    char max_Password_Length[30];
} login;

typedef struct acc {
    // Payload

    // Reference to the next node
    struct acc* next; // Pointer to reference the next node in the linked list
    int id;
    char owner_Name[30];
    char owner_Surname[30];
    int year_Built;
    float monthly_Rental;
    char owner_Email[30];

    int type;
    int num_Bedrooms;
    int pets_Allowed;
    int duration;
    int choice_Type_acc;
    int choice_Average_Stay;

} acc;

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

int main()
{

    acc* headPtr = NULL;
    int choice;
    int position;

    loadFile(&headPtr);

    printf(".1 to Add accommodation\n");
    printf(".2 to add an accommodation at the end of the list\n");
    printf(".3 to add an accommodation at a certain position in the list\n");
    printf(".4 to delete an accommodation at the start of the list\n");
    printf(".5 to delete an accommodation at the end of the list\n");
    printf(".6 to delete an accommodation from a certain position in the list\n");
    printf(".7 to display all accommodations\n");
    printf(".8 to display accommodation by ID\n");
    printf(".9 to delete accommodation by ID\n");
    printf(".-1 to exit\n");
    scanf("%d", &choice);

    while (choice != -1)
    {
        if (choice == 1)
        {
            add_acc(&headPtr);
        }
        else if (choice == 2)
        {
            addNodeAtEnd(&headPtr);
        }
        else if (choice == 3)
        {
            printf("Please enter the position in the list where you wish to add the accommodation\n");
            printf("Note the first node is position 1\n");
            scanf("%d", &position);

            if (position < 1 || position > listLength(headPtr) + 1)
            {
                printf("Invalid position selected\n");
            }
            else if (position == 1)
            {
                add_acc(&headPtr);
            }
            else if (position == listLength(headPtr) + 1)
            {
                addNodeAtEnd(&headPtr);
            }
            else
            {
                addNodeAtPos(&headPtr, position);
            }
        }
        else if (choice == 4)
        {
            deleteAtTheStart(&headPtr);
        }
        else if (choice == 5)
        {
            if (listLength(headPtr) == 1)
                deleteAtTheStart(&headPtr);
            else
                deleteAtTheEnd(&headPtr);
        }
        else if (choice == 6)
        {
            printf("Please enter the position in the list where you wish to delete the node\n");
            printf("Note the first node is position 1\n");
            scanf("%d", &position);

            if (position < 1 || position > listLength(headPtr))
            {
                printf("Invalid position selected\n");
            }
            else if (position == 1)
            {
                deleteAtTheStart(&headPtr);
            }
            else if (position == listLength(headPtr))
            {
                deleteAtTheEnd(&headPtr);
            }
            else
            {
                deleteAtPost(&headPtr, position);
            }
        }
        else if (choice == 7)
        {
            display_accs(headPtr);
        }
        else if (choice == 8)
        {
            int id;
            printf("Please enter the ID of the accommodation you want to search for: ");
            scanf("%d", &id);
            searchById(headPtr, id);
        }
        else if (choice == 9)
        {
            int id;
            printf("Please enter the ID of the accommodation you want to DELETE: ");
            scanf("%d", &id);
            deleteById(&headPtr, id);
        }

        printf(".1 to Add accommodation\n");
        printf(".2 to add an accommodation at the end of the list\n");
        printf(".3 to add an accommodation at a certain position in the list\n");
        printf(".4 to delete an accommodation at the start of the list\n");
        printf(".5 to delete an accommodation at the end of the list\n");
        printf(".6 to delete an accommodation from a certain position in the list\n");
        printf(".7 to display all accommodations\n");
        printf(".8 to display accommodation by ID\n");
        printf(".9 to delete accommodation by ID\n");
        printf(".-1 to exit and save all accommodation details\n");
        scanf("%d", &choice);
    }

    saveFile(headPtr);

    return 0;
}

// method that saves to a file all the information about an accommodation
void saveFile(acc* root)
{
    FILE* file = fopen("acc.txt", "w");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(1);
    }
    for (acc* node = root; node != NULL; node = node->next)
    {
        fprintf(file, "%d,%s,%s,%d,%f,%s,%d,%d,%d,%d,%d,%d\n",
            node->id, node->owner_Name, node->owner_Surname, node->year_Built,
            node->monthly_Rental, node->owner_Email, node->type, node->num_Bedrooms,
            node->pets_Allowed, node->duration, node->choice_Type_acc, node->choice_Average_Stay);
    }
    fclose(file);
}

// method that loads previous information inputted by the user to the database
void loadFile(acc** top)
{
    FILE* fp;
    char line[256];

    fp = fopen("acc.txt", "r");
    if (fp == NULL)
    {
        perror("file error");
        return;
    }

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        acc* new_node = (acc*)malloc(sizeof(acc));
        if (new_node == NULL)
        {

        }

        // setting variables to 0 before calling them
        new_node->id = 0;
        new_node->year_Built = 0;
        new_node->type = 0;
        new_node->num_Bedrooms = 0;
        new_node->num_Bedrooms = 0;
        new_node->pets_Allowed = 0;
        new_node->duration = 0;
        new_node->choice_Type_acc = 0;
        new_node->choice_Average_Stay = 0;

            scanf(line, "%d,%[^,],%[^,],%d,%f,%[^,],%d,%d,%d,%d,%d,%d\n",
            &new_node->id, new_node->owner_Name, new_node->owner_Surname, &new_node->year_Built,
            &new_node->monthly_Rental, new_node->owner_Email, &new_node->type, &new_node->num_Bedrooms,
            &new_node->num_Bedrooms, &new_node->pets_Allowed, &new_node->duration, &new_node->choice_Type_acc, &new_node->choice_Average_Stay);

        if (*top == NULL)
        {
            new_node->next = NULL;
        }
        else
        {
            new_node->next = *top;
        }

        *top = new_node;
    }

    fclose(fp);
}

// method to add an accommodation
void add_acc(acc** top)
{
    acc* newNode = (acc*)malloc(sizeof(acc));

    if (newNode == NULL)
    {
        printf("Error: Memory allocation failed.\n");
        return;
    }

    printf("Property Identification Number: ");
    scanf("%d", &newNode->id);
    printf("\n");
    printf("Owner First Name: ");
    scanf("%s", newNode->owner_Name);
    printf("\n");
    printf("Owner Last Name: ");
    scanf("%s", newNode->owner_Surname);
    printf("\n");
    printf("Year built: ");
    scanf("%d", &newNode->year_Built);
    printf("\n");
    printf("Monthly rental: ");
    scanf("%f", &newNode->monthly_Rental);
    printf("\n");
    printf("Owner email address: ");
    scanf("%s", newNode->owner_Email);
    printf("\n");
    printf("Accommodation type:\n0 single room accommodation,\n1 apartment accommodation,\n2 bungalow accommodation,\n3 two-story accommodation\n");
    scanf("%d", &newNode->type);
    printf("\n");
    printf("How many bedrooms are available:\n0 One\n1 Two\n2 Three\n3 Four\n4 More than 4\n");
    scanf("%d", &newNode->num_Bedrooms);
    printf("\n");
    printf("Are pets allowed? (1 for Yes, 0 for No):\n");
    scanf("%d", &newNode->pets_Allowed);
    printf("\n");
    printf("On average how long you plan to stay: \n0 for 1 day\n1 for less than 3 days\n2 for less than 7 days\n3 for more than 7 days\n");
    scanf("%d", &newNode->duration);
    printf("\n");
    printf("Type of accommodation (1 for hotel, 2 for motel, 3 for cabin): ");
    scanf("%d", &newNode->choice_Type_acc);
    printf("\n");
    printf("Type of average stay (1 for single, 2 for couple, 3 for family, 4 for business): ");
    scanf("%d", &newNode->choice_Average_Stay);
    printf("\n");

    if (*top == NULL)
    {
        newNode->next = NULL;
    }
    else
    {
        newNode->next = *top;
    }

    *top = newNode;
}

// add accommodation at the end of the list
void addNodeAtEnd(acc** top)
{
    acc* newNode;
    acc* temp;

    newNode = (acc*)malloc(sizeof(acc) * 1);

    temp = *top;

    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = newNode;
    newNode->next = NULL;
}

// function to generate a file that contains details of each accommodation entry in the linked list
void printaccReport(acc** top)
{
    FILE* reportFile = fopen("report.txt", "w");
    if (reportFile == NULL)
    {
        perror("Error opening report file");
        return;
    }

    // Print all accommodation details
    fprintf(reportFile, "Accommodation Details:\n");
    acc* node = *top;
    while (node != NULL)
    {
        fprintf(reportFile, "ID: %d\n", node->id);
        fprintf(reportFile, "Owner Name: %s %s\n", node->owner_Name, node->owner_Surname);
        fprintf(reportFile, "Year Built: %d\n", node->year_Built);
        fprintf(reportFile, "Monthly Rental: %.2f\n", node->monthly_Rental);
        fprintf(reportFile, "Owner Email: %s\n", node->owner_Email);
        fprintf(reportFile, "Type: %d\n", node->type);
        fprintf(reportFile, "Number of Bedrooms: %d\n", node->num_Bedrooms);
        fprintf(reportFile, "Duration: %d\n", node->duration);
        fprintf(reportFile, "Pets Allowed: %d\n", node->pets_Allowed);
        fprintf(reportFile, "Type of accommodation (1 for hotel, 2 for motel, 3 for cabin): %d\n", node->choice_Type_acc);
        fprintf(reportFile, "Type of average stay (1 for single, 2 for couple, 3 for family, 4 for business): %d\n", node->choice_Average_Stay);
        fprintf(reportFile, "\n");

        node = node->next;
    }

    // Calculate accommodation statistics
    int totalaccs = 0;
    float totalRentalSum = 0.0;
    int totalBedrooms = 0;

    node = *top;
    while (node != NULL)
    {
        totalaccs++;
        totalRentalSum += node->monthly_Rental;
        totalBedrooms += node->num_Bedrooms;

        node = node->next;
    }

    float averageRental = totalRentalSum / totalaccs;

    // Print accommodation statistics
    fprintf(reportFile, "Accommodation Statistics:\n");
    fprintf(reportFile, "Total accommodations: %d\n", totalaccs);
    fprintf(reportFile, "Total Rental Sum: %.2f\n", totalRentalSum);
    fprintf(reportFile, "Average Rental: %.2f\n", averageRental);
    fprintf(reportFile, "Total Bedrooms: %d\n", totalBedrooms);

    fclose(reportFile);
}

// method to display all the accommodations added by the user
void display_accs(acc* top)
{
    acc* temp;

    temp = top;

    while (temp != NULL)
    {
        printf("Property Identification Number:%d \n", temp->id);
        printf("Owner First Name: %s\n", temp->owner_Name);
        printf("Owner Last Name: %s\n", temp->owner_Surname);
        printf("Year built: %d\n", temp->year_Built);
        printf("Monthly rental: %.2f\n", temp->monthly_Rental);
        printf("Owner email address: %s\n", temp->owner_Email);
        printf("Accommodation type: %d\n", temp->type);
        printf("Number of Bedrooms: %d\n", temp->num_Bedrooms);
        printf("Duration: %d\n", temp->duration);
        printf("Pets Allowed: %d\n", temp->pets_Allowed);
        printf("Type of accommodation (1 for hotel, 2 for motel, 3 for cabin): %d\n", temp->choice_Type_acc);
        printf("Type of average stay (1 for single, 2 for couple, 3 for family, 4 for business): %d\n", temp->choice_Average_Stay);
        printf("\n");

        temp = temp->next;
    }
}

// method to delete a specific accommodation
void deleteById(acc** top, int id)
{
    if (*top == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    acc* node = *top;
    acc* previous = NULL;

    while (node != NULL && node->id != id)
    {
        previous = node;
        node = node->next;
    }

    if (node == NULL)
    {
        printf("Accommodation not found.\n");
        return;
    }

    if (previous == NULL)
    {
        *top = node->next;
    }
    else
    {
        previous->next = node->next;
    }

    free(node);
    printf("Accommodation with ID %d deleted.\n", id);
}

// method to search the accommodation by ID
void searchById(acc* top, int id)
{
    if (top == NULL)
    {
        printf("The list is empty.\n");
        return;
    }

    acc* node = top;
    while (node != NULL)
    {
        if (node->id == id)
        {
            printf("Accommodation found:\n");
            printf("Owner First Name: %s\n", node->owner_Name);
            printf("Owner Last Name: %s\n", node->owner_Surname);
            printf("Year Built: %d\n", node->year_Built);
            printf("Monthly Rental: %.2f\n", node->monthly_Rental);
            printf("Owner Email: %s\n", node->owner_Email);
            printf("Accommodation Type: %d\n", node->type);
            printf("Number of Bedrooms: %d\n", node->num_Bedrooms);
            printf("Duration: %d\n", node->duration);
            printf("Pets Allowed: %d\n", node->pets_Allowed);
            printf("Type of accommodation (1 for hotel, 2 for motel, 3 for cabin): %d\n", node->choice_Type_acc);
            printf("Type of average stay (1 for single, 2 for couple, 3 for family, 4 for business): %d\n", node->choice_Average_Stay);
            return;
        }
        node = node->next;
    }
    printf("Accommodation with ID %d not found.\n", id);
}

// method to display the number of accommodations
int listLength(acc* top)
{
    acc* temp;
    int count = 0;

    temp = top;

    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }

    return count;
}

// method to delete the first accommodation in the database
void deleteAtTheStart(acc** top)
{
    if (*top == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    acc* temp;

    temp = *top;
    *top = temp->next;

    free(temp);
}

// method to delete the last accommodation added to the database
void deleteAtTheEnd(acc** top)
{
    if (*top == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    acc* temp = *top;
    acc* prevtemp = NULL;

    while (temp->next != NULL)
    {
        prevtemp = temp;
        temp = temp->next;
    }

    if (prevtemp == NULL)
    {
        *top = NULL;
    }
    else
    {
        prevtemp->next = NULL;
    }

    free(temp);
}

// adding an accommodation at a specific position
void addNodeAtPos(acc** top, int pos)
{
    if (pos < 1 || pos > listLength(*top) + 1)
    {
        printf("Invalid position selected\n");
        return;
    }

    acc* newNode;
    acc* temp;
    int i = 1;

    newNode = (acc*)malloc(sizeof(acc) * 1);

    temp = *top;

    while (i <= pos - 2)
    {
        temp = temp->next;
        i++;
    }

    newNode->next = temp->next;
    temp->next = newNode;
}

// method to delete a specific accommodation at a specific position in the list
void deleteAtPost(acc** top, int pos)
{
    if (pos < 1 || pos > listLength(*top))
    {
        printf("Invalid position selected\n");
        return;
    }

    acc* temp = *top;
    acc* prevtemp = NULL;
    int i = 1;

    while (i <= pos - 1)
    {
        prevtemp = temp;
        temp = temp->next;
        i++;
    }

    if (prevtemp == NULL)
    {
        *top = temp->next;
    }
    else
    {
        prevtemp->next = temp->next;
    }

    free(temp);
}
