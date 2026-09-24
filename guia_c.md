# C desde lógica de programación
> Ya sabés programar. Este doc es el *traductor* — de conceptos que conocés a cómo C los expresa.

---

## 1. El cambio mental: Python → C

| En Python | En C |
|---|---|
| `x = 5` | `int x = 5;` — declarás el tipo siempre |
| Sin punto y coma | Todo termina en `;` |
| El intérprete corre el código | Primero compilás: `gcc archivo.c -o programa` |
| La memoria se maneja sola | Vos pedís y liberás memoria |
| `list`, `dict` vienen incluidos | Las estructuras de datos las hacés vos |
| Los errores se ven al correr | Muchos errores se ven al compilar |

El compilador es tu primer filtro: si no compila, ni corres. Si compila y crashea, ahí empieza el trabajo real.

---

## 2. Tipos de datos y variables

```c
int    x = 10;       // entero, 4 bytes
short  s = 10;       // entero corto, 2 bytes  ← lo usamos en todas las listas
float  f = 3.14;     // decimal simple
double d = 3.14159;  // decimal doble precisión
char   c = 'A';      // un carácter, 1 byte (también es un número: 'A' == 65)
```

> Un `char` es a la vez un carácter y un número (ASCII). `'A'` vale `65`, `'a'` vale `97`, `'0'` vale `48`. Esto se explota en los ejercicios de frecuencia de caracteres.

### printf y scanf

```c
int n;
printf("Dame un número: ");
scanf("%d", &n);       // & es OBLIGATORIO — le decís DÓNDE guardar el valor
printf("Recibí: %d\n", n);
```

| Tipo | Format specifier |
|---|---|
| `int` / `short` | `%d` |
| `float` | `%f` |
| `double` | `%g` o `%lf` |
| `char` | `%c` |
| `char[]` (string) | `%s` |
| `float` con 2 decimales | `%.2f` |

---

## 3. Arrays estáticos

En Python las listas crecen solas. En C, el tamaño es fijo desde el principio:

```c
int numeros[30];           // 30 enteros, índice 0..29
float valores[10];         // 10 flotantes
int frecuencia[6] = {0};   // inicializado todo en 0 — truco útil
```

---

### 📌 Ej1.c — Frecuencia de números del 1 al 5

**Enunciado supuesto:** leer 30 números del 1 al 5 y mostrar cuántas veces aparece cada uno.

La idea clave: usar el **valor como índice**.

```c
int frecuencia[6] = {0};    // posiciones 0..5, usamos solo 1..5

for (i = 0; i < 30; i++) {
    scanf("%d", &numeros[i]);
    frecuencia[numeros[i]]++;  // si el número es 3 → frecuencia[3]++
}
```

En Python habrías hecho `freq.get(n, 0) + 1` con un dict. Acá no necesitás dict si sabés exactamente qué valores pueden entrar — el valor mismo dice en qué casilla contar.

---

### 📌 Ej2.c — Números con una sola ocurrencia

**Enunciado supuesto:** de 20 números, mostrar solo los que aparecen exactamente una vez.

Doble `for`: por cada número `i`, recorrer todo el array con `j` contando cuántas veces aparece.

```c
for (i = 0; i < 20; i++) {
    contador = 0;
    for (j = 0; j < 20; j++) {
        if (numeros[i] == numeros[j]) contador++;
    }
    if (contador == 1) printf("%d ", numeros[i]);
}
```

Sin sets, sin `.count()`. Comparación directa. Es O(n²) pero es la forma más directa de pensarlo.

---

### 📌 Ej3.c — Segundo menor y segundo mayor

**Enunciado supuesto:** de 10 flotantes, encontrar el segundo menor y el segundo mayor.

Ordenamos con **Selection Sort** y después solo accedemos a los índices:

