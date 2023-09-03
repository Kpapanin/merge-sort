#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "introprog_input_merge_sort.h"

/*
 * Diese Funktion ermittelt den kleineren von zwei Eingaeparametern
 * und gibt diesen zurück, oder den ersten, wenn sie gleich sind
 *
 * x : Integer
 * y : Integer
 */
int min(int x, int y){
    if (x > y){
        return y;
    } else{
        return x;
    }
}
/*
 * Diese Funktion fügt zwei bereits sortierte Arrays zu einem
 * sortierten Array zusammen
 *
 * array : Pointer auf das Array
 * first : Index des ersten Elemements (Beginn) des (Teil-)Array
 * middle: Index des mittleren Elements des (Teil-)Array
 * last  : Index des Letzten Elements (Ende) des (Teil-)Array
 */
void merge(int* array, int first, int middle, int last) {
    int temp_length = last - first + 1;
    int* temp_array = calloc(temp_length, sizeof(int));  // int* temp_array = malloc(temp_length * sizeof(int));

    int k = first;                                      // Hilfsvariable fuer linke Seite
    int m = middle + 1;                                 //                    rechte Seite
    int i = 0;                                          // Laufvariable fuer gemerktes Array

    // Solange Eintraege in biden Seiten vorhanden sind
    while ((k <= middle) && (m <= last)) {
        if (array[k] <= array[m]){                        // Eintrag auf linker Seite kleiner oder gleich
            temp_array[i] = array[k];
            k++;
        } else{                                           // Eintrag auf recheter Seite kleiner
            temp_array[i] = array[m];
            m++;
        }
        i++;                                              // Erhoehen der Laufvariable des gemerkten Arrays
    }
    while (k <= middle) {                                // Kopiere linken "Rest"
      temp_array[i] = array[k];
      k++;
      i++;
    }
    while (m <= last) {                                  // Kopiere rechten "Rest"
        temp_array[i] = array[m];
        m++;
        i++;
    }
    int j = 0;                                          // Rueckkopieren der gemerkten Eintraege
    while (j < i) {
        array[first + j] = temp_array[j];                 // Hinweis: j ist mit 1 initialisiert
        j++;
    }
    free(temp_array);
}

/*
 * Diese Funktion implementiert den iterativen Mergesort
 * Algorithmus auf einem Array. Sie soll analog zum Pseudocode
 * implementiert werden.
 *
 * array:  Pointer auf das Array
 * last :  Index des letzten Elements
 */
void merge_sort(int* array, int last) { 

    int step = 1;
    int right = 0;
    int left = 0;
    int middle = 0;
    while (step <= last) {
        left = 0;
        while (left <= (last - step)) {
            middle = left + step - 1;
            middle = min(middle, last);
            right = left + 2*step - 1;
            right = min(right, last);
            merge(array, left, middle, right);
            left += 2*step;
        }
        step *= 2;
    }

/*
    int n = sizeof(array) / sizeof(array[0]);
    int middle = 0;
    int right = 0;
    int left = 0;
    int step = 1;
    
    while (step < n) {
        left = 0;
        while (left <= n - step) {
            middle = min(left + step - 1, n - 1);
            right = min(left + 2 * step - 1, n - 1);
            merge(array, left, middle, right);
            left += 2 * step;
        }
        step *= 2;
    }
*/
}


/*
 * Hauptprogramm.
 *
 * Liest Integerwerte aus einer Datei und gibt diese sortiert im
 * selben Format über die Standardausgabe wieder aus.
 *
 * Aufruf: ./introprog_merge_sort_iterativ <maximale anzahl> \
 * 	   <dateipfad>
 */
int main (int argc, char *argv[])
{
    if (argc!=3){
        printf ("usage: %s <maximale anzahl>  <dateipfad>\n", argv[0]);
        exit(2);
    }
    
    char *filename = argv[2];
    
    int* array = calloc(atoi(argv[1]), sizeof(int)); // Hier array initialisieren

    int len = read_array_from_file(array, atoi(argv[1]), filename);

    printf("Eingabe:\n");
    print_array(array, len);

    merge_sort(array, len - 1); // HIER Aufruf von "merge_sort()"

    printf("Sortiert:\n");
    print_array(array, len);

    free(array);

    return 0;
}