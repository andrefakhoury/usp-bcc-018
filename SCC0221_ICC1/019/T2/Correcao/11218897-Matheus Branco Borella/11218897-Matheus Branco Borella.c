/* Trabalho 2 de ICC: Contando comentários.
 * Matheus Branco Borella. nUSP: 11218897.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Macro de debug. */
#define DBG_PRINT(...)

static const char*
GOOD[] = {
	"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei",
	"gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"
};
static unsigned int GOOD_COUNT = (sizeof(GOOD) / sizeof(const char*));

static const char*
BAD[] = {
	"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva",
	"odio", "pessima", "lento", "lenta", "fragil", "desisti"
};
static unsigned int BAD_COUNT = (sizeof(BAD) / sizeof(const char*));

static const char*
NEGATORS[] = {
	"nao", "jamais", "nunca"
};
static unsigned int NEGATORS_COUNT = (sizeof(NEGATORS) / sizeof(const char*));

/* Códigos de retorno de função. */
#define OK				0
#define ERR_MALLOC		1	/* Falha com memória.		*/
#define ERR_MALFORMED	2	/* Parâmetros inválidos.	*/
#define ERR_TODO		3	/* Função não implementada. */
#define ERR_EXISTS		4	/* Elemento já existe.		*/

/* Caracteres de separação de palavra reconhecidos. */
#define DELIMITERS "\n\t .,;\rØ"

/* Ponteiro para função de comparação binária entre dois elementos
 * de natureza genérica, retornando um valor positivo se o primeiro
 * elemento é maior que o segundo, menor que zero se esse for menor
 * e zero se os dois elementos forem iguais. */
typedef int(*BinComparator)(const void*, const void*);

/* Ponteiro para função de desconstrução dos dados associados aos nós
 * da árvore. Essa função é necessária pois a memória associada aos
 * nós é liberada durante a chamada de B_Delete(), e portanto, a função
 * deve saber como liberar os dados corretamente. */
typedef int(*BinDestructor)(void*);

typedef int(*BinMerger)(void*, void*);

/* Representa um dos nós de uma árvore binária. */
typedef struct
TreeNode
{
	void *key;				/* Chave associada ao nó.	*/
	void *data;				/* Dados associados ao nó.	*/
	struct TreeNode *left;	/* Nó filho à esquerda.		*/
	struct TreeNode *right;	/* Nó filho à direita.		*/
	struct TreeNode *up;	/* Nó pai acima.			*/
} BinTreeNode;

/* Representa uma árvore binária de busca. */
typedef struct
{
	BinComparator key_comp;		/* Comparador binário entre chaves.		*/
	BinDestructor data_destr;	/* Desconstrutor de dados.				*/
	BinMerger     data_merge;
	BinTreeNode *root;			/* Nó raiz da árvore.					*/
} BinTree;

/* Callback de iterador de travessia. */
typedef void(*BinTraversalCallback)(BinTreeNode*, void*);

void
B_New(
	BinTree* t,
	BinComparator key_comp,
	BinDestructor data_destr,
	BinMerger data_merge)
{
	t->key_comp   = key_comp;
	t->data_destr = data_destr;
	t->data_merge = data_merge;
	t->root = NULL;
}

void
B_FreeNode(BinTree *t, BinTreeNode *node)
{
	/* Ignora nós nulos. */
	if(node == NULL)
		return;

	B_FreeNode(t, node->left);
	B_FreeNode(t, node->right);

	if(t->data_destr != NULL)
		t->data_destr(node->data);

	free(node->data);
	free(node->key);

	node->left  = NULL;
	node->right = NULL;
	node->up	= NULL;
	node->data  = NULL;
	free(node);
}

int
B_Free(BinTree *t)
{
	if(t == NULL)
	{
		DBG_PRINT("B_Free(): Tree is NULL.\n");
		return ERR_MALFORMED;
	}

	B_FreeNode(t, t->root);
	t->key_comp = NULL;
	t->root = NULL;

	return OK;
}

BinTreeNode*
B_FindNode(BinTree b, const void *key)
{
	BinTreeNode *node;
	int direction;

	/* Anda a árvore a procura da chave. */
	node = b.root;
	if(node == NULL)
		return NULL;

	while((direction = b.key_comp(key, node->key)) != 0)
	{
		/* Se o próximo passo não existe, a busca terminou sem resultados. */
		if(direction < 0)
		{
			if(node->left == NULL)
				return NULL;
			else
				node = node->left;
		}
		else if(direction > 0)
		{
			if(node->right == NULL)
				return NULL;
			else
				node = node->right;
		}
	}

	return node;
}

