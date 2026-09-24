# Librería de Listas Enlazadas en C

Tres implementaciones de lista enlazada con la misma interfaz pública, pensadas para usarse como pila (`push`/`pop`) o como cola (`push`/`extract`, o `enqueue`/`pop`):

| Archivo | Tipo | Extra |
|---|---|---|
| `lista_simple.h/.c` | Simplemente enlazada | Base |
| `lista_doble.h/.c` | Doblemente enlazada | + `imprimirReversa` |
| `lista_circular.h/.c` | Circular (simple) | + `ultimo` |

Todos los nodos guardan un `short` en `dato`.

## Instalación / uso

Solo copia el `.h` y el `.c` que necesites a tu proyecto e inclúyelo:

```c
#include "lista_simple.h"   // o lista_doble.h / lista_circular.h

int main(void) {
    lista l = crearLista();
    push(10, l);
    push(20, l);
    imprimir(l);        // 20 10
    pop(l);
    destruirLista(l);
    return 0;
}
```

Compilación (ejemplo con la simple):

```bash
gcc main.c lista_simple.c -o programa
```

No mezcles los tres `.c` en el mismo binario: las tres definen `crearNodo`, `push`, etc. con el mismo nombre pero distinto comportamiento (choque de símbolos).

## API común

| Función | Qué hace |
|---|---|
| `lista crearLista()` | Reserva y devuelve una lista vacía (`top = NULL`). |
| `nodo crearNodo(short valor)` | Reserva un nodo con ese valor (uso interno). |
| `void push(short valor, lista l)` | Inserta al inicio (tope). |
| `short pop(lista l)` | Extrae y devuelve el valor del tope. `-1` y mensaje de error si está vacía. |
| `void enqueue(short valor, lista l)` | Inserta al final. |
| `short extract(lista l)` | Alias de `pop` (extrae por el tope). |
| `void insert(short valor, int pos, lista l)` | Inserta en la posición `pos` (0-indexado). Si `pos <= 0` o la lista está vacía, equivale a `push`. |
| `int size(lista l)` | Cantidad de nodos. |
| `int isEmpty(lista l)` | `1` si está vacía, `0` si no. |
| `void imprimir(lista l)` | Imprime del tope al final, separado por espacios. |
| `void destruirLista(lista l)` | Libera todos los nodos y la lista. |

Con esta API puedes usar cualquiera de las tres como **pila** (`push` + `pop`, LIFO) o como **cola** (`push` + `extract` que sale por el mismo extremo — o `enqueue` + `pop`, que combina inserción al final con extracción al inicio, FIFO).

## Diferencias entre implementaciones

**`lista_simple`**
Cada nodo solo tiene `nxt`. `enqueue` e `insert` recorren desde `top` hasta el punto de inserción (O(n)). Es la base sobre la que se comparan las otras dos.

**`lista_doble`**
Cada nodo agrega `prv`. Mismo comportamiento externo que la simple, pero `push`, `pop` e `insert` actualizan también el enlace hacia atrás (por ejemplo, en `insert` hay que enganchar `nuevo->prv`, `aux->nxt->prv` y `aux->nxt` en el orden correcto para no perder referencias). A cambio, gana `imprimirReversa(lista l)`, que recorre hasta el último nodo y regresa usando `prv` — no reinicia el algoritmo, solo aprovecha los enlaces dobles.

**`lista_circular`**
Nunca hay `NULL`: el último nodo apunta de vuelta al primero. Introduce `nodo ultimo(lista l)` (busca el nodo cuyo `nxt` es `top`, uso interno pero expuesto en el `.h`). Por eso:
- `push`/`pop`/`enqueue` con un solo nodo son casos especiales (el nodo se apunta a sí mismo).
- `size` e `imprimir` usan `do-while` en vez de `while`, porque la condición de parada es "volver a `top`", no "llegar a `NULL`".
- `insert` recorre comparando contra `listaActual->top` (no contra `NULL`) para no dar la vuelta completa si `pos` es mayor al tamaño.

## Notas

- No hay chequeo de límites en `insert` más allá de `pos <= 0`; si `pos` es mayor al tamaño, inserta al final (o, en la circular, antes de cerrar el círculo).
- `pop`/`extract` sobre lista vacía no crashean: imprimen error y devuelven `-1`.
- Todas hacen `exit(1)` si `malloc` falla.