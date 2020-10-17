// COMP2521 Assignment 1

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "invertedIndex.h"
#include "wordBSTs.h"

#define MAXLEN 100

static void trim(char *str);
static void lower(char *str);
static void rmvpunct(char *str);

static FileList generateFileList(char *collectionFilename);
static FileList createFileNode(char *filename, FileList fileList);
static FileList insertFileNode(FileList fileList ,char* filename);
static FileList duplicateFileList(FileList fileList);
static FileList searchFileNode(FileList fileList, char *filename);
static InvertedIndexBST createInvertedIndexNode(FileList fileList, char *word);
static InvertedIndexBST insertInvertedIndexNode(InvertedIndexBST invertedIndex, InvertedIndexBST invertedIndexNode);
static InvertedIndexBST searchInvertedIndexNode(InvertedIndexBST invertedIndex, char *word);
static void calculateTf(InvertedIndexBST invertedIndex, char *filename, int wordNum);

static void printFormattedInfo(InvertedIndexBST tree, FILE *outputFile);
static void printTf(FileList fileList, FILE *outputFile);

static double calculateIdf(FileList fileList, int D);
static TfIdfList createTfIdfNode(char *filename, double tfidf, TfIdfList tfidfList);
static TfIdfList insertTfIdfNode(TfIdfList tfIdfList, char *filename, double tfidf);


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
        while(fscanf(file, "%s", word) == 1) {
            word = normaliseWord(word);
            InvertedIndexBST currWordNode = searchInvertedIndexNode(invertedIndex, word);
            // generate a node for the word and insert it if not exist
            if (currWordNode == NULL) {
                currWordNode = createInvertedIndexNode(sampleFileList, word);
                invertedIndex = insertInvertedIndexNode(invertedIndex, currWordNode);
            }
            // search for the file node and occured time++
            FileList currFileNode = searchFileNode(currWordNode->fileList, curr->filename);
            currFileNode->tf++;
            wordNum++;
        }
        // for every file node matchs filename, tf = tf/wordNum
        calculateTf(invertedIndex, curr->filename, wordNum);
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
    InvertedIndexBST wordNode = searchInvertedIndexNode(tree, searchWord);
    // calculate the word's idf
    double idf = calculateIdf(wordNode->fileList, D);
    // generate TfIdf node for every file and add them to tfIdfList
    for (FileList curr = wordNode->fileList; curr != NULL; curr = curr->next) {
        double tfidf = curr->tf * idf;
        if (tfidf != 0) tfIdfList = insertTfIdfNode(tfIdfList, curr->filename, tfidf);
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
            InvertedIndexBST wordNode = searchInvertedIndexNode(tree, searchWords[i]);
            FileList currFile = searchFileNode(wordNode->fileList, filename);
            // sum up every word's tfidf value in this file
            if (currFile->tf != 0) {
                double idf = calculateIdf(wordNode->fileList, D);
                tfIdfSum = tfIdfSum + currFile->tf * idf;
            }
        }
        // insert a new tfIdfNode into tfIdfList
        if (tfIdfSum != 0) {
            tfIdfList = insertTfIdfNode(tfIdfList, filename, tfIdfSum); 
        }
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
    char *filename = malloc(MAXLEN * sizeof(char));
    // read file name collection and generate a fileList
    while (fscanf(collection, "%s", filename) == 1) {
        sampleFileList = insertFileNode(sampleFileList, filename);
    }
    free(filename);
    fclose(collection);
    return sampleFileList;
}

// generate a FileListNode for a given filename
static FileList createFileNode(char *filename, FileList fileList) {
    FileList newNode = malloc(sizeof(struct FileListNode));
    newNode->filename = strdup(filename);
    newNode->tf = 0;
    newNode->next = fileList;
    return newNode;
}

// insert a FileListNode into Filelist according to alphabatic order
static FileList insertFileNode(FileList fileList ,char *filename) {
    if (fileList == NULL || strcmp(fileList->filename, filename) > 0) {
        return createFileNode(filename, fileList);
    }
    fileList->next = insertFileNode(fileList->next, filename);
    return fileList;
}

// duplicate the filelist for every node in inverted index
static FileList duplicateFileList(FileList fileList) {
    if (fileList == NULL) return NULL;
    FileList newNode = malloc(sizeof(struct FileListNode));
    FileList newList = newNode;
    newNode->filename = strdup(fileList->filename);
    newNode->tf = fileList->tf;
    for (FileList curr = fileList->next; curr != NULL; curr = curr->next) {
        newNode->next = malloc(sizeof(struct FileListNode));
        newNode->next->filename = strdup(curr->filename);
        newNode->next->tf = curr->tf;
        newNode = newNode->next;
    }
    newNode->next = NULL;
    return newList;
}

