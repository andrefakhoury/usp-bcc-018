#include "register.h"

#define MAXDISKBTREE 105
#define M 7

typedef struct HeaderBTree {
    char status;
    int rootNode;
} HeaderBTree;

typedef struct InfoBTree {
    int P, C;
    int64_t Pr;
} InfoBTree;

typedef struct DataBTree {
    char isLeaf;
    int n;

    InfoBTree child[M - 1];
    int Pq;
} DataBTree;

void btree_printHeader(FILE* fp, HeaderBTree ht);

/** Update the HeaderIndex info */
void btree_updateHeaderStatus(FILE* fp, char status);

/** Update the HeaderIndex info */
void btree_updateHeaderRoot(FILE* fp, int rootNode);

void btree_loadHeader(FILE* fp, HeaderBTree* ht);

void btree_insertRegister(FILE* fp, int key, int64_t offset);

int64_t btree_findRegister(FILE* fp, HeaderBTree ht, int64_t key, int* level);