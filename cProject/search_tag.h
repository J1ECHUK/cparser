#ifndef CPROJECT_SEARCH_TAG_H
#define CPROJECT_SEARCH_TAG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "dict_of_words.h"
#include "dict_of_tags.h"
#include "search_word.h"

Multiple_text *fill_search_tags_multiple_text(char const *search_tags);
char *str_text_for_search_tags(Tags const *tags, char const *search_tags_str);


#endif //CPROJECT_SEARCH_TAG_H