```c
for (i = 0; i < 9; i++) {
    for (j = i + 1; j < 10; j++) {
        if (numeros[i] > numeros[j]) {
            temporal = numeros[i];    // intercambio con variable temporal
            numeros[i] = numeros[j];  // no podés hacer a,b = b,a en C
            numeros[j] = temporal;
        }
    }
}
// Resultado: numeros[0]=menor ... numeros[9]=mayor
printf("Segundo menor: %.2f\n", numeros[1]);
printf("Segundo mayor: %.2f\n", numeros[8]);
```

En Python habrías hecho `sorted(lista)[1]`. Acá el sort lo hacés vos. La variable `temporal` es obligatoria — C no tiene asignación simultánea.

---

## 4. Strings (arreglos de `char`)

En C no hay tipo `string`. Un string es un array de `char` que **termina con el carácter `'\0'`** (valor 0, el terminador nulo). Sin él, las funciones no saben dónde termina la cadena.

```c
char cadena[100];       // hasta 99 caracteres útiles + '\0' al final
scanf("%s", cadena);    // lee hasta espacio, agrega '\0' automático
                        // nota: sin & porque el array ya es un puntero (ver §5)
```

Recorrer un string = recorrer hasta encontrar `'\0'`:

```c
for (i = 0; cadena[i] != '\0'; i++) {
    // procesar cadena[i]
}
```

Funciones útiles (requieren `#include <string.h>`):

```c
strlen(s)           // longitud sin contar '\0'
strcpy(dest, src)   // copiar string
strcmp(s1, s2)      // 0 si son iguales, !=0 si no
strtok(s, " \n")    // dividir por separador, devuelve token por token
```

---

### 📌 Ej.c — Validar paréntesis balanceados

**Enunciado supuesto:** dada una cadena con `(`, `)`, `{`, `}`, `[`, `]`, decir si está bien balanceada.

```c
for (i = 0; cadena[i] != '\0'; i++) {
    if (cadena[i] == '(' || cadena[i] == '{' || cadena[i] == '[') {
        balance++;
    } else if (cadena[i] == ')' || cadena[i] == '}' || cadena[i] == ']') {
        balance--;
        if (balance < 0) break;  // cerró algo que nunca se abrió
    }
}
if (balance == 0) printf("SI\n");
else printf("NO\n");
```

> ⚠️ Este enfoque con contador no detecta `([)]` como inválido (cada tipo abre/cierra sin importar el orden entre tipos). Para validación exacta se necesita una pila real — ¿recordás `push`/`pop` de las listas? Ahí está la solución completa.

---

### 📌 Ej5.c — Prefijo común más largo

**Enunciado supuesto:** dadas `n` palabras, encontrar el prefijo que todas comparten.

Array 2D: primera dimensión = qué palabra, segunda = qué letra.

```c
char cadenas[10][21];   // 10 palabras de hasta 20 chars cada una

// cadenas[i][j] = letra j-ésima de la palabra i-ésima
```

Algoritmo: avanza letra por letra en la primera palabra. Para cada posición `j`, revisa que todas las demás palabras tengan la misma letra. En cuanto una difiere, para.

```c
for (j = 0; cadenas[0][j] != '\0'; j++) {
    int coinciden = 1;
    for (i = 1; i < n; i++) {
        if (cadenas[i][j] != cadenas[0][j]) { coinciden = 0; break; }
    }
    if (!coinciden) break;
}
cadenas[0][j] = '\0';   // truncar la primera palabra hasta donde llegamos
printf("%s\n", cadenas[0]);
```

---

### 📌 Ej4.c — Top 3 caracteres más frecuentes

**Enunciado supuesto:** de 10 caracteres ingresados, mostrar los 3 que más veces aparecen.

¿Recordás el truco de "valor como índice" del `Ej1.c`? Acá vuelve pero con chars:

```c
int frecuencias[256] = {0};          // 256 valores ASCII posibles

frecuencias[(int)caracteres[i]]++;   // cast char→int = posición en el array
```

Para el top 3: repetir 3 veces → buscar el máximo → imprimirlo → **poner ese índice en 0** → buscar el siguiente máximo.

