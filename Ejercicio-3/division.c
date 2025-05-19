//Programa para dividir dos números enteros, usando registros de 32 bits.
//La inclusión de este archivo permite usar funciones estándar como printf
#include <stdio.h>

int main() {
    int dividendo = 20, divisor = 5, cociente;

    asm volatile (
        "movl %[num], %%eax\n\t"  // dividendo -> EAX 
        "cltd\n\t"                // Extiende el signo de EAX a EDX (para división con signo)
        "idivl %[den]\n\t"        // EAX / divisor -> cociente en EAX, residuo en EDX
        "movl %%eax, %[res]\n\t"  // cociente (EAX) -> resultado (variable C)
        : [res] "=r"(cociente)    // salida
        : [num] "r"(dividendo), [den] "r"(divisor) // entradas
        : "%eax", "%edx"          // clobbers
    );

    printf("Resultado de la división (el cociente): %d\n", cociente);
    return 0;
}
