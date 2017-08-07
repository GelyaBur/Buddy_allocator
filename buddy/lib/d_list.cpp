#include <cstdio>
#include <cstdlib>
#include "d_list.h"
#include <iostream>

void push(node * phead, node * block)
{
    node * t = phead->s.next;
    phead->s.next = block;
    block->s.prev = phead;
    block->s.next = t;
    t->s.prev = block;
}

void del(node * block)
{
    block->s.prev->s.next = block->s.next;
    block->s.next->s.prev = block->s.prev;
}

void printlist(node * phead)
{
    node * cur = phead->s.next;
    while (cur != phead) {
        printf("size = %d\n", cur->s.size);
        cur = cur->s.next;
    }
}
