#include "holberton.h"
#include "alias.h"  // Include the header file where Alias type is defined
#include <string.h>

static Alias *alias_list = NULL;

void displayAliases() {
    Alias *current = alias_list;

    while (current != NULL) {
        printf("%s='%s'\n", current->name, current->value);
        current = current->next;
    }
}

Alias *findAlias(const char *name) {
    Alias *current = alias_list;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

void setAlias(const char *arguments) {
    char *name;
    char *value;

    name = strtok(arguments, "=");
    value = strtok(NULL, "=");

    if (name == NULL || value == NULL) {
        printf("Usage: alias name='value'\n");
        return;
    }

    Alias *existingAlias = findAlias(name);
    if (existingAlias != NULL) {
        // Update existing alias
        strcpy(existingAlias->value, value);
    } else {
        // Create a new alias
        Alias *newAlias = (Alias *)malloc(sizeof(Alias));
        if (newAlias != NULL) {
            strcpy(newAlias->name, name);
            strcpy(newAlias->value, value);
            newAlias->next = alias_list;
            alias_list = newAlias;
        }
    }
}

void freeAliases() {
    Alias *current = alias_list;
    Alias *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    alias_list = NULL;
}