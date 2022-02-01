#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "quicksort.h"



int main(){
  size_t MAX_LINE_LEN = 200;

  FILE* input_file = fopen("Eingabedaten_quicksort_unsortiert","r");

  // allocate buffer in which lines while be stored for parsing
  char* newline = (char*) malloc(MAX_LINE_LEN*sizeof(char));
  // stores lenght of read line
  int len;
  int pw_frequency = 0;
  // max passwort length will definitely be lower than max line length
  char* password = (char*) malloc(MAX_LINE_LEN*sizeof(char));

  
   /*
   * getline() reads an entire line from stream, storing the address
   * of the buffer containing the text into *lineptr.  The buffer is
   * null-terminated and includes the newline character, if one was
   * found. 
   * getline returns -1 when not succesful, otherwise lenth of string that was read
   */
  // read a line, but max MAX_LINE_LEN chars from input_file and store in newline
  // MAX_LINE_LEN has to be handed over as pointer to size_t value
  /*
  while((len=getline(&newline, &MAX_LINE_LEN, input_file))!= -1){


    // variables to store value in have to be handed over as pointers
    // char* password = malloc((len+1)*sizeof(char));
    sscanf(newline, "%d %c", &pw_frequency, password);
    printf("%d\n", pw_frequency);
    //free(password);
    puts(newline);


    
  } */

  while(fgets(newline, MAX_LINE_LEN, input_file) != NULL){
    sscanf(newline, "%s %d", password, &pw_frequency);
    printf("%s\n", password);
    printf("%d\n", pw_frequency);
    puts(newline);
  }

  free(password);
  free(newline);
  fclose(input_file);

  return 0;
}
