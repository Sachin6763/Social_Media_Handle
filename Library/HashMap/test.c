#include "HashMap.h"
#include <stdio.h>

int main()
{

    hashMap hM;
    hashMap *h = &hM;
    init(&h, 20);
    printf("hello \n");
    add(&h, 2, "sachin");
    add(&h, 3, "shreyash");
    add(&h, 4, "manthan");
    add(&h, 4, "ravi");
    traverse(h);
    return 0;
}