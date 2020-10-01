# Assignment 1 - Information Retrieval  

In this assignment, your task is to implement an information retrieval system using a well known term-weighting scheme called "tf-idf".

### Part-1: Inverted Index, using BST  

You need to implement the required functions in the file invertedIndex.c that reads data from a given collection of files in collection.txt and generates an "inverted index" that provides a sorted list (set) of filenames for every word in a given collection of files. You need to use binary search ADT to implement your inverted index.  

### Part-2: Information Retrieval Engine  

In this part, you need to implement an information retrieval function that finds files (documents) with one or more query terms, and uses the summation of tf-idf values of all matching query terms (words) for ranking such files (documents). You need to calculate the tf-idf value for each matching query term in a file (document), and rank files (documents) based on the summation of tf-idf values for all matching query terms present in that file. Use the "inverted index" you created in Part 1 to locate files with one or more query terms and calculate the required tf-idf values for such files.

*[Click here](http://www.cse.unsw.edu.au/~cs2521/20T3/assigns/ass1/Ass1.html#Download) for more information*  