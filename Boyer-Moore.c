//working code
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

#define NO_OF_CHARS 256

FILE *ToMatchWith;

FILE *OpenFile(char filename[]);
int boyerMooreSearch(char *txt, char *pat);
int max(int a, int b);
void badCharHeuristic(char *str, int size, int badchar[NO_OF_CHARS]);






int main() {
    //you can change the pattern to any string you want to search for
    char pattern[] = "wEDo";
    /////////////////////////////////////////////////

    int i,Filesize = 0;
    struct timeval start, end;
    FILE *toMatchWtih;
    char *text = (char*) calloc(10001,sizeof(char));
    char filename[] = "TestDoc#000.txt";
    for (i = 0; i < 100; i++) {
        Filesize += 100;
        filename[10] = '0' + i%10;
        filename[9] = '0' + (i/10);
        filename[8] = '0' + (i/100);

        toMatchWtih = OpenFile(filename);

        fread(text,1,Filesize,toMatchWtih);
        
        gettimeofday(&start, NULL);

        int index = boyerMooreSearch(text, pattern);

        gettimeofday(&end, NULL);
        double time_taken;
        time_taken = (end.tv_sec - start.tv_sec) * 1e6;
        time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
        printf("%lf\n", time_taken);

        /*if (index == -1) {
            printf("Pattern not found in iteration %d\n", i);
        } else {
            printf("Pattern found at index %d, in iteration %d\n", index, i);
        }*/
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
            //s += (s + m < n) ? m - badchar[(int)txt[s + m]] : 1;
        } else {
            s += max(1, j - badchar[(int)txt[s + j]]);
        }
    }
    return -1;
}