```c
for (i = 0; i < 3; i++) {
    max_frec = 0;
    for (j = 0; j < 256; j++) {
        if (frecuencias[j] > max_frec) { max_frec = frecuencias[j]; indice_max = j; }
    }
    printf("'%c' apareció %d veces\n", indice_max, max_frec);
    frecuencias[indice_max] = 0;  // anular para no volver a elegirlo
}
```

---

### 📌 Ej2.py — Frecuencia de caracteres (recorrido único)

**Enunciado:** dada una cadena, mostrar la frecuencia de cada carácter en orden de aparición. Solo un recorrido.

```python
for letra in cadena:
    if letra in letras:
        i = letras.index(letra)
        veces[i] += 1
    else:
        letras.append(letra)   # nueva letra
        veces.append(1)
```

Dos listas paralelas (`letras` y `veces`) en vez de un dict. El índice `i` conecta ambas. Es el mismo concepto que el array de frecuencias de C pero en Python idiomático.

---

## 5. Punteros ⚡

Este es **el** tema de C. Un puntero es una variable que guarda una **dirección de memoria**, no un valor.

```c
int x = 5;
int *p = &x;    // p guarda la dirección donde vive x
                // &  = "dame la dirección de"
                // *p = "dame el valor en esa dirección"

printf("%d\n", x);    // 5
printf("%d\n", *p);   // 5 — mismo valor, camino diferente

*p = 10;              // modifico x a través de p
printf("%d\n", x);    // 10
```

```
Memoria:
  dirección 0x1A4  →  [ 5 ]   ← x
                          ↑
  p = 0x1A4 ──────────────┘   ← p (guarda la dirección, no el 5)
```

**¿Por qué importa?** Tres casos que aparecen en los ejercicios:

1. `scanf("%d", &n)` — sin `&`, scanf no puede modificar `n` (solo recibiría una copia)
2. `scanf("%s", cadena)` — sin `&` porque `cadena` ya **es** un puntero al primer elemento del array
3. Las listas enlazadas son punteros que apuntan a structs que contienen punteros a otros structs

---

## 6. Structs y typedef

Un `struct` agrupa variables bajo un nombre. Es como una clase sin métodos.

```c
struct Nodo {
    float dato;
    struct Nodo *siguiente;   // puntero al mismo tipo — así se encadenan
};
```

`typedef` le da alias al tipo para no escribir `struct` en cada declaración:

```c
typedef struct node {
    short dato;
    struct node *nxt;
} tipoNodo, *nodo;
//  ^^^^^^^^  ^^^^
//  alias al struct   alias al PUNTERO al struct

// Sin typedef:   struct node *p = malloc(...);
// Con typedef:   nodo p = malloc(...);   ← mucho más limpio
```

Este patrón exacto está en los tres archivos `.h` de las listas.

---

## 7. Memoria dinámica: `malloc` y `free`

Cuando creás `int x`, el compilador reserva espacio fijo en el **stack** (se libera solo). Cuando usás `malloc`, pedís espacio en el **heap** que persiste hasta que vos lo liberés con `free`.

```c
#include <stdlib.h>

nodo nuevo = (nodo) malloc(sizeof(tipoNodo));
//            ^^^^          ^^^^^^^^^^^^^^
//           cast al tipo   bytes que necesita un tipoNodo

if (nuevo == NULL) {       // malloc devuelve NULL si no hay memoria
    printf("Error: sin memoria\n");
    exit(1);
}

// ... usar nuevo ...

free(nuevo);    // devolver la memoria al sistema
```

> Si hacés `malloc` sin `free` → **fuga de memoria**. El programa pierde esa memoria hasta que termina. En `pop` de las listas, siempre hay un `free(tope)` exactamente por esto.

---

## 8. Listas enlazadas — todo junto

Una lista enlazada es una cadena de nodos en memoria dinámica. Cada nodo sabe dónde está el siguiente.

