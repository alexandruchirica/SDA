#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char nume[30];
    char prenume[30];
    int varsta;
    float nota;
    int id;
    struct Student* urmatorul;
};

typedef struct Student Student;

Student* citireElemente();
void afisareElemente(Student* cap);
int cautareElement(Student* cap, int valoareCautata);
void eliberareMemorie(Student* cap);
Student* sortareElemente(Student* cap);
Student* inserareLaCapat(Student* cap);
Student* inserareLaInceput(Student* cap);
Student* inserareLaPozitie(Student* cap);
Student* stergereDeLaPozitie(Student* cap);
Student* inversareLista(Student* cap);
void curatareLista(Student* cap);

int main() {
    Student* cap = NULL;
    int optiune;

    do {
        printf("\nMeniu:\n");
        printf("1. Citire elemente de la tastatura\n");
        printf("2. Afisare elemente\n");
        printf("3. Cautare element\n");
        printf("4. Eliberare memorie\n");
        printf("5. Sortare elemente\n");
        printf("6. Inserare la capat\n");
        printf("7. Inserare la inceput\n");
        printf("8. Inserare la pozitie\n");
        printf("9. Stergere de la pozitie\n");
        printf("10. Inversare ordine elemente\n");
        printf("11. Curatare lista\n");
        printf("0. Iesire\n");
        printf("Alegeți o opțiune: ");
        scanf("%d", &optiune);

        switch(optiune) {
            case 1:
                cap = citireElemente();
                break;
            case 2:
                afisareElemente(cap);
                break;
            case 3: {
                int valoareCautata;
                printf("Introduceți valoarea de căutare: ");
                scanf("%d", &valoareCautata);
                int pozitie = cautareElement(cap, valoareCautata);
                if (pozitie != -1) {
                    printf("Elementul a fost găsit la poziția %d.\n", pozitie);
                } else {
                    printf("Elementul nu a fost găsit.\n");
                }
                break;
            }
            case 4:
                eliberareMemorie(cap);
                break;
            case 5:
                cap = sortareElemente(cap);
                break;
            case 6:
                cap = inserareLaCapat(cap);
                break;
            case 7:
                cap = inserareLaInceput(cap);
                break;
            case 8:
                cap = inserareLaPozitie(cap);
                break;
            case 9:
                cap = stergereDeLaPozitie(cap);
                break;
            case 10:
                cap = inversareLista(cap);
                break;
            case 11:
                curatareLista(cap);
                break;
            case 0:
                printf("Iesire din program.\n");
                break;
            default:
                printf("Opțiune invalidă. Alegeți din nou.\n");
        }
    } while(optiune != 0);

    return 0;
}

Student* citireElemente() {
    Student* cap = NULL;
    int nrElemente;
    printf("Introduceți numărul de elemente: ");
    scanf("%d", &nrElemente);

    for (int i = 0; i < nrElemente; i++) {
        Student* nou = (Student*)malloc(sizeof(Student));
        printf("Introduceți numele studentului: ");
        scanf("%s", nou->nume);
        printf("Introduceți prenumele studentului: ");
        scanf("%s", nou->prenume);
        printf("Introduceți vârsta studentului: ");
        scanf("%d", &nou->varsta);
        printf("Introduceți nota studentului: ");
        scanf("%f", &nou->nota);
        printf("Introduceți ID-ul studentului: ");
        scanf("%d", &nou->id);

        nou->urmatorul = cap;
        cap = nou;
    }

    return cap;
}

void afisareElemente(Student* cap) {
    printf("Elementele listei sunt:\n");
    while (cap != NULL) {
        printf("Nume: %s, Prenume: %s, Varsta: %d, Nota: %.2f, ID: %d\n", cap->nume, cap->prenume, cap->varsta, cap->nota, cap->id);
        cap = cap->urmatorul;
    }
}

int cautareElement(Student* cap, int valoareCautata) {
    int pozitie = 0;
    while (cap != NULL) {
        if (cap->varsta == valoareCautata) {
            return pozitie;
        }
        cap = cap->urmatorul;
        pozitie++;
    }
    return -1;
}

void eliberareMemorie(Student* cap) {
    while (cap != NULL) {
        Student* temp = cap;
        cap = cap->urmatorul;
        free(temp);
    }
    printf("Memoria listei a fost eliberata.\n");
}

