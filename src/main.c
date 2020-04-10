#include <stdio.h>
#include <gmp.h>

#include "miller_rabbin.h"

int main(int argc, char **argv) {
    if(argc != 1)
        return 1;

    mpz_t n;
    mpz_init(n);
    printf("Choisissez le nombre à tester : \n");
    mpz_inp_str(n, 0, 10);

    printf("\n");

    mpz_t k;
    mpz_init(k);
    printf("Choisissez le nombre d'itération : \n");
    mpz_inp_str(k, 0, 10);

    printf("\n");

    if(miller_rabbin(n, k)) {
        printf("Vôtre nombre est premier\n");
    }
    else {
        printf("Vôtre nombre n'est pas premier\n");
    }

    mpz_clear(n);
    mpz_clear(k);

    return 0;
}