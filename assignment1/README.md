# Assignment 1 - Information Retrieval  

In this assignment, your task is to implement an information retrieval system using a well known term-weighting scheme called "tf-idf".

### Part-1: Inverted Index, using BST  

You need to implement the required functions in the file invertedIndex.c that reads data from a given collection of files in collection.txt and generates an "inverted index" that provides a sorted list (set) of filenames for every word in a given collection of files. You need to use binary search ADT to implement your inverted index.  

### Part-2: Information Retrieval Engine  

In this part, you need to implement an information retrieval function that finds files (documents) with one or more query terms, and uses the summation of tf-idf values of all matching query terms (words) for ranking such files (documents). You need to calculate the tf-idf value for each matching query term in a file (document), and rank files (documents) based on the summation of tf-idf values for all matching query terms present in that file. Use the "inverted index" you created in Part 1 to locate files with one or more query terms and calculate the required tf-idf values for such files.
 

## Test Summary

```
!!perftab       ** PERFORMANCE ANALYSIS **

Test  1 (0.4)   Exmp1 - 1 - normaliseWord  ..  ..  ..  ..  ..  ..  ..  ..  !!PASSed
Test  2 (0.6)   Exmp1 - 2 - generateInvertedIndex + printInvertedIndex ..  !!PASSed
Test  3 (0.1)   Exmp1 - 3 - calculateTfIdf ..  ..  ..  ..  ..  ..  ..  ..  !!PASSed
Test  4 (0.1)   Exmp1 - 4 - calculateTfIdf ..  ..  ..  ..  ..  ..  ..  ..  !!PASSed
Test  5 (0.1)   Exmp1 - 5 - calculateTfIdf ..  ..  ..  ..  ..  ..  ..  ..  !!PASSed
Test  6 (0.3)   Exmp1 - 6 - retrieve   ..  ..  ..  ..  ..  ..  ..  ..  ..  !!PASSed
Test  7 (0.6)   Exmp2 - 2 - generateInvertedIndex + printInvertedIndex ..  !!PASSed
Test  8 (0.1)   Exmp2 - 3 - calculateTfIdf ..  ..  ..  ..  ..  ..  ..  ..  !!PASSed
Test  9 (0.1)   Exmp2 - 4 - calculateTfIdf ..  ..  ..  ..  ..  ..  ..  ..  !!PASSed
Test 10 (0.2)   Exmp2 - 5 - retrieve   ..  ..  ..  ..  ..  ..  ..  ..  ..  !!PASSed
Test 11 (0.2)   Exmp2 - 6 - retrieve   ..  ..  ..  ..  ..  ..  ..  ..  ..  !!PASSed
Test 12 (1.2)   Exmp3 - 2 - generateInvertedIndex + printInvertedIndex ..  !!PASSed
Test 13 (0.4)   Exmp3 - 3 - calculateTfIdf ..  ..  ..  ..  ..  ..  ..  ..  !!PASSed
Test 14 (0.4)   Exmp3 - 4 - retrieve   ..  ..  ..  ..  ..  ..  ..  ..  ..  !!PASSed
Test 15 (0.4)   Exmp3 - 5 - retrieve   ..  ..  ..  ..  ..  ..  ..  ..  ..  !!PASSed
Test 16 (1.2)   Exmp4 - 2 - generateInvertedIndex + printInvertedIndex ..  !!PASSed
Test 17 (0.4)   Exmp4 - 3 - calculateTfIdf ..  ..  ..  ..  ..  ..  ..  ..  !!PASSed
Test 18 (0.4)   Exmp4 - 4 - calculateTfIdf ..  ..  ..  ..  ..  ..  ..  ..  !!PASSed
Test 19 (0.4)   Exmp4 - 5 - retrieve   ..  ..  ..  ..  ..  ..  ..  ..  ..  !!PASSed
Test 20 (0.4)   Exmp4 - 6 - retrieve   ..  ..  ..  ..  ..  ..  ..  ..  ..  !!PASSed

!!perfmark      ** TOTAL PERFORMANCE MARK:    8/8

!!marktab       **  MARKER'S  ASSESSMENT  **

                    Style and Complexity  (2)   2
 ^
 + ============================================== +
 + Really neat styling, appropriate amount of     +
 + commenting, nice and simple but effective      +
 + approach to problems in the assignment. Great  +
 + job!                                           +
 + ============================================== +

!!finalmark     **  FINAL  ASSIGNMENT  MARK:    10/10

5285978 Cheng, Yuancong                         3707/2 COMPBH


Marked by z5116701 on Sun Nov 15 16:47:13 2020
```