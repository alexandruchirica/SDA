#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

typedef struct Document {
    int doc_id;
    char doc_name[MAX_NAME_LENGTH];
    int total_lines;
    int lines_left;
    struct Document* next_doc;
} Document;

typedef struct Printer {
    int printer_id;
    int print_speed;
    Document* current_doc;
    struct Printer* next_printer;
} Printer;

// Creates a new document with the given ID, name, and total lines
Document* create_document(int id, const char* name, int total_lines) {
    Document* doc = (Document*)malloc(sizeof(Document));
    if (doc == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    doc->doc_id = id;
    strncpy(doc->doc_name, name, sizeof(doc->doc_name));
    doc->total_lines = total_lines;
    doc->lines_left = total_lines;
    doc->next_doc = NULL;
    return doc;
}

// Creates a new printer with the given ID and print speed
Printer* create_printer(int id, int print_speed) {
    Printer* printer = (Printer*)malloc(sizeof(Printer));
    if (printer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    printer->printer_id = id;
    printer->print_speed = print_speed;
    printer->current_doc = NULL;
    printer->next_printer = NULL;
    return printer;
}

// Adds a document to the print queue
void add_document(Document** queue, Document* doc) {
    if (*queue == NULL) {
        *queue = doc;
    } else {
        Document* current = *queue;
        while (current->next_doc != NULL) {
            current = current->next_doc;
        }
        current->next_doc = doc;
    }
}

// Distributes queued documents to available printers
void distribute_documents(Document** queue, Printer* printers) {
    Document* current_doc = *queue;
    while (current_doc != NULL) {
        Printer* min_printer = NULL;
        int min_time = -1;
        Printer* current_printer = printers;
        while (current_printer != NULL) {
            if (current_printer->current_doc == NULL) {
                int time = current_doc->lines_left * current_printer->print_speed;
                if (min_time == -1 || time < min_time) {
                    min_time = time;
                    min_printer = current_printer;
                }
            }
            current_printer = current_printer->next_printer;
        }
        if (min_printer != NULL) {
            min_printer->current_doc = current_doc;
            current_doc = current_doc->next_doc;
        } else {
            break; // No available printer
        }
    }
}

// Simulates the printing process
void print_documents(Document** queue, Printer* printers) {
    Document* current_doc = *queue;
    while (current_doc != NULL) {
        Printer* current_printer = printers;
        while (current_printer != NULL) {
            if (current_printer->current_doc == current_doc) {
                int lines_to_print = current_doc->lines_left;
                if (lines_to_print > 0) {
                    int printed_lines = current_printer->print_speed;
                    if (printed_lines >= lines_to_print) {
                        printf("Printer %d printed document %d completely\n", current_printer->printer_id, current_doc->doc_id);
                        current_printer->current_doc->lines_left = 0;
                        current_printer->current_doc = NULL;
                    } else {
                        current_printer->current_doc->lines_left -= printed_lines;
                        printf("Printer %d is printing document %d, %d seconds remaining\n", current_printer->printer_id, current_doc->doc_id, (current_doc->lines_left / current_printer->print_speed) * current_printer->print_speed);
                    }
                }
            }
            current_printer = current_printer->next_printer;
        }
        current_doc = current_doc->next_doc;
    }
}

// Displays the status of the print queue and printers
void display_status(Document* queue, Printer* printers) {
    printf("Print Queue:\n");
    Document* current_doc = queue;
    while (current_doc != NULL) {
        printf("Document %d (%s) - %d lines left\n", current_doc->doc_id, current_doc->doc_name, current_doc->lines_left);
        current_doc = current_doc->next_doc;
    }
    printf("\nPrinters:\n");
    Printer* current_printer = printers;
    while (current_printer != NULL) {
        printf("Printer %d - %d seconds per line\n", current_printer->printer_id, current_printer->print_speed);
        if (current_printer->current_doc != NULL) {
            printf("  Printing Document %d\n", current_printer->current_doc->doc_id);
        } else {
            printf("  Idle\n");
        }
        current_printer = current_printer->next_printer;
    }
}

// Frees memory allocated for documents and printers
void free_memory(Document* queue, Printer* printers) {
    Document* current_doc = queue;
    while (current_doc != NULL) {
        Document* temp = current_doc;
        current_doc = current_doc->next_doc;
        free(temp);
    }
    Printer* current_printer = printers;
    while (current_printer != NULL) {
        Printer* temp = current_printer;
        current_printer = current_printer->next_printer;
        free(temp);
    }
}

// Main function
int main() {
    int num_printers;
    printf("Enter the number of printers: ");
    scanf("%d", &num_printers);

    Printer* printers = NULL;
    for (int i = 1; i <= num_printers; i++) {
        int print_speed;
        printf("Enter print speed for printer %d (in seconds per line): ", i);
        scanf("%d", &print_speed);
        if (printers == NULL) {
            printers = create_printer(i, print_speed);
        } else {
            Printer* temp = create_printer(i, print_speed);
            temp->next_printer = printers;
            printers = temp;
        }
    }

    int num_documents;
    printf("Enter the number of documents: ");
    scanf("%d", &num_documents);

    Document* queue = NULL;
    for (int i = 1; i <= num_documents; i++) {
        char name[MAX_NAME_LENGTH];
        int total_lines;
        printf("Enter name and total lines for document %d: ", i);
        scanf("%s %d", name, &total_lines);
        add_document(&queue, create_document(i, name, total_lines));
    }

    distribute_documents(&queue, printers);
    print_documents(&queue, printers);
    display_status(queue, printers);
    free_memory(queue, printers);

    return 0;
}
