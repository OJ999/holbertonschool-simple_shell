#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALIAS_MAX 50
#define COMMAND_MAX 100

typedef struct {
    char name[50];
    char value[50];
} Alias;

Alias aliases[ALIAS_MAX];
int aliasCount = 0;

void displayAliases() {
    for (int i = 0; i < aliasCount; i++) {
        printf("%s='%s'\n", aliases[i].name, aliases[i].value);
    }
}

void setAlias(char *input) {
    char *name = strtok(input, "=");
    char *value = strtok(NULL, "");

    if (name != NULL && value != NULL && aliasCount < ALIAS_MAX) {
        strcpy(aliases[aliasCount].name, name);
        strcpy(aliases[aliasCount].value, value);
        aliasCount++;
    } else {
        fprintf(stderr, "Error: Invalid alias format\n");
    }
}

int main() {
    char command[COMMAND_MAX];

    while (1) {
        printf("$ ");
        if (fgets(command, COMMAND_MAX, stdin) == NULL) {
            break; // End of file (Ctrl+D)
        }

        // Remove newline character
        command[strcspn(command, "\n")] = '\0';

        if (strncmp(command, "alias", 5) == 0) {
            char *arguments = command + 5;
            if (strlen(arguments) > 0) {
                setAlias(arguments);
            } else {
                displayAliases();
            }
        } else {
            // Handle other commands
            printf("Executing: %s\n", command);
        }
    }

    return 0;
}
