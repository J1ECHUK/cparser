#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "dict_of_words.h"


Text *parseKeyValue(FILE *input_file, int *key) {
    char line[1000];
    Text *value = init_text();
    fgets(line, sizeof(line), input_file);

    if (strstr(line, "search_mode=")) {
        *key = 1;
        int start = strlen("search_mode=");
        int end = strcspn(line + start, "\n\r") + start;
        for (int i = start; i < end; i++) {
            add_char_to_text(value, line[i]);
        }
        return value;
    } else if (strstr(line, "search_words=")) {
        *key = 2;
        int start = strlen("search_words=");
        int end = strcspn(line + start, "\n\r") + start;
        for (int i = start; i < end; i++) {
            add_char_to_text(value, line[i]);
        }
        return value;
    } else if (strstr(line, "search_tags=")) {
        *key = 3;
        int start = strlen("search_tags=");
        int end = strcspn(line + start, "\n\r") + start;
        for (int i = start; i < end; i++) {
            add_char_to_text(value, line[i]);
        }
        return value;
    } else if (strstr(line, "search_domain=")) {
        *key = 4;
        int start = strlen("search_domain=");
        int end = strcspn(line + start, "\n\r") + start;
        for (int i = start; i < end; i++) {
            add_char_to_text(value, line[i]);
        }
        return value;
    } return init_text();
}
Text *loadSearchMode1() {
    FILE *input_file = fopen("selections.txt", "r");
    int key;
    Text *value = init_text();

    while (!feof(input_file)) {
        value = parseKeyValue(input_file, &key);

        if (key == 1) return value;
        value = init_text();
    }
    fclose(input_file);
    return init_text();
}
Text *loadSearchMode2() {
    FILE *input_file = fopen("selections.txt", "r");
    int key;
    Text *value = init_text();

    while (!feof(input_file)) {
        value = parseKeyValue(input_file, &key);

        if (key == 2) return value;
        value = init_text();
    }
    fclose(input_file);
    return init_text();
}
Text *loadSearchMode3() {
    FILE *input_file = fopen("selections.txt", "r");
    int key;
    Text *value = init_text();

    while (!feof(input_file)) {
        value = parseKeyValue(input_file, &key);

        if (key == 3) return value;
        value = init_text();
    }
    fclose(input_file);
    return init_text();
}
Text *loadSearchMode4() {
    FILE *input_file = fopen("selections.txt", "r");
    int key;
    Text *value = init_text();

    while (!feof(input_file)) {
        value = parseKeyValue(input_file, &key);

        if (key == 4) return value;
        value = init_text();
    }
    fclose(input_file);
    return init_text();
}