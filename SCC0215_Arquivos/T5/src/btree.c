#include "btree.h"

/** Print the header of b-tree */
void btree_printHeader(FILE* fp, HeaderBTree ht) {
    // print status and root
    fwrite(&ht.status, sizeof(ht.status), 1, fp);
    fwrite(&ht.rootNode, sizeof(ht.rootNode), 1, fp);
    
    // fill empty the rest of diskpage
    bin_printEmpty(fp, MAXDISKBTREE - sizeof(ht.status) - sizeof(ht.rootNode));
}

/** Update the HeaderIndex status (to valid/invalid) */
void btree_updateHeaderStatus(FILE* fp, char status) {
    fseek(fp, 0, SEEK_SET); // go to begin of file
    fwrite(&status, sizeof(status), 1, fp);
}

/** Update the Headerbtree root */
void btree_updateHeaderRoot(FILE* fp, int rootNode) {
    fseek(fp, 1, SEEK_SET); // ignore first byte (status)
    fwrite(&rootNode, sizeof(rootNode), 1, fp);
    fflush(fp); // flush stream
}

/** Reads the index header */
void btree_loadHeader(FILE* fp, HeaderBTree* ht) {
    fread(&ht->status, sizeof(char), 1, fp);
    fread(&ht->rootNode, sizeof(int), 1, fp);

    // ignore the first diskpage
    fseek(fp, MAXDISKBTREE, SEEK_SET);
}

/** Write a page (node of the tree) */
void btree_writePage(FILE* fp, DataBTree dt) {
    // print info from DataBTree struct
    fwrite(&dt.isLeaf, sizeof(dt.isLeaf), 1, fp);
    fwrite(&dt.n, sizeof(dt.n), 1, fp);
    
    for (int i = 0; i < M-1; i++) {
        fwrite(&dt.child[i].P, sizeof(dt.child[i].P), 1, fp);
        fwrite(&dt.child[i].C, sizeof(dt.child[i].C), 1, fp);
        fwrite(&dt.child[i].Pr, sizeof(dt.child[i].Pr), 1, fp);
    }

    fwrite(&dt.Pq, sizeof(dt.Pq), 1, fp);

    // flush the stream
    fflush(fp);
}

