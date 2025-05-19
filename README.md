# Operaciones Aritméticas con Ensamblador en C

Este repositorio contiene ejemplos de programas en C que utilizan código ensamblador en línea (inline assembly) para realizar operaciones aritméticas básicas como resta, multiplicación y división. Se trabaja con registros de 8, 16 y 32 bits según el caso.

# Ejercicio 1
Es un programa para multiplicar dos números enteros, usando registros de 8 bits.

### Explicación del código:

```c
short a = 50, b = 11, c = 7;
short resultado;
```

Iniciamos declarando las 3 variables de tipo short (porque trabajamos con 16 bits) que se van a restar (a, b y c), y la variable “resultado” también de tipo short, para guardar el resultado de la resta.

Usa “asm volatile(…)” para evitar que el compilador optimice, elimine o reordene este bloque de instrucciones de ensamblador.

### Instrucciones en ensamblador:

```nasm
"movw %[x], %%ax\n\t"
```

“movw” significa mover un **word** (de 16 bits), mueve la variable “a” que se representa con el alias “x” hacia el registro “AX” (de 16 bits), haciendo: fuente —> destino. Sería algo como: ax = a

**Aclaración**: Pueden usarse los “alias” o también números como “%0, %1…”, ¿cómo saber el orden si se quiere usar números y no alias?

Los **salidas** se enumeran primero: `%0`, `%1`, …

Luego vienen las entradas que continúan la numeración donde quedaron las salidas.

```nasm
"subw %[y], %%ax\n\t"
```

“subw” hace una resta de 16 bits con la variable “b” que se representa con el alias “y” y almacena el resultado en “ax”,  haciendo: fuente —> destino. Sería algo como: ax = ax - b

```nasm
"subw %[z], %%ax\n\t"
```

“subw” hace una resta de 16 bits con la variable “c” que es representada con el alias “z” y almacena en resultado en “ax”, siendo algo como: ax = ax - c

```nasm
"movw %%ax, %[res]\n\t"
```

“movw” mueve “AX” (que es el resultado final) a la variable “resultado” que es representada por el alias “res”.

**Salida:**

```nasm
: [res] "=r" (resultado)  
```

”[res]” es un **alias** o **etiqueta simbólica** que representa la variable “resultado” de C.
”=r” significa: 

“=” esta es una variable de salida, así que ensamblador le asignará un valor, “r” para que el compilador elija un registro de propósito general para almacenarlo (como ax, bx, etc).

“(resultado)” es la **variable de C** que va a recibir el valor resultante de la operación.

**Entradas:**

```nasm
: [x] "r" (a), [y] "r" (b), [z] "r" (c)
```

[x], [y], y [z] son alias para las variables: (a), (b) y  (c) de C.

“r” le dice al compilador: usa un registro para esta variable.

“(a), (b) y  (c)” son el valor de las variables de C “a, b y c” que se habían declarado al inicio del código.

**Clobber:**

```nasm
: "%ax"
```

Declaramos que “ax” será modificado y así el compilador no use ese registro para otra cosa.

```c
printf("Resultado de la resta: %d\n", resultado);
```

Por último, imprimimos el resultado.

### ¿Cómo compilarlo?

Asegurarse de tener el paquete: gcc-multilib

Luego compilar en la terminal: gcc -m32 -o resta resta.c

Ejecutar en la terminal: ./resta

---
# Ejercicio 2
Es un programa para multiplicar dos números enteros, usando registros de 8 bits.

### Explicación del código:

```c
char a = 6, b = 3;
short resultado;
```

Iniciamos declarando los 2 variables “a” y “b” de tipo char (8 bits con signo), y les asignamos a = 6, b = 3

También declaramos una variable “resultado” de tipo short (16 bits con signo), donde se almacenará el resultado de la multiplicación.

Usa “asm volatile(…)” para evitar que el compilador optimice, elimine o reordene este bloque de instrucciones de ensamblador.

### Instrucciones en ensamblador:

```nasm
movb %1, %%al\n\t
```

“movb” significa mover 1 byte (8 bits) y mueve a “%1” que hace referencia a la primer entrada (el valor de “a”) hacia el registro “%%al” que es la parte baja del registro AX (registro de 8 bits).

**Aclaración**: Pueden usarse los “alias” o también números “%0, %1…” justo como en este caso, ¿cómo saber el orden de los números?

Los **salidas** se enumeran primero: %0, %1…

