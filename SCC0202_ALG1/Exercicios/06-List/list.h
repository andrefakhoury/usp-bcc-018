typedef int var;

typedef strut node node;
typedef struct list {
	node *front, *back;
} list;

void list_create(list*);

void list_include(list*, var);