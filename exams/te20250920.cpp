#include <iostream>
#include <cstring>

using namespace std;

struct VERBALE {
    char codice[16];
    char data_emissione[11];     // aaaa-mm-gg
    char data_appello[11];       // aaaa-mm-gg
    char data_superamento[11];   // aaaa-mm-gg
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

void CalcolaConteggiAppelli(NODO *lista,
                            char *dateAppelli[], int size,
                            int conteggi[]) {
    // inizializzazione
    for (int i = 0; i < size; i++)
        conteggi[i] = 0;

    NODO *p;
    int pos;

    p = lista;
    while (p != NULL) {
        pos = cerca_data(p->dato.data_appello, dateAppelli, size);
        if (pos >= 0)
            conteggi[pos]++;
        p = p->next;
    }

}

int CalcolaMaxPos(int conteggi[], int size) {
    int max_pos = -1;
    int max_val = 0;

    for (int i = 0; i < size; i++) {
        if (conteggi[i] > max_val) {
            max_val = conteggi[i];
            max_pos = i;
        }
    }

    if (max_val == 0)
        return -1;  // dataMax non esiste
    return max_pos;
}

int CopiaSeDataMax(NODO *lista, char dataMax[], NODO * &listaOut) {
    NODO *p = lista;
    while (p != NULL) {
        if (strcmp(p->dato.data_appello, dataMax) == 0) {
            if (ins_testa(listaOut, p->dato) == -1)
                return -1; // errore allocazione
        }
        p = p->next;
    }
    return 0;
}

NODO* CopiaAlcuniVerbali(NODO *lista1, NODO *lista2, char *dateAppelli[], int size) {
    if (size < 1)
        return NULL;

    int conteggi[size];
    NODO *listaOut = NULL;
    for (int i = 0; i < size; i++)
        conteggi[i] = 0;
    // (1) conteggio (una scansione per lista)
    CalcolaConteggiAppelli(lista1, dateAppelli, size, conteggi);
    CalcolaConteggiAppelli(lista2, dateAppelli, size, conteggi);

    // (2) dataMax (se esiste)
    int max_pos = CalcolaMaxPos(conteggi, size);
    if (max_pos < 0)
        return NULL;

    char *dataMax = dateAppelli[max_pos];

    // (3) copia (seconda scansione per lista)
    if (CopiaSeDataMax(lista1, dataMax, listaOut) == -1)
        return NULL;

    if (CopiaSeDataMax(lista2, dataMax, listaOut) ==1)
        return NULL;

    return listaOut;
}