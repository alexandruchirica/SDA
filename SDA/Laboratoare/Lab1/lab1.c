#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Crearea unei structuri cu persoane
struct Persoana {
    char *name;
    char *sname;
    int age;
    int telephone;
    char *gmail;
};

typedef struct Persoana persoana;

int numara_linii(FILE *fp) {
    char ch;
    int linii = 0;
    while (!feof(fp)) {
        ch = fgetc(fp);
        if (ch == '\n') {
            linii++;
        }
    }
    rewind(fp);
    return ++linii;
}

void gasesteElementul(persoana *vect, int nr_linii, int cautare_varsta, int pozitii[], int *nr_pozitii) {
    *nr_pozitii = 0;
    for (int i = 0; i < nr_linii; i++) {
        if ((vect + i)->age == cautare_varsta) {
            pozitii[*nr_pozitii] = i;
            (*nr_pozitii)++;
        }
    }
}

int main() {
    FILE *f = fopen("persoana.txt", "r");

    int nr_linii = numara_linii(f);

    persoana *vect = (persoana *)malloc(nr_linii * sizeof(persoana));

    for (int i = 0; i < nr_linii; i++) {
        (vect + i)->name = (char *)malloc(30 * sizeof(char));
        (vect + i)->sname = (char *)malloc(30 * sizeof(char));
        (vect + i)->gmail = (char *)malloc(50 * sizeof(char));

        fscanf(f, "%s %s %d %d %s", (vect + i)->name, (vect + i)->sname, &(vect + i)->age, &(vect + i)->telephone, (vect + i)->gmail);
    }
    fclose(f);

    for (int i = 0; i < nr_linii; i++) {
        printf("\nNume: %s\nPrenume: %s\nVârsta: %d  \nNumărul de telefon: %d\nGmail: %s\n\n",
               (vect + i)->name, (vect + i)->sname, (vect + i)->age, (vect + i)->telephone, (vect + i)->gmail);
    }

    // Introducere numar de telefon de la tastatura
    int cautare_varsta;
    printf("Introduceti varsta pentru cautare: ");
    scanf("%d", &cautare_varsta);

    int *pozitii = (int *)malloc(nr_linii * sizeof(int));
    int nr_pozitii;

    gasesteElementul(vect, nr_linii, cautare_varsta, pozitii, &nr_pozitii);

    if (nr_pozitii > 0) {
        printf("Elementul a fost gasit la urmatoarele pozitii:\n");
        for (int i = 0; i < nr_pozitii; i++) {
            printf("Pozitia %d\n", pozitii[i]);
        }
    } else {
        printf("Elementul nu a fost gasit\n");
    }

    // Eliberare memorie alocata dinamic
    for (int i = 0; i < nr_linii; i++) {
        free((vect + i)->name);
        free((vect + i)->sname);
        free((vect + i)->gmail);
    }
    free(vect);
    free(pozitii);

    return 0;
}
