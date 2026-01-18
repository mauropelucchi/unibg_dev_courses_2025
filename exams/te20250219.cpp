#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

struct VERBALE {
    char codice[16];
    char data_verbalizzazione[11]; // aaaa-mm-gg
    char data_appello[11];         // aaaa-mm-gg
    char data_superamento[11];     // aaaa-mm-gg
    char codice_insegnamento[11];
    char nome_docente[51];
    char matricola[8];
    int voto; // 31 = 30 e lode
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

int estrai_valore(char data[], int ini, int len) {
    char buffer[16];
    int i;
    for (i = 0; i < len; i++)
        buffer[i] = data[ini + i];
    buffer[i] = '\0';
    return atoi(buffer);
}

// date nel formato "aaaa-mm-gg": anno = [0..3], mese = [5..6]
int stesso_mese(char data_verb[], char data_app[]) {
    int annoV = estrai_valore(data_verb, 0, 4);
    int annoA = estrai_valore(data_app, 0, 4);
    int meseV = estrai_valore(data_verb, 5, 2);
    int meseA = estrai_valore(data_app, 5, 2);
    if (annoV == annoA && meseV == meseA)
        return 1;
    return 0;
}

int cerca_insegnamento(char codice_insegnamento[], char *insegnamenti[], int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(codice_insegnamento, insegnamenti[i]) == 0)
            return i;
    }
    return -1;
}

void InitInt(int a[], int size, int val) {
    for (int i = 0; i < size; i++)
        a[i] = val;
}

// 1a scansione: calcola somma voti e conteggi per ogni insegnamento (solo verbali "stesso mese")
void CalcolaSommeConteggi(NODO *listaIn, char *insegnamenti[], int size,
                          int somme[], int conteggi[]) {
    InitInt(somme, size, 0);
    InitInt(conteggi, size, 0);

    NODO *p = listaIn;
    while (p != NULL) {
        int pos = cerca_insegnamento(p->dato.codice_insegnamento, insegnamenti, size);
        if (pos >= 0) {
            if (stesso_mese(p->dato.data_verbalizzazione, p->dato.data_appello)) {
                somme[pos] += p->dato.voto;
                conteggi[pos]++;
            }
        }
        p = p->next;
    }
}

// restituisce l'indice dell'insegnamento con media massima (tra quelli con conteggi>0), altrimenti -1.
// in uscita mette anche mediaMax.
int TrovaMaxMedia(int somme[], int conteggi[], int size, float &mediaMax) {
    int max_pos = -1;
    mediaMax = 0.0f;

    for (int i = 0; i < size; i++) {
        if (conteggi[i] > 0) {
            float media = (float)somme[i] / (float)conteggi[i];
            if (max_pos < 0 || media > mediaMax) {
                mediaMax = media;
                max_pos = i;
            }
        }
    }
    return max_pos;
}

// 2a scansione: copia i verbali dell'insegnamento scelto con voto > mediaMax
NODO* VerbaliVotiAlti(NODO *listaIn, char *insegnamenti[], int size) {
    if (size < 1)
        return NULL;

    int somme[size];
    int conteggi[size];

    // (1) prima scansione
    CalcolaSommeConteggi(listaIn, insegnamenti, size, somme, conteggi);

    // (2) trova insegnamento con media più alta
    float mediaMax;
    int max_pos = TrovaMaxMedia(somme, conteggi, size, mediaMax);
    if (max_pos < 0)
        return NULL; // nessuna media esistente

    // (3) seconda scansione: copia
    NODO *listaOut = NULL;
    NODO *p = listaIn;
    while (p != NULL) {
        if (strcmp(p->dato.codice_insegnamento, insegnamenti[max_pos]) == 0) {
            if (p->dato.voto > mediaMax) {
                if (ins_testa(listaOut, p->dato) == -1)
                    return NULL;
            }
        }
        p = p->next;
    }

    return listaOut;
}