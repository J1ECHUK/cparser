#ifndef CPROJECT_DICT_OF_WORDS_H
#define CPROJECT_DICT_OF_WORDS_H

typedef struct {
    char *text;
    int count;
} Text;
typedef struct {
    Text *texts;
    int count;
} Multiple_text;
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

Text *init_text();
Multiple_text *init_multiple_text();
Word *init_word();
Dict *init_dict();

bool is_str_in_multiple_text(Multiple_text *multiple_text, char* str);
char *join_texts(Multiple_text *multiple_text, char *separator);
void add_char_to_text(Text *text, char c);
void add_text_to_multiple_text(Multiple_text *sentence, Text *text);
void add_word_to_dict(Dict *dict, Word *word);
void add_char_to_word(Word *word, char c);

int is_char(char c);

Dict *fill_dict(Text *text, char *tag);

void print_dict(Dict *dict);

#endif //CPROJECT_DICT_OF_WORDS_H
