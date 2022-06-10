// Copyright 2022 UW Madison
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>





/**
 *
 * char* source_buffer - passed in buffer
 *
 * char* alpha_numeric_buffer - buffer with removed alpha-numeric characters 
 * 
 *
 * function to remove non alpha-numeric characters (excluding NULL char
 * and newline) 
 *
 * (E.g. 'A', 'Z', '1', '9', '0' '\0' '\n' are all valid, '#', '"', "'", 
 * '$' are not.)
 * 
 * 
 *
 */
void remove_non_AN_chars(char* source_buffer, char* alpha_numeric_buffer) {
    //  initialize starting index of new string to 0
    int new_string_index = 0;
    // for all characters in source buffer
    for (int i = 0; i <strlen(source_buffer); i++) {
        // add to new buffer if char is alpha-numeric or newline
        // Note: Do Not USE STRNCAT terrible time complexity
        if ((isalnum(source_buffer[i])) || source_buffer[i] == '\n') {
            alpha_numeric_buffer[new_string_index] = source_buffer[i];
            new_string_index++;
        }
    }
  //  add a NULL char at end
    alpha_numeric_buffer[new_string_index] = '\0';
}
/**
 *
 * Main method
 *
 * int argc - number of CLAs
 * char *argv[] - pointer to array containing CLAs
 */
int main(int argc, char *argv[]) {
    int option;  // initialize variable used to parse command line options

    FILE *fp = NULL;  // initialized file pointer, file to be opened

    // for all optional CLAs
    while ((option = getopt(argc, argv, "Vhf:")) != -1) {
        // switch statement given variable returned by getopt
        switch (option) {
            // optional command line argument -V, prints info about my-look
            case 'V':
                printf("my-look from CS537 Summer 2022\n");
                exit(0);  // successful exit

                // optional command line argument -h, prints man page of
        //  my-look
            case 'h':
                printf(
"my-look: display lines beginning with a certain string");

                exit(0);  // successful exit

                // optional command line argument -f <required file>, tells
                // what file to read from (rather than stdin

            case 'f':


                // file to read is at next CLA or optarg
                fp = fopen(optarg, "r");
                // fopen returns NULL on failure
                if (fp == NULL) {
                    printf("cannot open file\n");
                    exit(1);  // exit (failure)
                }
                break;
                // all other options are invalid
            default:
                printf("my-look: invalid command line\n");
                exit(1);  // exit (failure)
        }
    }

  if (optind != argc -1) {
  printf("invalid command\n");
  exit(1);
  }
    // if -f optional argument not given, read from stdin
    if (!fp) {
        fp = stdin;
    }
    // String to be matched (case insensitive)
    char *str_to_find = argv[argc - 1];

    // initialize buffer
    char buffer[256];




    // for each line of the file (or stdin), put that line in the buffer
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        // initialize the buffer that will have only non-alpha-numeric chars
    // (and newline)

        char alpha_numeric_buffer[256];
        remove_non_AN_chars(buffer, alpha_numeric_buffer);
        // if the returned alpha-numeric buffer contains string to be matched
    // at the start, print the original non-alpha-numeric buffer
        if ((strncasecmp(alpha_numeric_buffer,
        str_to_find, strlen(str_to_find)) == 0)) {
            printf("%s", buffer);
        }
    }
    // close the file.
    if (fclose(fp) != 0) {
        printf("Error while closing the file.\n");
        exit(1);  // exit (failure)
    }

    // successfully exit and return 0
    return 0;
}
