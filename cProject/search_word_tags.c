#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "dict_of_words.h"
#include "dict_of_tags.h"
#include "search_word.h"
#include "search_tag.h"

bool is_int_in_array(Array *arr, int n) {
    for (int i = 0; i < arr->count; i++) {
        if (arr->array[i] == n) return true;
    }
    return false;
}

char *str_text_for_search_word_tag(Tags const *tags, char const *search_tags_str, char const *search_words_str) {
    Array *number_of_tags = search_word(tags, search_words_str);
    Multiple_text *search_tags = fill_search_tags_multiple_text(search_tags_str);
    Multiple_text *texts_for_search = init_multiple_text();

    for (int i = 0; i < tags->count; i++) {
        if (is_str_in_multiple_text(search_tags, tags->dicts[i]->tag) && is_int_in_array(number_of_tags, i)) {
            add_text_to_multiple_text(texts_for_search, tags->texts[i]);
        }
    }
    free(number_of_tags->array);
    return join_texts(texts_for_search, "\n\t");
}