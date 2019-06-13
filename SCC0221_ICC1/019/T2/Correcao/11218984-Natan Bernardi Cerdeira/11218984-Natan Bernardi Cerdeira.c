
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _DEBUG
    #define DEBUG(fmt, ...) printf(fmt "\n", __VA_ARGS__)
#else
    #define DEBUG(fmt, ...)
#endif

#define INITIAL_SIZE 20
#define GROWTH_FACTOR 1.5

#define PANIC(_MSG, ...)                                                                                    \
    do {                                                                                                    \
        fprintf(stderr, _MSG "\n", __VA_ARGS__);                                                            \
        fflush(stderr);                                                                                     \
        exit(1);                                                                                            \
    } while(0)

#define GROW_IF_NEEDED(_STRUCTURE, _ENTRY_TYPE)                                                             \
    do {                                                                                                    \
        if((_STRUCTURE)->size == (_STRUCTURE)->allocatedSize) {                                             \
            int newSize = ((_STRUCTURE)->allocatedSize == 0 ?                                               \
                INITIAL_SIZE :                                                                              \
                (_STRUCTURE)->allocatedSize * GROWTH_FACTOR);                                               \
            DEBUG("Growing " #_STRUCTURE " from %d to %d", (_STRUCTURE)->size, newSize);                    \
            if((_STRUCTURE)->entries == NULL) {                                                             \
                (_STRUCTURE)->entries = allocate(sizeof(_ENTRY_TYPE) * newSize);                            \
            } else {                                                                                        \
                (_STRUCTURE)->entries = reallocate((_STRUCTURE)->entries, sizeof(_ENTRY_TYPE) * newSize);   \
            }                                                                                               \
        }                                                                                                   \
    } while(0)

/**
 * Attempts to allocate `size` bytes and return the allocated
 * memory. If allocating fails this function panics. On success,
 * this function behaves the same as malloc.
 *
 * @param size Size of the block to allocate.
 *
 * @returns The allocated memory block.
 */
void* allocate(size_t size) {
    void* ptr = malloc(size);
    if(ptr == NULL) {
        PANIC("Failed to allocate %ld bytes", size);
    }
    return ptr;
}

/**
 * Attempts to reallocate `ptr` to `size` bytes. If reallocating
 * fails, this function panics. On success, this function behaves
 * the same as realloc.
 *
 * @param ptr Memory to reallocate.
 * @param size New size for the memory block.
 *
 * @returns The location of the resulting memory block.
 */
void* reallocate(void* ptr, size_t size) {
    void* newPtr = realloc(ptr, size);
    if(newPtr == NULL) {
        PANIC("Failed to reallocate %p to %ld bytes", ptr, size);
    }
    return newPtr;
}

char* POSITIVE[] = {
    "bom",
    "maravilhoso",
    "otimo",
    "sensacional",
    "excelente",
    "adorei",
    "gostei",
    "amei",
    "eficiente",
    "boa",
    "maravilhosa",
    "otima"
};

char* NEGATIVE[] = {
    "detestei",
    "odiei",
    "ruim",
    "pessimo",
    "terrivel",
    "raiva",
    "odio",
    "pessima",
    "lento",
    "lenta",
    "fragil",
    "desisti"
};

char* NEGATION[] = {
    "nao",
    "jamais",
    "nunca"
};

/**
 * Tests whether or not a word is considered positive.
 *
 * @param word Word to test.
 *
 * @returns 1 if the word is positive, 0 otherwise.
 */
int isPositive(char* word) {
    DEBUG("Testing if %s is a positive word", word);
    for(size_t i = 0; i < sizeof(POSITIVE)/sizeof(char*); i++) {
        if(strcmp(POSITIVE[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

/**
 * Tests whether or not a word is considered negative.
 *
 * @param word Word to test.
 *
 * @returns 1 if the word is negative, 0 otherwise.
 */
int isNegative(char* word) {
    DEBUG("Testing if %s is a negative word", word);
    for(size_t i = 0; i < sizeof(POSITIVE)/sizeof(char*); i++) {
        if(strcmp(NEGATIVE[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

/**
 * Tests whether or not a word is considered a negation.
 *
 * @param word Word to test.
 *
 * @returns 1 if the word is a negation, 0 otherwise.
 */
int isNegation(char* word) {
    DEBUG("Testing if %s is a negation word", word);
    for(size_t i = 0; i < sizeof(NEGATION)/sizeof(char*); i++) {
        if(strcmp(NEGATION[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

/**
 * Creates a copy of the given string. The copy is stored in the heap.
 *
 * The caller is responsible for freeing the string.
 *
 * @param str String to copy.
 *
 * @returns A copy of the string.
 */
char* copyString(char* str) {
    int l = strlen(str);
    char* dest = allocate(sizeof(char) * (l + 1));
    for(int i = 0; i < l; i++) {
        dest[i] = str[i];
    }
    dest[l] = '\0';
    return dest;
}

/**
 * Represents an entry in a bag of words. Associates a word with
 * the number of occurences it has.
 */
typedef struct BagEntry {
    int count;
    char* word;
} BagEntry;

/**
 * Represents a bag of words. This structure can be represented as
 * a map of words (char*) to counts (int).
 */
typedef struct Bag {
    int size; /* Number of valid elements in the `entries` vector. */
    int allocatedSize; /* Number of elements the `entries` vector can hold */
    BagEntry* entries; /* Vector containing the entries in this bag */
    int words; /* Number of words in the bag - length of the `inOrder` vector */
    int* inOrder; /* Indices of the `entries` vector with the order the words appear */
} Bag;

/**
 * Creates an empty bag of words. After it's been used, `bag_free`
 * should be called on it.
 *
 * @returns A new bag of words.
 */
Bag* bag_new() {
    Bag* bag = calloc(sizeof(Bag), 1);
    bag->entries = NULL;
    bag->inOrder = NULL;
    bag->size = bag->allocatedSize = 0;
    bag->words = 0;
    return bag;
}

/**
 * Releases the memory used by a bag. After calling this function,
 * the bag is invalidated and may not be used.
 *
 * @param bag Bag to free.
 */
void bag_free(Bag* bag) {
    //check if the vector actually exists - it won't while the bag is empty
    if(bag->entries != NULL) {
        for(int i = 0; i < bag->size; i++) {
            free(bag->entries[i].word);
        }
        free(bag->entries);
        free(bag->inOrder);
    }
    free(bag);
}

/**
 * Appends an index to the `inOrder` vector of the bag.
 * The word on that position of the `entries` vector
 * will be considered the next word to appear in the comment
 * when iterating this bag.
 *
 * @param bag Bag to modify.
 * @param index Index to insert.
 */
void bag_append_word_index(Bag* bag, int index) {
    if(bag->inOrder == NULL) {
        bag->inOrder = allocate(sizeof(int));
    } else {
        bag->inOrder = reallocate(bag->inOrder, sizeof(int) * (bag->words + 1));
    }
    bag->inOrder[bag->words++] = index;
}

/**
 * Inserts a word into the bag if it's not present, otherwise increases it's
 * count by 1. A copy of the word will be made before inserting.
 *
 * @param bag Bag where the word should be inserted.
 * @param word Word to insert.
 */
void bag_insert(Bag* bag, char* word) {
    DEBUG("Inserting word %s into bag %p", word, bag);
    //try finding the word before growing the vector
    for(int i = 0; i < bag->size; i++) {
        if(strcmp(bag->entries[i].word, word) == 0) {
            bag->entries[i].count++;
            bag_append_word_index(bag, i);
            return;
        }
    }
    GROW_IF_NEEDED(bag, BagEntry);
    bag->entries[bag->size].word = copyString(word);
    bag->entries[bag->size].count = 1;
    bag_append_word_index(bag, bag->size);
    bag->size++;
}

/**
 * Returns the count of the provided word in the bag.
 *
 * @param bag Bag where the word should be searched for.
 * @param word Word to search for.
 *
 * @returns The amount of times the word was inserted into the bag.
 */
int bag_count(Bag* bag, char* word) {
    for(int i = 0; i < bag->size; i++) {
        if(strcmp(bag->entries[i].word, word) == 0) {
            return bag->entries[i].count;
        }
    }
    return 0;
}

/**
 * Represents a list of bags.
 */
typedef struct BagList {
    int size;
    Bag** bags;
} BagList;

/**
 * Creates a new list of bags. After it's been used, `baglist_free`
 * should be called on it.
 *
 * @returns A new list of bags.
 */
BagList* baglist_new() {
    BagList* list = calloc(sizeof(BagList), 1);
    list->size = 0;
    list->bags = NULL;
    return list;
}

/**
 * Releases the memory used by a list. After calling this function,
 * the list is invalidated and may not be used.
 *
 * @param list List to free.
 */
void baglist_free(BagList* list) {
    if(list->bags != NULL) {
        for(int i = 0; i < list->size; i++) {
            bag_free(list->bags[i]);
        }
        free(list->bags);
    }
    free(list);
}

/**
 * Creates and inserts a new bag into the list, returning it.
 *
 * @param list List to insert a new bag.
 *
 * @returns The inserted bag
 */
Bag* baglist_insert(BagList* list) {
    if(list->bags == NULL) {
        list->bags = allocate(sizeof(Bag*));
    } else {
        list->bags = reallocate(list->bags, sizeof(Bag*) * (list->size + 1));
    }
    Bag* bag = bag_new();
    DEBUG("Inserting bag %p into baglist %p", bag, list);
    list->bags[list->size++] = bag;
    return bag;
}

/**
 * Represents an entry in a map of bags. Associates a product with
 * a list of bags.
 */
typedef struct MapEntry {
    char* product;
    BagList* baglist;
} MapEntry;

/**
 * Represents a map of products (char*) to lists of bags (BagList*).
 */
typedef struct Map {
    int size;
    int allocatedSize;
    MapEntry* entries;
} Map;

/**
 * Creates an empty map. After it has been used, `map_free` shoud
 * be called on it.
 *
 * @returns A new map of bags.
 */
Map* map_new() {
    Map* map = calloc(sizeof(Map), 1);
    map->entries = NULL;
    map->size = map->allocatedSize = 0;
    return map;
}

/**
 * Releases the memory used by a map. After calling this function,
 * the map is invalidated and may not be used.
 *
 * @param map Map to free.
 */
void map_free(Map* map) {
    if(map->entries != NULL) {
        for(int i = 0; i < map->size; i++) {
            baglist_free(map->entries[i].baglist);
            free(map->entries[i].product);
        }
        free(map->entries);
    }
    free(map);
}

/**
 * Returns the bag list for the given product. If there isn't one in the map,
 * a new bag list is created and inserted.
 *
 * @param map Map of the wanted bag list.
 * @param product Product identifying the wanted bag list.
 *
 * @returns The bag list associated with the provided product.
 */
BagList* map_at(Map* map, char* product) {
    for(int i = 0; i < map->size; i++) {
        if(strcmp(map->entries[i].product, product) == 0) {
            return map->entries[i].baglist;
        }
    }
    DEBUG("Inserting baglist for product %s into map %p", product, map);
    GROW_IF_NEEDED(map, MapEntry);
    BagList* baglist = baglist_new();
    map->entries[map->size].product = copyString(product);
    map->entries[map->size].baglist = baglist;
    map->size++;
    DEBUG("New baglist = %p", baglist);
    return baglist;
}

/**
 * Trims any trailing whitespace from a string.
 * Trimming is implemented by replacing whitespace
 * (only ' ' is supported) with the null character.
 *
 * @param string String to trim.
 *
 * @returns The provided string, after trimming.
 */
char* trim(char* string) {
    for(int i = strlen(string) - 1; i >= 0; i--) {
        if(string[i] == ' ') {
            string[i] = 0;
        } else {
            break;
        }
    }
    return string;
}

/**
 * Holds a buffer and it's size, used for reading strings
 * from the standard input.
 */
typedef struct {
    int size;
    char* data;
    int nextChar;
    int hasNextChar;
} InputBuffer;

/**
 * Global buffer used for storing strings being read from
 * the standard input. Since this program is single threaded
 * it's safe to have a global buffer.
 */
InputBuffer buffer;

/**
 * Sets up the input buffer used for reading strings from
 * the standard input.
 */
void setup_input_buffer() {
    buffer.size = 0;
    buffer.data = allocate(0);
    buffer.hasNextChar = 0;
}

/**
 * Destroys the input buffer used for reading strings from
 * the standard input.
 */
void destroy_input_buffer() {
    free(buffer.data);
}

/**
 * Ensures the input buffer is big enough to hold at
 * least `size` characters.
 *
 * @param size Minimum size the input buffer needs to have.
 */
void ensure_input_buffer_size(int size) {
    if(size >= buffer.size) {
        int newSize = buffer.size + 20;
        if(size > newSize) {
            newSize = size;
        }
        buffer.data = realloc(buffer.data, newSize);
        buffer.size = newSize;
    }
}

/**
 * Reads the next char from standard input, transforming
 * CRLF into LF. A single CR (that is, not followed by a LF)
 * is returned as-is.
 *
 * @returns The next char from standard input.
 */
char readChar() {
    if(buffer.hasNextChar) {
        buffer.hasNextChar = 0;
        return (char) buffer.nextChar;
    }
    char c = getchar();
    if(c == '\r') {
        char d = getchar();
        if(d == '\n') {
            return d;
        } else {
            buffer.nextChar = (int) d;
            buffer.hasNextChar = 1;
            return c;
        }
    }
    return c;
}

/**
 * Reads a string from the standard input until one of the
 * characters in the delimiters string is reached. The delimiter
 * character is not included in the returned string. The returned
 * value is only valid until this function is called again. If
 * EOF is reached while reading, this function will stop reading
 * and return the characters read, as if a delimiter had been
 * found.
 *
 * @param delimiters Characters to be used as delimiters.
 *
 * @returns A string with the characters read until the first
 *          delimiter was reached.
 */
char* readString(char* delimiters) {
    int len = strlen(delimiters);
    int index = 0;
    while(1) {
        char current = readChar();
        if(current == EOF) {
            ensure_input_buffer_size(index + 1);
            buffer.data[index] = 0;
            return buffer.data;
        }
        for(int i = 0; i < len; i++) {
            if(delimiters[i] == current) {
                ensure_input_buffer_size(index + 1);
                buffer.data[index] = 0;
                return buffer.data;
            }
        }
        ensure_input_buffer_size(index + 1);
        buffer.data[index++] = current;
    }
    PANIC("Unreachable location reached (%s:%d)", __FILE__, __LINE__);
    return NULL;
}

/**
 * Returns 1 if the target string ends with the provided
 * ending, 0 otherwise.
 *
 * @param target Target string.
 * @param ending Ending to test.
 *
 * @returns 1 if the target string ends with ending, 0 otherwise
 */
int endsWith(char* target, char* ending) {
    int lenT = strlen(target);
    int lenE = strlen(ending);
    if(lenE > lenT) {
        return 0;
    }
    for(int i = 1; i <= lenE; i++) {
        if(target[lenT - i] != ending[lenE - i]) {
            return 0;
        }
    }
    return 1;
}

/**
 * Reads a comment and inserts it's data into the map.
 * This function reads the product name until a ';' is
 * reached, removing any trailing whitespace and using
 * the result as the map key (`key = trim(readString(";"))`).
 * Then, it reads each word until the `Ø` terminator and
 * inserts into the bag for the product.
 *
 * @param map Map to insert the data.
 */
void handleComment(Map* map) {
    Bag* bag = baglist_insert(map_at(map, trim(readString(";"))));
    while(1) {
        char* word = readString(" \n");
        if(strlen(word) > 0) {
            DEBUG("Read %s", word);
        }
        int done = endsWith(word, "Ø");
        if(done) {
            word[strlen(word) - strlen("Ø")] = 0;
            DEBUG("Removed trailing identifier: %s", word);
        }
        //don't waste time/memory with empty strings
        if(strlen(word) > 0) {
            bag_insert(bag, word);
        }
        if(done) {
            return;
        }
    }
}

/**
 * Counts the number of bags in the list that match the
 * `direct` predicate, or are negated and match the `inverse`
 * predicate.
 *
 * @param list List of bags to test.
 * @param direct Direct predicate, testing the wanted result.
 * @param inverse Inverse predicate, testing the opposite result.
 *
 * @returns The number of bags that match the filter.
 */
int count(BagList* list, int (*direct)(char*), int (*inverse)(char*)) {
    int result = 0;
    for(int i = 0; i < list->size; i++) {
        Bag* bag = list->bags[i];
        int negationCounter = 0; //set to 3 when a negation is found, decreased for each
                                 //additional word, set to 0 on a positive/negative word.
        for(int j = 0; j < bag->words; j++) {
            char* word = bag->entries[bag->inOrder[j]].word;
            if(isNegation(word)) {
                DEBUG("Negation word: %s", word);
                negationCounter = 3;
                continue;
            }
            if((negationCounter < 1 && direct(word)) || (negationCounter > 0 && inverse(word))) {
                DEBUG("Got match: %s, direct = %d", word, direct(word));
                result++;
                break;
            }
            DEBUG("Regular word: %s", word);
            negationCounter--;
        }
    }
    return result;
}

/**
 * Reads and interprets a question.
 * The two types of questions can be identified by the
 * first word:
 * - palavra: read one word (target), drop one word, read rest of line (product)
 *    - count how many times `target` appears in each bag of `product` and print.
 * - quantos: read one word, compare to "negativos", drop one word, read rest of line (product)
 *    - with `list` being the list of bags for `product`
 *    - if counting negatives, print `count(list, &isNegative, &isPositive)`
 *    - if counting positives, print `count(list, &isPositive, &isNegative)`
 *
 * @param map Map to read data from.
 */
void handleQuestion(Map* map) {
    char* word = readString(" ");
    DEBUG("Question type = %s", word);
    if(strcmp(word, "palavra") == 0) {
        char* target = copyString(readString(" "));
        readString(" "); // "em"
        char* product = readString("\n");
        DEBUG("Target = %s, product = %s", target, product);
        BagList* list = map_at(map, product);
        int total = 0;
        for(int i = 0; i < list->size; i++) {
            total += bag_count(list->bags[i], target);
        }
        printf("%d\n", total);
        free(target);
    } else if(strcmp(word, "quantos") == 0) {
        char* type = readString(" ");
        int negative = strcmp(type, "negativos") == 0;
        if(!negative && strcmp(type, "positivos") != 0) {
            PANIC("Unknown type %s", type);
        }
        readString(" "); // "em"
        char* product = readString("\n");
        DEBUG("Type = %s, product = %s", negative ? "negative" : "positive", product);
        BagList* list = map_at(map, product);
        float matching = negative ? count(list, &isNegative, &isPositive) : count(list, &isPositive, &isNegative);
        printf("%.1f%%\n", matching / list->size * 100);
    } else {
        printf("panic\n");
        PANIC("Unknown word %s", word);
    }
}

int main(void) {
    setup_input_buffer();
    Map* map = map_new();
    int sentences, questions;
    scanf("%d %d", &sentences, &questions);
    readChar(); /* drop \r\n */
    for(int i = 0; i < sentences; i++) {
        handleComment(map);
    }
    for(int i = 0; i < questions; i++) {
        handleQuestion(map);
    }
    map_free(map);
    destroy_input_buffer();
}
