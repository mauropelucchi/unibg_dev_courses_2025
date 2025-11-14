/*
OBIETTIVO
Creare un codice capace di trovare i numeri equilibrati conpresi in un intervallo [a,b] inserito dall'utente. Un numero e' detto equilibrato se la somma delle cifre pari e' uguale alla somma delle cifre dispari.
Ad esempio, 1210 e' un numero equilibrato in quanto (1+1) = (2+0), mentre 1230 non lo e' in quanto (1+3) != (2+0).

RAGIONAMENTO per trovare le cifre di un numero n:
 le cifre di un numero n si possono esprimere come la cifra di un numero moltiplicata per la sua posizione
dove ogni cifra e' moltiplicata per la sua posizione
         (unità, decine, centinaia, migliaia == 1, 10, 100, 1000, ... )
es. 3456 = 3 * 1000 + 4 * 100 + 5 * 10 + 6 * 1

Per trovare le cifre di un numero n, si puo' procedere cosi':
     1) trovare la posizione piu' alta del numero n (es. per 3456 e' 1000)
     2) dividere n per la posizione piu' alta per trovare la cifra in quella posizione (es. 3456 / 1000 = 3.456 -> cifra = 3)
     3) rimuovere la cifra trovata da n (es. 3456 - 3 * 1000 = 456)
     4) ripetere i punti 2 e 3 fino all'ultima cifra (posizione 1)
 */

#include <iostream>
using namespace std;

bool isNumeroEquilibrato(int n);  // funzione che controlla se un numero e' equilibrato o meno

int main() {
    int a, b, count = 0;

    do{
        cout << "Inserisci l'intervallo [a,b]   (a e b positivi, ed a minore di b): " << endl;
        cin >> a;
        cin >> b;
    }while(a < 0 || a >= b); // assicuro che a e b siano positivi e che a sia minore di b
    cout << endl << endl;

    cout << "Numeri equilibrati nell'intervallo [" << a << ", " << b << "]: ";
    for(int i = a; i <= b; i++){
        if(isNumeroEquilibrato(i)){
            cout << i << "  ";
            count++;
        }
    }
    cout << endl << endl;

    if( count ){
        cout << endl << "Totale numeri equilibrati trovati: " << count << endl;
    } else {
        cout << "Nessun numero equilibrato trovato nell'intervallo specificato.[" << a << ", " << b << "]..." << endl;
    }
}


bool isNumeroEquilibrato(int n){
    bool isEquilibrato = false;

    int sommaPari = 0, sommaDispari = 0, posizione = 1, cifra;

    // trovo la posizione piu' alta
    do{
        posizione *= 10;
    }while((float)(n / posizione) >= 1); // se n / posizione < 1, allora la posizione esatta e' la precedente (operazione eseguita nel do while successivo)

    do{ // mi trovo tutte le cifre, partendo da quella con la posizione piu' alta
        posizione /= 10; // scendo di una posizione (dalla prima all'ultima)

        // calcolo la cifra in posizione
        cifra = 0;
        do{
            cifra++;
        }while((float)(n / (cifra * posizione)) >= 1); // se n / (cifra * posizione) < 1, allora la cifra esatta e' la precedente
        cifra--;  // riporto la cifra corretta

        if(cifra % 2){
            // cifra dispari
            sommaDispari += cifra;
        } else {
            // cifra pari
            sommaPari += cifra;
        }

        n = n - (cifra * posizione); // rimuovo la cifra trovata da n
    }while(posizione != 1); // ripeto finche' non arrivo all'ultima cifra

    if(sommaPari == sommaDispari){
        isEquilibrato = true;
    }

    return isEquilibrato;
}
