#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "dict_of_words.h"
#include "dict_of_tags.h"
#include "search_word.h"

Multiple_text *fill_search_tags_multiple_text(char const *search_tags) {
    Multiple_text *search_tags_multiple = init_multiple_text();
    Text *search_tags_text = init_text();
    for (int i = 0; i < strlen(search_tags); i++) {
        add_char_to_text(search_tags_text, search_tags[i]);
    }
    Dict *search_tags_dict = fill_dict(search_tags_text, NULL, NULL);
    for (int j = 0; j < search_tags_dict->count; j++) {
        Text *temp_search_tag = init_text();
        add_char_to_text(temp_search_tag, '<');
        add_char_to_text(temp_search_tag, '/');
        for (int t = 0; t < search_tags_dict->words[j]->count; t++) {
            add_char_to_text(temp_search_tag, search_tags_dict->words[j]->word[t]);
        }
        add_char_to_text(temp_search_tag, '>');
        add_text_to_multiple_text(search_tags_multiple, temp_search_tag);
    }
    return search_tags_multiple;
}

char *str_text_for_search_tags(Tags const *tags, char const *search_tags_str) {
    Multiple_text *text_for_search_tags = init_multiple_text();
    Multiple_text *search_tags = fill_search_tags_multiple_text(search_tags_str);
    for (int i = 0; i < tags->count; i++) {
        if (is_str_in_multiple_text(search_tags, tags->dicts[i]->tag)) {
            add_text_to_multiple_text(text_for_search_tags, tags->texts[i]);
        }
    }
    return join_texts(text_for_search_tags, "\n\t");
}