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
Array *search_word(Tags const *tags, char const *word);
char *str_text_for_search_word(Tags const *tags, char const *word);


#endif //CPROJECT_SEARCH_WORD_H
