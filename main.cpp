#include <cstdio>
#include <cstring>
#include <ctime>
struct data
{
    char imie[13];
    char nazwisko[13];
};

struct node
{
    node* parent;
    node* L;
    node* R;
    int count;
    int key;
    data d;
};

node * root = NULL;

node * getNode(int n, node * tree)
{
    int x = 0;
    int y = 0;
    if(tree->L)x+=tree->L->count;
    if(tree->R)y+=tree->R->count;
    if(n < x)return getNode(n, tree->L);
    if(n == x)return tree;
    return getNode(n-x-1, tree->R);
}

node * getNext(node * tree)
{
    if(tree->L == NULL) return 0;
    tree = tree->L;
    while(tree->R)
    {
        tree = tree->R;
    }
    return tree;
}

//inserts y into place where x was before
void replace(node* x, node* y)
{

    if(root == x)
    {
        node* p = y->parent;
        node* lefto = x->L;

        if(p->L == y) p->L = x;
        else p->R = x;

        x->parent=y->parent;

        root = y;
        y->parent = NULL;

        y->R = x->R;
        x->R = NULL;
        if(x->L == y)
        {x->L = y->L;
        y->L=NULL;}
        else {
            x->L = y->L;
                y->L = lefto;}


    }
    else
    {


        node* z = x->parent;
        node* p = y->parent;
        node* lefto = x->L;

        if(z->L == x)
        {
            if(p->L == y) y->L = x;
            else p->R = x;
            z->L = y;

        }
        else
        {
            if(p->L == y) y->L = x;
            else p->R = x;
            z->R = y;
        }

        y->R = x->R;
        x->R = NULL;

        if(lefto == y) {
         x->L = y->L;
                y->L = NULL;}

        else {
                 x->L = y->L;
        y->L = lefto;}


        /*  node* z = x->parent;
          node* l = y->L;
          node* p = y->parent;
          if(z->L == x) z->L = y;
          else z->R = y;

          y->parent = z;
          y->R = x->R;





          if(x->L == y)
              {
                  y->L = x;
          x->parent = y;
        }
          else
          {
                  y->L = x->L;
                  x->parent = p;
          }

          x->R = NULL;
          if(l==NULL)x->L = NULL;
          else x->L = l;*/
    }
}

void replaceAndDelete(node * n, node * m)
{
    node * parent = n->parent;
    if(parent->L == n) parent->L = m;
    if(parent->R == n) parent->R = m;
    delete n;
}
/*
void recalc(node * x)
{
    x->count = 1;
    if(x->L)x->count += x->L->count;
    if(x->R)x->count += x->R->count;
}

void lrotation(node* x)
{
    node* y = x->L;
    x->L = y->R;
    y->R = x;
    replace(x,y);
    x->parent = y;
    recalc(x);
    recalc(y);
}

void rrotation(node* x)
{
    node* y = x->R;
    x->R = y->L;
    y->L = x;
    replace(x,y);
    x->parent = y;
    recalc(x);
    recalc(y);
}
*/
node* find(int key, node * current, bool muv = 1)
{
    if(current->key == key)return current;
    if(current->key > key)
    {
        if(current->L) return find(key, current->L);
        return current;
    }
    if(current->R) return find(key, current->R);
    return current;
}

int remove(int key)
{

    node * n = find(key, root);

    if(root == n && root->L == NULL && root->R == NULL)
    {

        delete root;
        root=NULL;
        return 0;
    }



    node * m = getNext(n);


    if(m==NULL)  //nie ma lewego dziecka - podpinamy prawego
    {


        replaceAndDelete(n, n->R);

    }
    else   //zamieniamy m z n i usuwamy potem
    {
        replace(n,m);
            node * parent = m->parent;
    if(parent->L == m) parent->L = m->L;
    if(parent->R == m) parent->R = m->L;
    delete m;
     //  replaceAndDelete(m, m->L);
    }

    if(!n)return 0;
    return 1;
}

bool add(int key, data d)
{
    node * parent = NULL;
    node * n = new node;
    n->count = 1;
    n->key = key;
    n->L = NULL;
    n->R = NULL;
    strcpy(n->d.imie, d.imie);
    strcpy(n->d.nazwisko, d.nazwisko);
    if(root)
    {
        parent = find(key, root, NULL);
        if(parent->key == key)return 0;
        n->parent = parent;
        if(parent->key > key)parent->L = n;
        else parent->R = n;
        parent->count++;
    }
    else
    {
        root = n;
        n->parent = n;
    }
    return 1;
}

void add(int key)
{
    data d;
    add(key, d);
}

void printNode(node *n)
{
    if (n == NULL) return;
    printf("%d\n",n->key);
    printf("left: ");
    printNode(n->L);
    printf("right: ");
    printNode(n->R);
}

void printTree()
{
    printNode(root);
}

int main(int argc, char* argv[])
{
    int n;
    char c;
    data dane;
    unsigned long time;

    while(1)
    {
        scanf("%c",&c);
        switch (c)
        {
        case 'a': //if(c=='a')
        {
            scanf("%d %s %s", &n, dane.imie, dane.nazwisko);
            if(add(n,dane))
            {
                printf("Added.\n");
            }
            else
                printf("Not added - Already here.\n");
        }
        break;
        case 'f': //else if(c=='f')
        {
            scanf("%d", &n);
            node * f = find(n, root);
            if(f->key == n)
                printf("Indeks: %d Imie: %s Nazwisko %s\n",n,f->d.imie, f->d.nazwisko);
            else printf("Nie znaleziono kurwa.\n");
        }
        break;
        case 'd': //else if(c=='r')
        {
            scanf("%d", &n);
            node * f = find(n, root);

            if(f->key == n)
            {
                remove(n);
                printf("usunieto\n");
            }
            else printf("Nie usunieto kurwa.\n");
        }
        break;
        case 's':
            time = clock();
            break;
        case 't':
            printf("%lu \n", clock() - time);
            break;
        case 'p': //else
        {

            printTree();
        }
        }
    }
}
