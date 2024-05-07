#include <stdio.h>
#include <string.h>

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

void KMPSearch(char *text, char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);

    int lps[m];
    computeLPSArray(pattern, m, lps);

    int i = 0;  // index for text[]
    int j = 0;  // index for pattern[]

    while (i < n) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }

        if (j == m) {
            printf("Pattern found at index %d\n", i - j);
            return;
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
}

int main() {
    char text[] = "ABABDABACDABABCABAB";
    char pattern[] = "ABAB";
    
    KMPSearch(text, pattern);
    
    return 0;
}
