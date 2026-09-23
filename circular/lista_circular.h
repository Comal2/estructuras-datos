#ifndef LISTA_CIRCULAR_H
#define LISTA_CIRCULAR_H

typedef struct node {
    short dato;
    struct node *nxt;
} tipoNodo, *nodo;

typedef struct {
    nodo top;
} tipoLista, *lista;

nodo crearNodo(short valor);
lista crearLista();
nodo ultimo(lista listaActual);
void push(short valor, lista listaActual);
short pop(lista listaActual);
void enqueue(short valor, lista listaActual);
short extract(lista listaActual);
void insert(short valor, int pos, lista listaActual);
int size(lista listaActual);
int isEmpty(lista listaActual);
void imprimir(lista listaActual);
void destruirLista(lista listaActual);

#endif