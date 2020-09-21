// list_recursive.h

struct node {
    struct node *next;
    int         data;
};

// Create a new struct node containing the specified data,
// and next fields, return a pointer to the new struct node.
struct node *create_node(int data, struct node *next);

// return pointer to last node in list
// NULL is returned if list is empty
struct node *last(struct node *head);

// create a new list node containing value
// and append it to end of list
struct node *append(struct node *head, int value);

// return sum of list data fields: using recursive call
int sum(struct node *head);

// print contents of list in Python syntax
void print_list(struct node *head);
void print_list_items(struct node *head);

// return count of nodes in list
int length(struct node *head);

// return pointer to first node with specified data value
// return NULL if no such node
struct node *find_node(struct node *head, int data);

// Delete a Node from a List: Recursive
struct node *deleteR(struct node *head, int value);

// Insert a Node into an Ordered List: recursive
struct node *insertR(struct node *head, int value);






