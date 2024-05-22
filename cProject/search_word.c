#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "dict_of_words.h"
#include "dict_of_tags.h"

typedef struct {
    int *array;
    int count;
} Array;
Array *init_array() {
    Array *result = malloc(sizeof(Array));
    result->count = 0;
    result->array = NULL;
    return result;
}

void add_int_to_array(Array *array, int num) {
    array->array = realloc(array->array, (array->count + 1) * sizeof(int));
    array->array[array->count] = num;
    array->count++;
}
void array_reverse(Array *arr) {
    int temp, start = 0;
    int end = arr->count - 1;

    while (start < end) {
        temp = arr->array[start];
        arr->array[start] = arr->array[end];
        arr->array[end] = temp;

        start++;
        end--;
    }
}


Array *search_word(Tags *tags, char const *word) {
    Array *number_of_tags = init_array();
    for (int i = 0; i < tags->count; i++) {
        for (int j = 0; j < tags->dicts[i]->count; j++) {
            if (!strcmp(tags->dicts[i]->words[j]->word, word)) {
                add_int_to_array(number_of_tags, i);
            }
        }
    }
    return number_of_tags;
}

char *str_text_for_search_word(Tags *tags, char const *word) {
    Array *number_of_tags = search_word(tags, word);
    Multiple_text *texts_for_search_word = init_multiple_text();

    for (int i = 0; i < number_of_tags->count; i++) {
        add_text_to_multiple_text(texts_for_search_word, tags->texts[number_of_tags->array[i]]);
    }
    free(number_of_tags);
    return join_texts(texts_for_search_word, "\n\t");
}