Student* sortareElemente(Student* cap) {
    // Bubble sort
    int schimbat;
    Student *p, *ultim = NULL;

    if (cap == NULL) {
        return cap;
    }

    do {
        schimbat = 0;
        p = cap;

        while (p->urmatorul != ultim) {
            if (p->varsta > p->urmatorul->varsta) {
                // Schimbare elemente
                int tempVarsta = p->varsta;
                p->varsta = p->urmatorul->varsta;
                p->urmatorul->varsta = tempVarsta;

                float tempNota = p->nota;
                p->nota = p->urmatorul->nota;
                p->urmatorul->nota = tempNota;

                int tempID = p->id;
                p->id = p->urmatorul->id;
                p->urmatorul->id = tempID;

                char tempNume[30];
                strcpy(tempNume, p->nume);
                strcpy(p->nume, p->urmatorul->nume);
                strcpy(p->urmatorul->nume, tempNume);

                char tempPrenume[30];
                strcpy(tempPrenume, p->prenume);
                strcpy(p->prenume, p->urmatorul->prenume);
                strcpy(p->urmatorul->prenume, tempPrenume);

                schimbat = 1;
            }
            p = p->urmatorul;
        }
        ultim = p;
    } while (schimbat);

    printf("Elementele au fost sortate.\n");
    return cap;
}

Student* inserareLaCapat(Student* cap) {
    Student* nou = (Student*)malloc(sizeof(Student));
    printf("Introduceți numele pentru noul element: ");
    scanf("%s", nou->nume);
    printf("Introduceți prenumele pentru noul element: ");
    scanf("%s", nou->prenume);
    printf("Introduceți vârsta pentru noul element: ");
    scanf("%d", &nou->varsta);
    printf("Introduceți nota pentru noul element: ");
    scanf("%f", &nou->nota);
    printf("Introduceți ID-ul pentru noul element: ");
    scanf("%d", &nou->id);

    nou->urmatorul = NULL;

    if (cap == NULL) {
        cap = nou;
    } else {
        Student* temp = cap;
        while (temp->urmatorul != NULL) {
            temp = temp->urmatorul;
        }
        temp->urmatorul = nou;
    }

    return cap;
}

Student* inserareLaInceput(Student* cap) {
    Student* nou = (Student*)malloc(sizeof(Student));
    printf("Introduceți numele pentru noul element: ");
    scanf("%s", nou->nume);
    printf("Introduceți prenumele pentru noul element: ");
    scanf("%s", nou->prenume);
    printf("Introduceți vârsta pentru noul element: ");
    scanf("%d", &nou->varsta);
    printf("Introduceți nota pentru noul element: ");
    scanf("%f", &nou->nota);
    printf("Introduceți ID-ul pentru noul element: ");
    scanf("%d", &nou->id);

    nou->urmatorul = cap;
    cap = nou;

    return cap;
}

Student* inserareLaPozitie(Student* cap) {
    int pozitie;
    printf("Introduceți poziția de inserare: ");
    scanf("%d", &pozitie);

    if (pozitie < 0) {
        printf("Poziție invalidă. Inserarea nu poate fi efectuată.\n");
        return cap;
    }

    Student* nou = (Student*)malloc(sizeof(Student));
    printf("Introduceți numele pentru noul element: ");
    scanf("%s", nou->nume);
    printf("Introduceți prenumele pentru noul element: ");
    scanf("%s", nou->prenume);
    printf("Introduceți vârsta pentru noul element: ");
    scanf("%d", &nou->varsta);
    printf("Introduceți nota pentru noul element: ");
    scanf("%f", &nou->nota);
    printf("Introduceți ID-ul pentru noul element: ");
    scanf("%d", &nou->id);

    if (pozitie == 0) {
        nou->urmatorul = cap;
        cap = nou;
    } else {
        Student* temp = cap;
        for (int i = 0; i < pozitie - 1 && temp != NULL; i++) {
            temp = temp->urmatorul;
        }
        if (temp == NULL) {
            printf("Poziție invalidă. Inserarea nu poate fi efectuată.\n");
            return cap;
        }
        nou->urmatorul = temp->urmatorul;
        temp->urmatorul = nou;
    }

    return cap;
}

Student* stergereDeLaPozitie(Student* cap) {
    int pozitie;
    printf("Introduceți poziția de ștergere: ");
    scanf("%d", &pozitie);

    if (pozitie < 0) {
        printf("Poziție invalidă. Ștergerea nu poate fi efectuată.\n");
        return cap;
    }

    if (cap == NULL) {
        printf("Lista este goală. Ștergerea nu poate fi efectuată.\n");
        return cap;
    }

    if (pozitie == 0) {
        Student* temp = cap;
        cap = cap->urmatorul;
        free(temp);
    } else {
        Student* temp = cap;
        for (int i = 0; i < pozitie - 1 && temp != NULL; i++) {
            temp = temp->urmatorul;
        }
        if (temp == NULL || temp->urmatorul == NULL) {
            printf("Poziție invalidă. Ștergerea nu poate fi efectuată.\n");
            return cap;
        }
        Student* deSters = temp->urmatorul;
        temp->urmatorul = deSters->urmatorul;
        free(deSters);
    }

    return cap;
}

Student* inversareLista(Student* cap) {
    Student* prev = NULL;
    Student* current = cap;
    Student* next = NULL;

    while (current != NULL) {
        next = current->urmatorul;
        current->urmatorul = prev;
        prev = current;
        current = next;
    }

    cap = prev; // Noul cap al listei

    printf("Ordinea elementelor a fost inversată.\n");
    return cap;
}
