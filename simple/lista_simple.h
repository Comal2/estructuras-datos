#ifndef LISTA_SIMPLE_H
#define LISTA_SIMPLE_H

typedef struct node {
    short dato;
    struct node *nxt;
} tipoNodo, *nodo;

typedef struct {
    nodo top;
} tipoLista, *lista;

nodo crearNodo(short);
lista crearLista();
void push(short, lista);
short pop(lista);
void enqueue(short, lista);
short extract(lista);
void insert(short, int, lista);
int size(lista);
int isEmpty(lista);

#endif