/** Read a disk page (b-tree indexed register) */
DataBTree btree_readRegister(FILE* fp) {
    DataBTree dt;

    fread(&dt.isLeaf, sizeof(dt.isLeaf), 1, fp);
    if (feof(fp)) { // end of file, just return some trash
        return dt;
    }

    fread(&dt.n, sizeof(dt.n), 1, fp);
    if (feof(fp)) { // end of file, just return some trash
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

/** Recursive function to go through the tree and insert a register */
InfoBTree btree_insertRegisterInner(FILE* fp, int key, int64_t offset, int node) {
    // the nodes are size-fixed, so just jump to the right position
    int64_t curOffset = MAXDISKBTREE * (node + 1);
    fseek(fp, curOffset, SEEK_SET);

    // reads the current info
    DataBTree dt = btree_readRegister(fp);

    // promote index, in case of split
    InfoBTree promote;
    promote.P = -1;
    promote.C = -1;
    promote.Pr = -1;
    
    // insertion position
    int inserted = 0;

    if (dt.isLeaf == '1' && dt.n < M-1) { // is leaf and has space
    
        // just insert on the right position, no need to split
        int i = 0;
        while (i < dt.n && dt.child[i].C < key) {
            i++;
        }

        for (int j = dt.n + 1; j > i; j--) {
            if (j == M - 1) {
                dt.Pq = dt.child[j-1].P;
            } else {
                dt.child[j] = dt.child[j-1];
            }
        }

        dt.child[i].P = -1;
        dt.child[i].C = key;
        dt.child[i].Pr = offset;
        dt.n++;

        // just insert
        fseek(fp, curOffset, SEEK_SET);
        btree_writePage(fp, dt);

        // return null promote
        return promote;
    } else if (dt.isLeaf == '1') { // is leaf, no space
        
        // need to split; fill all the info
        InfoBTree info[M];
        for (int i = 0, j = 0, aux = key; j < M; j++) {
            if (i < M-1 && dt.child[i].C < aux) {
                info[j] = dt.child[i];
                i++;
            } else {
                info[j].P = -1;
                info[j].C = aux;
                info[j].Pr = offset;
                aux = __INT_MAX__; // just to make sure that the children key will be always less than aux
            }
        }

        // promote the element from mid
        promote = info[M/2];

        // new data page to create
        DataBTree dt2;
        dt2.isLeaf = '1';
        dt2.n = M/2;
        dt2.Pq = -1;

        dt.Pq = -1;
        dt.n = M/2;

        // update this dataPage, and fill the new data page with correct elements
        for (int i = 0; i < M-1; i++) {
            if (i < dt.n) {
                dt.child[i] = info[i];
                dt2.child[i] = info[dt2.n + i + 1];
            } else {
                dt.child[i].C = -1;
                dt.child[i].P = -1;
                dt.child[i].Pr = -1;

                dt2.child[i].C = -1;
                dt2.child[i].P = -1;
                dt2.child[i].Pr = -1;
            }
        }

        // write the updated info
        fseek(fp, curOffset, SEEK_SET);
        btree_writePage(fp, dt);
    
        fseek(fp, 0, SEEK_END);
        int newNode = ftell(fp) / MAXDISKBTREE - 1;
        btree_writePage(fp, dt2);

        // promote will point to the new node (the next pointer)
        promote.P = newNode;
        
        // return
        return promote;
    } else { // isn't leaf, find a space to insert
        for (int i = 0; !inserted && i < M - 1; i++) {
            if (dt.child[i].C == -1 || dt.child[i].C > key) {
                promote = btree_insertRegisterInner(fp, key, offset, dt.child[i].P);
                inserted = i+1; // update the called index
            }
        }

        if (!inserted) { // use the Pq pointer
            promote = btree_insertRegisterInner(fp, key, offset, dt.Pq);
            inserted = M;
        }
    }

    if (promote.C != -1) { // need to promote

        if (dt.n < M-1) { // there is space

            // position that will be inserted
            int i = inserted - 1;

            // just insert on the right position
            for (int j = dt.n+1; j > i; j--) {
                if (j == M - 1) {
                    dt.Pq = dt.child[j-1].P;
                } else {
                    dt.child[j] = dt.child[j-1];
                }
            }

            // swap the promotion pointer to the right one
            int* next;
            if (i <= M-2) {
                next = &dt.child[i+1].P;
            } else {
                next = &dt.Pq;
            }

            int aux = *next;
            *next = promote.P;
            dt.child[i].P = aux;

            // update info
            dt.child[i].C = promote.C;
            dt.child[i].Pr = promote.Pr;
            dt.n++;

            // insert on stream
            fseek(fp, curOffset, SEEK_SET);
            btree_writePage(fp, dt);

            // return promotion values to null
            promote.C = -1;
            promote.P = -1;
            promote.Pr = -1;
        } else { // no space, has to split
            InfoBTree info[M];

            // fill all the elements to info
            int ind;
            for (int i = 0, j = 0, aux = promote.C; j < M; j++) {
                if (i < M-1 && dt.child[i].C < aux) {
                    info[j] = dt.child[i];
                    i++;
                } else {
                    ind = j;
                    info[j] = promote;
                    aux = __INT_MAX__;
                }
            }

            // find the position that promotion will fit
            int i = ind;

            // swap the promotion pointer to the right one
            int *next;
            
            if (i <= M-2) {
                next = &info[i+1].P;
            } else {
                next = &dt.Pq;
            }

            int aux = *next;
            *next = promote.P;
            info[i].P = aux;

            // will promote the mid
            promote = info[M/2];

            // new data page
            DataBTree dt2;

            // fill both pages with correct values
            dt2.isLeaf = '1';
            dt2.n = M/2;
            dt.n = M/2;

            for (int i = 0; i < M-1; i++) {
                if (i < dt.n) {
                    dt.child[i] = info[i];
                    dt2.child[i] = info[dt2.n + i + 1];
                } else {
                    dt.child[i].C = -1;
                    dt.child[i].P = -1;
                    dt.child[i].Pr = -1;

                    dt2.child[i].C = -1;
                    dt2.child[i].P = -1;
                    dt2.child[i].Pr = -1;
                }

                // if has at least one child, isn't root
                if (dt2.child[i].P != -1) {
                    dt2.isLeaf = '0';
                }
            }

            // update pointers
            dt.child[M/2].P = info[M/2].P;
            dt2.child[M/2].P = dt.Pq;

            dt2.Pq = -1;
            dt.Pq = -1;

            // write correct pages
            fseek(fp, curOffset, SEEK_SET);
            btree_writePage(fp, dt);

            fseek(fp, 0, SEEK_END);

            int newNode = ftell(fp) / MAXDISKBTREE - 1;
            btree_writePage(fp, dt2);

            // promote pointer will be the new created disk page
            promote.P = newNode;
        }
    }

    // return promoted node
    return promote;
}

/** Return the root of b-tree */
int btree_getRoot(FILE* fp) {
    fseek(fp, 1, SEEK_SET);
    int rootNode;
    fread(&rootNode, sizeof(rootNode), 1, fp);
    return rootNode;
}

/** Driver function to insert a new register */
void btree_insertRegister(FILE* fp, int key, int64_t offset) {    
    int oldRoot = btree_getRoot(fp);

    // invalid root - need to create a new one
    if (oldRoot == -1) {
        DataBTree dt;

        // fill with fixed elements
        dt.isLeaf = '1';
        dt.n = 1;
        dt.Pq = -1;

        for (int i = 0; i < M-1; i++) {
            dt.child[i].P = -1;
            dt.child[i].C = -1;
            dt.child[i].Pr = -1;
        }

        // update the first key
        dt.child[0].C = key;
        dt.child[0].Pr = offset;

        // update the root
        btree_updateHeaderRoot(fp, 0);

        // insert first disk page
        fseek(fp, 0, SEEK_END);
        btree_writePage(fp, dt);

        return; // everything was done; just return
    }

    // try to insert on the old root
    InfoBTree promote = btree_insertRegisterInner(fp, key, offset, oldRoot);

    // need to promote a new root
    if (promote.C != -1) {
        DataBTree dt;

        // fill with fixed elements
        dt.isLeaf = '0';
        dt.n = 1;
        dt.Pq = -1;
        
        for (int i = 1; i < M-1; i++) {
            dt.child[i].C = -1;
            dt.child[i].P = -1;
            dt.child[i].Pr = -1;
        }

        // update with promotion info
        dt.child[0].P = oldRoot;
        dt.child[0].C = promote.C;
        dt.child[0].Pr = promote.Pr;
        dt.child[1].P = promote.P;

        // find the value of new root
        fseek(fp, 0, SEEK_END);
        int node = ftell(fp) / MAXDISKBTREE - 1;

        // write new root
        btree_writePage(fp, dt);

        // update value of root
        btree_updateHeaderRoot(fp, node);
    }
}

/** Recursive function to find a register */
int64_t btree_findRegisterNode(FILE* fp, int key, int node, int* level) {
    int64_t offset = MAXDISKBTREE * (node + 1);

    // didn't find the key
    if (node == -1 || offset == 0) {
        return -1;
    }    

    // read the current page
    fseek(fp, offset, SEEK_SET);
    DataBTree dt = btree_readRegister(fp);

    *level += 1;

    // try to find on all children
    for (int i = 0; i < M - 1; i++) {
        if (dt.child[i].C == -1) { // first null children
            return btree_findRegisterNode(fp, key, dt.child[i].P, level);
        } else if (dt.child[i].C == key) {
            *level -= 1; // found the key, no need to sum the level
            return dt.child[i].Pr; // return the right offset
        } else if (dt.child[i].C > key) { // key is less than current children key
            return btree_findRegisterNode(fp, key, dt.child[i].P, level);
        }
    }

    // recursive call to Pq pointer
    return btree_findRegisterNode(fp, key, dt.Pq, level);
}

/** Driver function to find a register */
int64_t btree_findRegister(FILE* fp, HeaderBTree ht, int64_t key, int* level) {
    *level = 1; // root is on first level
    return btree_findRegisterNode(fp, key, ht.rootNode, level); // call starting from the root
}