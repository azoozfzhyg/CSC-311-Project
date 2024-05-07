#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

FILE *ToMatchWith;
FILE *OpenFile(char filename[]);

int bruteForceStringMatch(char *pattern, int Filesize, char filename[]);

int main() {
    int i;
    int Filesize = 0;
    char filename[] = "TestDoc#000.txt";
    char pattern[] = "4H7#'.1.844XE3jJcb5W-fN'.Xve!WLh#qn!pUzBfHmZ3G-Po4mnM4dEfpQAM48d23lkx9OMZBwRuCMwk'R5v26toxPYB2EHuYWsCtTOeUc!lHHowxHgMn4buMIYsVP1";
    for(i = 0 ; i< 100; i++){
        Filesize += 100;
        filename[10] = '0' + i%10;
        filename[9] = '0' + (i/10);
        filename[8] = '0' + (i/100);
        clock_t start_time = clock();

        int index = bruteForceStringMatch( pattern, Filesize, filename);

        clock_t end_time = clock();
        double elapsed_time = ((double) (end_time - start_time));
        printf("Time taken for iteration %d: %f\n", i, elapsed_time);

        if (index == -1) {
            printf("Pattern not found in iteration %d\n", i);
        } else {
            printf("Pattern found at index %d, in iteration %d\n", index, i);
        }
    }

    return 0;
}

FILE *OpenFile(char filename[]){
    ToMatchWith = fopen(filename, "r");
    if (ToMatchWith == NULL) {
        printf("Could not open file %s\n", filename);
        exit(1);
    }
    return ToMatchWith;
}

int bruteForceStringMatch(char *pattern, int Filesize, char filename[]) {
    int n = Filesize;
    int m = strlen(pattern);
    ToMatchWith = OpenFile(filename);
    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if (fgetc(ToMatchWith) != pattern[j]) {
                break;
            }
        }
        if (j == m) {
            // Pattern found at index i in the text
            fclose(ToMatchWith);
            return i;
        }
    }
    // Pattern not found in the text
    fclose(ToMatchWith);
    return -1;
}

