union node {
   struct {
       int size;
       int tag;
       union node *next;
       union node *prev;
   } s;
   char c[32];
};


void push(node *, node *);
void printlist(node *);
void del(node *);

