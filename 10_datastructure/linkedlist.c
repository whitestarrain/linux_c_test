#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>

static link head = NULL;

link make_node(unsigned char item)
{
    // sizeof get size by expression's type, not variable content
    link p  = malloc(sizeof(*p));
    p->item = item;
    p->next = NULL;
    return p;
}

void free_node(link p)
{
    free(p);
}

link search(unsigned char key)
{
    link p;
    for (p = head; p; p = p->next) {
        if (p->item == key) {
            return p;
        }
    }
    return NULL;
}

void insert(link p)
{
    p->next = head;
    head    = p;
}

void delete_node(link p)
{
    link pre;
    if (p == head) {
        head = p->next;
        return;
    }
    for (pre = head; pre; pre = pre->next) {
        if (pre->next == p) {
            pre->next = p->next;
            return;
        }
    }
}

void delete_node_v2(link p)
{
    link *pnext;
    for (pnext = &head; *pnext; pnext = &(*pnext)->next) {
        if (*pnext == p) {
            *pnext = p->next;
            return;
        }
    }
}

void traverse(void (*visit)(link))
{
    link p;
    for (p = head; p; p = p->next) visit(p);
}

void destroy(void)
{
    link q, p = head;
    head = NULL;
    while (p) {
        q = p;
        p = p->next;
        free_node(q);
    }
}


void push(link p)
{
    insert(p);
}
link pop(void)
{
    if (head == NULL)
        return NULL;
    else {
        link p = head;
        head   = head->next;
        return p;
    }
}


void print_item(link p)
{
    printf("%d\n", p->item);
}

void reverse()
{
    link p1    = head;
    link p2    = head == NULL ? NULL : head->next;
    head->next = NULL;
    while (p2) {
        link tmp = p2->next;
        p2->next = p1;
        p1       = p2;
        p2       = tmp;
    }
    head = p1;
}


int main(int argc, char *argv[])
{
    for (int i = 0; i < 2; i++) {
        link p = make_node(i);
        insert(p);
    }
    for (link p = head; p; p = p->next) {
        printf("%d\n", p->item);
    }

    printf("\n");
    reverse();

    for (link p = head; p; p = p->next) {
        printf("%d\n", p->item);
    }
    return 0;
}
