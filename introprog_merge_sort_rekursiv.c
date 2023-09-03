#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "introprog_input_merge_sort.h"

/*
 * Diese Funktion fügt zwei bereits sortierte Arrays zu einem
 * sortierten Array zusammen
 *
 * array : Pointer auf das Array
 * first : Index des ersten Elements (Beginn) des (Teil-)Array
 * middle: Index des mittleren Elements des (Teil-)Array
 * last  : Index des letzten Elements(Ende) des (Teil-)Array
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


/* 
  int temp_length = last - middle + 1;
  int* temp_array = calloc(temp_length, sizeof(int));

  int i = first;                                                  // indexing left half
  int j = middle + 1;                                             // indexing right half
  int k = 1;                                                      // indexing sorted part

  while ((i < temp_length) && (j <= last)) {
    if(temp_array[i] <= array[j]){
      array[k++] = temp_array[i++];
    } else{
      array[k++] = array[j++];
    }
  }
  while (i < temp_length) {
    array[k++] = temp_array[i++];
  }

  free(temp_array);
  

  int temp_length = last - first + 1;
  int* temp_array = calloc(temp_length, sizeof(int));  // int* temp_array = malloc(temp_length * sizeof(int));

  int i = first;
  int j = middle + 1;
  int k = 1;
  while ((i <= middle) && (j <= last)) {
    if(array[i] <= array[j]){
      temp_array[k++] = array[i++];
    } else{
      temp_array[k++] = array[j++];
    }
  }
  while (i <= middle) {                                            
    temp_array[k++] = array[i++];
  }
  while (j <= last) {
    temp_array[k++] = array[j++];
  }
  for (int m = first; m < temp_length; m++) {
    array[m + first] = temp_array[m];
  }

  free(temp_array);*/
}

/*
 * Diese Funktion implementiert den rekursiven Mergesort
 * Algorithmus auf einem Array. Sie soll analog zum Pseudocode
 * implementiert werden.
 *
 * array: Pointer auf das Array
 * first: Index des ersten Elements des (Teil-)Array
 * last:  Index des letzten Elements des (Teil-)Array
 */
void merge_sort(int* array, int first, int last) {
  if((last - first) < 1){
    return;
  }
  int middle = (first + last) / 2;
  merge_sort(array, first, middle);
  merge_sort(array, middle + 1, last);
  merge(array, first, middle, last);
}

/*
 * Hauptprogramm.
 *
 * Liest Integerwerte aus einer Datei und gibt diese sortiert im
 * selben Format über die Standardausgabe wieder aus.
 *
 * Aufruf: ./introprog_merge_sort_rekursiv <maximale anzahl> \
 *         <dateipfad>
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

    merge_sort(array, 0, len - 1); // HIER Aufruf von "merge_sort()"

    printf("Sortiert:\n");
    print_array(array, len);

    free(array);

    return 0;
}
