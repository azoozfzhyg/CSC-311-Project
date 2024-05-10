#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define NO_OF_CHARS 69

FILE *ToMatchWith;

FILE *OpenFile(char filename[]);
int boyerMooreSearch(char *txt, char *pat);
int max(int a, int b);
void badCharHeuristic(char *str, int size, int badchar[NO_OF_CHARS]);






int main() {
    char pattern[] = "QbY";
    int i,Filesize = 0;
    FILE *toMatchWtih;
    char *text = (char*) calloc(10001,sizeof(char));
    char filename[] = "TestDoc#000.txt";
    for (i = 0; i < 10000; i++) {
        Filesize += 100;
        filename[10] = '0' + i%10;
        filename[9] = '0' + (i/10);
        filename[8] = '0' + (i/100);

        toMatchWtih = OpenFile(filename);

        fread(text,1,10000,toMatchWtih);

        clock_t start_time = clock();
        int index = boyerMooreSearch(text, pattern);
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

int max(int a, int b) {
    return (a > b) ? a : b;
}

void badCharHeuristic(char *str, int size, int badchar[NO_OF_CHARS]) {
    int i;

    for (i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;

    for (i = 0; i < size; i++)
        badchar[(int) str[i]] = i;
}

int boyerMooreSearch(char *txt, char *pat) {
    int m = strlen(pat);
    int n = strlen(txt);

    int badchar[NO_OF_CHARS];

    badCharHeuristic(pat, m, badchar);

    int s = 0;
    while (s <= (n - m)) {
        int j = m - 1;

        while (j >= 0 && pat[j] == txt[s + j])
            j--;

        if (j < 0) {
            return s;
            s += (s + m < n) ? m - badchar[txt[s + m]] : 1;
        } else {
            s += max(1, j - badchar[txt[s + j]]);
        }
    }
}