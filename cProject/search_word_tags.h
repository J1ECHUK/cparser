#ifndef CPROJECT_SEARCH_WORD_TAG_H
#define CPROJECT_SEARCH_WORD_TAG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "dict_of_words.h"
#include "dict_of_tags.h"
#include "search_word.h"
#include "search_tag.h"

bool is_int_in_array(Array *arr, int n);
char *str_text_for_search_word_tag(Tags const *tags, char const *search_tags_str, char const *search_words_str);


#endif //CPROJECT_SEARCH_WORD_TAG_H
