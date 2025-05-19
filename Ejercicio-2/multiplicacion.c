//Programa para multiplicar dos números enteros, usando registros de 8 bits.
//La inclusión de este archivo permite usar funciones estándar como printf
#include <stdio.h>

int main() {
    char a = 6, b = 3;
    short resultado;

    asm volatile (
        "movb %1, %%al\n\t"    // a -> AL (8 bits)
        "movb %2, %%bl\n\t"    // b -> BL (8 bits)
        "imulb %%bl\n\t"       // AL × BL -> AX (resultado de 16 bits)
        "movw %%ax, %0\n\t"    // AX -> resultado (16 bits)
        : "=m"(resultado)      // salida
        : "m"(a), "m"(b)       // entradas
        : "ax", "bx"           // registro clobber
    );

    printf("Resultado: %hd\n", resultado);
    return 0;
}