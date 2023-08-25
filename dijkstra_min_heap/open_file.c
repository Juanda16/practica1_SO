#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const int SIZE = 150000;

int main (int argc, char *argv[]) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(argv[1], "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    int line_number = 0;

    while ((read = getline(&line, &len, fp)) != -1) {
        if (line_number > 0) {
            char *token;
            char *s = NULL;
            int i = 0;
            while ((token = strtok_r(line, ",", &line))) {
                switch (i) {
                    case 0:
                    printf("%s\n", token);
                        break;
                    case 1:
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                    case 4:
                        break;
                    case 5:
                        s = token;
                        while (*s != '\n') {
                            ++s;
                        }
                        *s = '\0';
                        break;
                }
                ++i;
            }
        }
        ++line_number;
    }

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}