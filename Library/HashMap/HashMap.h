typedef struct linknode
{
    char *str;
    struct linknode *next;
} linknode;

typedef struct hashMap
{
    linknode **arr;
    int size;
} hashMap;

void initHash(hashMap **h, int size);
void add(hashMap **h, int i, char *str);
void rem(hashMap **h, int i);
char *getHashVal(hashMap *h, int i);
void traverse(hashMap *h);
int hashCount(hashMap *h);
