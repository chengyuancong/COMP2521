// COMP2521 Assignment 1

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "invertedIndex.h"

#define MAXLEN 100

static void trim(char *str);
static void lower(char *str);
static void rmvpunct(char *str);

static FileList generateFileList(char *collectionFilename);
static FileList generateFileListNode(char *filename);
static FileList insertFileListNode(FileList fileList ,FileList fileListNode);
static FileList duplicateFileList(FileList filelist);
static FileList searchFileList(FileList filelist, char *filename);
static InvertedIndexBST generateInvertedIndexNode(FileList fileList, char *word);
static InvertedIndexBST insertInvertedIndexNode(InvertedIndexBST invertedIndex, InvertedIndexBST invertedIndexNode);
static InvertedIndexBST searchInvertedIndex(InvertedIndexBST invertedIndex, char *word);
static InvertedIndexBST calculateTf(InvertedIndexBST invertedIndex, char *filename, int wordNum);

static void printFormattedInfo(InvertedIndexBST tree, FILE *outputFile);
static void printTf(FileList fileList, FILE *outputFile);

static TfIdfList generateTfIdfList(FileList fileList);
static TfIdfList generateTfIdfNode(FileList fileListNode);
static TfIdfList insertTfIdfNode(TfIdfList);


char *normaliseWord(char *str) {
    trim(str);
    lower(str);
    rmvpunct(str);
    return str;
}

InvertedIndexBST generateInvertedIndex(char *collectionFilename) {
    FileList sampleFileList = generateFileList(collectionFilename);
    InvertedIndexBST invertedIndex = NULL;
    for (FileList curr = sampleFileList; curr != NULL; curr = curr->next) {
        FILE *file = fopen(curr->filename, "r");
        char *word = malloc(MAXLEN * sizeof(char));
        int wordNum = 0;
        while(fscanf(file, "%s", &word)) {
            word = normaliseWord(*word);
            InvertedIndexBST currWordNode = searchInvertedIndex(invertedIndex, word);
            if (currWordNode == NULL) {
                currWordNode = generateInvertedIndexNode(sampleFileList, word);
                invertedIndex = insertInvertedIndexNode(invertedIndex, currWordNode);
            }
            FileList currFileNode = searchFileList(currWordNode->fileList, curr->filename);
            currFileNode->tf++;
            wordNum++;
        }
        invertedIndex = calculateTf(invertedIndex, curr->filename, wordNum);
        fclose(file);
    }
    return invertedIndex;
}

void printInvertedIndex(InvertedIndexBST tree) {
    FILE *output = fopen("invertedIndex.txt", "w");
    printFormattedInfo(tree, output);
    fclose(output);
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


// generate a list of FileListNodes in alphabatic order
static FileList generateFileList(char *collectionFilename) {
    FILE *collection = fopen(collectionFilename, "r");
    // if null
    char *filename = malloc(MAXLEN * sizeof(char));
    FileList sampleFileList = NULL;
    while (fscanf(collection, "%s", &filename) == 1) {
        FileList newFileListNode = generateFileListNode(filename);
        sampleFileList = insertFileListNode(sampleFileList, newFileListNode);
    }
    fclose(collection);
    return sampleFileList;
}

// generate a FileListNode for a given filename
static FileList generateFileListNode(char *filename) {
    
}

// insert a FileListNode into Filelist according to alphabatic order
static FileList insertFileListNode(FileList fileList ,FileList fileListNode) {

}

// duplicate the filelist for every node in inverted index
static FileList duplicateFileList(FileList filelist) {

}

// search a node containing a filename in a file list
static FileList searchFileList(FileList filelist, char *filename) {

}

// generate a inverted index node for a word
static InvertedIndexBST generateInvertedIndexNode(FileList fileList, char *word) {

}

// insert a inverted index node into invertedIndexBST according to alphabatic order
static InvertedIndexBST insertInvertedIndexNode(InvertedIndexBST invertedIndex, InvertedIndexBST invertedIndexNode) {

}

// search a node containing a word in inverted index
static InvertedIndexBST searchInvertedIndex(InvertedIndexBST invertedIndex, char *word) {

}

// calculate tf value for every word in inverted index after a file has been read 
// and number of words has been counted
static InvertedIndexBST calculateTf(InvertedIndexBST invertedIndex, char *filename, int wordNum) {

}