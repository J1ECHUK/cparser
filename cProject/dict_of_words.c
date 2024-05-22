#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char *text;
    int count;
} Text;
typedef struct {
    Text **texts;
    int count;
} Multiple_text;
Text *init_text() {
    Text *result = malloc(sizeof(Text));
    result->count = 0;
    result->text = NULL;
    return result;
}
Multiple_text *init_multiple_text() {
    Multiple_text *result = malloc(sizeof(Multiple_text));
    result->count = 0;
    result->texts = NULL;
    return result;
}

void add_char_to_text(Text *text, char c) {
    text->count = (text->text) ? strlen(text->text) : 0;
    text->text = realloc(text->text, (text->count + 2) * sizeof(char));
    text->text[text->count] = c;
    text->text[text->count + 1] = '\0';
    text->count++;
}
void add_text_to_multiple_text(Multiple_text *multiple_text, Text *text) {
    multiple_text->texts = realloc(multiple_text->texts, (multiple_text->count + 1) * sizeof(Text));
    multiple_text->texts[multiple_text->count] = text;
    multiple_text->count++;
}
char *join_texts(Multiple_text *multiple_text, char *separator) {
    char *result = malloc(sizeof(char));
    result[0] = '\0';
    strcat(result, separator);
    for (int i = 0; i < multiple_text->count; i++) {
        strcat(result, multiple_text->texts[i]->text);
        strcat(result, separator);
    }
    return result;
}
bool is_str_in_multiple_text(Multiple_text *multiple_text, char* str) {
    for (int i = 0; i < multiple_text->count; i++) {
        if (!strcmp(str, multiple_text->texts[i]->text)) {
            return true;
        }
    }
    return false;
}

typedef struct {
    char *word;
    int count;
    int sentence;
    int paragraph;
} Word;
typedef struct {
    Word **words;
    char *tag;
    int count;
} Dict;
Word *init_word() {
    Word *result = malloc(sizeof(Word));
    result->count = 0;
    result->sentence = 0;
    result->paragraph = 0;
    result->word = NULL;
    return result;
}
Dict *init_dict() {
    Dict *result = malloc(sizeof(Word));
    result->count = 0;
    result->tag = NULL;
    result->words = NULL;
    return result;
}

void add_word_to_dict(Dict *dict, Word *word){
    dict->words = realloc(dict->words, (dict->count + 1) * sizeof(Word));
    dict->words[dict->count] = word;
    dict->count++;
}
void add_char_to_word(Word *word, char c) {
    word->count = (word->word) ? strlen(word->word) : 0;
    word->word = realloc(word->word, (word->count + 2) * sizeof(char));
    word->word[word->count] = c;
    word->word[word->count + 1] = '\0';
    word->count++;
}

int is_char(char c) {
    return (('a' <= c) && (c <= 'z')) ||
           (('A' <= c) && (c <= 'Z')) ||
           (('0' <= c) && (c <= '9'));
}

Dict *fill_dict(Text *text, char *tag) {
    Word *word = init_word();
    Dict *dict = init_dict();
    dict->tag = tag;
    int sentence = 0;
    int paragraph = 0;

    for (int i = 0; i < text->count; i++) {
        char c = text->text[i];
        if (is_char(c)) add_char_to_word(word, c);
        else {
            if (word->word != NULL) {
                word->sentence = sentence;
                word->paragraph = paragraph;
                add_word_to_dict(dict, word);
                word = init_word();
            }
            if (c == '.' || c == '!' || c == '?') {
                sentence++;
            }
            if (c == '\n') {
                paragraph++;
            }
        }
    }
    if (word->word != NULL) {
        word->sentence = sentence;
        word->paragraph = paragraph;
        add_word_to_dict(dict, word);
    }

    return dict;
}
void print_dict(Dict *dict) {
    printf("      Tag name: %s\n      Words: {", dict->tag);
    for (int i = 0; i < dict->count; i++) {
        if (i+1 == dict->count) printf("%s", dict->words[i]->word);
        else printf("%s; ", dict->words[i]->word);
    }
    printf("}\n");
}