```
[ dato | nxt ] → [ dato | nxt ] → [ dato | nxt ] → NULL
      ↑
     top
```

Las tres variantes que implementamos en el proyecto:

| | Simple | Doble | Circular |
|---|---|---|---|
| Punteros por nodo | `nxt` | `nxt` + `prv` | `nxt` |
| El último apunta a | `NULL` | `NULL` | `top` |
| Función extra | — | `imprimirReversa` | `ultimo()` |
| Caso especial | — | Actualizar `prv` en cada operación | Nodo solo se apunta a sí mismo |

---

### El flujo de `push` (insertar al inicio) en las tres variantes

**Simple** — dos líneas:
```c
nuevo->nxt = listaActual->top;   // nuevo apunta a lo que era el tope
listaActual->top = nuevo;        // el nuevo ES el tope
```

**Doble** — lo mismo + actualizar `prv`:
```c
nuevo->nxt = listaActual->top;
if (listaActual->top != NULL)
    listaActual->top->prv = nuevo;  // el antiguo tope apunta hacia atrás
listaActual->top = nuevo;
```

**Circular** — hay que re-cerrar el círculo:
```c
nodo fin = ultimo(listaActual);   // el que apuntaba al antiguo top
nuevo->nxt = listaActual->top;
fin->nxt = nuevo;                 // el último ahora apunta al nuevo tope
listaActual->top = nuevo;
```

En la circular, `ultimo()` recorre hasta encontrar el nodo cuyo `nxt == top`. Por eso `size`, `imprimir` y todo lo que recorra usan `do-while` con condición `!= top` en vez de `!= NULL`.

---

### 📌 Ayuda_del_profesor.c — La pila para invertir orden (conversión a binario)

Este es el ejemplo más limpio de **para qué sirve una pila**: cuando procesás datos en un orden y los necesitás en el orden inverso.

El problema: convertir un número entero a binario. `numero % 2` te da el bit **menos** significativo (el de la derecha), pero necesitás imprimir de izquierda a derecha.

```
13 en binario = 1101

Paso a paso:
13 % 2 = 1  → push(1),  numero = 6
 6 % 2 = 0  → push(0),  numero = 3
 3 % 2 = 1  → push(1),  numero = 1
 1 % 2 = 1  → push(1),  numero = 0  ← para

Pila (top → bottom): 1 | 1 | 0 | 1

pop → 1
pop → 1
pop → 0
pop → 1    imprime: 1 1 0 1  ✓
```

El código es sorprendentemente corto:

```c
while(numero != 0){
    bit = (short)(numero % 2);
    numero = (numero - bit) / 2;   // equivale a numero / 2 en entero
    push(bit, binario);
}
while(!isEmpty(binario)){
    printf("%d", pop(binario));
}
```

LIFO (Last In, First Out) = el último en entrar es el primero en salir = los bits quedan en el orden correcto. Esto es lo que hace una pila útil para cualquier problema donde necesitás revertir una secuencia.

---

### 📌 Ejercio_Lista_*.c — Los ejercicios de clase

Los tres archivos de ejercicio tienen exactamente el mismo `main`:

```c
push(3, l);         // l: 3
push(5, l);         // l: 5 → 3
enqueue(9, l);      // l: 5 → 3 → 9
insert(7, 1, l);    // l: 5 → 7 → 3 → 9  (pos 1 = después del tope)

size(l)     // → 4
pop(l)      // → 5,  l: 7 → 3 → 9
extract(l)  // → 7,  l: 3 → 9
// bucle extract: saca 3, saca 9
```

La diferencia entre los tres no está en el `main` sino en **cómo** `push`, `pop` e `insert` mantienen los enlaces internamente. La interfaz es idéntica.

---

### 📌 Ejercio_10_09_2026.c — Pila con array

¿Recordás `push` y `pop` de las listas? Este ejercicio implementa **una pila sin structs ni malloc** — solo un array + un índice `tope`:

