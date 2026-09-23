#include <stdio.h>
#include <stdlib.h>
#include "lista_doble.h"

nodo crearNodo(short valor){
    nodo nuevo = (nodo) malloc(sizeof(tipoNodo));
    if(nuevo == NULL){
        printf("Error: sin memoria\n");
        exit(1);
    }
    nuevo->dato = valor;
    nuevo->nxt = NULL;
    nuevo->prv = NULL;
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

void push(short valor, lista listaActual){
    nodo nuevo = crearNodo(valor);
    nuevo->nxt = listaActual->top;
    if(listaActual->top != NULL){
        listaActual->top->prv = nuevo;   // actualizar la ida Y la vuelta
    }
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
    listaActual->top = tope->nxt;
    if(listaActual->top != NULL){
        listaActual->top->prv = NULL;    // el nuevo top ya no tiene anterior
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
    nuevo->prv = aux;                    // enlazar la vuelta
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
    nuevo->nxt = aux->nxt;               // 1
    nuevo->prv = aux;                    // 2
    if(aux->nxt != NULL){
        aux->nxt->prv = nuevo;           // 3 (solo si hay nodo despues)
    }
    aux->nxt = nuevo;                    // 4 (siempre al final)
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

void imprimir(lista listaActual){
    nodo aux = listaActual->top;
    while(aux != NULL){
        printf("%d ", aux->dato);
        aux = aux->nxt;
    }
    printf("\n");
}

void imprimirReversa(lista listaActual){
    if(isEmpty(listaActual)){
        printf("(vacia)\n");
        return;
    }
    nodo aux = listaActual->top;
    while(aux->nxt != NULL){             // ir hasta el ultimo
        aux = aux->nxt;
    }
    while(aux != NULL){                  // volver con prv
        printf("%d ", aux->dato);
        aux = aux->prv;
    }
    printf("\n");
}

void destruirLista(lista listaActual){
    while(!isEmpty(listaActual)){
        pop(listaActual);
    }
    free(listaActual);
}