#include <stdio.h>
#include <string.h>

#define NO_OF_CHARS 256

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

void boyerMooreSearch(char *pat, FILE *fp) {
    int m = strlen(pat);
    int badchar[NO_OF_CHARS];

    badCharHeuristic(pat, m, badchar);

    int s = 0;
    int shift = 0;
    char txt[m + 1]; // Buffer to hold text of length equal to the pattern (+1 for null terminator)
    int readBytes;

    while ((readBytes = fread(txt + shift, 1, m - shift, fp)) > 0) {
        txt[m] = '\0'; // Null terminate the text buffer
        int n = strlen(txt);
        
        s = 0;
        while (s <= (n - m)) {
            int j = m - 1;

            while (j >= 0 && pat[j] == txt[s + j])
                j--;

            if (j < 0) {
                printf("Pattern occurs at index %d \n", s);
                s += (s + m < n) ? m - badchar[txt[s + m]] : 1;
            } else {
                s += max(1, j - badchar[txt[s + j]]);
            }
        }

        // Update shift for the next read
        shift = m - s;
        if (shift > 0)
            memcpy(txt, txt + s, shift);
    }
}

int main() {
    char pattern[] = "pattern"; // Pattern to search for
    FILE *file = fopen("example.txt", "r"); // Open the text file for reading
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    boyerMooreSearch(pattern, file); // Call the Boyer-Moore search function

    fclose(file); // Close the file
    return 0;
}