```c
char pila[100];
int tope = -1;

// push:  pila[++tope] = valor;
// pop:   valor = pila[tope--];
// peek:  pila[tope]
```

Es la misma lógica que `listaActual->top` de las listas, pero con array estático. Funciona cuando sabés de antemano el tamaño máximo.

El ejercicio usa esto para convertir una expresión matemática de notación **infija** (`3 + 4 * 2`) a **posfija** (`3 4 2 * +`) — el algoritmo Shunting Yard. La pila guarda operadores pendientes y los saca según su precedencia.

Después evalúa la expresión posfija con una segunda pila (de `double`):

```c
// número → meter a la pila
// operador → sacar dos, operar, meter resultado
double b = nums[topeNum--];
double a = nums[topeNum--];
nums[++topeNum] = a + b;   // o -, *, /, pow()
```

Al final, el único elemento en la pila es el resultado de toda la expresión.

---

### 📌 Ej1.c (versión lista) — Inserción ordenada

¿Recordás `insert(valor, pos, l)` que insertaba en una posición fija? Acá el criterio no es posición sino **orden**:

```c
void orderedInsertion(float numero) {
    // caminar hasta que el siguiente sea mayor que numero
    while (actual->siguiente != NULL &&
           actual->siguiente->dato < numero) {
        actual = actual->siguiente;
    }
    nuevo->siguiente = actual->siguiente;
    actual->siguiente = nuevo;
}
```

Misma mecánica de inserción en medio de la lista. La diferencia es la condición del `while`.

---

## 9. Ejercicios Python — algoritmos

Los ejercicios de diagnóstico y práctica en Python. Los conceptos son los mismos que en C pero Python da más herramientas.

---

### 📌 Ej2.py — Frecuencia de caracteres (recorrido único)

**Enunciado:** frecuencia de cada carácter en orden de aparición. Solo un recorrido permitido.

```python
for letra in cadena:
    if letra in letras:
        i = letras.index(letra)
        veces[i] += 1
    else:
        letras.append(letra)
        veces.append(1)
```

Dos listas paralelas en vez de un dict — el índice `i` las conecta. En C hiciste algo equivalente con `frecuencias[char]++`. La restricción "un solo recorrido" fuerza a no usar `cadena.count(c)` (que recorrería todo por cada letra).

---

### 📌 Ej1.py — Sublistas y subsecuencias sin repetidos

**Enunciado:** dada una cadena, listar todas las sublistas (consecutivas) y subsecuencias (no necesariamente consecutivas) sin caracteres repetidos.

**Sublistas** — doble for con slicing:
```python
for i in range(len(texto)):
    for j in range(i + 1, len(texto) + 1):
        sub = texto[i:j]
        if len(set(sub)) == len(sub):   # set elimina duplicados → si el tamaño no cambia, no había repetidos
            sublistas.add(sub)
```

**Subsecuencias** — recursivo:
```python
def calcular_subsecuencias(texto):
    if not texto: return {""}          # caso base
    primer_char = texto[0]
    resto = calcular_subsecuencias(texto[1:])   # llamada recursiva
    resultado = set()
    for sub in resto:
        resultado.add(sub)             # sin el primer char
        nueva = primer_char + sub
        if len(set(nueva)) == len(nueva):
            resultado.add(nueva)       # con el primer char, si no repite
    return resultado
```

La recursión piensa: "las subsecuencias de `texto` son las subsecuencias del resto, más cada una de ellas con `primer_char` al inicio (si no repite)". Divide y vencerás.

---

### 📌 Diag_1.py — Flecha más larga en una cadena

**Enunciado:** dada una cadena con flechas tipo `<---` o `===>`, encontrar la de mayor longitud.

```python
for i in range(len(cadena)):
    if cadena[i] == '<':              # punta izquierda → cuerpo va hacia la derecha
        j = i + 1
        while j < len(cadena) and cadena[j] == '-':   # contar guiones
            longitud_actual += 1; j += 1
    elif cadena[i] == '>':            # punta derecha → cuerpo va hacia la izquierda
        j = i - 1
        while j >= 0 and cadena[j] == '-':
            longitud_actual += 1; j -= 1
```

