#include <stdio.h>
#include "lista_circular.h"     // << LA UNICA LINEA QUE CAMBIA
                              //    ("lista_doble.h" / "lista_circular.h")
int main()
{
    lista l = crearLista();

    push(3, l);
    push(5, l);
    enqueue(9, l);
    insert(7, 1, l);      // 5 7 3 9

    imprimir(l);
    printf("size: %d\n", size(l));

    printf("pop: %d\n", pop(l));
    printf("extract: %d\n", extract(l));
    imprimir(l);          // 3 9

    while(!isEmpty(l)){
        printf("%d ", extract(l));
    }
    printf("\n");

    destruirLista(l);
    return 0;
}