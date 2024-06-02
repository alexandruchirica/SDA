#include <stdio.h>
#include <string.h>

#define MAX_PERSONS 100

struct Persoana {
    char nume[30];
    char prenume[30];
    int varsta;
};

typedef struct Persoana Persoana;

// Am folosit prototipurile functiilor pentru a realiza in continuare diverse operatii
void citireElemente(Persoana tablou[], int *nrElemente);
void afisareElemente(Persoana tablou[], int nrElemente);
int cautareElement(Persoana tablou[], int nrElemente, int valoareCautata);
void sortareElemente(Persoana tablou[], int nrElemente);
void inserareLaCapat(Persoana tablou[], int *nrElemente);
void inserareLaInceput(Persoana tablou[], int *nrElemente);
void stergereDeLaPozitie(Persoana tablou[], int *nrElemente, int pozitie);

int main() {
    Persoana tablou[MAX_PERSONS];
    int nrElemente = 0;
    int optiune;

//Am aplicat bucla do-while ca programul sa functioneze atat timp pana cand nu voi selecta 0
    do {
        printf("\nMeniu:\n");
        printf("1. Citire elemente de la tastatura\n");
        printf("2. Afisare elemente\n");
        printf("3. Cautare element\n");
        printf("4. Sortare elemente\n");
        printf("5. Inserare la capat\n");
        printf("6. Inserare la inceput\n");
        printf("7. Stergere de la pozitie\n");
        printf("0. Iesire\n");
        printf("Alegeti o optiune: ");
        scanf("%d", &optiune);

        switch(optiune) {
            case 1:
                citireElemente(tablou, &nrElemente);
                break;
            case 2:
                afisareElemente(tablou, nrElemente);
                break;
            case 3: {
                int valoareCautata;
                printf("Introduceti valoarea de cautare: ");
                scanf("%d", &valoareCautata);
                int pozitie = cautareElement(tablou, nrElemente, valoareCautata);
                if (pozitie != -1) {
                    printf("Elementul a fost gasit la pozitia %d.\n", pozitie);
                } else {
                    printf("Elementul nu a fost gasit.\n");
                }
                break;
            }
            case 4:
                sortareElemente(tablou, nrElemente);
                break;
            case 5:
                inserareLaCapat(tablou, &nrElemente);
                break;
            case 6:
                inserareLaInceput(tablou, &nrElemente);
                break;
            case 7: {
                int pozitie;
                printf("Introduceti pozitia de stergere: ");
                scanf("%d", &pozitie);
                stergereDeLaPozitie(tablou, &nrElemente, pozitie);
                break;
            }
            case 0:
                printf("Iesire din program.\n");
                break;
            default:
                printf("Optiune invalida. Alegeti din nou.\n");
        }
    } while(optiune != 0);

    return 0;
}

void citireElemente(Persoana tablou[], int *nrElemente) {
    printf("Introduceti numarul de elemente: ");
    scanf("%d", nrElemente);

    for (int i = 0; i < *nrElemente; i++) {

        printf("Introduceti numele persoanei %d: ", i + 1);
        scanf("%s", tablou[i].nume);
        printf("Introduceti prenumele persoanei %d: ", i + 1);
        scanf("%s", tablou[i].prenume);
        printf("Introduceti varsta persoanei %d: ", i + 1);
        scanf("%d", &tablou[i].varsta);
    }
}

void afisareElemente(Persoana tablou[], int nrElemente) {
    printf("\nElementele tabloului sunt:\n");
    for (int i = 0; i < nrElemente; i++) {
        printf("\nNume: %s, \nPrenume: %s, \nVarsta: %d\n\n", tablou[i].nume, tablou[i].prenume, tablou[i].varsta);
    }
}

int cautareElement(Persoana tablou[], int nrElemente, int valoareCautata) {
    for (int i = 0; i < nrElemente; i++) {
        if (tablou[i].varsta == valoareCautata) {
            return i;
        }
    }
    return -1;
}

void sortareElemente(Persoana tablou[], int nrElemente) {
    for (int i = 0; i < nrElemente - 1; i++) {
        for (int j = 0; j < nrElemente - i - 1; j++) {
            if (tablou[j].varsta > tablou[j + 1].varsta) {

                Persoana temp = tablou[j];
                tablou[j] = tablou[j + 1];
                tablou[j + 1] = temp;
            }
        }
    }
    printf("Elementele au fost sortate.\n");
}

void inserareLaCapat(Persoana tablou[], int *nrElemente) {
    if (*nrElemente < MAX_PERSONS) {

        printf("Introduceti numele pentru noul element: ");
        scanf("%s", tablou[*nrElemente].nume);
        printf("Introduceti prenumele pentru noul element: ");
        scanf("%s", tablou[*nrElemente].prenume);
        printf("Introduceti varsta pentru noul element: ");
        scanf("%d", &tablou[*nrElemente].varsta);

        (*nrElemente)++; 
    } else {
        printf("Tabloul este plin. Inserarea nu poate fi efectuata.\n");
    }
}

void inserareLaInceput(Persoana tablou[], int *nrElemente) {
    if (*nrElemente < MAX_PERSONS) {

        for (int i = *nrElemente; i > 0; i--) {
            tablou[i] = tablou[i - 1];
        }

        printf("Introduceti numele pentru noul element: ");
        scanf("%s", tablou[0].nume);
        printf("Introduceti prenumele pentru noul element: ");
        scanf("%s", tablou[0].prenume);
        printf("Introduceti varsta pentru noul element: ");
        scanf("%d", &tablou[0].varsta);

        (*nrElemente)++;
    } else {
        printf("Inserarea nu poate fi efectuata.\n");
    }
}

void stergereDeLaPozitie(Persoana tablou[], int *nrElemente, int pozitie) {
    if (pozitie >= 0 && pozitie < *nrElemente) {

        for (int i = pozitie; i < *nrElemente - 1; i++) {
            tablou[i] = tablou[i + 1];
        }

        (*nrElemente)--;
    } else {
        printf("Stergerea nu poate fi efectuata.\n");
    }
}
