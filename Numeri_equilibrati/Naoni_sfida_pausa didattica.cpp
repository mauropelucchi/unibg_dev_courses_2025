// scrivere un codice che trovi tutti i numeri bilanciati in un intervallo definito dall'utente
// numero bilanciato: somma cifre pasi = somma cifre dispari

#include <iostream>
#define DIM 100

using namespace std;

int main()
{

    int num_inizio, num_fine;
    int numeri_bilanciati[DIM];
    int cifre_pari, cifre_dispari, cifra;
    int indice = 0;

    cout << "definizione range" << endl;

    do
    {
        cout << "insierisci il numero di inizio: ";
        cin >> num_inizio;
        if (num_inizio < 0)
            cout << endl
                 << "inserisci un numero intero positivo..." << endl;
    } while (num_inizio < 0);

    do
    {
        cout << "insierisci il numero di fine: ";
        cin >> num_fine;
        if (num_fine < num_inizio)
            cout << endl
                 << "inserisci un numero intero meggiore del numero iniziale..." << endl;
    } while (num_fine < num_inizio);

    for (int i = num_inizio; i <= num_fine; i++)
    {
        cifre_pari = 0;
        cifre_dispari = 0;

        string num_temp = to_string(i);
        for (int j = 0; j < num_temp.length(); j++)
        {
            cifra = num_temp[j] - '0'; // sottrazione tra numero che identifica i simboli nel codice ascii
            if (cifra % 2 == 0)
                cifre_pari += cifra;
            else
                cifre_dispari += cifra;
        }

        if (cifre_pari == cifre_dispari)
        {
            numeri_bilanciati[indice] = i;
            indice++;
        }
    }

    for (int i = 0; i < indice; i++)
    {
        cout << numeri_bilanciati[i] << endl;
    }

    return 0;
}