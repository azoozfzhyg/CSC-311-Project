#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void computeLPSArray(char *pat, int M, int *lps) {
    int len = 0;
    lps[0] = 0;

    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0)
                len = lps[len - 1];
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void KMPSearch(char *pat, FILE *fp) {
    int M = strlen(pat);
    int lps[M];

    computeLPSArray(pat, M, lps);

    int q = 0; // index for pat[]
    char txt[M + 1]; // Buffer to hold text of length equal to the pattern (+1 for null terminator)
    int readBytes;

    while ((readBytes = fread(txt + q, 1, M - q, fp)) > 0) {
        txt[M] = '\0'; // Null terminate the text buffer
        int N = strlen(txt);
        
        int i = 0; // index for txt[]
        while (i < N) {
            if (pat[q] == txt[i]) {
                q++;
                i++;
            }
            if (q == M) {
                printf("Pattern found at index %d\n", i - q);
                q = lps[q - 1];
            } else if (i < N && pat[q] != txt[i]) {
                if (q != 0)
                    q = lps[q - 1];
                else
                    i++;
            }
        }

        // Update q for the next read
        q = M - lps[M - 1];
        if (q > 0)
            memcpy(txt, txt + N - q, q);
    }
}

int main() {
    char pattern[] = "pRK9Y28D"; // Pattern to search for
    FILE *file = fopen("TestDoc#099.txt", "r"); // Open the text file for reading
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    KMPSearch(pattern, file); // Call the KMP search function

    fclose(file); // Close the file
    return 0;
}