int
B_PutNode(BinTree *t, BinTreeNode *n)
{
	if(t == NULL)
	{
		DBG_PRINT("B_PutNode(): Tree is NULL.\n");
		return ERR_MALFORMED;
	}

	BinTreeNode *node;
	BinTreeNode **target;

	if(n == NULL)
		return OK;

	node   = t->root;
	target = NULL;

	if(node == NULL)
		target = &t->root;
	else
	{
		int direction;
		while((direction = t->key_comp(n->key, node->key)) != 0)
		{
			if(direction < 0 && node->left == NULL)
			{
				target = &node->left;
				break;
			}
			else if(direction > 0 && node->right == NULL)
			{
				target = &node->right;
				break;
			}

			node = direction < 0 ? node->left : node->right;
		}
	}

	if(target == NULL)
	{
		DBG_PRINT("B_PutNode(): Node already exists.\n");
		return ERR_EXISTS;
	}

	n->up = node;
	*target = n;

	return OK;
}

BinTreeNode*
B_RemoveNode(BinTree *t, void *key)
{
	if(t == NULL)
	{
		DBG_PRINT("B_RemoveNode(): Tree is NULL.\n");
		return NULL;
	}

	BinTreeNode *node;
	node = B_FindNode(*t, key);

	if(node == NULL)
		return NULL;

	/* Desliga o no da arvore. */
	if(node->up != NULL)
	{
		if(t->key_comp(node->up->key, node->key) < 0)
			node->up->left = NULL;
		else
			node->up->right = NULL;
	}
	else t->root = NULL;

	B_PutNode(t, node->left);
	B_PutNode(t, node->right);

	node->up    = NULL;
	node->left  = NULL;
	node->right = NULL;

	return node;
}

void*
B_Find(BinTree t, const void *key)
{
	BinTreeNode *node;
	node = B_FindNode(t, key);

	if(node == NULL)
		return NULL;
	else
		return node->data;
}

int
B_Put(BinTree *t, void *key, void *data)
{
	if(t == NULL)
	{
		DBG_PRINT("B_Put(): Tree is NULL.\n");
		return ERR_MALFORMED;
	}

	BinTreeNode *node;
	node = malloc(sizeof(BinTreeNode));

	if(node == NULL)
	{
		DBG_PRINT("B_Put(): Cannot allocate memory for new node.\n");
		return ERR_MALLOC;
	}

	node->key = key;
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	node->up = NULL;

	int result = B_PutNode(t, node);
	if(result != OK)
	{
		DBG_PRINT("B_Put(): Cannot add node to tree.\n");
		free(node);
	}

	return result;
}

void*
B_Remove(BinTree *t, void *key)
{
	if(t == NULL)
	{
		DBG_PRINT("B_Remove(): Tree is NULL.\n");
		return NULL;
	}

	BinTreeNode *node;
	node = B_RemoveNode(t, key);
	if(node == NULL)
		return NULL;

	/* Libera memoria associada ao no. */
	void *data;
	data = node->data;

	free(node->key);
	free(node);

	return data;
}

int
B_Delete(BinTree *t, void *key)
{
	if(t == NULL)
	{
		DBG_PRINT("B_Delete(): Tree is NULL.\n");
		return ERR_MALFORMED;
	}

	void *data;
	data = B_Remove(t, key);

	if(t->data_destr != NULL)
		t->data_destr(data);

	free(data);
	return OK;
}

void
B_Traverse(BinTreeNode *node, BinTraversalCallback c, void* data)
{
	if(node == NULL)
		return;

	B_Traverse(node->left, c, data);
	B_Traverse(node->right, c, data);

	c(node, data);
}

void
B__MergeTraversalCallback(BinTreeNode *node, void* t)
{
	struct
	{
		BinTree *dst;
		BinTree *src;
	} *data;
	data = t;

	void *existing;
	existing = B_Find(*data->dst, node->key);
	if(existing != NULL)
	{
		node->left = NULL;
		node->right = NULL;
		data->dst->data_merge(existing, node->data);
		B_FreeNode(data->src, node);
	}
	else
	{
		node->left = NULL;
		node->right = NULL;
		B_PutNode(data->dst, node);
	}
}

int
B_Merge(BinTree *target, BinTree *src)
{
	struct
	{
		BinTree *dst;
		BinTree *src;
	} data;
	data.dst = target;
	data.src = src;

	B_Traverse(src->root, B__MergeTraversalCallback, &data);
	return OK; /* TODO: Add proper error checking here. */
}

int
StrKeyCompare(const void *a, const void *b)
{
	const char *c = a;
	const char *d = b;
	DBG_PRINT("strcmp(\"%s\", \"%s\") = %d\n", c, d, strcmp(c, d));
	return strcmp(c, d);
}

char *
StrNClone(const char *str, int length)
{
	char *a;
	unsigned int len;

	if(length < 0)
		len = strlen(str);
	else if(length > 0)
		len = length;
	else
		return NULL;

	a = malloc(len + 1);
	memcpy(a, str, len);
	a[len] = 0;

	return a;
}

