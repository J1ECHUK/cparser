#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "dict_of_words.h"
#include "dict_of_tags.h"
#include "search_word.h"



int main() {
    char *filename = "html.txt";
    char *search_word = "HTML";
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error while open file\n");
        return 0;
    }
    Tags *tags = fill_tags(file);
    //print_tags(tags);
    fclose(file);
    printf("Text for searched word:\n %s\n\n\n", str_text_for_search_word(tags, search_word));
    return 0;
}
