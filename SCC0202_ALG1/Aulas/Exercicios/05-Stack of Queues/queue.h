#define qSize 100
#define qString 10

typedef enum {
	integer, real, string
} types;

typedef union {
	int i;
	float f;
	char s[qString];
} type;

typedef struct q {
	type vec[qSize];
	int start, end, size;
	types t;
} Queue;

Queue queueCreate(types t);
void queueEmpty(Queue* q);
int queueIsFull(Queue q);
int queueIsEmpty(Queue q);
int queueSize(Queue q);
int queuePush(Queue* q, type x);
int queuePop(Queue* q, type* x);
