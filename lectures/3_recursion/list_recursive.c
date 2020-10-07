// linked list processing functions from list.c - recursive versions
// 

#include <stdio.h>
#include <stdlib.h>
#include "list_recursive.h"

int main(int argc, char *argv[]) {
    struct node *list = NULL;
    int number;

    printf("Enter a number: ");
    while (scanf("%d", &number) == 1) {
        list = append(list, number);
        printf("Enter a number: ");
    }

    if (list == NULL) {
        printf("List is empty.\n");
        return 0;
    }
    printf("\n\nList entered was: ");
    print_list(list);

    printf("\n\nFirst element in list is: %d.\n", list->data);
    printf("\nLast element in list is: %d.\n", last(list)->data);
    printf("\nLength of list is: %d.\n", length(list));
    printf("\nSum of the list is: %d.\n\n", sum(list));

    if (find_node(list, 42) != NULL) {
        printf("42 is in the list.\n");
    } else {
        printf("42 is not in the list.\n");
    }

    printf("\nBefore deleting 50\n");
    print_list(list);
    printf("\n\n");

    list = deleteR(list, 50);

    printf("\nAfter deleting 50\n");
    print_list(list);
    printf("\n\n");
   
    struct node *listOrd = NULL;
    listOrd = append(listOrd, 12);    
    listOrd = append(listOrd, 27);    
    listOrd = append(listOrd, 33);    
    listOrd = append(listOrd, 55);    
    listOrd = append(listOrd, 78);    

    listOrd = insertR(listOrd, 52);

    printf("\nAfter inserting 52 in the ordered list [12, 27, 33, 55, 78]\n");
    print_list(listOrd);
    printf("\n\n");

    return 0;
}


// Create a new struct node containing the specified data,
// and next fields, return a pointer to the new struct node.
struct node *create_node(int data, struct node *next) {
    struct node *n = malloc(sizeof (struct node));
    if (n == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    n->data = data;
    n->next = next;
    return n;
}

// return pointer to last node in list
// NULL is returned if list is empty
struct node *last(struct node *list) {
    if (list == NULL || list->next == NULL) {
        return list;
    }
    return last(list->next);
}


// create a new list node containing value
// and append it to end of list
struct node *append(struct node *list, int value) {
    if (list == NULL) {
        return create_node(value, NULL);
    }
    list->next = append(list->next, value);
    return list;
}

// return sum of list data fields: using recursive call
int sum(struct node *list) {
    if (list == NULL) {
        return 0;
    }
    return list->data + sum(list->next);
}

// print contents of list in Python syntax
void print_list(struct node *list) {
    printf("[");
    if (list != NULL) {
        print_list_items(list);
    }
    printf("]");
}

void print_list_items(struct node *list) {
    printf("%d", list->data);
    if (list->next != NULL) {
        printf(", ");
        print_list_items(list->next);
    }
}

// return count of nodes in list
int length(struct node *list) {
    if (list == NULL) {
        return 0;
    }
    return 1 + length(list->next);
}


// return pointer to first node with specified data value
// return NULL if no such node
struct node *find_node(struct node *list, int data) {
    if (list == NULL || list->data == data) {
        return list;
    }
    return find_node(list->next, data);
}


// Delete a Node from a List: Recursive
struct node *deleteR(struct node *list, int value) {
   if (list == NULL) {
      fprintf(stderr, "warning: value %d is not in list\n", value);
      
   } else if (list->data == value) {
      struct node *tmp = list;
      list = list->next;        // remove first item
      free(tmp);
      
   } else {
      list->next = deleteR(list->next, value);
   }
   return list;
}

// Insert a Node into an Ordered List: recursive
struct node *insertR(struct node *list, int value) {
   if (list == NULL || list->data >= value) {

      struct node *newHead = create_node(value, NULL);
      newHead->next = list;
      return newHead;

      // Alternatively, in one line
      // return create_node(value, list) ; 
   }
   
   list->next = insertR(list->next, value);	
   
   return list;
}



