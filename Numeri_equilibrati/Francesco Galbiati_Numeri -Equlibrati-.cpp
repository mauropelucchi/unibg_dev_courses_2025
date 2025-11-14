#include <iostream>

using namespace std;

const unsigned short arrayBufferSize = 2569;            //Numero massimo di Numeri equilibrati possibili nell'intervallo [0; 65534] (Memorizzati nell'array)
const unsigned short minValueAllowed = 0;           //Valore minimo consentito per l'estremo sx dell'intervallo
const unsigned short maxValueAllowed = 65534;       //Valore massimo consentito per l'estremo dx dell'intervallo
const unsigned short maxDigits = 5;                     //Numero massimo di cifre da analizzare per numero
const short bannedValue = -1;                       //Valore indicativo di stop per l'analisi dei numeri equilibrati (scelto arbitrariamente)

void ResetValues(bool &sValueN_A, bool &eValueN_A, bool &bNumsN_G);
char OptionMenu(bool &sValueN_A, bool &eValueN_A, unsigned short &sV, unsigned short &eV, bool &bNumsN_A);
unsigned short GetStartValue(bool &eValueN_A, unsigned short &eV);
unsigned short GetEndValue(unsigned short &sV);
void GetDigits(unsigned short &tNum, short tDigits[maxDigits]);
bool GetBalancedCondition(short tDigits[maxDigits]);
void GetBalancedNumbers(unsigned short &sV, unsigned short &eV, unsigned short bNums[arrayBufferSize], unsigned short &bNumsCount, bool &bNumsN_A);
void GoalOfTheApp();

int main()
{
    unsigned short startValue, endValue, balancedNums[arrayBufferSize], bNumsCounter, tempValue;
    bool sValueNotAssigned, eValueNotAssigned, bNumsNotGet;
    char userChoice;

    ResetValues(sValueNotAssigned, eValueNotAssigned, bNumsNotGet);         //Imposta i valori del programma come 'Non assegnati' [N/A]

    do {
        userChoice = OptionMenu(sValueNotAssigned, eValueNotAssigned, startValue, endValue, bNumsNotGet);

        switch (userChoice) {
            case '1':
                if (sValueNotAssigned) {
                    sValueNotAssigned = false;          //Imposta il valore minimo dell'intervallo come 'Assegnato'
                }
                else if (bNumsNotGet == false) {
                    tempValue = startValue;
                }

                startValue = GetStartValue(eValueNotAssigned, endValue);

                if (bNumsNotGet == false && tempValue != startValue) {
                    bNumsNotGet = true;                                     //Imposta l'array dei numeri equilibrati come 'Non assegnato' se il valore dell'intervallo minimo cambia effettivamente
                }
                break;
            case '2':
                if (sValueNotAssigned) {
                    cout << "Errore! Motivazione -> Valore minimo dell\'intervallo non assegnato!" << endl;     //Il valore minimo deve essere stato assegnato per poter dichiarare il valore massimo
                }
                else {
                    if (eValueNotAssigned) {
                        eValueNotAssigned = false;      //Imposta il valore massimo dell'intervallo come 'Assegnato'
                    }
                    else if (bNumsNotGet == false) {
                        tempValue = endValue;
                    }

                    endValue = GetEndValue(startValue);

                    if (bNumsNotGet == false && tempValue != endValue) {
                        bNumsNotGet = true;                                 //Imposta l'array dei numeri equilibrati come 'Non assegnato' se il valore dell'intervallo massimo cambia effettivamente
                    }
                }
                break;
            case '3':
                GetBalancedNumbers(startValue, endValue, balancedNums, bNumsCounter, bNumsNotGet);
                break;
            case '4':
                GoalOfTheApp();
                break;
            case '5':
                ResetValues(sValueNotAssigned, eValueNotAssigned, bNumsNotGet);
                cout << "I valori inseriti in precedenza sono stati resettati..." << endl;
                break;
            case '0':
                cout << "Uscita dal programma..." << endl;
                break;
        }
        if (userChoice >= 48 && userChoice <= 53) {
            system("pause");                            //Imposta un punto di interruzione (come conferma di lettura) solo dopo ogni opzione valida scelta dal menu principale
        }
        system("cls");
    } while (userChoice != '0');

    return EXIT_SUCCESS;
}

void ResetValues(bool &sValueN_A, bool &eValueN_A, bool &bNumsN_G)
{
    sValueN_A = true;
    eValueN_A = true;
    bNumsN_G = true;
}

char OptionMenu(bool &sValueN_A, bool &eValueN_A, unsigned short &sV, unsigned short &eV, bool &bNumsN_A)
{
    char choice;

    cout << "| DATI INSERITI |" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "Valore minimo intervallo: ";
    if (sValueN_A) {
        cout << "N/A" << endl;
    }
    else {
        cout << sV << endl;
    }
    cout << "Valore massimo intervallo: ";
    if (eValueN_A) {
        cout << "N/A" << endl;
    }
    else {
        cout << eV << endl;
    }
    cout << "Numeri equilibrati: ";
    if (bNumsN_A) {
        cout << "Non ancora calcolati" << endl;
    }
    else {
        cout << "Gia' calcolati" << endl;
    }
    cout << "----------------------------------------------------------------------------" << endl;

    cout << "| OPZIONI |" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "1. Dichiarare il valore minimo dell\'intervallo" << endl;
    cout << "2. Dichiarare il valore massimo dell\'intervallo" << endl;
    cout << "3. Stampare i \"Numeri equilibrati\" appartenenti all\'intervallo dichiarato" << endl;
    cout << "4. Visionare la condizione dei \"Numeri equilibrati\" [FAQ]" << endl;
    cout << "5. Resettare i valori inseriti" << endl;
    cout << "0. Uscire dal programma" << endl;
    cout << "----------------------------------------------------------------------------" << endl << endl;

    cout << "Scelta: ";
    cin >> choice;

    cout << endl << endl;

    return choice;
}

