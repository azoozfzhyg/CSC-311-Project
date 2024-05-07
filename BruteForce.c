#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int bruteForceStringMatch(char *text, char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);

    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) {
                break;
            }
        }
        if (j == m) {
            // Pattern found at index i in the text
            return i;
        }
    }
    // Pattern not found in the text
    return -1;
}

int main() {
    int Filesize = 0;
    char filename[] = "Test.Doc#000.txt";
    char pattern[] = "sample";
    for(i = 0 ; i< 100; i++){
            Filesize += 100;
            filename[10] = '0' + i%10;
            filename[9] = '0' + (i/10);
            filename[8] = '0' + (i/100);
        int index = bruteForceStringMatch("", pattern);
        printf("Pattern found at index %d, in iteration i\n", index, i);
    }

    if (index != -1) {
        printf("Pattern found at index %d\n", index);
    } else {
        printf("Pattern not found\n");
    }

    return 0;
}
