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
void push(short, lista);          // inserta al inicio
short pop(lista);                 // quita del inicio
void enqueue(short, lista);       // inserta al final (cola)
short extract(lista);             // quita del inicio (cola)
void insert(short, int, lista);   // inserta en una posicion
int size(lista);
int isEmpty(lista);

int main()
{
    lista l = crearLista();

    push(3, l);          // 3
    push(5, l);          // 5 3
    enqueue(9, l);       // 5 3 9
    insert(7, 1, l);     // 5 7 3 9

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

void push(short valor, lista listaActual){
    nodo nuevo = crearNodo(valor);
    nuevo->nxt = listaActual->top;
    listaActual->top = nuevo;
}

short pop(lista listaActual){
    short valor;
    nodo tope = listaActual->top;
    valor = tope->dato;
    listaActual->top = tope->nxt;
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
    while(aux->nxt != NULL){     // llegar al ultimo
        aux = aux->nxt;
    }
    aux->nxt = nuevo;
}

short extract(lista listaActual){
    return pop(listaActual);     // en la cola tambien se saca del inicio
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