unsigned short GetStartValue(bool &eValueN_A, unsigned short &eV)
{
    int userNum;
    bool numDenied;

    do {
        system("cls");
        numDenied = false;

        cout << "Inserire il valore minimo dell\'intervallo: ";
        cin >> userNum;
        cout << endl;

        if (userNum < minValueAllowed || userNum > maxValueAllowed - 1) {
            numDenied = true;
            cout << "Valore inserito invalido -> Condizione da rispettare: " << minValueAllowed  << " <= val. minimo <= " << maxValueAllowed - 1 << endl;
            system("pause");
        }
        if (eValueN_A == false && userNum >= eV) {
            numDenied = true;
            cout << "Valore inserito invalido -> Condizione da rispettare: n < " << eV << " [Valore massimo dichiarato dell'intervallo]" << endl;
            system("pause");
        }
    } while (numDenied);

    cout << "Valore minimo accettato!" << endl << endl;

    return (unsigned short)userNum;
}

unsigned short GetEndValue(unsigned short &sV)
{
    int userNum;
    bool numDenied;

    do {
        system("cls");
        numDenied = false;

        cout << "Inserire il valore massimo dell\'intervallo: ";
        cin >> userNum;
        cout << endl;

        if (userNum > maxValueAllowed || userNum < minValueAllowed + 1) {
            numDenied = true;
            cout << "Valore inserito invalido -> Condizione da rispettare: " << minValueAllowed + 1 << " <= val. massimo <= " << maxValueAllowed << endl;
            system("pause");
        }
        if (userNum <= sV) {
            numDenied = true;
            cout << "Valore inserito invalido -> Condizione da rispettare: n > " << sV << " [Valore minimo dichiarato dell'intervallo]" << endl;
            system("pause");
        }
    } while (numDenied);

    cout << "Valore massimo accettato!" << endl << endl;

    return (unsigned short)userNum;
}

void GetDigits(unsigned short &tNum, short tDigits[maxDigits])
{
    /* 
    Ottiene le cifre che compongono il numero da analizzare
    N.B.: Il valore di stop (bannedValue) servirà per ridurre il numero di operazioni da compiere, evitando di eseguire controlli ridondanti
    P.S.: L'ordine di come vengono sistemate le cifre non è di grande importanza
    */

    for (int i = 0; i < maxDigits; i++) {
        if (tNum != 0) {
            tDigits[i] = tNum % 10;
            tNum /= 10;
        }
        else {
            tDigits[i] = bannedValue;
            break;
        }
    }
}

bool GetBalancedCondition(short tDigits[maxDigits])
{
    //Calcolo e confronto somma cifre pari e somma cifre dispari

    unsigned short sumEvenDigits = 0, sumOddDigits = 0;
    for (int i = 0; i < maxDigits; i++) {
        if (tDigits[i] == bannedValue) {
            break;                          //Condizione di ottimizzazione (citata nella procedura 'GetDigits')
        }
        else {
            if (tDigits[i] % 2 == 0) {
                sumEvenDigits += tDigits[i];
            }
            else {
                sumOddDigits += tDigits[i];
            }
        }
    }
    if (sumEvenDigits == sumOddDigits) {
        return true;
    }
    return false;                           //Impostato come return di default della funzione per evitare 'avvertenze'/falle di ogni tipo
}

void GetBalancedNumbers(unsigned short &sV, unsigned short &eV, unsigned short bNums[arrayBufferSize], unsigned short &bNumsCount, bool &bNumsN_A)
{
    unsigned short tempNum, lineController = 0;
    short tempDigits[maxDigits];
    bool isBalanced;

    if (bNumsN_A) {                     //Esegue il calcolo dei numeri equilibrati SOLO se non sono già stati ottenuti in precedenza (tenendo in conto dei valori di intervallo)
        
        bNumsCount = 0;

        for (unsigned short treatedNum = sV; treatedNum <= eV; treatedNum++) {      //I valori dell'intervallo vengono usati nelle condizioni del for
            tempNum = treatedNum;

            GetDigits(tempNum, tempDigits);
            isBalanced = GetBalancedCondition(tempDigits);

            if (isBalanced) {
                bNums[bNumsCount] = treatedNum;
                bNumsCount++;
            }
        }

        bNumsN_A = false;
    }

    cout << "| Numeri equilibrati presenti nell\'intervallo [" << sV << "; " << eV << "] |" << endl << endl;
    for (int i = 0; i < bNumsCount; i++) {
        cout << bNums[i] << " ";
        lineController++;
        if (lineController == 10) {             //Gestione della stampa per rappresentare a schermo in modo 'ordinato' i numeri equilibrati
            cout << endl;
            lineController = 0;
        }
    }
    cout << endl << endl;
}

void GoalOfTheApp()
{
    //Spiegazione della scopo del programma

    cout << "Che cosa sono i \"Numeri equilibrati\"?" << endl << endl;
    cout << "| Definizione |" << endl;
    cout << "Un numero viene definito come \"equilibrato\" quando rispetta la seguente condizione:" << endl;
    cout << "   (Somma cifre dispari) = (Somma cifre pari)  " << endl;
    cout << "| Esempi |" << endl;
    cout << "   1223 -> (1 + 3) = (2 + 2) -> 4 = 4 -> Numero equilibrato" << endl;
    cout << "   73 -> (7 + 3) = (0) -> 10 = 0 -> Numero non equilibrato" << endl << endl;
}