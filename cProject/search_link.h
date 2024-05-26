#ifndef CPROJECT_SEARCH_LINK_H
#define CPROJECT_SEARCH_LINK_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "dict_of_words.h"
#include "dict_of_tags.h"
#include "search_word.h"
#include "search_tag.h"
#include "search_word_tags.h"

char* extract_link(const char* tag);
char *str_text_for_search_link(Tags const *tags, char const *domain, char const *search_tags_str);

#endif //CPROJECT_SEARCH_LINK_H
