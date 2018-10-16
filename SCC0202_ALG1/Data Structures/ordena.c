void list_sort(list* l) {
	node *i, *j;
	node *pi, *pj;

	i = l->begin;
	pi = NULL;

	while(i != l->end) {
		j = i->next;
		pj = i;

		while(j != NULL) {
			if (j->value < i->value) {

				if (i == l->begin) {
					if (j == l->end) l->end = i;

					l->begin = j;
					pj->next = i;

					node* aux = i->next;
					i->next = j->next;
					j->next = aux;
				} else {
					if (j == l->end) l->end = i;

					pi->next = j;
					pj->next = i;

					node* aux = i->next;
					i->next = j->next;
					j->next = aux;
				}

				node* aux = i;
				i = j;
				j = aux;
			}

			pj = j;
			j = j->next;
		}

		pi = i;
		i = i->next;
	}
}