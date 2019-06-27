
#include "register.h"

#define MAXDISKBTREE 105
#define M 7

typedef struct HeaderBTree {
    char status;
    int rootNode;
} HeaderBTree;

typedef struct DataBTree {
    char isLeaf;
    int n;

    struct {
        int P, C;
        int64_t Pr;
    } child[M];

} DataBTree;

