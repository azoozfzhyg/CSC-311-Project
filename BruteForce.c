//working code
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>


FILE *ToMatchWith;
FILE *OpenFile(char filename[]);

int bruteForceStringMatch(char *pattern, int Filesize, char filename[]);

int main() {
    int i;
    int Filesize = 0;
    char filename[] = "TestDoc#000.txt";
    //you can change the pattern to any string you want to search for
    char pattern[] = "wEDo";
    /////////////////////////////////////////////////
    struct timeval start, end;
    for(i = 0 ; i< 100; i++){
        Filesize += 100;
        filename[10] = '0' + i%10;
        filename[9] = '0' + (i/10);
        filename[8] = '0' + (i/100);
        
        gettimeofday(&start, NULL);

        int index = bruteForceStringMatch( pattern, Filesize, filename);

        gettimeofday(&end, NULL);
        double time_taken;
        time_taken = (end.tv_sec - start.tv_sec) * 1e6;
        time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
        printf("Time taken for iteration %d: %lf\n", i, time_taken);

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

