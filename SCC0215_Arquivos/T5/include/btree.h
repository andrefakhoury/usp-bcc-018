#include "register.h"

/** Pre-determined size of b-tree disk page size */
#define MAXDISKBTREE 105

/** Maximum order */
#define M 7

/** Struct for the header of b-tree */
typedef struct HeaderBTree {
    char status; // invalid/valid
    int rootNode; // index of root node
} HeaderBTree;

/** Struct for the information of each child of b-tree node */
typedef struct InfoBTree {
    int P; // pointer to the next node
    int C; // key
    int64_t Pr; // byte offset of key on data file
} InfoBTree;

/** Struct for the information of each node of b-tree */
typedef struct DataBTree {
    char isLeaf;
    int n; // qtt of nodes

    InfoBTree child[M - 1];
    int Pq;
} DataBTree;

/** Print the header of b-tree */
void btree_printHeader(FILE* fp, HeaderBTree ht);

/** Update the HeaderIndex status (to valid/invalid) */
void btree_updateHeaderStatus(FILE* fp, char status);

/** Update the Headerbtree root */
void btree_updateHeaderRoot(FILE* fp, int rootNode);

/** Reads the index header */
void btree_loadHeader(FILE* fp, HeaderBTree* ht);

/** Driver function to insert a new register */
void btree_insertRegister(FILE* fp, int key, int64_t offset);

/** Driver function to find a register */
int64_t btree_findRegister(FILE* fp, HeaderBTree ht, int64_t key, int* level);