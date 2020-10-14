// COMP2521 Assignment 1

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "invertedIndex.h"

#define MAXLEN 100

static void trim(char *str);
static void lower(char *str);
static void rmvpunct(char *str);

static FileList generateFileList(char *collectionFilename);
static FileList generateFileListNode(char *filename);
static FileList insertFileListNode(FileList fileList ,FileList fileListNode);
static FileList duplicateFileList(FileList fileList);
static FileList searchFileList(FileList fileList, char *filename);
static InvertedIndexBST generateInvertedIndexNode(FileList fileList, char *word);
static InvertedIndexBST insertInvertedIndexNode(InvertedIndexBST invertedIndex, InvertedIndexBST invertedIndexNode);
static InvertedIndexBST searchInvertedIndex(InvertedIndexBST invertedIndex, char *word);
static InvertedIndexBST calculateTf(InvertedIndexBST invertedIndex, char *filename, int wordNum);

static void printFormattedInfo(InvertedIndexBST tree, FILE *outputFile);
static void printTf(FileList fileList, FILE *outputFile);

static double calculateIdf(FileList fileList, int D);
static TfIdfList generateTfIdfNode(char *filename, double tfidf);
static TfIdfList insertTfIdfNode(TfIdfList tfIdfList, TfIdfList tfIdfNode);


char *normaliseWord(char *str) {
    trim(str);
    lower(str);
    rmvpunct(str);
    return str;
}

InvertedIndexBST generateInvertedIndex(char *collectionFilename) {
    FileList sampleFileList = generateFileList(collectionFilename);
    InvertedIndexBST invertedIndex = NULL;
    char *word = malloc(MAXLEN * sizeof(char));
    // read words from all files
    for (FileList curr = sampleFileList; curr != NULL; curr = curr->next) {
        FILE *file = fopen(curr->filename, "r");
        int wordNum = 0;
        // read words from a file and insert/count it in the tree
        while(fscanf(file, "%s", &word)) {
            word = normaliseWord(word);
            InvertedIndexBST currWordNode = searchInvertedIndex(invertedIndex, word);
            // generate a node for the word and insert it if not exist
            if (currWordNode == NULL) {
                currWordNode = generateInvertedIndexNode(sampleFileList, word);
                invertedIndex = insertInvertedIndexNode(invertedIndex, currWordNode);
            }
            // search for the file node and occured time++
            FileList currFileNode = searchFileList(currWordNode->fileList, curr->filename);
            currFileNode->tf++;
            wordNum++;
        }
        // for every file node matchs filename, tf = tf/wordNum
        invertedIndex = calculateTf(invertedIndex, curr->filename, wordNum);
        fclose(file);
    }
    // free the buffer
    free(word);
    return invertedIndex;
}

void printInvertedIndex(InvertedIndexBST tree) {
    FILE *output = fopen("invertedIndex.txt", "w");
    printFormattedInfo(tree, output);
    fclose(output);
}

TfIdfList calculateTfIdf(InvertedIndexBST tree, char *searchWord, int D) {
    TfIdfList tfIdfList = NULL;
    // search the word in tree
    InvertedIndexBST wordNode = searchInvertedIndex(tree, searchWord);
    // calculate the word's idf
    double idf = calculateIdf(wordNode->fileList, D);
    // generate TfIdf node for every file and add them to tfIdfList
    for (FileList curr = wordNode->fileList; curr != NULL; curr = curr->next) {
        double tfidf = curr->tf * idf;
        TfIdfList tfIdfNode = generateTfIdfNode(curr->filename, tfidf);
        tfIdfList = insertTfIdfNode(tfIdfList, tfIdfNode);
    }
    return tfIdfList;
}

TfIdfList retrieve(InvertedIndexBST tree, char *searchWords[], int D) {
    TfIdfList tfIdfList = NULL;
    // read ordered filename from a fileList
    FileList sampleFileList = tree->fileList;
    // calculate every file's tfIdfSum with given searchWords list 
    for (FileList curr = sampleFileList; curr != NULL; curr = curr->next) {
        char *filename = curr->filename;
        double tfIdfSum = 0;
        // calculate every word's idf and multiply it to it tf value in current file 
        for (int i = 0; searchWords[i] != NULL; i++) {
            InvertedIndexBST wordNode = searchInvertedIndex(tree, searchWords[i]);
            double idf = calculateIdf(wordNode->fileList, D);
            FileList currFile = searchFileList(wordNode->fileList, filename);
            // sum up every word's tfidf value in this file
            tfIdfSum = tfIdfSum + currFile->tf * idf;
        }
        // generate a tfIdfNode for this file and insert it in to tfIdfList
        TfIdfList tfIdfNode = generateTfIdfNode(filename, tfIdfSum);
        tfIdfList = insertTfIdfNode(tfIdfList, tfIdfNode);
    }
    return tfIdfList;
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
    FileList sampleFileList = NULL;
    FILE *collection = fopen(collectionFilename, "r");
    // if null
    char *filename = malloc(MAXLEN * sizeof(char));
    // read file name collection and generate a fileList
    while (fscanf(collection, "%s", &filename) == 1) {
        FileList newFileListNode = generateFileListNode(filename);
        sampleFileList = insertFileListNode(sampleFileList, newFileListNode);
    }
    free(filename);
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
static FileList duplicateFileList(FileList fileList) {

}

// search a node containing a filename in a file list
static FileList searchFileList(FileList fileList, char *filename) {

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

// traverse every node in the tree and print formatted tf values for a word
static void printFormattedInfo(InvertedIndexBST tree, FILE *outputFile) {

}

// print formatted tf values in every file (ignore tf == 0)
static void printTf(FileList fileList, FILE *outputFile) {

}

// 
static double calculateIdf(FileList fileList, int D) {
    double containFileNum = 0;
    for (FileList curr = fileList; curr->next != NULL; curr = curr->next) {
        if (curr->tf > 0) containFileNum++;
    }
    double idf = log10(D/containFileNum);
    return idf;
}

// 
static TfIdfList generateTfIdfNode(char *filename, double tfidf) {

}

// 
static TfIdfList insertTfIdfNode(TfIdfList tfIdfList, TfIdfList tfIdfNode) {
    
}