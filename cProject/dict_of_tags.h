#ifndef CPROJECT_DICT_OF_TAGS_H
#define CPROJECT_DICT_OF_TAGS_H

typedef struct {
    Dict **dicts;
    Text **texts;
    int count;
} Tags;
Tags *init_tags();

void add_text_to_tags(Tags *tags, Text *text, Dict *dict);

bool skip_tag(char *c, FILE *file, Text *tag_name);
bool check_empty_text(Text *text);

Tags *fill_tags(FILE *file);
void print_tags(Tags *tags);

#endif //CPROJECT_DICT_OF_TAGS_H
