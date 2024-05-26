#ifndef CPROJECT_SEARCH_WORD_H
#define CPROJECT_SEARCH_WORD_H

#include <stdlib.h>
#include <string.h>

#include "dict_of_words.h"
#include "dict_of_tags.h"

typedef struct {
    int *array;
    int count;
} Array;

Array *init_array();
void add_int_to_array(Array *array, int num);
void array_reverse(Array *arr);
Array *search_word(Tags const *tags, char const *search_words_str);
char *str_text_for_search_word(Tags const *tags, char const *search_words);
Multiple_text *fill_search_words_multiple_text(char const *search_words);

#endif //CPROJECT_SEARCH_WORD_H
