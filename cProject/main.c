#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <WinSock2.h>

#include "dict_of_words.h"
#include "dict_of_tags.h"
#include "search_word.h"
#include "search_tag.h"
#include "search_word_tags.h"
#include "search_link.h"
#include "parser_for_search.h"




int main() {
    char *filename = "C:\\Users\\New\\Downloads\\temp\\cProject\\html.txt";
    Text *search_mode = loadSearchMode1();
    Text *search_words = loadSearchMode2();
    Text *search_tags = loadSearchMode3();
    Text *search_domain = loadSearchMode4();
//    printf("! %s %s %s %s !", search_mode->text, search_words->text, search_tags->text, search_domain->text);


    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error while open file\n");
        return 0;
    }
    Tags *tags = fill_tags(file);
    fclose(file);



    char* result;
    char *final;
    FILE *output = fopen("C:\\Users\\New\\Downloads\\temp\\cProject\\output.txt", "w");
    if (!strcmp(search_mode->text, "1")) result = str_text_for_search_word(tags, search_words->text);

    if (!strcmp(search_mode->text, "2")) result = str_text_for_search_tags(tags, search_tags->text);

    if (!strcmp(search_mode->text, "3")) result = str_text_for_search_word_tag(tags, search_tags->text, search_words->text);

    if (!strcmp(search_mode->text, "4")) result = str_text_for_search_link(tags, search_domain->text, "a li");

    fwrite("Text for searched information:", sizeof(char),strlen("Text for searched information:"), output);
    fwrite(result, sizeof(char),strlen(result), output);
    fclose(output);
//    printf("%s", result);

    printf("The program is completed, the search results are recorded in the output file");

    //print_tags(tags);

//    printf("Text for searched word: %s\n\n", str_text_for_search_word(tags, search_words->text));
//    printf("Text for searched tags: %s\n\n", str_text_for_search_tags(tags, search_tags->text));
//    printf("Text for searched word and tags: %s\n\n", str_text_for_search_word_tag(tags, search_tags->text, search_words->text));
//    printf("Text for searched links: %s\n\n", str_text_for_search_link(tags, search_domain->text, "a li link"));


    return 0;
}

