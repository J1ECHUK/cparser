cmake_minimum_required(VERSION 3.25)
project(cProject C)

set(CMAKE_C_STANDARD 11)

add_executable(cProject main.c dict_of_words.c dict_of_words.h dict_of_words.h dict_of_tags.h dict_of_tags.h dict_of_tags.c search_word.c search_word.h)