Luego vienen las entradas que continúan la numeración donde quedaron las salidas.

```nasm
movb %2, %%bl\n\t
```

Similar a la anterior lo que hace es mover a “%2” (que es el valor de b) hacia el registro “%%bl” que es la parte baja del registro BX.

```nasm
imulb %%bl\n\t
```

“imulb” es una multiplicación con signo de 8 bits. lo que hace es que multiplica AL * BL y **el resultado se guarda en AX** (¡muy importante!).

Por eso “resultado” debe ser de **16 bits**, porque:

6 * 3 = 18 cabe en 8 bits, pero en general, char * char puede dar hasta **255 * 255 = 65025**.

```nasm
movw %%ax, %0\n\t
```

“movw” mueve 2 bytes (16 bits), mueve el resultado de la multiplicación que está en “%%ax” hacia “%0” el cual hace referencia “resultado” que es la salida.

**Salida:**

```nasm
: "=m"(resultado)
```

Le dice al compilador que va a guardar el resultado de mi código ensamblador, “=” indica que es **salida,** en una variable C llamada “resultado”, y que lo ponga en memoria (por eso "m"), y ese registro lo asocia como %0 dentro del bloque ensamblador.

**Entradas**:

```nasm
: "m"(a), "m"(b)
```

las variables “a” y “b”, son pasadas por dirección (memoria) y se asocian como “%1” y “%2” dentro del bloque ensamblador.

**Clobbers:**

```nasm
: "ax", "bx”
```

Indica al compilador que los registros AX y BX serán modificados y aunque solo se usa AL y BL, declarar AX y BX cubre toda la palabra (por si acaso AH también se ve afectado).

```c
printf("Resultado: %hd\n", resultado);
```

Usa “%hd” porque “resultado” es de tipo short con signo, y como char también es con signo y la multiplicación se hizo con “imul” (que conserva el signo), el resultado también puede ser negativo.

### ¿Cómo compilarlo?

Asegurarse de tener el paquete: gcc-multilib

Luego compilar en la terminal: gcc -m32 -o multiplicacion multiplicacion.c

Ejecutar en la terminal: ./multiplicacion

---
# Ejercicio 3
Es un programa para dividir dos números enteros, usando registros de 32 bits.

### Explicación del código:

```c
int dividendo = 20, divisor = 5, cociente;
```

Iniciamos declarando los 2 variables de tipo int (porque trabajamos con registros de 32 bits) que se van a dividir “dividendo” y “divisor”, y la variable “cociente” en la cual se guardará el resultado. 

Usa “asm volatile(…)” para evitar que el compilador optimice, elimine o reordene este bloque de instrucciones de ensamblador.

### Instrucciones en ensamblador:

```nasm
movl %[num], %%eax\n\t
cltd\n\t
```

“movl”mueve un valor long (de 32 bits) el cual es “%[num]” que hace referencia al  “dividendo”, hacia “%%eax” el cual es el registro donde va el dividendo.

”cltd”(convert long to double) copia el bit de signo de EAX a todo EDX para hacer una división con signo correctamente. Es obligatorio antes de usar “idiv”.

```nasm
idivl %[den]\n\t
```

“idivl” divide el par EDX:EAX entre el operando, “%[den]” es el alias del divisor y el resultado será: el cociente en EAX, el residuo en EDX.

```nasm
movl %%eax, %[res]\n\t
```

“movl” mueve el resultado (cociente) de EAX a la variable “cociente” que es representada por el alias “res”.

**Salida:** 

```nasm
: [res] "=r"(cociente)    
```

El compilador colocará el valor de EAX al final en “cociente” y “res” es su alias.

**Entradas**:

```nasm
: [num] "r"(dividendo), [den] "r"(divisor)
```

Usamos alias “num” y “den” para referirnos a las variables de C. “r” le dice al compilador que lo ponga en un registro cualquiera (por eso "r").

Clobbers:

```nasm
: "%eax", "%edx”
```

Indicamos que se modifican los registros “eax” y “edx”, para que el compilador no use esos registro para otra cosa.

```c
 printf("Resultado de la división (el cociente): %d\n", cociente);
```

Por último, imprimimos el resultado.

### ¿Cómo compilarlo?

Asegurarse de tener el paquete: gcc-multilib

Luego compilar en la terminal: gcc -m32 -o division division.c

Ejecutar en la terminal: ./division

---