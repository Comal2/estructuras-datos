
```c
#include <stdio.h>

#include <stdlib.h>

  

typedef struct node{

    short dato;

    struct node *nxt;

}tipoNodo, *nodo;

  

typedef struct{

    nodo top;

}tipoLista, *lista;

  

nodo crearNodo(short);

lista crearLista();

nodo ultimo(lista);               // devuelve el ultimo nodo

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

    return nuevo;

}

  

lista crearLista(){

    lista nuevaLista = (lista) malloc(sizeof(tipoLista));

    nuevaLista->top = NULL;

    return nuevaLista;

}

  

nodo ultimo(lista listaActual){

    nodo aux = listaActual->top;

    while(aux->nxt != listaActual->top){   // para cuando regresa al inicio

        aux = aux->nxt;

    }

    return aux;

}

  

void push(short valor, lista listaActual){

    nodo nuevo = crearNodo(valor);

    if(isEmpty(listaActual)){

        nuevo->nxt = nuevo;                // se apunta a si mismo

        listaActual->top = nuevo;

        return;

    }

    nodo fin = ultimo(listaActual);

    nuevo->nxt = listaActual->top;

    fin->nxt = nuevo;                      // el ultimo ahora apunta al nuevo top

    listaActual->top = nuevo;

}

  

short pop(lista listaActual){

    short valor;

    nodo tope = listaActual->top;

    valor = tope->dato;

    if(tope->nxt == tope){                 // solo hay un nodo

        listaActual->top = NULL;

    } else {

        nodo fin = ultimo(listaActual);

        listaActual->top = tope->nxt;

        fin->nxt = listaActual->top;       // cerrar el circulo de nuevo

    }

    free(tope);

    return valor;

}

  

void enqueue(short valor, lista listaActual){

    nodo nuevo = crearNodo(valor);

    if(isEmpty(listaActual)){

        nuevo->nxt = nuevo;

        listaActual->top = nuevo;

        return;

    }

    nodo fin = ultimo(listaActual);

    fin->nxt = nuevo;

    nuevo->nxt = listaActual->top;         // el nuevo es el ultimo, apunta al top

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

    for(i = 0; i < pos-1 && aux->nxt != listaActual->top; i++){

        aux = aux->nxt;

    }

    nodo nuevo = crearNodo(valor);

    nuevo->nxt = aux->nxt;

    aux->nxt = nuevo;

}

  

int size(lista listaActual){

    int cont = 0;

    if(!isEmpty(listaActual)){

        nodo aux = listaActual->top;

        do{

            cont++;

            aux = aux->nxt;

        } while(aux != listaActual->top);

    }

    return cont;

}

  

int isEmpty(lista listaActual){

    return listaActual->top == NULL;

}
```