// search a node containing a filename in a file list
static FileList searchFileNode(FileList fileList, char *filename) {
    if (fileList == NULL) {
        return NULL;
    } else if (strcmp(fileList->filename, filename) == 0) {
        return fileList;
    } else {
        return searchFileNode(fileList->next, filename);
    }
}

// generate a inverted index node for a word
static InvertedIndexBST createInvertedIndexNode(FileList fileList, char *word) {
    InvertedIndexBST newNode = malloc(sizeof(struct InvertedIndexNode));
    newNode->word = strdup(word);
    newNode->fileList = duplicateFileList(fileList);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// insert a inverted index node into invertedIndexBST according to alphabatic order
static InvertedIndexBST insertInvertedIndexNode(InvertedIndexBST invertedIndex, InvertedIndexBST invertedIndexNode) {
    if (invertedIndex == NULL) {
        return invertedIndexNode;
    } else if (strcmp(invertedIndex->word, invertedIndexNode->word) > 0) {
        invertedIndex->left = insertInvertedIndexNode(invertedIndex->left, invertedIndexNode);
        return invertedIndex;
    } else if (strcmp(invertedIndex->word, invertedIndexNode->word) < 0) {
        invertedIndex->right = insertInvertedIndexNode(invertedIndex->right, invertedIndexNode);
        return invertedIndex;
    } else {
        return invertedIndex;
    }
}

// search a node containing a word in inverted index
static InvertedIndexBST searchInvertedIndexNode(InvertedIndexBST invertedIndex, char *word) {
    if (invertedIndex == NULL) {
        return NULL;
    } else if (strcmp(invertedIndex->word, word) > 0) {
        return searchInvertedIndexNode(invertedIndex->left, word);
    } else if (strcmp(invertedIndex->word, word) < 0) {
        return searchInvertedIndexNode(invertedIndex->right, word);
    } else {
        return invertedIndex;
    }
}

// calculate tf value for every word in inverted index after a file has been read 
// and number of words has been counted
static void calculateTf(InvertedIndexBST invertedIndex, char *filename, int wordNum) {
    if (invertedIndex != NULL) {
        calculateTf(invertedIndex->left, filename, wordNum);
        FileList currFile = searchFileNode(invertedIndex->fileList, filename);
        currFile->tf = currFile->tf/wordNum;
        calculateTf(invertedIndex->right, filename, wordNum);
    }
}

// traverse every node in the tree and print formatted tf values for a word
static void printFormattedInfo(InvertedIndexBST tree, FILE *outputFile) {
    if (tree != NULL) {
        printFormattedInfo(tree->left, outputFile);
        fprintf(outputFile, "%s ", tree->word);
        printTf(tree->fileList, outputFile);
        printFormattedInfo(tree->right, outputFile);
    }
}

// print formatted tf values in every file (ignore tf == 0)
static void printTf(FileList fileList, FILE *outputFile) {
    for (FileList curr = fileList; curr != NULL; curr = curr->next) {
        if (curr->tf != 0) {
            fprintf(outputFile, "%s (%.6f) ", curr->filename, curr->tf);
        }
    }
    fprintf(outputFile, "\n"); 
}

// calculate a word's idf value from a given fileList
static double calculateIdf(FileList fileList, int D) {
    double containFileNum = 0;
    for (FileList curr = fileList; curr != NULL; curr = curr->next) {
        if (curr->tf > 0) containFileNum++;
    }
    double idf = log10(D/containFileNum);
    return idf;
}

// create a new TfIdfNode 
static TfIdfList createTfIdfNode(char *filename, double tfidf, TfIdfList tfIdfList) {
    TfIdfList newNode = malloc(sizeof(struct TfIdfNode));
    newNode->filename = strdup(filename);
    newNode->tfIdfSum = tfidf;
    newNode->next = tfIdfList;
    return newNode;
}

// insert a new TfIdfNode to a tfIdfList according to decending tfidf order
static TfIdfList insertTfIdfNode(TfIdfList tfIdfList, char *filename, double tfidf) {
    if (tfIdfList == NULL || 
       (tfIdfList->tfIdfSum < tfidf || 
       (tfIdfList->tfIdfSum == tfidf && 
        strcmp(tfIdfList->filename, filename) > 0))) {
            return createTfIdfNode(filename, tfidf, tfIdfList);
    }
    tfIdfList->next = insertTfIdfNode(tfIdfList->next, filename, tfidf);
    return tfIdfList;
}