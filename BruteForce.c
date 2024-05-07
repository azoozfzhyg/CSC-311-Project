#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *ToMatchIn;
FILE *OpenFile(char filename[]);

int bruteForceStringMatch(char *text, char *pattern, int Filesize, char filename[]);

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
        int index = bruteForceStringMatch("", pattern, Filesize, filename);
        if (index == -1) {
            printf("Pattern not found in iteration i\n", i);
        } else {
            printf("Pattern found at index %d, in iteration i\n", index, i);
        }
    }

    return 0;
}

FILE *OpenFile(char filename[]){
    ToMatchIn = fopen(filename, "r");
    if (ToMatchIn == NULL) {
        printf("Could not open file %s\n", filename);
        exit(1);
    }
    return ToMatchIn;
}

int bruteForceStringMatch(char *text, char *pattern, int Filesize, char filename[]) {
    int n = strlen(text);
    int m = Filesize;
    filename = OpenFile(filename);
    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if (text[i + j] != fgetc(filename)) {
                break;
            }
        }
        if (j == m) {
            // Pattern found at index i in the text
            fclose(ToMatchIn);
            return i;
        }
    }
    // Pattern not found in the text
    fclose(ToMatchIn);
    return -1;
}

