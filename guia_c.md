# C desde lógica de programación

> Referencia práctica para quienes conocen lógica de programación pero no C. Se asumen como conocidos los conceptos de variables, bucles, funciones y estructuras de datos. El enfoque está en la sintaxis, el modelo de memoria y los patrones propios del lenguaje.

---

## 0. El compilador y el entorno de trabajo

A diferencia de los lenguajes interpretados, C requiere una etapa de **compilación** antes de ejecutar. El compilador lee el código fuente (`.c`) y genera un ejecutable binario. Si hay errores de sintaxis, el proceso se detiene y los reporta — no existe "correr y ver qué pasa".

El compilador más extendido es **GCC** (GNU Compiler Collection). En Linux suele venir preinstalado. En Windows se instala a través de **MSYS2**.

### Instalación en Windows (MSYS2 + MinGW UCRT64)

1. Descargar e instalar MSYS2 desde [https://www.msys2.org](https://www.msys2.org)
2. Abrir la terminal **MSYS2 UCRT64** (no la genérica MSYS2)
3. Instalar el toolchain completo:

```bash
pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain
```

4. Agregar al **PATH** de Windows la carpeta `bin` de la instalación. La ruta típica es:

```
C:\msys64\ucrt64\bin
```

Para verificar que quedó bien, abrir PowerShell y ejecutar `gcc --version`. Si imprime la versión, el PATH está correcto.

### Compilación desde terminal

```bash
# Compilar un archivo simple:
gcc archivo.c -o programa.exe

# Si el archivo usa <math.h> (pow, sqrt, etc.), agregar -lm al final:
gcc archivo.c -lm -o programa.exe

# Compilar varios .c juntos (necesario cuando se usan las librerías del proyecto):
gcc main.c lista_simple.c -o programa.exe

# Ejecutar:
.\programa.exe       # PowerShell / Windows
./programa           # bash / Linux / Git Bash
```

### Flags de GCC más usados

| Flag | Efecto |
|---|---|
| `-o nombre` | Nombre del ejecutable de salida |
| `-lm` | Vincular la librería matemática (`<math.h>`) |
| `-Wall` | Mostrar todos los warnings (recomendado siempre) |
| `-g` | Incluir información para depurador |

### Configuración en VS Code con Code Runner

Con la extensión **Code Runner**, se puede compilar y ejecutar directamente desde el editor con `Ctrl+Alt+N`. La configuración relevante en `settings.json`:

```json
"code-runner.runInTerminal": true,
"code-runner.saveFileBeforeRun": true,
"code-runner.clearPreviousOutput": true,

"code-runner.executorMap": {
    "c": "cd $dir; gcc *.c -o $fileNameWithoutExt.exe; if ($?) { .\\$fileNameWithoutExt.exe; Remove-Item $fileNameWithoutExt.exe }"
}
```

Qué hace el comando paso a paso:

| Fragmento | Qué hace |
|---|---|
| `cd $dir` | Ir al directorio del archivo abierto |
| `gcc *.c` | Compilar **todos** los `.c` en esa carpeta (necesario para las librerías) |
| `-o $fileNameWithoutExt.exe` | Nombre del ejecutable igual al archivo fuente |
| `if ($?)` | Solo ejecutar si la compilación fue exitosa (PowerShell) |
| `Remove-Item $fileNameWithoutExt.exe` | Borrar el ejecutable después de correr |

> El `gcc *.c` es importante: cuando se trabaja con las librerías (`lista_simple.c` + `main_simple.c`), compilar solo el `main` da errores de "símbolo no definido". Al compilar todos los `.c` de la carpeta, GCC los enlaza automáticamente.

> Para archivos que usen `<math.h>`, agregar `-lm` antes del punto y coma: `gcc *.c -lm -o ...`

---

## 1. De lenguajes de alto nivel a C

| Lenguajes de alto nivel | C |
|---|---|
| `x = 5` | `int x = 5;` — el tipo se declara siempre |
| Sin punto y coma | Toda sentencia termina en `;` |
| El intérprete ejecuta el código | Primero se compila; el binario resultante se ejecuta |
| La memoria se gestiona automáticamente | El programador la reserva y la libera |
| Estructuras de datos incluidas (`list`, `dict`...) | Las estructuras se implementan desde cero |
| Los errores aparecen al correr | Muchos errores se detectan al compilar |

El compilador actúa como primer filtro: un programa que no compila no puede ejecutarse. Un programa que compila correctamente puede aun tener errores lógicos, que se detectan al probar.

---

## 2. Tipos de datos y variables

```c
int    x = 10;       // entero, 4 bytes
short  s = 10;       // entero corto, 2 bytes  ← usado en las listas del proyecto
float  f = 3.14;     // decimal de precisión simple
double d = 3.14159;  // decimal de doble precisión
char   c = 'A';      // un carácter, 1 byte (internamente es un número: 'A' == 65)
```

> Un `char` es simultáneamente un carácter y un entero según el estándar ASCII. `'A'` vale `65`, `'a'` vale `97`, `'0'` vale `48`. Esta propiedad se explota en los ejercicios de frecuencia de caracteres.

### Entrada y salida básica

```c
int n;
printf("Ingrese un número: ");
scanf("%d", &n);       // & indica la dirección donde se almacenará el valor
printf("Recibido: %d\n", n);
```

| Tipo | Especificador de formato |
|---|---|
| `int` / `short` | `%d` |
| `float` | `%f` |
| `double` | `%g` o `%lf` |
| `char` | `%c` |
| `char[]` (cadena) | `%s` |
| `float` con 2 decimales | `%.2f` |

---

## 3. Arrays estáticos

El tamaño de un array se define en tiempo de compilación y no puede cambiar en ejecución.

```c
int numeros[30];           // 30 enteros, índices 0..29
float valores[10];         // 10 flotantes
int frecuencia[6] = {0};   // inicializado completamente en cero
```

---

### 📌 Ej1.c — Frecuencia de números del 1 al 5

**Enunciado:** leer 30 números del 1 al 5 y mostrar cuántas veces aparece cada uno.

Técnica: **valor como índice**. Si el número leído es `3`, se incrementa `frecuencia[3]`. El valor determina la posición.

```c
int frecuencia[6] = {0};    // posiciones 0..5; se usan solo 1..5

for (i = 0; i < 30; i++) {
    scanf("%d", &numeros[i]);
    frecuencia[numeros[i]]++;  // el valor leído indexa el array
}
```

En Python se resolvería con un diccionario (`freq[n] = freq.get(n, 0) + 1`). En C, cuando el rango de valores es conocido y acotado, un array indexado por valor es más directo y eficiente.

---

### 📌 Ej2.c — Números con una sola ocurrencia

**Enunciado:** de 20 números ingresados, mostrar solo los que aparecen exactamente una vez.

Para cada elemento `i`, se recorre todo el array con `j` contando coincidencias:

```c
for (i = 0; i < 20; i++) {
    contador = 0;
    for (j = 0; j < 20; j++) {
        if (numeros[i] == numeros[j]) contador++;
    }
    if (contador == 1) printf("%d ", numeros[i]);
}
```

La solución es O(n²). En Python se usaría `lista.count(x) == 1`. En C, sin estructuras auxiliares, la comparación directa con doble bucle es la aproximación más simple.

---

### 📌 Ej3.c — Segundo menor y segundo mayor

**Enunciado:** de 10 flotantes, encontrar el segundo menor y el segundo mayor.

Se ordena el array con **Selection Sort** y se accede por índice:

```c
for (i = 0; i < 9; i++) {
    for (j = i + 1; j < 10; j++) {
        if (numeros[i] > numeros[j]) {
            temporal = numeros[i];    // intercambio requiere variable auxiliar
            numeros[i] = numeros[j];  // C no tiene asignación simultánea
            numeros[j] = temporal;
        }
    }
}
// Tras ordenar: numeros[0] = mínimo, numeros[9] = máximo
printf("Segundo menor: %.2f\n", numeros[1]);
printf("Segundo mayor: %.2f\n", numeros[8]);
```

La variable `temporal` es obligatoria: sin ella, la primera asignación sobreescribiría el valor antes de que pueda moverse.

---

## 4. Cadenas de caracteres

C no tiene un tipo `string`. Una cadena es un array de `char` que **termina con el carácter nulo `'\0'`** (valor entero 0). Sin ese terminador, las funciones de cadena no saben dónde acaba el texto.

```c
char cadena[100];       // hasta 99 caracteres útiles + '\0'
scanf("%s", cadena);    // lee hasta el primer espacio y agrega '\0' automáticamente
                        // no lleva & porque el nombre del array ya es un puntero
```

Recorrer una cadena equivale a avanzar hasta encontrar `'\0'`:

```c
for (i = 0; cadena[i] != '\0'; i++) {
    // procesar cadena[i]
}
```

Funciones de la librería estándar (`#include <string.h>`):

```c
strlen(s)           // longitud sin contar '\0'
strcpy(dest, src)   // copiar cadena
strcmp(s1, s2)      // 0 si son iguales, valor distinto si no
strtok(s, " \n")    // tokenizar por separador — empleado en Ejercio_10_09_2026.c
```

---

### 📌 Ej.c — Validar paréntesis balanceados

**Enunciado:** dada una cadena con `(`, `)`, `{`, `}`, `[`, `]`, determinar si está bien balanceada.

```c
for (i = 0; cadena[i] != '\0'; i++) {
    if (cadena[i] == '(' || cadena[i] == '{' || cadena[i] == '[') {
        balance++;
    } else if (cadena[i] == ')' || cadena[i] == '}' || cadena[i] == ']') {
        balance--;
        if (balance < 0) break;  // se cerró algo que no estaba abierto
    }
}
if (balance == 0) printf("SI\n");
else              printf("NO\n");
```

> ⚠️ Este enfoque con contador simple no distingue tipos: `([)]` pasaría como válido. Para validación exacta por tipo se necesita una pila real que recuerde qué abridor se usó — el mismo mecanismo de `push`/`pop` de las listas enlazadas del proyecto.

---

### 📌 Ej5.c — Prefijo común más largo

**Enunciado:** dadas `n` palabras, encontrar el prefijo que todas comparten.

Array bidimensional: primera dimensión = índice de palabra, segunda = posición de carácter.

```c
char cadenas[10][21];   // 10 palabras de hasta 20 caracteres cada una

// cadenas[i][j] = carácter j-ésimo de la palabra i-ésima
```

Algoritmo: avanzar letra por letra sobre la primera palabra; para cada posición `j`, verificar que todas las demás tengan el mismo carácter. Al primer desacuerdo, detener.

```c
for (j = 0; cadenas[0][j] != '\0'; j++) {
    int coinciden = 1;
    for (i = 1; i < n; i++) {
        if (cadenas[i][j] != cadenas[0][j]) { coinciden = 0; break; }
    }
    if (!coinciden) break;
}
cadenas[0][j] = '\0';   // truncar en la posición donde se detuvo
printf("%s\n", cadenas[0]);
```

---

### 📌 Ej4.c — Top 3 caracteres más frecuentes

**Enunciado:** de 10 caracteres ingresados, mostrar los 3 que más veces aparecen.

La misma técnica de valor-como-índice del Ej1.c, extendida a los 256 valores ASCII posibles:

```c
int frecuencias[256] = {0};          // posición = valor ASCII del carácter

frecuencias[(int)caracteres[i]]++;   // cast char → int da el índice ASCII
```

Para obtener el top 3: encontrar el máximo, registrarlo, poner esa posición en `0` para excluirla, y repetir:

```c
for (i = 0; i < 3; i++) {
    max_frec = 0;
    for (j = 0; j < 256; j++) {
        if (frecuencias[j] > max_frec) { max_frec = frecuencias[j]; indice_max = j; }
    }
    printf("'%c' apareció %d veces\n", indice_max, max_frec);
    frecuencias[indice_max] = 0;  // excluir en la siguiente búsqueda
}
```

---

## 5. Punteros

Un puntero es una variable que almacena una **dirección de memoria**, no un valor directo.

```c
int x = 5;
int *p = &x;    // p contiene la dirección donde está almacenado x
                // &  = operador "dirección de"
                // *p = "valor en la dirección p" (desreferencia)

printf("%d\n", x);    // 5
printf("%d\n", *p);   // 5 — mismo resultado, acceso indirecto

*p = 10;              // modifica x a través del puntero
printf("%d\n", x);    // 10
```

```
Memoria:
  dirección 0x1A4  →  [ 5 ]   ← x
                          ↑
  p = 0x1A4 ──────────────┘   ← p (almacena la dirección, no el 5)
```

Los punteros aparecen en tres contextos recurrentes en los ejercicios:

1. `scanf("%d", &n)` — sin `&`, `scanf` recibiría una copia del valor y no podría modificarlo
2. `scanf("%s", cadena)` — sin `&` porque el nombre de un array ya es la dirección de su primer elemento
3. Las listas enlazadas son estructuras donde cada nodo contiene un puntero al siguiente nodo

---

## 6. Structs y typedef

Un `struct` agrupa variables heterogéneas bajo un mismo nombre. No tiene métodos — es solo un contenedor de datos.

```c
struct Nodo {
    float dato;
    struct Nodo *siguiente;   // puntero al mismo tipo: la base del encadenamiento
};
```

`typedef` define alias para evitar escribir `struct` en cada declaración:

```c
typedef struct node {
    short dato;
    struct node *nxt;
} tipoNodo, *nodo;
//  ^^^^^^^^  ^^^^
//  alias para el struct   alias para el puntero al struct

// Sin typedef:   struct node *p = malloc(...);
// Con typedef:   nodo p = malloc(...);
```

Este patrón aparece de forma idéntica en los tres archivos `.h` de las librerías del proyecto.

---

## 7. Memoria dinámica: `malloc` y `free`

Las variables declaradas normalmente (`int x`) se alojan en el **stack** y se liberan automáticamente al salir del bloque. Con `malloc`, la memoria se reserva en el **heap** y persiste hasta que se libera explícitamente con `free`.

```c
#include <stdlib.h>

nodo nuevo = (nodo) malloc(sizeof(tipoNodo));
//            ^^^^          ^^^^^^^^^^^^^^
//           cast al tipo   bytes que ocupa un tipoNodo

if (nuevo == NULL) {       // malloc devuelve NULL si no hay memoria disponible
    printf("Error: sin memoria\n");
    exit(1);
}

// ... uso de nuevo ...

free(nuevo);    // devolver la memoria al sistema operativo
```

> Cada `malloc` sin su correspondiente `free` constituye una **fuga de memoria**: el programa retiene esa memoria hasta terminar. En la implementación de `pop` de las listas, el `free(tope)` existe precisamente por esta razón.

---

## 8. Listas enlazadas

Una lista enlazada es una secuencia de nodos en memoria dinámica donde cada nodo conoce la dirección del siguiente.

```
[ dato | nxt ] → [ dato | nxt ] → [ dato | nxt ] → NULL
      ↑
     top
```

Las tres variantes implementadas en el proyecto:

| | Simple | Doble | Circular |
|---|---|---|---|
| Punteros por nodo | `nxt` | `nxt` + `prv` | `nxt` |
| El último apunta a | `NULL` | `NULL` | `top` |
| Función extra | — | `imprimirReversa` | `ultimo()` |
| Caso especial | — | Actualizar `prv` en cada operación | Nodo único se apunta a sí mismo |

---

### El flujo de `push` en las tres variantes

**Simple** — dos asignaciones:
```c
nuevo->nxt = listaActual->top;   // el nuevo apunta a lo que era el tope
listaActual->top = nuevo;        // el nuevo pasa a ser el tope
```

**Doble** — igual, más actualizar el enlace inverso:
```c
nuevo->nxt = listaActual->top;
if (listaActual->top != NULL)
    listaActual->top->prv = nuevo;  // el antiguo tope apunta hacia atrás
listaActual->top = nuevo;
```

**Circular** — hay que mantener el círculo cerrado:
```c
nodo fin = ultimo(listaActual);   // nodo cuyo nxt apuntaba al antiguo top
nuevo->nxt = listaActual->top;
fin->nxt = nuevo;                 // el último ahora apunta al nuevo tope
listaActual->top = nuevo;
```

En la circular, `ultimo()` recorre hasta encontrar el nodo donde `nxt == top`. Por eso `size`, `imprimir` y cualquier recorrido usan `do-while` con condición `!= top`, no `!= NULL`.

---

### 📌 Ayuda_del_profesor.c — La pila para invertir orden (conversión a binario)

Caso concreto de uso de una pila: cuando los datos se producen en un orden y se necesitan en el orden inverso.

La división sucesiva por 2 genera los bits del **menos** significativo al **más** significativo, pero para imprimir un número binario se necesita el orden contrario. La pila resuelve esto sin recalcular:

```
13 en binario:

13 % 2 = 1  → push(1),  13 → 6
 6 % 2 = 0  → push(0),   6 → 3
 3 % 2 = 1  → push(1),   3 → 1
 1 % 2 = 1  → push(1),   1 → 0  (fin)

Pila (top → base): 1 | 1 | 0 | 1

pop → 1
pop → 1
pop → 0
pop → 1    Salida: 1 1 0 1  ✓
```

```c
while(numero != 0){
    bit = (short)(numero % 2);
    numero = (numero - bit) / 2;
    push(bit, binario);
}
while(!isEmpty(binario)){
    printf("%d", pop(binario));
}
```

La propiedad LIFO (Last In, First Out) hace que el último bit calculado — el más significativo — sea el primero en salir. Este mismo principio es aplicable a cualquier problema de reversión de secuencias.

---

### 📌 Ejercio_Lista_*.c — Los ejercicios de clase

Los tres archivos de ejercicio comparten el mismo `main`:

```c
push(3, l);         // l: 3
push(5, l);         // l: 5 → 3
enqueue(9, l);      // l: 5 → 3 → 9
insert(7, 1, l);    // l: 5 → 7 → 3 → 9  (pos 1 = después del tope)

size(l)     // → 4
pop(l)      // → 5,  l: 7 → 3 → 9
extract(l)  // → 7,  l: 3 → 9
// bucle extract: 3, luego 9
```

La diferencia entre las tres implementaciones no está en la interfaz sino en cómo `push`, `pop` e `insert` mantienen los enlaces internamente.

---

### 📌 Ejercio_10_09_2026.c — Pila con array

Una pila puede implementarse sin structs ni memoria dinámica, usando un array y un índice `tope`:

```c
char pila[100];
int tope = -1;

// push:  pila[++tope] = valor;
// pop:   valor = pila[tope--];
// peek:  pila[tope]
```

La lógica es idéntica a la de las listas enlazadas, pero con array estático. Es válida cuando el tamaño máximo se conoce de antemano.

El ejercicio implementa el algoritmo **Shunting Yard**: convierte una expresión infija (`3 + 4 * 2`) a notación posfija (`3 4 2 * +`), donde los operadores van después de sus operandos. La pila almacena los operadores pendientes y los vuelca según su precedencia.

Para evaluar la expresión posfija, una segunda pila (de `double`) almacena los operandos:

```c
// token es número → meterlo a la pila
// token es operador → sacar dos operandos, operar, meter el resultado
double b = nums[topeNum--];
double a = nums[topeNum--];
nums[++topeNum] = a + b;   // o -, *, /, pow()
```

Al terminar, el único elemento en la pila es el resultado de la expresión completa.

---

### 📌 Ej1(1).c — Inserción ordenada en lista enlazada

**Enunciado** (incluido en el archivo): mantener una lista enlazada siempre ordenada de menor a mayor. Los números en punto flotante se leen hasta encontrar `#`.

La función `orderedInsertion` avanza hasta encontrar el punto de inserción correcto:

```c
void orderedInsertion(float numero) {
    // ...
    while (actual->siguiente != NULL &&
           actual->siguiente->dato < numero) {
        actual = actual->siguiente;    // avanzar mientras el siguiente sea menor
    }
    nuevo->siguiente = actual->siguiente;
    actual->siguiente = nuevo;
}
```

Misma mecánica de inserción en medio de una lista. La diferencia respecto a `insert(valor, pos, l)` es que el criterio de parada es un valor relativo, no una posición absoluta.

---

## 9. Ejercicios Python — algoritmos

---

### 📌 Ej2.py — Frecuencia de caracteres (un solo recorrido)

**Enunciado:** dada una cadena, mostrar la frecuencia de cada carácter en orden de aparición. Se permite recorrer la cadena una sola vez.

```python
for letra in cadena:
    if letra in letras:
        i = letras.index(letra)
        veces[i] += 1
    else:
        letras.append(letra)
        veces.append(1)
```

Dos listas paralelas (`letras` y `veces`) en lugar de un diccionario. El índice `i` las mantiene sincronizadas. La restricción de un solo recorrido impide usar `cadena.count(c)` (que recorrería la cadena por cada carácter único).

---

### 📌 Ej1.py — Sublistas y subsecuencias sin caracteres repetidos

**Enunciado:** dada una cadena, listar todas las sublistas (subcadenas consecutivas) y subsecuencias (no necesariamente consecutivas) formadas por caracteres sin repetición.

**Sublistas** — doble bucle con slicing:
```python
for i in range(len(texto)):
    for j in range(i + 1, len(texto) + 1):
        sub = texto[i:j]
        if len(set(sub)) == len(sub):   # set elimina duplicados; si el tamaño no cambia, no había repetidos
            sublistas.add(sub)
```

**Subsecuencias** — recursivo:
```python
def calcular_subsecuencias(texto):
    if not texto: return {""}              # caso base
    primer_char = texto[0]
    resto = calcular_subsecuencias(texto[1:])
    resultado = set()
    for sub in resto:
        resultado.add(sub)                 # sin el primer carácter
        nueva = primer_char + sub
        if len(set(nueva)) == len(nueva):  # incluir solo si no repite
            resultado.add(nueva)
    return resultado
```

La recursión plantea: "las subsecuencias de `texto` son las del resto, más cada una de ellas con `primer_char` al inicio (si no introduce repetición)". Es un esquema de inclusión/exclusión.

---

### 📌 Diag_1.py — Flecha más larga en una cadena

**Enunciado:** dada una cadena con flechas tipo `<---` o `====>`, encontrar la de mayor longitud.

Para cada `<`, el cuerpo crece hacia la derecha. Para cada `>`, crece hacia la izquierda:

```python
if cadena[i] == '<':
    j = i + 1
    while j < len(cadena) and cadena[j] == '-':
        longitud_actual += 1; j += 1
elif cadena[i] == '>':
    j = i - 1
    while j >= 0 and cadena[j] == '-':
        longitud_actual += 1; j -= 1
```

Técnica de dos punteros: `i` fijo en la punta, `j` avanzando a lo largo del cuerpo.

---

### 📌 Diag_2.py — Palíndromo por suma con reverso

**Enunciado:** dado un número, sumarlo con su reverso repetidamente hasta obtener un palíndromo. Máximo 100 intentos; si no se logra, imprimir `"imposible"`.

```python
while intentos < 100:
    num_str = str(numero_actual)
    num_invertido = int(num_str[::-1])    # [::-1] invierte la secuencia
    suma = numero_actual + num_invertido
    intentos += 1
    if str(suma) == str(suma)[::-1]:      # comprobar palíndromo
        print(suma); break
    numero_actual = suma
```

El slice `[::-1]` es la forma idiomática de invertir una secuencia en Python. El equivalente en C requiere un bucle con dos índices avanzando desde los extremos hacia el centro.

---

### 📌 Diag_3.py — Suma de tres primos

**Enunciado:** dado un número P, expresarlo como suma de tres primos `p1 + p2 + p3` con `p1 ≤ p2 ≤ p3`.

```python
def es_primo(num):
    if num < 2: return False
    for i in range(2, int(num**0.5) + 1):   # basta verificar hasta √num
        if num % i == 0: return False
    return True
```

Tres bucles anidados. La restricción `p2` empieza desde `p1` (no desde 2) y `p3` se calcula directamente:

```python
p3 = p - p1 - p2      # si p1 y p2 son fijos, p3 está determinado
if p3 >= p2 and es_primo(p3):
    print(p1, p2, p3)
```

Calcular `p3` en lugar de iterarlo sobre él elimina un tercer bucle completo.

---

## Resumen: concepto central por ejercicio

| Archivo | Concepto central |
|---|---|
| `Ej1.c` | Array, valor-como-índice |
| `Ej2.c` | Doble bucle, O(n²) |
| `Ej3.c` | Selection sort, swap con variable temporal |
| `Ej4.c` | `char` → `int` (ASCII), búsqueda del máximo por iteraciones |
| `Ej5.c` | Array 2D de cadenas, comparación carácter por carácter |
| `Ej.c` | Recorrido de cadena hasta `'\0'`, contador de balance |
| `Ej1(1).c` | Lista enlazada + inserción por criterio de orden |
| `Ayuda_del_profesor.c` | Pila LIFO para inversión de secuencia (binario) |
| `Ejercio_10_09_2026.c` | Pila con array, precedencia de operadores, Shunting Yard |
| `Ejercio_Lista_*.c` | Lista enlazada: push / pop / enqueue / insert |
| `Ej2.py` | Listas paralelas como estructura de frecuencia |
| `Ej1.py` | Slicing, recursión con inclusión/exclusión, `set` para unicidad |
| `Diag_1.py` | Dos punteros, parseo de patrones en cadena |
| `Diag_2.py` | Inversión con `[::-1]`, palíndromo numérico |
| `Diag_3.py` | Triple bucle, criba de primos, tercer valor calculado |

---

## Compilación rápida

```bash
# Archivo simple:
gcc Ej1.c -o ej1.exe && .\ej1.exe

# Con math.h:
gcc Ejercio_10_09_2026.c -lm -o calc.exe && .\calc.exe

# Librerías (desde la carpeta correspondiente):
gcc main_simple.c lista_simple.c -o test.exe && .\test.exe

# VS Code: Ctrl+Alt+N  (con la configuración de Code Runner del §0)
```