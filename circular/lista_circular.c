#include <stdio.h>
#include <stdlib.h>
#include "lista_circular.h"

nodo crearNodo(short valor){
    nodo nuevo = (nodo) malloc(sizeof(tipoNodo));
    if(nuevo == NULL){
        printf("Error: sin memoria\n");
        exit(1);
    }
    nuevo->dato = valor;
    nuevo->nxt = NULL;
    return nuevo;
}

lista crearLista(){
    lista nuevaLista = (lista) malloc(sizeof(tipoLista));
    if(nuevaLista == NULL){
        printf("Error: sin memoria\n");
        exit(1);
    }
    nuevaLista->top = NULL;
    return nuevaLista;
}

nodo ultimo(lista listaActual){
    nodo aux = listaActual->top;
    if(aux == NULL) return NULL;
    while(aux->nxt != listaActual->top){  // para cuando va a regresar al inicio
        aux = aux->nxt;
    }
    return aux;
}

void push(short valor, lista listaActual){
    nodo nuevo = crearNodo(valor);
    if(isEmpty(listaActual)){
        nuevo->nxt = nuevo;               // el unico nodo se apunta a si mismo
        listaActual->top = nuevo;
        return;
    }
    nodo fin = ultimo(listaActual);
    nuevo->nxt = listaActual->top;
    fin->nxt = nuevo;                     // re-cerrar el circulo
    listaActual->top = nuevo;
}

short pop(lista listaActual){
    if(isEmpty(listaActual)){
        printf("Error: lista vacia\n");
        return -1;
    }
    short valor;
    nodo tope = listaActual->top;
    valor = tope->dato;
    if(tope->nxt == tope){                // solo habia un nodo
        listaActual->top = NULL;
    } else {
        nodo fin = ultimo(listaActual);
        listaActual->top = tope->nxt;
        fin->nxt = listaActual->top;      // re-cerrar el circulo
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
    nuevo->nxt = listaActual->top;        // el nuevo es el ultimo: apunta a top
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
        do{                               // do-while: visitar antes de preguntar
            cont++;
            aux = aux->nxt;
        } while(aux != listaActual->top);
    }
    return cont;
}

int isEmpty(lista listaActual){
    return listaActual->top == NULL;
}

void imprimir(lista listaActual){
    if(isEmpty(listaActual)){
        printf("(vacia)\n");
        return;
    }
    nodo aux = listaActual->top;
    do{
        printf("%d ", aux->dato);
        aux = aux->nxt;
    } while(aux != listaActual->top);
    printf("\n");
}

void destruirLista(lista listaActual){
    while(!isEmpty(listaActual)){
        pop(listaActual);
    }
    free(listaActual);
}