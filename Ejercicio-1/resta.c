//Programa para restar tres enteros, usando sólo registros de 16 bits.
//La inclusión de este archivo permite usar funciones estándar como printf
#include <stdio.h>

int main() {
    short a = 50, b = 11, c = 7;
    short resultado;

    asm volatile (
        "movw %[x], %%ax\n\t"   // ax = a (16 bits)
        "subw %[y], %%ax\n\t"   // ax = ax - b
        "subw %[z], %%ax\n\t"   // ax = ax - c
        "movw %%ax, %[res]\n\t" // resultado = ax
        : [res] "=r" (resultado)   // salida
        : [x] "r" (a), [y] "r" (b), [z] "r" (c) // entradas
        : "%ax" // registro clobber
    );

    printf("Resultado de la resta: %d\n", resultado);
    return 0;
}