char *
StrClone(const char *str)
{
	return StrNClone(str, -1);
}

char *
StrTrim(const char *str, const char *tok)
{
	unsigned int i, j;
	for(i = 0; i < strlen(str); ++i)
	{
		char c[2] = {str[i], 0};
		if(strspn(c, tok) == 0)
			break;
	}

	for(j = strlen(str); j > 0; --j)
	{
		char c[2] = {str[j - 1], 0};
		if(strspn(c, tok) == 0)
			break;
	}

	return StrNClone(&str[i], j - i);
}

/* Representa uma palavra na bag of words. */
typedef struct
{
	char         *word;		/* Conteúdo da palavra.				*/
	unsigned int occur;		/* Número de ocorrências.			*/
	unsigned int *indices;	/* Índices de palavra onde ocorre.	*/
} Token;

int
TokenDestructor(void* a)
{
	Token *b = a;

	if(b == NULL)
		return OK;

	free(b->word);
	free(b->indices);

	return OK;
}

int
TokenCount(BinTree *t, const char *word, unsigned int index)
{
	DBG_PRINT("counting %s @ %u\n", word, index);

	Token *token;
	token = B_Find(*t, word);
	if(token == NULL)
	{
		char *key = StrClone(word);
		char *dword = StrClone(word);

		unsigned int *indices = malloc(1 * sizeof(unsigned int));
		indices[0] = index;

		token = malloc(sizeof(Token));
		if(token == NULL)
		{
			DBG_PRINT("TokenCount(): Cannot allocate memory for token\n");
			return ERR_MALLOC;
		}

		token->word = dword;
		token->occur = 1;
		token->indices = indices;

		B_Put(t, key, token);
	}
	else
	{
		token->indices = realloc(token->indices,
			(++token->occur) * sizeof(unsigned int));
		token->indices[token->occur - 1] = index;
	}

	return OK;
}

int
TokenMerge(void *tgtp, void *srcp)
{
	Token *tgt = tgtp;
	Token *src = srcp;

	unsigned int max;
	unsigned int i, j;

	max = 0;
	for(i = 0; i < tgt->occur; ++i)
		if(max < tgt->indices[i])
			max = tgt->indices[i];

	tgt->occur += src->occur;
	tgt->indices = realloc(tgt->indices, tgt->occur * sizeof(unsigned int));
	if(tgt->indices == NULL)
		return ERR_MALLOC;

	j = i;
	for(; i < tgt->occur; ++i)
		tgt->indices[i] = src->indices[i - j] + max + 1;

	return OK;
}

typedef
struct
{
	unsigned int pos;
	unsigned int neg;
	BinTree tree;
} Product;

int
ProductMerge(void *a, void *b)
{
	Product *c = a;
	Product *d = b;

	c->pos += d->pos;
	c->neg += d->neg;
	B_Merge(&c->tree, &d->tree);
	return OK;
}

int
ProductFree(void *a)
{
	Product *b;
	b = a;

	B_Free(&b->tree);
	return OK;
}

/* Tokenize() -- Cria uma árvore de Tokens de uma string dada
 * uma string base e uma lista de separadores terminada em \0.
 * Parâmetros:
 * 		tokens:		Ponteiro para o ponteiro de Tokens.
 *		string:		A string base.
 *		separators:	Separadores.
 * Retorna:
 * 		OK quando bem-sucedida e algum código de erro se não.
 */
int
Tokenize(
	Product *t,
	const char *string,
	const char *separators)
{
	unsigned int i;		/* Índice do caractere atual.			*/
	unsigned int wb;	/* Índice do início da palavra atual.	*/
	unsigned int wi;	/* Índice da palavra atual.				*/
	unsigned int wl;	/* Tamanho em chars da palavra atual.	*/
	unsigned int j;		/* Iteradores.							*/
	int ni;				/* Índice do último negador que houve.	*/
	int direction;		/* Comentário positivo ou negativo.		*/

	B_New(&t->tree, StrKeyCompare, TokenDestructor, TokenMerge);
	t->pos = 0;
	t->neg = 0;

	wb = 0;
	wi = 0;
	wl = 0;
	ni = -1;
	direction = 0;


	for(i = 0; i < strlen(string) + 1; ++i)
	{
		char c[2] = {string[i], 0};
		if(strspn(c, separators) || c[0] == 0)
		{
			/* Ignora tokens vazios. */
			if(wl == 0)
			{
				++wb;
				continue;
			}

			/* Final de um token, adicione-o ao dicionário
			 * e comece a busca por um novo. */
			char *word = StrNClone(&string[wb], wl);

			for(j = 0; j < NEGATORS_COUNT; ++j)
				if(strcmp(NEGATORS[j], word) == 0)
					ni = wi;

			for(j = 0; j < GOOD_COUNT; ++j)
				if(strcmp(GOOD[j], word) == 0)
				{
					if(ni >= 0 && wi - ni <= 3)
					{
						--direction;
						ni = -1;
					}
					else ++direction;
				}

			for(j = 0; j < BAD_COUNT; ++j)
				if(strcmp(BAD[j], word) == 0)
				{
					if(ni >= 0 && wi - ni <= 3)
					{
						++direction;
						ni = -1;
					}
					else --direction;
				}
	

			TokenCount(&t->tree, word, wi);
			free(word);

			wb = i + 1;
			wl = 0;
			++wi;

			continue;
		}

		++wl;
	}

	if(direction > 0)
		++t->pos;
	else if(direction < 0)
		++t->neg;

	return OK;
}

