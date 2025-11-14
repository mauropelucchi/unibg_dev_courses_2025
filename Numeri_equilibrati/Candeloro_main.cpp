//  Numeri-equilibrati
//  Ingegneria informatica UniBG
//  Created by Andrea Candeloro on 12/11/25.

#include <iostream>
using namespace std;

int nCifre(int n);

bool equilibrato(int n);

int main() {
    
    int numero_iniziale, numero_finale, differenza=0;
    
    do {
        cout << "\nNumeri Equilibrati\n-----------------\nCONDIZIONI INPUT: \nnumero iniziale<numero finale\nnumero iniziale>0\nnumero finale>0\n" << endl;
        cout << "Inserire numero iniziale: ";
        cin >> numero_iniziale;
        
        cout << "Inserire numero finale: ";
        cin >> numero_finale;
        
    } while (numero_iniziale>numero_finale || numero_finale<0 || numero_iniziale<0);
    
    differenza=numero_finale-numero_iniziale;
    
    int v[differenza+1]; // Il vettore lo dichiaro qui perché differenza lo uso come grandezza
    
    for (int i=0; i<=differenza; i++) {
        if (i==0)
            v[i]=numero_iniziale;
        else
            v[i]=v[i-1]+1;
    }
    
    // Stampa elenco numeri analizzati
    cout << "\n-----------------\nELENCO NUMERI IN ANALISI\n-----------------\n";
    for (int i=0; i<=differenza; i++) {
        cout << v[i] << " ";
    }
    cout << "\n-----------------\n";
    
    // Cerca se ogni elemento dell'array è eqiulibrato
    for (int i=0; i<=differenza; i++) {
        if (equilibrato(v[i])==true)
            cout << "✅ HAI TROVATO UN NUMERO EQUILIBRATO: " << v[i] << endl;
        else
            cout << "❌ " << v[i] << " non è equilibrato" << endl;
    }

    return 0;
}

int nCifre(int n) {
    
    int i;
    for (i=0; n>0; i++) {
        n/=10;
    }
    
    return i;
}

bool equilibrato(int n) {
    
    int a=nCifre(n);
    int contatore=1;
    int t[a], f[a];
    int pari=0, dispari=0;
    
    
    for (int i=0; i<a; i++) {
        t[i]=n%(10*contatore);
        contatore*=10;
    }
    
    f[0]=t[0];
    contatore=1;
    for (int i=1; i<a; i++) {
        f[i]=t[i]/(10*contatore);
        contatore*=10;
    }
    
    for (int i=0; i<a; i++) {
        if (f[i]%2==0)
            pari+=f[i];
        else
            dispari+=f[i];
    }
    
    if (dispari==pari)
        return true;
    else
        return false;
}


