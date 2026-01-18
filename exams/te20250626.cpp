#include <iostream>
#include <cstring>

using namespace std;

struct VERBALE {
    char codice[16];
    char data_verbalizzazione[11]; // aaaa-mm-gg
    char data_appello[11];         // aaaa-mm-gg
    char data_superamento[11];     // aaaa-mm-gg
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
    NODO *t = new NODO;
    if (t == NULL) {
        cout << "Errore Allocazione";
        return -1;
    }
    t->dato = dato;
    t->next = head;
    head = t;
    return 0;
}

int cerca_data(char data[], char *dateAppelli[], int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(data, dateAppelli[i]) == 0)
            return i;
    }
    return -1;
}

void InitArrayInt(int a[], int size, int val) {
    for (int i = 0; i < size; i++)
        a[i] = val;
}

// 1 sola scansione di lista2: conteggi2[i] = #verbali in lista2 con data_appello == dateAppelli[i]
void CalcolaConteggiLista2(NODO *lista2, char *dateAppelli[], int size, int conteggi2[]) {
    InitArrayInt(conteggi2, size, 0);

    NODO *p = lista2;
    while (p != NULL) {
        int pos = cerca_data(p->dato.data_appello, dateAppelli, size);
        if (pos >= 0)
            conteggi2[pos]++;
        p = p->next;
    }
}

// 1a scansione di lista1: calcola conteggi1[i]
void CalcolaConteggiLista1(NODO *lista1, char *dateAppelli[], int size, int conteggi1[]) {
    InitArrayInt(conteggi1, size, 0);

    NODO *p = lista1;
    while (p != NULL) {
        int pos = cerca_data(p->dato.data_appello, dateAppelli, size);
        if (pos >= 0)
            conteggi1[pos]++;
        p = p->next;
    }
}

// costruisce un array "seleziona[i]" = 1 se conteggi1[i] > conteggi2[i], altrimenti 0
void CalcolaSelezione(int conteggi1[], int conteggi2[], int size, int seleziona[]) {
    for (int i = 0; i < size; i++) {
        if (conteggi1[i] > conteggi2[i])
            seleziona[i] = 1;
        else
            seleziona[i] = 0;
    }
}

// 2a scansione di lista1: copia i verbali con data_appello in date selezionate
int CopiaDaLista1(NODO *lista1, char *dateAppelli[], int size, int seleziona[], NODO * &listaOut) {
    NODO *p = lista1;
    while (p != NULL) {
        int pos = cerca_data(p->dato.data_appello, dateAppelli, size);
        if (pos >= 0 && seleziona[pos] == 1) {
            if (ins_testa(listaOut, p->dato) == -1)
                return 1; // errore allocazione
        }
        p = p->next;
    }
    return 0;
}

NODO* VerbaliVotiAlti(NODO *lista1, NODO *lista2, char *dateAppelli[], int size) {
    if (size < 1)
        return NULL;

    int conteggi1[size];
    int conteggi2[size];
    int seleziona[size];

    // 1 scansione di lista2
    CalcolaConteggiLista2(lista2, dateAppelli, size, conteggi2);

    // 1a scansione di lista1
    CalcolaConteggiLista1(lista1, dateAppelli, size, conteggi1);

    // punto (2)
    CalcolaSelezione(conteggi1, conteggi2, size, seleziona);

    // punto (3) - 2a scansione di lista1
    NODO *listaOut = NULL;
    if (CopiaDaLista1(lista1, dateAppelli, size, seleziona, listaOut) == -1)
        return NULL;

    return listaOut;
}