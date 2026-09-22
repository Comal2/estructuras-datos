#include <stdio.h>
#include "lista_simple.h"

int main()
{
    lista l = crearLista();

    push(3, l);
    push(5, l);
    enqueue(9, l);
    insert(7, 1, l);   // 5 7 3 9

    printf("size: %d\n", size(l));
    printf("pop: %d\n", pop(l));
    printf("extract: %d\n", extract(l));

    while(!isEmpty(l)){
        printf("%d ", extract(l));
    }
    return 0;
}
