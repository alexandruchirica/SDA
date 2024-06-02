#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: No hardcoding \/
// TODO: switch to english naming \/
// TODO: documentation according to doxygen standard 

#define MAX_NAME_LENGTH 50

/**
 * @brief Structure representing a student.
 */
struct Student {
    char name[MAX_NAME_LENGTH]; /**< Name of the student. */
    char surname[MAX_NAME_LENGTH]; /**< Surname of the student. */
    int age; /**< Age of the student. */
    float average; /**< Average grade of the student. */
    char specialization[MAX_NAME_LENGTH]; /**< Specialization of the student. */
    int year_of_study; /**< Year of study of the student. */
    struct Student *next; /**< Pointer to the next student in the list. */
};
/**
 * @brief Reads information about a student from the user.
 * 
 * @return A pointer to the newly created student.
 */
// Reading function
struct Student* read_element() {
    struct Student *new_student = (struct Student*)malloc(sizeof(struct Student));
    if (new_student == NULL) {
        printf("Error allocating memory\n");
        exit(1);
    }

    printf("Enter student's name: ");
    scanf("%s", new_student->name);
    printf("Enter student's surname: ");
    scanf("%s", new_student->surname);
    printf("Enter student's age: ");
    scanf("%d", &new_student->age);
    printf("Enter student's average grade: ");
    scanf("%f", &new_student->average);
    printf("Enter student's specialization: ");
    scanf("%s", new_student->specialization);
    printf("Enter student's year of study: ");
    scanf("%d", &new_student->year_of_study);

    new_student->next = NULL;
    return new_student;
}

/**
 * @brief Displays the information of all students in the list.
 * 
 * @param head Pointer to the first student in the list.
 */
void display_list(struct Student *head) {
    struct Student *current = head;
    while (current != NULL) {
        printf("\nName: %s,\nSurname: %s,\nAge: %d,\nAverage: %.2f,\nSpecialization: %s,\nYear of study: %d \n\n",
               current->name, current->surname, current->age, current->average, current->specialization, current->year_of_study);
        current = current->next;
    }
}

// Memory release function
void release_memory(struct Student *head) {
    struct Student *current = head;
    struct Student *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

// Inserting a new element at the beginning
struct Student* insert_beginning(struct Student *head) {
    struct Student *new_student = read_element();
    new_student->next = head;
    return new_student;
}

// Inserting a new element at the end
void insert_end(struct Student *head) {
    struct Student *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = read_element();
}

// Searching for an element
int search_element(struct Student *head, char surname_search[]) {
    struct Student *current = head;
    int position = 0;
    while (current != NULL) {
        if (strcmp(current->surname, surname_search) == 0) {
            return position;
        }
        current = current->next;
        position++;
    }
    return -1; // Element not found
}

// Deleting an element from a specified position
struct Student* delete_element(struct Student *head, int position) {
    if (head == NULL) {
        return NULL;
    }

    if (position == 0) {
        struct Student *temp = head->next;
        free(head);
        return temp;
    }

    struct Student *current = head;
    int i;
    for (i = 0; current != NULL && i < position - 1; i++) {
        current = current->next;
    }

    if (current == NULL || current->next == NULL) {
        return head;
    }

    struct Student *next = current->next->next;
    free(current->next);
    current->next = next;
    return head;
}

// Clearing the list
void clear_list(struct Student **head) {
    release_memory(*head);
    *head = NULL;
}

int main() {
    struct Student *head = NULL;
    int option;
    char surname_search[MAX_NAME_LENGTH];
    int position;

    do {
        printf("\nMenu:\n");
        printf("1. Read element\n");
        printf("2. Display list\n");
        printf("3. Search element by surname\n");
        printf("4. Release list memory\n");
        printf("5. Insert new element at beginning\n");
        printf("6. Insert new element at end\n");
        printf("7. Delete element from position\n");
        printf("8. Clear list\n");
        printf("0. Exit program\n");

        printf("Choose an option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                if (head == NULL) {
                    head = read_element();
                } else {
                    insert_end(head);
                }
                break;
            case 2:
                display_list(head);
                break;
            case 3:
                printf("Enter surname to search: ");
                scanf("%s", surname_search);
                position = search_element(head, surname_search);
                if (position != -1) {
                    printf("Element with surname %s is at position %d\n", surname_search, position);
                } else {
                    printf("Element with surname %s was not found\n", surname_search);
                }
                break;
            case 4:
                release_memory(head);
                head = NULL;
                printf("Memory of the list has been released\n");
                break;
            case 5:
                head = insert_beginning(head);
                printf("Element was successfully inserted at the beginning of the list\n");
                break;
            case 6:
                insert_end(head);
                printf("Element was successfully inserted at the end of the list\n");
                break;
            case 7:
                printf("Enter position to delete: ");
                scanf("%d", &position);
                head = delete_element(head, position);
                printf("Element from position %d was successfully deleted\n", position);
                break;
            case 8:
                clear_list(&head);
                printf("List has been successfully cleared\n");
                break;
            case 0:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid option\n");
        }
    } while (option != 0);

    return 0;
}
