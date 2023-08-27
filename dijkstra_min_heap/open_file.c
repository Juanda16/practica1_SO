#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int SIZE = 25;

void removeChar(char *str, char charToRemove);
void getEntry(char *str);

int main(int argc, char *argv[])
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(argv[1], "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    int line_number = 0;

    while ((read = getline(&line, &len, fp)) != -1)
    {
        if (line_number > 0)
        {

            char *entry;
            int i = 0;
            char *key;
            char *value;
            char *delimiter = "]";
            char comma = ',';
            char *colon = ":";

            removeChar(line, ' ');

            while ((entry = strtok_r(line, delimiter, &line)))
            {
                removeChar(entry, '[');

                if (entry[0] == comma)
                {
                    entry++;
                }

            
                key = strtok_r(entry, colon, &entry);
                printf("key: %s\n", key);
                value = entry;
                printf("value: %s\n", value);
            }
        }
        ++line_number;
    }

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}

void removeChar(char *str, char charToRemove)
{
    // To keep track of non-space character count
    int count = 0;
    // Traverse the provided string. If the current character is not a space,
    // move it to index 'count++'.
    for (int i = 0; str[i]; i++)
        if (str[i] != charToRemove)
            str[count++] = str[i]; // here count is incremented
    str[count] = '\0';
}

void getEntry(char *str)
{
    char *entry;
}