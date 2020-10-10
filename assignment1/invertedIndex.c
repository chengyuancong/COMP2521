// COMP2521 Assignment 1

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "invertedIndex.h"

#define MAXLEN 100

static void trim(char *str);
static void lower(char *str);
static void rmvpunct(char *str);

char *normaliseWord(char *str) {
    trim(str);
    lower(str);
    rmvpunct(str);
    return str;
}

InvertedIndexBST generateInvertedIndex(char *collectionFilename) {

}

void printInvertedIndex(InvertedIndexBST tree) {

}

TfIdfList calculateTfIdf(InvertedIndexBST tree, char *searchWord, int D) {

}

TfIdfList retrieve(InvertedIndexBST tree, char *searchWords[], int D) {

}


// remove leading and trailing spaces
static void trim(char *str) {
    int start = 0;
    while (isspace(str[start])) start++;
    int end = strlen(str) - 1;
    while (isspace(str[start])) end--;
    int i = 0;
    for (int j = start; j <= end; i++, j++) str[i] = str[j];
    str[i] = '\0';
}

// convert all characters to lowercase
static void lower(char *str) {
    for (int i = 0; str[i] != '\0'; i++) str[i] = tolower(str[i]);
}

// remove the following punctuation marks, if they appear at the end of a word
static void rmvpunct(char *str) {
    int end = strlen(str) - 1;
    if (str[end] == '.' || str[end] == ','
        || str[end] == ';' || str[end] == '?') {
        str[end] = '\0';
    }
}

