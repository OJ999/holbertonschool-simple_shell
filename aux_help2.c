#include "holberton.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Assume _strlen() and other necessary functions are implemented */

/* Structure to store aliases */
typedef struct Alias {
    char *name;
    char *value;
} Alias;

/* Function to print aliases */
void print_aliases(Alias *aliases, int count) {
    int i;

    for (i = 0; i < count; i++) {
        printf("%s='%s'\n", aliases[i].name, aliases[i].value);
    }
}

/* Function to find an alias by name */
int find_alias_index(Alias *aliases, int count, const char *name) {
    int i;

    for (i = 0; i < count; i++) {
        if (strcmp(aliases[i].name, name) == 0) {
            return i;
        }
    }

    return -1;
}

/* Function to add or update an alias */
void add_alias(Alias **aliases, int *count, const char *name, const char *value) {
    int index = find_alias_index(*aliases, *count, name);

    if (index != -1) {
        /* Update existing alias */
        free((*aliases)[index].value);
        (*aliases)[index].value = strdup(value);
    } else {
        /* Add new alias */
        (*count)++;
        *aliases = realloc(*aliases, (*count) * sizeof(Alias));
        (*aliases)[*count - 1].name = strdup(name);
        (*aliases)[*count - 1].value = strdup(value);
    }
}

/* Function to handle the 'alias' command */
void handle_alias(char *args) {
    char *token;
    char *saveptr;
    int count = 0;
    Alias *aliases = NULL;
    char *equal_sign;  /* Move this declaration outside the loop */

    token = strtok_r(args, " \t\n", &saveptr);

    equal_sign = NULL;  /* Initialize outside the loop */

    while (token != NULL) {
        if (strcmp(token, "alias") == 0) {
            /* Skip the initial 'alias' keyword */
            token = strtok_r(NULL, " \t\n", &saveptr);
            continue;
        }

        /* Check if the token contains '=' */
        equal_sign = strchr(token, '=');  /* Move this inside the loop */

        if (equal_sign != NULL) {
            /* Token is in the form 'name=value' */
            *equal_sign = '\0';
            add_alias(&aliases, &count, token, equal_sign + 1);
        } else {
            /* Token is just an alias name */
            int index = find_alias_index(aliases, count, token);
            if (index != -1) {
                printf("%s='%s'\n", aliases[index].name, aliases[index].value);
            }
        }

        token = strtok_r(NULL, " \t\n", &saveptr);
    }

    /* Print all aliases if no specific aliases were requested */
    if (count > 0 && aliases != NULL) {
        print_aliases(aliases, count);
    }

    /* Free allocated memory */
    for (i = 0; i < count; i++) {
        free(aliases[i].name);
        free(aliases[i].value);
    }
    free(aliases);
}

/* Rest of your code (aux_help(), aux_help_alias(), aux_help_cd(), etc.) */

int main(void) {
    /* Your main function logic */
    return 0;
}
