#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_LINES 10
#define MAX_LINE_LENGTH 1024

void printLastNLines(char **lines, int n, int lineCount) {
    int start = lineCount < n ? 0 : lineCount % n;
    int totalLines = lineCount < n ? lineCount : n;

    for (int i = 0; i < totalLines; i++) {
        printf("%s", lines[(start + i) % n]);
    }
}

int main(int argc, char *argv[]) {
    int n = DEFAULT_LINES;

    if (argc == 2) {
        n = atoi(argv[1]);
        if (n <= 0) {
            fprintf(stderr, "Invalid number of lines: %s\n", argv[1]);
            return 1;
        }
    }

    // Dynamically allocate memory for lines
    char **lines = malloc(n * sizeof(char *));
    if (lines == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    int lineCount = 0;
    char buffer[MAX_LINE_LENGTH];

    while (fgets(buffer, sizeof(buffer), stdin)) {
        if (lineCount < n) {
            lines[lineCount] = strdup(buffer);
            if (lines[lineCount] == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                return 1;
            }
        } else {
            free(lines[lineCount % n]);
            lines[lineCount % n] = strdup(buffer);
            if (lines[lineCount % n] == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                return 1;
            }
        }
        lineCount++;
    }

    printLastNLines(lines, n, lineCount);

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        if (lines[i]) {
            free(lines[i]);
        }
    }
    free(lines);

    return 0;
}
