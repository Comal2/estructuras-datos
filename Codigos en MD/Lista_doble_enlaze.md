
```c
#include <stdio.h>

#include <stdlib.h>

  

typedef struct node{

    short dato;

    struct node *nxt;

    struct node *prv;

}tipoNodo, *nodo;

  

typedef struct{

    nodo top;

}tipoLista, *lista;

  

nodo crearNodo(short);

lista crearLista();

void push(short, lista);

short pop(lista);

void enqueue(short, lista);

short extract(lista);

void insert(short, int, lista);

int size(lista);

int isEmpty(lista);

  

int main()

{

    lista l = crearLista();

  

    push(3, l);

    push(5, l);

    enqueue(9, l);

    insert(7, 1, l);     // 5 7 3 9

  

    printf("size: %d\n", size(l));

    printf("pop: %d\n", pop(l));

    printf("extract: %d\n", extract(l));

  

    while(!isEmpty(l)){

        printf("%d ", extract(l));

    }

    return 0;

}

  

nodo crearNodo(short valor){

    nodo nuevo = (nodo) malloc(sizeof(tipoNodo));

    nuevo->dato = valor;

    nuevo->nxt = NULL;

    nuevo->prv = NULL;

    return nuevo;

}

  

lista crearLista(){

    lista nuevaLista = (lista) malloc(sizeof(tipoLista));

    nuevaLista->top = NULL;

    return nuevaLista;

}

  

void push(short valor, lista listaActual){

    nodo nuevo = crearNodo(valor);

    nuevo->nxt = listaActual->top;

    if(listaActual->top != NULL){

        listaActual->top->prv = nuevo;   // el de atras apunta al nuevo

    }

    listaActual->top = nuevo;

}

  

short pop(lista listaActual){

    short valor;

    nodo tope = listaActual->top;

    valor = tope->dato;

    listaActual->top = tope->nxt;

    if(listaActual->top != NULL){

        listaActual->top->prv = NULL;

    }

    free(tope);

    return valor;

}

  

void enqueue(short valor, lista listaActual){

    nodo nuevo = crearNodo(valor);

    if(isEmpty(listaActual)){

        listaActual->top = nuevo;

        return;

    }

    nodo aux = listaActual->top;

    while(aux->nxt != NULL){

        aux = aux->nxt;

    }

    aux->nxt = nuevo;

    nuevo->prv = aux;                    // enlazar hacia atras

}

  

short extract(lista listaActual){

    return pop(listaActual);

}

  

void insert(short valor, int pos, lista listaActual){

    if(pos <= 0 || isEmpty(listaActual)){

        push(valor, listaActual);

        return;

    }

    nodo aux = listaActual->top;

    int i;

    for(i = 0; i < pos-1 && aux->nxt != NULL; i++){

        aux = aux->nxt;

    }

    nodo nuevo = crearNodo(valor);

    nuevo->nxt = aux->nxt;

    nuevo->prv = aux;

    if(aux->nxt != NULL){

        aux->nxt->prv = nuevo;           // el siguiente apunta al nuevo

    }

    aux->nxt = nuevo;

}

  

int size(lista listaActual){

    int cont = 0;

    nodo aux = listaActual->top;

    while(aux != NULL){

        cont++;

        aux = aux->nxt;

    }

    return cont;

}

  

int isEmpty(lista listaActual){

    return listaActual->top == NULL;

}
```
