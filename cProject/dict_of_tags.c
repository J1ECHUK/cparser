#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "dict_of_words.h"

typedef struct {
    Dict **dicts;
    Text **texts;
    int count;
} Tags;
Tags *init_tags() {
    Tags *result = malloc(sizeof(Tags));
    result->count = 0;
    result->dicts = NULL;
    result->texts = NULL;
    return result;
}

void add_text_to_tags(Tags *tags, Text *text, Dict *dict) {
    tags->texts = realloc(tags->texts, (tags->count + 1) * sizeof(Text));
    tags->texts[tags->count] = text;
    tags->dicts = realloc(tags->dicts, (tags->count + 1) * sizeof(Text));
    tags->dicts[tags->count] = dict;
    tags->count++;
}

bool skip_tag(char *c, FILE *file, Text *tag_name) {
    bool skip = false;
    if (*c == '<') {
        add_char_to_text(tag_name, '<');
        skip = true;
        while (true) {
            *c = getc(file);
            if (*c == '>') {
                break;
            }
            add_char_to_text(tag_name, *c);
        }
        add_char_to_text(tag_name, '>');
    }
    return skip;
}
bool check_empty_text(Text *text) {
    if (text->text == NULL) return false;
    for (int i = 0; i < text->count; i++) {
        if (text->text[i] != ' ' && text->text[i] != '\n') {
            return true;
        }
    }
    *text = *init_text();
    return false;
}

Tags *fill_tags(FILE *file) {
    Text *text = init_text();
    Tags *tags = init_tags();
    Text *last_tag_name = init_text();

    while (true) {
        Text *tag_name = init_text();
        if (feof(file)) {
            break;
        }
        char c = getc(file);
        if (skip_tag(&c, file, tag_name)) {
            //printf("c  %s  |  %s  c\n", tag_name->text, last_tag_name->text);
            if (check_empty_text(text)) {
                add_text_to_tags(tags, text, fill_dict(text, tag_name->text, last_tag_name->text));
                text = init_text();
            }
            last_tag_name = copy_text(last_tag_name, tag_name);
        }
        else add_char_to_text(text, c);
    }
    return tags;
}
void print_tags(Tags *tags) {
    for (int i = 0; i < tags->count; i++) {
        printf("Tag #%d:\n  Text: '%s'\n  Dict:\n", i+1, tags->texts[i]->text);
        print_dict(tags->dicts[i]);
        printf("\n\n\n");
    }
}

