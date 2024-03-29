
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Fb.h"
#include "Map.h"
#include "Queue.h"

#define MAX_PEOPLE 128

struct fb {
    int   numPeople;

    char *names[MAX_PEOPLE]; // the id of a person is simply the index
                             // that contains their name in this array
    
    Map   nameToId; // maps names to ids
                    // question to think about: why do we have this when
                    // the names array already provides this information?

    bool  friends[MAX_PEOPLE][MAX_PEOPLE];
};

static char *myStrdup(char *s);
static int   nameToId(Fb fb, char *name);

////////////////////////////////////////////////////////////////////////

// Creates a new instance of FriendBook
Fb   FbNew(void) {
    Fb fb = malloc(sizeof(*fb));
    if (fb == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }

    fb->numPeople = 0;
    fb->nameToId = MapNew();

    for (int i = 0; i < MAX_PEOPLE; i++) {
        for (int j = 0; j < MAX_PEOPLE; j++) {
            fb->friends[i][j] = false;
        }
    }

    return fb;
}

void FbFree(Fb fb) {
    for (int i = 0; i < fb->numPeople; i++) {
        free(fb->names[i]);
    }

    MapFree(fb->nameToId);
    free(fb);
}

bool FbAddPerson(Fb fb, char *name) {
    if (fb->numPeople == MAX_PEOPLE) {
        fprintf(stderr, "error: could not add more people\n");
        exit(EXIT_FAILURE);
    }

    if (!MapContains(fb->nameToId, name)) {
        int id = fb->numPeople++;
        fb->names[id] = myStrdup(name);
        MapSet(fb->nameToId, name, id);
        return true;
    } else {
        return false;
    }
}

bool FbHasPerson(Fb fb, char *name) {
    return MapContains(fb->nameToId, name);
}

List FbGetPeople(Fb fb) {
    List l = ListNew();
    for (int id = 0; id < fb->numPeople; id++) {
        ListAppend(l, fb->names[id]);
    }
    return l;
}

bool FbFriend(Fb fb, char *name1, char *name2) {
    int id1 = nameToId(fb, name1);
    int id2 = nameToId(fb, name2);
    assert(id1 != id2);

    if (!fb->friends[id1][id2]) {
        fb->friends[id1][id2] = true;
        fb->friends[id2][id1] = true;
        return true;
    } else {
        return false;
    }
}

bool FbUnfriend(Fb fb, char *name1, char *name2) {
    int id1 = nameToId(fb, name1);
    int id2 = nameToId(fb, name2);
    assert(id1 != id2);

    if (fb->friends[id1][id2]) {
        fb->friends[id1][id2] = false;
        fb->friends[id2][id1] = false;
        return true;
    } else {
        return false;
    }
}

bool FbIsFriend(Fb fb, char *name1, char *name2) {
    int id1 = nameToId(fb, name1);
    int id2 = nameToId(fb, name2);
    return fb->friends[id1][id2];
}

List FbGetFriends(Fb fb, char *name) {
    int id1 = nameToId(fb, name);
    
    List l = ListNew();
    for (int id2 = 0; id2 < fb->numPeople; id2++) {
        if (fb->friends[id1][id2]) {
            ListAppend(l, fb->names[id2]);
        }
    }
    return l;
}

int  FbNumFriends(Fb fb, char *name) {
    int id1 = nameToId(fb, name);
    
    int numFriends = 0;
    for (int id2 = 0; id2 < fb->numPeople; id2++) {
        if (fb->friends[id1][id2]) {
            numFriends++;
        }
    }
    return numFriends;
}

////////////////////////////////////////////////////////////////////////
// Your tasks

List FbMutualFriends(Fb fb, char *name1, char *name2) {
    List l = ListNew();
    int id1 = nameToId(fb, name1);
    int id2 = nameToId(fb, name2);
    for (int i = 0; i < fb->numPeople; i++) {
        if (fb->friends[i][id1] && fb->friends[i][id2]) {
            ListAppend(l, fb->names[i]);
        }
    }
    return l;
}

void FbFriendRecs1(Fb fb, char *name) {
    int id = nameToId(fb, name);
    int *mutualNum = calloc(fb->numPeople, sizeof(int));

    // calculate how many mutual friends and store in int mutualNum[]
    for (int i = 0; i < fb->numPeople; i++) {
        if (i != id && !fb->friends[i][id]) {
            List l = FbMutualFriends(fb, fb->names[i], fb->names[id]);
            mutualNum[i] = ListSize(l);
            ListFree(l);
        }
    }

    // print num of mutual friends in decending order
    printf("%s's friend recommendations\n", name);
    for (int i = fb->numPeople-2; i > 0; i--) {
        for (int j = 0; j < fb->numPeople; j++) {
            if (mutualNum[j] == i) {
                printf("\t%-20s%4d mutual friends\n", fb->names[j], i);
            }
        }
    }
    free(mutualNum);
}

void FbFriendRecs2(Fb fb, char *name) {
    int id = nameToId(fb, name);
    int *visited = calloc(fb->numPeople, sizeof(int));
    Queue q = QueueNew();
    QueueEnqueue(q, id);
    visited[id] = 1;
    int recsNum = 0;
    printf("%s's friend recommendations\n", name);
    while (!QueueIsEmpty(q) && recsNum < 20) {
        int curr =QueueDequeue(q);
        for (int i = 0; i < fb->numPeople; i++) {
            if (fb->friends[curr][i] && visited[i] == 0) {
                visited[i] = 1;
                QueueEnqueue(q, i);
                if (!fb->friends[id][i]) {
                    printf("\t%s\n", fb->names[i]);
                    recsNum++;
                }
            } 
        }
    }
}

////////////////////////////////////////////////////////////////////////
// Helper Functions

static char *myStrdup(char *s) {
    char *copy = malloc((strlen(s) + 1) * sizeof(char));
    if (copy == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }
    return strcpy(copy, s);
}

// Converts a name to an ID. Raises an error if the name doesn't exist.
static int nameToId(Fb fb, char *name) {
    if (!MapContains(fb->nameToId, name)) {
        fprintf(stderr, "error: person '%s' does not exist!\n", name);
        exit(EXIT_FAILURE);
    }
    return MapGet(fb->nameToId, name);
}
