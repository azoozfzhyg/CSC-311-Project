#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *ToMatchWith;
FILE *OpenFile(char filename[]);

int bruteForceStringMatch(char *pattern, int Filesize, char filename[]);

int main() {
    int i;
    int Filesize = 0;
    char filename[] = "Test.Doc#000.txt";
    char pattern[] = "sample";
    for(i = 0 ; i< 100; i++){
            Filesize += 100;
            filename[10] = '0' + i%10;
            filename[9] = '0' + (i/10);
            filename[8] = '0' + (i/100);
        int index = bruteForceStringMatch( pattern, Filesize, filename);
        if (index == -1) {
            printf("Pattern not found in iteration i\n", i);
        } else {
            printf("Pattern found at index %d, in iteration i\n", index, i);
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
            if (fgetc(filename) != pattern[j]) {
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

