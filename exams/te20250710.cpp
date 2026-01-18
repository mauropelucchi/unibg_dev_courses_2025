#include <iostream>
#include <cstring>

using namespace std;

struct VERBALE {
    char codice[16];
    char data_emissione[11]; // YYYY-MM-DD
    char data_appello[11]; // YYYY-MM-DD
    char data_superamento[11]; // YYYY-MM-DD
    char codice_insegnamento[11];
    char nome_docente[51];
    char matricola[8];
    int voto;
};

struct NODO {
    VERBALE dato;
    NODO *next;
};

int ins_testa(NODO * &head, VERBALE dato) {
    NODO *t;
    t = new NODO;
    if (t == NULL) {
        cout << "Errore Allocazione";
        return -1;
    }
    t->dato = dato;
    t->next = head;
    head = t;
    return 0;
}

// Funzione ausiliaria per cercare una data nel vettore
int cerca_data(char data[], char *dateEmissione[], int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(data, dateEmissione[i]) == 0)
            return i;
    }
    return -1; // data non trovata
}

// Funzione per calcolare i conteggi per ogni data
void CalcolaConteggi(NODO *lista, char *dateEmissione[], int size, int conteggi[]) {
    NODO *p;
    int pos_data;
    
    p = lista;
    while (p != NULL) {
        pos_data = cerca_data(p->dato.data_emissione, dateEmissione, size);
        if (pos_data >= 0) {
            conteggi[pos_data]++;
        }
        p = p->next;
    }
    
}

// Funzione per calcolare la media dei conteggi
float CalcolaMedia(int conteggi[], int size) {
    int somma = 0;
    for (int i = 0; i < size; i++) {
        somma += conteggi[i];
    }
    return (float)somma / size;
}

// Funzione per copiare i verbali che soddisfano la condizione
int CopiaVerbaliCondizione(NODO *lista, char *dateEmissione[], int size, int conteggi[], float media, NODO * &listaOut) {
    NODO *p;
    int pos_data;
    
    p = lista;
    while (p != NULL) {
        pos_data = cerca_data(p->dato.data_emissione, dateEmissione, size);
        if (pos_data >= 0) {
            if (conteggi[pos_data] > media) {
                if (ins_testa(listaOut, p->dato) == -1)
                    return -1; // errore allocazione
            }
        }
        p = p->next;
    }
    return 0;
}

NODO* CopiaAlcuniVerbali(NODO *lista1, NODO *lista2, char *dateEmissione[], int size) {
    if (size < 1)
        return NULL;
    
    int conteggi[size];
    NODO *listaOut = NULL;
    

    // Inizializzazione dei conteggi
    for (int i = 0; i < size; i++)
        conteggi[i] = 0;
    // Punto 1: Calcola i conteggi per ogni data (1 scansione per lista)
    CalcolaConteggi(lista1, dateEmissione, size, conteggi);
    CalcolaConteggi(lista2, dateEmissione, size, conteggi);
    
    // Punto 2: Calcola la media
    float media = CalcolaMedia(conteggi, size);
    
    // Punto 3: Copia i verbali con conteggio > media (1 scansione per lista)
    // Seconda scansione di lista1
    if (CopiaVerbaliCondizione(lista1, dateEmissione, size, conteggi, media, listaOut) == -1)
        return NULL;
    
    // Seconda scansione di lista2
    if (CopiaVerbaliCondizione(lista2, dateEmissione, size, conteggi, media, listaOut) == -1)
        return NULL;
    
    return listaOut;
}