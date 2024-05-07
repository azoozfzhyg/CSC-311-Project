#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

FILE *ToMatchWith;
FILE *OpenFile(char filename[]);

void computeLPSArray(char *pattern, int m, int *lps);

int KMPSearch(char filename[],int Filesize, char *pattern) {
    int n = Filesize;
    int m = strlen(pattern);

    ToMatchWith = OpenFile(filename);

    int lps[m];
    computeLPSArray(pattern, m, lps);

    int i = 0;  // index for text[]
    int j = 0;  // index for pattern[]

    while (i < n) {
        if (pattern[j] == fgetc(ToMatchWith)) {
            j++;
            i++;
        }
        if (j == m) {
            fclose(ToMatchWith);
            return (i - j);
        } else if (i < n && pattern[j] != fgetc(ToMatchWith)) {
            if (j != 0){
                j = lps[j - 1];
                fseek(ToMatchWith, -2, SEEK_CUR);
            }
            else
                i++;
        }
    }
}

int main() {
    char pattern[] = "4H7#'.1.844XE3jJcb5W-fN'.Xve!WLh#qn!pUzBfHmZ3G-Po4mnM4dEfpQAM48d23lkx9OMZBwRuCMwk'R5v26toxPYB2EHuYWsCtTOeUc!lHHowxHgMn4buMIYsVP1";
    char filename[] = "TestDoc#000.txt";
    int i;
    int Filesize = 0;
    for(i = 0 ; i< 100; i++){
        Filesize += 100;
        filename[10] = '0' + i%10;
        filename[9] = '0' + (i/10);
        filename[8] = '0' + (i/100);
        clock_t start_time = clock();

        int index = KMPSearch(filename,Filesize, pattern);
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

void computeLPSArray(char *pattern, int m, int *lps) {
    int len = 0;  // Length of the previous longest prefix suffix

    lps[0] = 0;  // lps[0] is always 0

    int i = 1;
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}
