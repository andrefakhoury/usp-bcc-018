void cria(Lista *l) {
    l->ini = NULL;
    l->fim = NULL;
    return;
}

int insere(Lista *l, elem x) {
    No *p;
    // cria no
    p = (No *) malloc(sizeof(No));
    if (p==NULL)
        return 1;
    // atribui valores
    p->info = x;
    p->prox = NULL;
    // atualiza encadeamento
    if (l->ini == NULL)
        l->ini = p;
    else
        l->fim->prox = p;
    l->fim = p;
    return 0;
}

void finaliza(Lista *l) {
    No *p;
    p = l->ini;
    while (l->ini != NULL) {
        l->ini = l->ini->prox;
        free(p);
        p = l->ini;
    }
    l->fim = NULL;
    return;
}

void imprime(Lista l) {
    No *p;
    p = l.ini;
    while (p != NULL) {
        printf("%c", p->info);
        p = p->prox;
    }
    printf("\n");
    return;
}

int tamanho(Lista *l) {
    int tam = 0;
    No *p = l->ini;
    while (p != NULL) {
        tam++;
        p = p->prox;
    }
    return tam;
}

int tamanho_rec(No *p) {
    if (p == NULL)
        return 0;
    else
        return 1 + tamanho_rec(p->prox);
}

int esta_na_lista(Lista l, elem x) {
    while (l.ini != NULL) {
        if (l.ini->info == x)
            return 1;
        l.ini = l.ini->prox;
    }
    return 0;
}

int esta_na_lista_rec(No *p, elem x) {
    if (p == NULL)
        return 0;
    else {
        if (p->info == x)
            return 1;
        else
            return esta_na_lista_rec(p->prox, x);
    }
}

int elimina(Lista *l, elem x) {
    No *p, *ant;
    if (l->ini != NULL) {
        p = l->ini;
        ant = NULL;
        while (p != NULL) { // buscando
            if (p->info == x) { // achou
                if (p == l->ini)
                    l->ini = l->ini->prox; // elimina primeiro
                else
                    ant->prox = p->prox; // elimina outro
                if (p == l->fim)
                    l->fim = ant;
                free(p);
                return 0;
            }
            ant = p;
            p = p->prox;
        }
    }
    return 1; // nao achou
}

int elimina_rec(Lista *l, No *p, No *ant, elem x) {
    if (p == NULL)
        return 1; // nao achou
    else { // buscando
        if (p->info == x) { // achou
            // atualiza ponteiros
            if (p == l->ini)
                l->ini = l->ini->prox; // remove primeiro
            else
                ant->prox = p->prox; // remove outro
            if (p == l->fim)
                l->fim = ant; // atualiza fim
            
            // remove
            free(p);
            return 0;
        } else
            return elimina_rec(l, p->prox, p, x); // tenta eliminar na sublista
    }
}

int elimina2(Lista *l, elem x) {
    // chamada inicial da recursividade
    return elimina_rec(l, l->ini, NULL, x);
}

void troca_valores (No *i, No *j) {
    elem aux;
    aux = i->info;
    i->info = j->info;
    j->info = aux;
    return;
}

void ordena_valores(Lista *l) {
    No *i, *j;
    i = l->ini;
    while (i != l->fim) {
        j = i->prox;
        while (j != NULL) {
            if (i->info > j->info)
                troca_valores(i, j);
            j = j->prox;
        }
        i = i->prox;
    }
    return;
}

void troca_ponteiros (No **pi, No **pj, No **aponta_para_i, No **aponta_para_j) {
    No *aux;
    // atualiza a lista
    if ((*pi)->prox == (*pj)) {
        // caso 1: i e j em sequencia
        *aponta_para_i = *pj;
        aux = (*pj)->prox;
        (*pj)->prox = *pi;
        (*pi)->prox = aux;
    } else {
        // caso 2: i e j distantes
        aux = (*pi)->prox;
        (*pi)->prox = (*pj)->prox;
        (*pj)->prox = aux;
        *aponta_para_i = *pj;
        *aponta_para_j = *pi;
    }
    // troca i por j
    aux = *pi;
    *pi = *pj;
    *pj = aux;
    return;
}

void ordena_ponteiros(Lista *l) {
    No *i, *j, **aponta_para_i, **aponta_para_j;
    i = l->ini;
    aponta_para_i = &(l->ini);
    while (i != l->fim) {
        j = i->prox;
        aponta_para_j = &(i->prox);
        while (j != NULL) {
            if (i->info > j->info) {
                if (j == l->fim)
                    l->fim = i;
                troca_ponteiros(&i, &j, aponta_para_i, aponta_para_j);
            }
            aponta_para_j = &(j->prox);
            j = j->prox;
        }
        aponta_para_i = &(i->prox);
        i = i->prox;
    }
    return;
}