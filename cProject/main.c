#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "dict_of_words.h"
#include "dict_of_tags.h"
#include "search_word.h"
#include "search_tag.h"



int main() {
    char *filename = "html.txt";
    char *search_words = "OSINT osint";
    char *search_tags = "h1 h2 h3 p a";
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error while open file\n");
        return 0;
    }
    Tags *tags = fill_tags(file);
    //print_tags(tags);
    fclose(file);
    char *text_for_search_word = str_text_for_search_word(tags, search_words);
    //char *text_for_search_tags = str_text_for_search_tags(tags, search_tags);
    printf("Text for searched word: %s\n\n", text_for_search_word);
    //printf("Text for searched tags: %s\n\n", text_for_search_tags);
    return 0;
}
