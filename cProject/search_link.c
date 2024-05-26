#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "dict_of_words.h"
#include "dict_of_tags.h"
#include "search_word.h"
#include "search_tag.h"
#include "search_word_tags.h"

char* extract_link(const char *tag) {
    const char* href_attr = "href=";
    if (!strstr(tag, href_attr) || !strchr(tag, '"') || strlen(tag) < 6) return "";
    const char* href_start = strstr(tag, href_attr);
    if (href_start) {
        const char* link_start = href_start + strlen(href_attr) + 1;
        const char* link_end = strchr(link_start, '"');
        if (link_end) {
            char* href = (char*)malloc(link_end - link_start + 1);
            strncpy(href, link_start, link_end - link_start);
            href[link_end - link_start] = '\0';
            return href;
        }
    }
    return "";
}

char *str_text_for_search_link(Tags const *tags, char const *domain, char const *search_tags_str) {
    char *link;
    Multiple_text *text_for_search_links = init_multiple_text();
    Multiple_text *search_tags = fill_search_tags_multiple_text(search_tags_str);
    for (int i = 0; i < tags->count; i++) {
        if (is_str_in_multiple_text(search_tags, tags->dicts[i]->tag)) {
            link = extract_link(tags->dicts[i]->last_tag);
             if (strstr(link, domain)) {
                 Text *nice_link = init_text();
                 for (int t = 0; t < strlen(link); t++) {
                     add_char_to_text(nice_link, link[t]);
                 }
                 add_text_to_multiple_text(text_for_search_links, nice_link);
             }
        }
    }
    return join_texts(text_for_search_links, "\n\t");
}