La punta (`<` o `>`) tiene longitud 1 y el cuerpo (`-` o `=`) se cuenta en la dirección que apunta. Dos punteros: `i` fijo en la punta, `j` moviéndose a lo largo del cuerpo.

---

### 📌 Diag_2.py — Palíndromo por suma con reverso

**Enunciado:** dado un número, sumarle repetidamente su reverso hasta obtener un palíndromo. Máximo 100 intentos; si no se logra, imprimir "imposible".

```python
while intentos < 100:
    num_str = str(numero_actual)
    num_invertido = int(num_str[::-1])    # [::-1] = slice invertido = reverso del string
    suma = numero_actual + num_invertido
    intentos += 1
    if str(suma) == str(suma)[::-1]:      # ¿es palíndromo?
        print(suma); break
    numero_actual = suma
```

`[::-1]` es el truco de Python para invertir una secuencia. Equivalente en C requeriría un bucle manual con dos índices desde los extremos hacia el centro.

---

### 📌 Diag_3.py — Suma de tres primos

**Enunciado:** dado un número P, expresarlo como suma de tres primos `p1 + p2 + p3` con `p1 ≤ p2 ≤ p3`.

```python
def es_primo(num):
    if num < 2: return False
    for i in range(2, int(num**0.5) + 1):   # basta con llegar a √num
        if num % i == 0: return False
    return True
```

Tres loops anidados, con la restricción `p1 ≤ p2 ≤ p3` para no repetir combinaciones:

```python
p1 = 2
while p1 <= p:
    if es_primo(p1):
        p2 = p1                          # p2 empieza desde p1, no desde 2
        while p1 + p2 <= p:
            if es_primo(p2):
                p3 = p - p1 - p2
                if p3 >= p2 and es_primo(p3):   # p3 ≥ p2 para mantener el orden
                    print(p1, p2, p3); encontrado = True
            p2 += 1
    p1 += 1
```

El `p3 = p - p1 - p2` calcula directamente el tercer primo necesario en vez de iterar — si ya sabés dos de los tres, el tercero está determinado.

---

## Resumen: qué concepto usa cada ejercicio

| Archivo | Concepto central |
|---|---|
| `Ej1.c` | Array, valor-como-índice |
| `Ej2.c` | Doble for, O(n²) |
| `Ej3.c` | Selection sort, swap con variable temporal |
| `Ej4.c` | char→int (ASCII), buscar máximo repetidamente |
| `Ej5.c` | Array 2D de strings, comparación char por char |
| `Ej.c` | Recorrido de string con `'\0'`, contador de balance |
| `Ej1(1).c` | Lista enlazada + inserción ordenada |
| `Ayuda_del_profesor.c` | Pila LIFO para revertir orden (binario) |
| `Ejercio_10_09_2026.c` | Pila con array, precedencia, Shunting Yard |
| `Ejercio_Lista_*.c` | Lista enlazada: push/pop/enqueue/insert |
| `Ej2.py` | Listas paralelas como estructura de frecuencia |
| `Ej1.py` | Slicing, recursión, set para unicidad |
| `Diag_1.py` | Dos punteros, parseo de patrones en string |
| `Diag_2.py` | Reverso con `[::-1]`, palíndromo numérico |
| `Diag_3.py` | Triple loop, criba de primos, p3 calculado directamente |

---

## Compilar los archivos de este repo

```bash
# Cualquier .c simple:
gcc Ej1.c -o ej1 && ./ej1

# Si usa <math.h> (pow, etc.) — siempre con -lm al final:
gcc Ejercio_10_09_2026.c -lm -o calc && ./calc

# Las listas (desde dentro de la carpeta):
gcc main_simple.c lista_simple.c -o test && ./test
```