void
print(BinTreeNode *node, void* data)
{
	Token *t = node->data;

	DBG_PRINT("\t");
	DBG_PRINT("%s: ", t->word);
	DBG_PRINT("x%u -> ", t->occur);

	for(unsigned int j = 0; j < t->occur; ++j)
		DBG_PRINT("@ %u, ", t->indices[j]);
	DBG_PRINT("\n");
}

void
print_trees(BinTreeNode *node, void *data)
{
	Product *p;
	p = node->data;

	DBG_PRINT("Product: %s <= pos: %u, neg: %u\n", (char*) node->key, p->pos, p->neg);
	B_Traverse(p->tree.root, print, data);
}

int
main()
{
	unsigned int cn, qn;	/* Numero de comentarios e de perguntas.	*/
	BinTree products;		/* Mapa de produtos.						*/
	unsigned int i, j;		/* Iteradores.								*/

	scanf("%u %u", &cn, &qn);

	B_New(&products, StrKeyCompare, ProductFree, ProductMerge);
	for(i = 0; i < cn; ++i)
	{
		char unused[2];
		char keyraw[50];
		char cmmraw[500];

		scanf(u8"%[^;]", keyraw);
		scanf(u8"%[;\n]", unused);
		scanf(u8"%[^Ø]", cmmraw);
		scanf(u8"%[Ø\n]", unused);

		char *cmm = StrTrim(cmmraw, DELIMITERS);
		char *key = StrTrim(keyraw, DELIMITERS);

		DBG_PRINT("\n====================\nKey: %s\nComment: %s\n\n", key, cmm);

		Product *prod;
		prod = malloc(sizeof(Product));
		if(Tokenize(prod, cmm, DELIMITERS) != OK)
		{
			DBG_PRINT("main(): Could not tokenize phrase.\n");
			return 1;
		}

		Product *existing;
		existing = B_Find(products, key);
		if(existing == NULL)
		{
			char *kc = StrClone(key);
			B_Put(&products, kc, prod);
		}
		else
		{
			ProductMerge(existing, prod);
			free(prod);
		}

		free(cmm);
		free(key);
	}
	DBG_PRINT("\n====================\n");
	B_Traverse(products.root, print_trees, NULL);

	DBG_PRINT("\n====================\n");
	for(j = 0; j < qn; ++j)
	{
		int used;
		int count;
		char buff[200];
		char queryr[20];
		char keyr[40];

		char *query;
		char *key;

		if(fgets(buff, 200, stdin) == NULL)
			break;

		used = 0;
		count = sscanf(buff, "palavra %s em %[^\n]", queryr, keyr);
		if(count > 0)
		{
			key = StrTrim(keyr, DELIMITERS);
			query = StrTrim(queryr, DELIMITERS);

			DBG_PRINT("looking for %s in %s\n", query, key);
			Product *t = B_Find(products, key);
			if(t == NULL)
				printf("no product %s\n", key);
			else
			{
				Token *tok;
				tok = B_Find(t->tree, query);
				if(tok == NULL)
					printf("0\n");
				else
					printf("%d\n", tok->occur);
			}

			used = 1;
			free(key);
			free(query);
		}

		count = sscanf(buff, "quantos %s em %[^\n]", queryr, keyr);
		if(count > 0)
		{
			key = StrTrim(keyr, DELIMITERS);
			query = StrTrim(queryr, DELIMITERS);
			DBG_PRINT("looking for %s in %s\n", query, key);
			
			Product *t = B_Find(products, key);
			if(t == NULL)
				printf("no product %s\n", key);
			else
			{
				if(strcmp("positivos", query) == 0)
					printf("%.1lf%%\n", (double) t->pos * 100.0 / (t->pos + t->neg));
				else if(strcmp("negativos", query) == 0)
					printf("%.1lf%%\n", (double) t->neg * 100.0 / (t->pos + t->neg));
			}

			used = 1;
			free(key);
			free(query);
		}

		if(!used)
			--j;
	}

	B_Free(&products);

	return 0;
}
