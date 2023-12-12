#ifndef ALIAS_H
#define ALIAS_H

#define MAX_NAME_LENGTH 128
#define MAX_VALUE_LENGTH 256

typedef struct Alias {
    char name[MAX_NAME_LENGTH];
    char value[MAX_VALUE_LENGTH];
    struct Alias *next;
} Alias;

#endif /* ALIAS_H */
