#include "buddy_alloc.h"

BuddyAllocator::BuddyAllocator(void *pool, size_t size)
{
    num_lev = 0;
    for (; num_lev < pow_lar(size); num_lev++) {
        if ((pow(2, num_lev) + sizeof(union node)*num_lev) > size) {
            num_lev-=1;
            break;
        }
    }
    std::cerr << "num_lev = " << num_lev << '\n';
    phead = (node **) pool;
    std::cerr << "here\n";
    phead[0] = (node *) pool + (num_lev + 1)*sizeof(union node *);
    for (int i = 0; i <= num_lev; i++) {
        phead[i] = phead[0]  + i;
        phead[i]->s.next = phead[i];
        phead[i]->s.prev = phead[i];
    }
    p0 = (node *) pool + (num_lev+1)*(sizeof(union node) + sizeof(union node *));
    std::cerr << "P: " << p0 << '\n';
    std::cerr << '\n';
    std::cerr << phead[0] << " " << phead[0]->s.prev << " " << phead[0]->s.next << '\n';
    phead[num_lev]->s.next = p0;
    phead[num_lev]->s.prev = p0;
    p0->s.next = phead[num_lev];
    p0->s.prev = phead[num_lev];
    p0->s.size= num_lev;
    p0->s.tag = 1;

}

void *BuddyAllocator::calloc(size_t n, size_t size)
{
    std::cerr << "calloc"  << '\n';
    void *p =BuddyAllocator:: malloc(n);
    int i = 0;
    for (; i < n*size;i++) {
        *((char *)p + i) &= 0;
    }
    return p;
}


void *BuddyAllocator::realloc(void*p, size_t size)
{
    std::cerr << "realloc"  << '\n';
    if (p == nullptr)
        return BuddyAllocator::malloc(size);
    void *ptr = BuddyAllocator::malloc(size);
    if (!ptr)
        return nullptr;
    memmove(ptr, p, size);
    free(p);
    return ptr;
}

void *BuddyAllocator::malloc(size_t nbytes)
{
    for (int j = 1; j <= num_lev; j++) {
        std::cerr << phead[j] << " " << phead[j]->s.next->s.next << " " << phead[j]->s.next  << " " << phead[j]->s.next->s.size << '\n';
    }
    int n = pow_lar(sizeof(union node) + nbytes);
    int i = n;
    std::cerr << "allocation = " << i <<'\n';
    while ((phead[i]->s.next == phead[i]) && i <= num_lev) {
        i++;
    }
    if (i > num_lev) {
        std::cerr << "no enough memory!\n";
        exit(1);
    } else if (i == n) {
        node * r = phead[i]->s.next;
        del(phead[i]->s.next);
        phead[i]->s.tag = 0;
        return (void *) (r + 1);
    } else {
        node * p = phead[i]->s.next;
        std::cerr << "phead next= " << p << " phead = " << phead[i]->s.next<< "phead = " << phead[i]->s.prev  << '\n';
        del(p);
        while (i != n) {
            p->s.tag = 0;
            p->s.size = i-1;
            node * buddy = (node *) ((char *) p + mem(i-1));
            buddy->s.size = i-1;
            buddy->s.tag = 1;
            push(phead[i-1], buddy);
            i--;
        }
        return (void *) (p + 1);
        }
}

void BuddyAllocator::free(void *p)
{
    if (!p)
        return;
    std::cerr << "free\n" ;
    node * pp =  (node *) p - 1;
    long int t = (pp - p0);
    node * buddy = (node *) ((t^mem(pp->s.size)) + (char *) p0);
    std::cerr << "FREE: " << (char *)buddy-(char *) pp << " " << buddy << " " << pp << " " << pp->s.size << '\n';
    while (pp->s.size != num_lev && buddy->s.tag == 1 && buddy->s.size == pp->s.size) {
        del(buddy);
        if (pp > buddy) {
            pp = buddy;
            }
        pp->s.size += 1;
        t = (pp - p0);
        buddy =(node *) ((t^mem(pp->s.size)) +(char *) p0);
    }
    pp->s.tag = 1;
    push(phead[pp->s.size], pp);
}

int BuddyAllocator::pow_lar(int x)
{
    int i = 0;
    int y = log2(x);
    for (;x != 0; x >>= 1, i++);
    if ((int) y == y)
        return i;
    else
        return i+1;
}

int BuddyAllocator::mem(int n)
{
    int m = 1;
    for (; n>0;n--)
        m *= 2;
    return m;
}
