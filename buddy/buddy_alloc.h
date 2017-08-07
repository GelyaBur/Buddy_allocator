#include <cstdio>
#include <cstdlib>
#include "d_list.h"
#include <cstring>
#include <cmath>
#include <iostream>

//class BuddyAllocator {
//public:
//    BuddyAllocator(void *pool, size_t size) {};
//    void *malloc(size_t size) {return ::malloc(size);};
//    void free(void *p) {::free; return;};
//    void *realloc(void *p, size_t size) {return ::realloc(p, size);};
//    void *calloc(size_t n, size_t size) {return ::calloc(n, size);};
//};
class BuddyAllocator {
public:
    BuddyAllocator(void *pool, size_t size);
    void *malloc(size_t size);
    void free(void *p);
    void *realloc(void *p, size_t size);
    void *calloc(size_t n, size_t size);
    int mem(int);
    int pow_lar(int);
private:
    node **phead;
    node * p0;
    int num_lev;
};



