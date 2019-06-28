#include "btree.h"

void btree_printHeader(FILE* fp, HeaderBTree ht) {
    fwrite(&ht.status, sizeof(ht.status), 1, fp);
    fwrite(&ht.rootNode, sizeof(ht.rootNode), 1, fp);
    
    bin_printEmpty(fp, MAXDISKBTREE - sizeof(ht.status) - sizeof(ht.rootNode));
}

/** Update the HeaderIndex info */
void btree_updateHeaderStatus(FILE* fp, char status) {
    fseek(fp, 0, SEEK_SET);
    fwrite(&status, sizeof(status), 1, fp);
}

/** Update the Headerbtree info */
void btree_updateHeaderRoot(FILE* fp, int rootNode) {
    fseek(fp, 1, SEEK_SET);
    fwrite(&rootNode, sizeof(rootNode), 1, fp);
}

/** Reads the index header */
void btree_loadHeader(FILE* fp, HeaderBTree* ht) {
    fread(&ht->status, sizeof(char), 1, fp);
    fread(&ht->rootNode, sizeof(int), 1, fp);

    fseek(fp, MAXPAGE, SEEK_SET);
}

void btree_writePage(FILE* fp, DataBTree dt) {
    fwrite(&dt.isLeaf, sizeof(dt.isLeaf), 1, fp);
    fwrite(&dt.n, sizeof(dt.n), 1, fp);
    
    for (int i = 0; i < M-1; i++) {
        fwrite(&dt.child[i].P, sizeof(dt.child[i].P), 1, fp);
        fwrite(&dt.child[i].C, sizeof(dt.child[i].C), 1, fp);
        fwrite(&dt.child[i].Pr, sizeof(dt.child[i].Pr), 1, fp);
    }

    fwrite(&dt.Pq, sizeof(dt.Pq), 1, fp);
}

//insert() {
//    promote = -1
//    if (folha e tem espaço) {
//       insere e pronto
//    } else if (folha e não tem espaço) {
//       return split(); // split cria o novo nó, divide os elementos entre os dois, e retorna o elemento a ser promovido
//    } else {
//       promote = insert() // recursão
//    }
// }

//   if (promote != -1) {
//      faz a promoção
//   }
// }

DataBTree btree_readRegister(FILE* fp) {
    DataBTree dt;
    dt.child[0].C = -1;

    fread(&dt.isLeaf, sizeof(dt.isLeaf), 1, fp);
    if (feof(fp)) {
        return dt;
    }

    fread(&dt.n, sizeof(dt.n), 1, fp);
    if (feof(fp)) {
        return dt;
    }
    
    for (int i = 0; i < M - 1; i++) {
        fread(&dt.child[i].P, sizeof(dt.child[i].P), 1, fp);
        fread(&dt.child[i].C, sizeof(dt.child[i].C), 1, fp);
        fread(&dt.child[i].Pr, sizeof(dt.child[i].Pr), 1, fp);
    }

    fread(&dt.Pq, sizeof(dt.Pq), 1, fp);

    return dt;
}

InfoBTree btree_insertRegisterInner(FILE* fp, int key, int64_t offset, int node) {
    int64_t curOffset = MAXDISKBTREE * (node + 1);

    fseek(fp, curOffset, SEEK_SET);
    DataBTree dt = btree_readRegister(fp);

    InfoBTree promote;
    promote.C = -1;

    if (dt.isLeaf == '1' && dt.n < M-1) {
        int i;
        for (i = 0; i < dt.n && dt.child[i].C < key; i++);
        for (int j = dt.n; j > i; j--) {
            dt.child[j].P = dt.child[j-1].P;
            dt.child[j].C = dt.child[j-1].C;
            dt.child[j].Pr = dt.child[j-1].Pr;
        }

        dt.child[i].P = -1;
        dt.child[i].C = key;
        dt.child[i].Pr = offset;
        dt.n++;

        fseek(fp, offset, SEEK_SET);
        btree_writePage(fp, dt);
    } else if (dt.isLeaf == '1') {

        InfoBTree info[M];
        for (int i = 0, j = 0, aux = key; i < M - 1; j++) {
            if (dt.child[i].C < aux) {
                info[j] = dt.child[i];
                i++;
            } else {
                info[j].C = aux;
                info[j].P = -1;
                info[j].Pr = offset;
                aux = __INT_MAX__;
            }
        }

        promote = info[(M+1)/2];

        DataBTree dt2;

        dt2.isLeaf = '1';
        dt2.n = (M-1)/2;
        dt2.Pq = -1;

        dt.n = (M-1)/2;

        for (int i = 0; i < M-1; i++) {
            if (i < dt.n) {
                dt.child[i] = info[i];
                dt2.child[i] = info[dt2.n + i];
            } else {
                dt.child[i].C = -1;
                dt.child[i].P = -1;
                dt.child[i].Pr = -1;

                dt2.child[i].C = -1;
                dt2.child[i].P = -1;
                dt2.child[i].Pr = -1;
            }
        }

        return promote;
    } else {
        int inserted = 0;
        for (int i = 0; !inserted && i < M - 1; i++) {
            if (dt.child[i].C == -1) {
                promote = btree_insertRegisterInner(fp, key, offset, dt.child[i].P);
                inserted = 1;
            } else if (dt.child[i].C > key) {
                promote = btree_insertRegisterInner(fp, key, offset, dt.child[i].P);
                inserted = 1;
            }
        }

        if (!inserted) {
            promote = btree_insertRegisterInner(fp, key, offset, dt.Pq);
            inserted = 1;
        }
    }

    if (promote.C != -1) {
        return btree_insertRegisterInner(fp, promote.C, promote.Pr, node);
    }

    return promote;
}

void btree_insertRegister(FILE* fp, int key, int64_t offset) {
    
}

int64_t btree_findRegisterNode(FILE* fp, int key, int node, int* level) {
    int64_t offset = MAXDISKBTREE * (node + 1);

    if (node == -1 || offset == 0) {
        return -1;
    }    

    fseek(fp, offset, SEEK_SET);
    DataBTree dt = btree_readRegister(fp);

    *level += 1;
    for (int i = 0; i < M - 1; i++) {
        if (dt.child[i].C == -1) {
            return btree_findRegisterNode(fp, key, dt.child[i].P, level);
        } else if (dt.child[i].C == key) {
            *level -= 1;
            return dt.child[i].Pr;
        } else if (dt.child[i].C > key) {
            return btree_findRegisterNode(fp, key, dt.child[i].P, level);
        }
    }

    return btree_findRegisterNode(fp, key, dt.Pq, level);
}

int64_t btree_findRegister(FILE* fp, HeaderBTree ht, int64_t key, int* level) {
    *level = 1;
    return btree_findRegisterNode(fp, key, ht.rootNode, level);
}