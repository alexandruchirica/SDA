#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * @brief Initializes the array with random numbers.
 *
 * @param arr Pointer to the array.
 * @param length Length of the array.
 */
void initialize_array(int *arr, int length) {
    srand(time(NULL));
    for (int i = 0; i < length; i++) {
        arr[i] = rand() % 1000; // Generate random numbers between 0 and 999
    }
}

/**
 * @brief Displays the array.
 *
 * @param arr Pointer to the array.
 * @param length Length of the array.
 */
void display_array(int *arr, int length) {
    printf("Array: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/**
 * @brief Frees the memory occupied by the array.
 *
 * @param arr Pointer to the array.
 */
void free_memory(int *arr) {
    free(arr);
}

/**
 * @brief Sorts the array using Selection Sort.
 *
 * @param arr Pointer to the array.
 * @param length Length of the array.
 */
void selection_sort(int *arr, int length) {
    clock_t start = clock();
    
    for (int i = 0; i < length - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < length; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        // Swap
        int temp = arr[i];
        arr[i] = arr[min_index];
        arr[min_index] = temp;
    }

    clock_t end = clock();
    double execution_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Selection Sort executed in %.6f seconds.\n", execution_time);
}

/**
 * @brief Helper function for Quick Sort.
 *
 * @param arr Pointer to the array.
 * @param low Starting index.
 * @param high Ending index.
 */
void quick_sort(int *arr, int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;

        int pi = i + 1;
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

/**
 * @brief Sorts the array using Quick Sort and measures the execution time.
 *
 * @param arr Pointer to the array.
 * @param length Length of the array.
 */
void quick_sort_wrapper(int *arr, int length) {
    clock_t start = clock();
    quick_sort(arr, 0, length - 1);
    clock_t end = clock();
    double execution_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Quick Sort executed in %.6f seconds.\n", execution_time);
}

/**
 * @brief Enumeration for menu options.
 */
typedef enum {
    INITIALIZE_ARRAY = 1,
    DISPLAY_ARRAY,
    FREE_MEMORY,
    SORT_ARRAY_SIMPLE,
    SORT_ARRAY_ADVANCED,
    EXIT_PROGRAM
} MenuOptions;

/**
 * @brief Prints the menu options.
 */
void print_menu() {
    printf("\nMenu:\n");
    printf("1. Initialize the array with random numbers\n");
    printf("2. Display the array\n");
    printf("3. Free the memory of the array\n");
    printf("4. Sort the array using a simple method (Selection Sort)\n");
    printf("5. Sort the array using an advanced method (Quick Sort)\n");
    printf("6. Exit\n");
}

/**
 * @brief Handles the menu and user interaction.
 *
 * @param arr Pointer to the pointer of the array.
 * @param length Pointer to the length of the array.
 */
void menu(int **arr, int *length) {
    int choice;
    int is_initialized = 0;
    do {
        print_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case INITIALIZE_ARRAY:
                if (*arr != NULL) {
                    free_memory(*arr);
                }
                printf("Enter the length of the array: ");
                scanf("%d", length);
                *arr = (int*)malloc(*length * sizeof(int));
                initialize_array(*arr, *length);
                is_initialized = 1;
                break;
            case DISPLAY_ARRAY:
                if (is_initialized) {
                    display_array(*arr, *length);
                } else {
                    printf("Array not initialized. Please initialize the array first.\n");
                }
                break;
            case FREE_MEMORY:
                if (is_initialized) {
                    free_memory(*arr);
                    *arr = NULL;
                    is_initialized = 0;
                    printf("Memory freed.\n");
                } else {
                    printf("Array not initialized. Please initialize the array first.\n");
                }
                break;
            case SORT_ARRAY_SIMPLE:
                if (is_initialized) {
                    selection_sort(*arr, *length);
                } else {
                    printf("Array not initialized. Please initialize the array first.\n");
                }
                break;
            case SORT_ARRAY_ADVANCED:
                if (is_initialized) {
                    quick_sort_wrapper(*arr, *length);
                } else {
                    printf("Array not initialized. Please initialize the array first.\n");
                }
                break;
            case EXIT_PROGRAM:
                printf("Exiting program\n");
                if (is_initialized) {
                    free_memory(*arr);
                }
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != EXIT_PROGRAM);
}

/**
 * @brief Main function to start the program.
 *
 * @return int Returns 0 on successful execution.
 */
int main() {
    int *arr = NULL;
    int length = 0;
    menu(&arr, &length);
    return 0;
}