/*
  Progetto: IlCalendario;
  Descrizione: lo scopo del software e' quello di stampare a video il calendario dell'anno inserito in input dall'utente;
  Cognome Nome: Carlino Giuseppe;
  Data: 01/07/2024.

  Dizionario dati:

  -------------------------------------------------------------------------------------------------------------------------------
  |Nome costante      |     Tipo      |     Utilizzo    |      Descrizione                                                      |
  -------------------------------------------------------------------------------------------------------------------------------
  |NOME_MESI[12][10]  |     Stringa   |     Lavoro      |      Matrice contenente il nome di tutti i mesi dell'anno.            |
  |MAX_GIORNI_MESI[12]|     Intero    |     Lavoro      |      Vettore contenente il numero di giorni di tutti i mesi dell'anno.|
  -------------------------------------------------------------------------------------------------------------------------------

  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  |Nome variabile|     Tipo      |     Utilizzo    |      Descrizione                                                                                                                            |
  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  |anno_scelto   |     Intero    |  Input/Output   |      Anno di cui l'utente desidera visualizzare il calendario.                                                                              |
  |anno_rif      |     Intero    |     Lavoro      |      Anno da prendere come riferimento per la costruzione del calendario dell'anno anno_scelto.                                             |
  |dif_anni      |     Intero    |     Lavoro      |      Differenza di anni tra anno_rif e anno_scelto.                                                                                         |
  |primo_giorno  |     Intero    |     Lavoro      |      Primo giorno di ogni mese dell'anno.                                                                                                   |
  |mese          |     Intero    |     Output      |      Indice delle righe della matrice NOME_MESI[12][10]. Indica il mese da stampare a video.                                                |
  |vuoto         |     Intero    |     Lavoro      |      Indica i vuoti che ci sono prima del primo giorno di ogni mese dell'anno.                                                              |
  |giorno        |     Intero    |     Output      |      Indica il giorno di quel mese da stampare a video. Si prolunga fino al valore numerico all'indice mese del vettore MAX_GIORNI_MESI[12].|
  |flag_bisestile|     Intero    |     Lavoro      |      Flag utile a verificare se un anno e' bisestile o no.                                                                                  |
  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/


// Inclusione librerie utilizzate
#include <stdio.h> // Includere la libreria standard STANDARD INPUT/OUTPUT


// Dichiarazione ed implementazione costanti
const char NOME_MESI[12][10] = {"Gennaio", "Febbraio", "Marzo", "Aprile", "Maggio", "Giugno", "Luglio", "Agosto", "Settembre", "Ottobre", "Novembre", "Dicembre"}; // Nome dei 12 mesi dell'anno
const int MAX_GIORNI_MESI[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // Numero massimo di giorni di ogni mese dell'anno (ad eccezione di febbraio, che non e' sempre costituito da 29 giorni)


// Dichiarazione prototipi di funzioni e/o procedure
int primo_giorno_inizio(int);
int primo_giorno_fine(int);
int controllo_bisestile(int);
void calcolo_primo_giorno(int);
void stampa_calendario(int, int);


int main() {

    // Dichiarazione variabili
    int anno_scelto;

    // Titolo del software
    printf("++++++++++++++++++++++++++++++++++++IlCalendario++++++++++++++++++++++++++++++++++++\n\n");

    // Istruzioni finalizzate a garantire il corretto utilizzo del software
    printf("Lo scopo del software e' quello di stampare a video il calendario dell'anno inserito in input dall'utente.\n\n\n");

    // Inserimento dell'anno di cui si vuole conoscere il calendario
    do {
        printf("Inserire l'anno di cui si vuole conoscere il calendario (min: 1582; max: 9999): ");
        scanf("%d", &anno_scelto);

        if (anno_scelto < 1582 || anno_scelto > 9999)
            printf("Attenzione! Rispettare l'intervallo indicato.\n\n");
    } while (anno_scelto < 1582 || anno_scelto > 9999);

    // Calcolo del primo giorno dell'anno scelto (L, M, M, G, V, S o D)
    calcolo_primo_giorno(anno_scelto);

    // Mettere in pausa il software alla fine della sua esecuzione
    printf("Premere un tasto per continuare . . .");
    getchar();
    getchar();

    // Chiudere la funzione main
    return 0;
}


// Funzione finalizzata a riportare a 1 il valore di primo_giorno se questo supera il valore 7
int primo_giorno_inizio(int pprimo_giorno) {

    // Reset di primo_giorno a 1
    if (pprimo_giorno > 7)
        return 1;

    // Nessun reset
    else
        return pprimo_giorno;
}

// Funzione finalizzata a riportare a 7 il valore di primo_giorno se questo scende sotto il valore 1
int primo_giorno_fine(int pprimo_giorno) {

    // Reset di primo_giorno a 7
    if (pprimo_giorno < 1)
        return 7;

    // Nessun reset
    else
        return pprimo_giorno;
}

// Funzione finalizzata a verificare se un anno e' bisestile o no
int controllo_bisestile(int panno) {

    // Anno secolare
    if (panno % 100 == 0) {
        if (panno % 4 == 0 && panno % 400 == 0)
            return 1;
        else
            return 0;

    // Anno non secolare
    } else if (panno % 4 == 0) {
        return 1;

    // Anno non bisestile
    } else {
        return 0;
    }
}

// Procedura finalizzata a calcolare il primo giorno dell'anno scelto
void calcolo_primo_giorno(int panno_scelto) {

    // Dichiarazione (ed implementazione) variabili
    int anno_rif = 4210, dif_anni, primo_giorno = 1, flag_bisestile;

    // Calcolo della differenza di anni tra anno_rif e panno_scelto
    dif_anni = anno_rif - panno_scelto;

    // Se la differenza e' maggiore di 0...
    if (dif_anni > 0) {

        // Scorrere anno_rif all'indietro fino ad anno_scelto
        for (anno_rif = 4210; anno_rif > panno_scelto; anno_rif--) {

            // Decrementare di 1 primo_giorno
            primo_giorno--;

            // Verificare che primo_giorno sia sceso sotto il valore di 1
            primo_giorno = primo_giorno_fine(primo_giorno);

            // Verificare che l'anno indicato da anno_rif - 1 sia bisestile o no
            flag_bisestile = controllo_bisestile(anno_rif - 1);

            if (flag_bisestile) {

                // Decrementare ancora di 1 primo_giorno se anno_rif - 1 e' bisestile
                primo_giorno--;

                // Quindi verificare di nuovo che primo_giorno sia sceso sotto il valore di 1
                primo_giorno = primo_giorno_fine(primo_giorno);
            }
        }
    } else {

        // Se la differenza e' minore di 0...
        if (dif_anni < 0) {

            // Scorrere anno_rif in avanti fino ad anno_scelto
            for (anno_rif = 4210; anno_rif < panno_scelto; anno_rif++) {

                // Incrementare di 1 primo_giorno
                primo_giorno++;

                // Verificare che primo_giorno abbia superato il valore 7
                primo_giorno = primo_giorno_inizio(primo_giorno);

                // Verificare che l'anno indicato da anno_rif sia bisestile o no
                flag_bisestile = controllo_bisestile(anno_rif);

                if (flag_bisestile) {

                    // Incrementare ancora di 1 primo_giorno se anno_rif e' bisestile
                    primo_giorno++;

                    // Quindi verificare di nuovo che primo_giorno abbia superato il valore 7
                    primo_giorno = primo_giorno_inizio(primo_giorno);
                }
            }
        }
    }

    printf("\n\n");

    // Stampa del calendario relativo all'anno scelto
    stampa_calendario(panno_scelto, primo_giorno);
}

// Procedura finalizzata a stampare il calendario dell'anno scelto
void stampa_calendario(int panno_scelto, int pprimo_giorno) {

    // Dichiarazione variabili
    int mese, vuoto, giorno, flag_bisestile;

    // Verificare che l'anno scelto sia bisestile o no
    flag_bisestile = controllo_bisestile(panno_scelto);

    // Stampa dell'anno scelto
    printf("\a**************%d**************\n", panno_scelto);

    // Stampa dei mesi dell'anno
    for (mese = 0; mese < 12; mese++) {

        // Stampa di una barra separatoria per ognuno dei mesi dell'anno
        printf("\n--------------------------------\n");

        // Stampa del nome del mese e della riga indicante i giorni della settimana
        printf("            %s\n", NOME_MESI[mese]);
        printf("L    M    M    G    V    S    D\n");

        // Verificare che primo_giorno abbia superato il valore 7
        pprimo_giorno = primo_giorno_inizio(pprimo_giorno);

        // Stampa dei vuoti presenti prima del primo giorno del mese
        for (vuoto = 1; vuoto < pprimo_giorno; vuoto++)
            printf("     ");

        // Stampa dei giorni del mese
        for (giorno = 1; giorno <= MAX_GIORNI_MESI[mese]; giorno++) {

            // Se passa una settimana...
            if (pprimo_giorno > 7) {

                // Andare a capo ad ogni settimana passata
                // Se capita il giorno 29 di febbraio, farlo solo se l'anno associato e' bisestile
                if (giorno == 29 && mese == 1) {
                    if (flag_bisestile)
                        printf("\n");
                } else {
                    printf("\n");
                }

                // Reset di primo_giorno a 1
                pprimo_giorno = 1;
            }

            // Incrementare di 1 primo_giorno
            pprimo_giorno++;

            // Se il giorno e' costituito da una cifra...
            if (giorno < 10) {

                // Stampare il giorno ed uno spazio in piu'
                printf("%d    ", giorno);

            // Se cosi' non e'...
            } else {

                // Se capita il giorno 29 di febbraio...
                if (giorno == 29 && mese == 1) {

                    // Stampare il suddetto giorno solo se l'anno e' bisestile
                    if (flag_bisestile) {
                        printf("%d", giorno);

                    // In caso contrario...
                    } else {

                        // Decrementare di 1 primo_giorno
                        pprimo_giorno--;

                        // Verificare che primo_giorno sia sceso sotto il valore di 1
                        pprimo_giorno = primo_giorno_fine(pprimo_giorno);
                    }

                // Altrimenti...
                } else {

                    // Stampa di un giorno del mese
                    printf("%d   ", giorno);
                }
            }
        }
    }

    // Stampa dell'ultima barra separatoria del calendario
    printf("\n--------------------------------\n\n\n");
}