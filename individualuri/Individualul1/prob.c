#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_BUFFER 1000

typedef struct Product {
    struct tm sale_date;
    int product_id;
    char product_name[MAX_BUFFER];
    char product_category[MAX_BUFFER];
    char product_subcategory[MAX_BUFFER];
    float unit_price;
    int quantity_sold;
    char sale_country[MAX_BUFFER];
    char sale_city[MAX_BUFFER];
} Product;

int compare_by_product_value(const void *a, const void *b);

void _insert_product_details_(Product *products, char *line, int index);

void read_file(Product **products, int *number_of_products, FILE *file);

void top_5_products_by_value(Product *products);

void print_monthly_profit(Product *products, int number_of_products);

void total_income_by_month(Product *products, int number_of_products);

void sales_distribution_by_category(Product *products, int number_of_products);

int main() {
    FILE *file = fopen("sales.csv", "r");

    if (file == NULL) {
        printf("Eroare la deschiderea fisierului\n");
        return 1;
    }

    int number_of_products = 0;
    Product *products = NULL;

    read_file(&products, &number_of_products, file);

    printf("Inserare finalizata\n");

    int choice;
    do {
        printf("\nMeniu:\n");
        printf("1. Venit total pe luna\n");
        printf("2. Primele 5 produse dupa valoare\n");
        printf("3. Distributia vanzarilor pe categorie\n");
        printf("4. Iesire\n");
        printf("Introduceti optiunea: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                total_income_by_month(products, number_of_products);
                break;
            case 2:
                top_5_products_by_value(products);
                break;
            case 3:
                sales_distribution_by_category(products, number_of_products);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Optiune invalida! Va rugam sa introduceti un numar intre 1 și 4.\n");
        }
    } while (choice != 4);

    fclose(file);
    free(products);
    return 0;
}

void _insert_product_details_(Product *products, char *line, int index) {
    const char delimiter[] = ",";
    char *token = strtok(line, ",");

    sscanf(token, "%d-%d-%d", &products[index].sale_date.tm_year, &products[index].sale_date.tm_mon, &products[index].sale_date.tm_mday);
    token = strtok(NULL, delimiter);
    products[index].sale_date.tm_mon--;

    products[index].product_id = atoi(token);
    token = strtok(NULL, delimiter);

    strcpy(products[index].product_name, token);
    token = strtok(NULL, delimiter);

    strcpy(products[index].product_category, token);
    token = strtok(NULL, delimiter);

    strcpy(products[index].product_subcategory, token);
    token = strtok(NULL, delimiter);

    products[index].unit_price = atof(token);
    token = strtok(NULL, delimiter);

    products[index].quantity_sold = atoi(token);
    token = strtok(NULL, delimiter);

    strcpy(products[index].sale_country, token);
    token = strtok(NULL, delimiter);

    strcpy(products[index].sale_city, token);
    products[index].sale_city[strcspn(products[index].sale_city, "\n")] = '\0';
}

void read_file(Product **products, int *number_of_products, FILE *file) {
    char line[MAX_BUFFER];

    int realloc_value = 1;

    if (fgets(line, MAX_BUFFER, file) == NULL) {
        printf("Eroare la citirea fisierului\n");
        exit(1);
    }

    while (fgets(line, MAX_BUFFER, file) != NULL) {

        if (realloc_value == *number_of_products) {
            realloc_value *= 2;
        }

        *products = realloc(*products, sizeof(Product) * (realloc_value));
        if (*products == NULL) {
            printf("Eroare la realocarea memoriei\n");
            exit(1);
        }

        _insert_product_details_(*products, line, *number_of_products);
        (*number_of_products)++;
    }

    *products = realloc(*products, sizeof(Product) * (*number_of_products));
}

int compare_by_product_value(const void *a, const void *b) {
    Product *productA = (Product *)a;
    Product *productB = (Product *)b;

    float totalA = productA->unit_price * productA->quantity_sold;
    float totalB = productB->unit_price * productB->quantity_sold;

    if (totalA > totalB) return -1;
    else if (totalA < totalB) return 1;
    else return 0;
}

void total_income_by_month(Product *products, int number_of_products) {
    printf("\nVenitul total pe luna:\n");
    float monthly_income[12] = {0};

    for (int i = 0; i < number_of_products; i++) {
        float product_value = products[i].unit_price * products[i].quantity_sold;
        int month_index = products[i].sale_date.tm_mon;
        monthly_income[month_index] += product_value;
    }

    printf("Luna\tVenit Total\n");
    for (int i = 0; i < 12; i++) {
        printf("%d\t%.2f\n", i + 1, monthly_income[i]);
    }
}

void top_5_products_by_value(Product *products) {
    printf("\nTop 5 produse dupa valoarea vanzarilor:\n");
    for (int i = 0; i < 5; ++i) {
        printf("Sale_date: %d-%02d-%02d\t Product_id_%d: %d\n", products[i].sale_date.tm_year, products[i].sale_date.tm_mon, products[i].sale_date.tm_mday, i + 1, products[i].product_id);
    }
}

void sales_distribution_by_category(Product *products, int number_of_products) {
    printf("\nIntroduceti categoria: ");
    char category[MAX_BUFFER];
    scanf("%s", category);

    int sales_count = 0;
    for (int i = 0; i < number_of_products; i++) {
        if (strcmp(products[i].product_category, category) == 0) {
            sales_count++;
        }
    }

    printf("Numarul de vanzari pentru categoria '%s': %d\n", category, sales_count);
}
