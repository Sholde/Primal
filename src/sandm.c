#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <gmp.h>

#include "sandm.h"

void nb_bit(mpz_t nb, mpz_t h) {
    mpz_set_ui(nb, 0);//initialiser nb à zéro ,nb=0

    mpz_t h2;
    mpz_init(h2);
    mpz_set(h2, h);//pour ne pas modifier la variable h et on la stocke dans h2 et on tavaille avec h2 ,h2=h
    
    do {
        mpz_div_ui(h2, h2, 2); //h2=h2/2
        mpz_add_ui(nb, nb, 1);//nb=nb+1
    } while( mpz_cmp_ui(h2, 0) > 0 );//tant que h2>0 on continue la boucle
    mpz_sub_ui(nb, nb, 1);//nb=nb-1;

    mpz_clear(h2);//libération de la mémoire 
}

void pos(mpz_t test, mpz_t i) {
    mpz_set_ui(test, 1);//test=1

    mpz_t j;
    mpz_init(j);//initialisation de la variable j

    for(mpz_set_ui(j, 0); mpz_cmp(j, i) < 0; mpz_add_ui(j, j, 1)) {//de j=0 à i-1
        mpz_mul_ui(test, test, 2);//test=test*2
    }

    mpz_clear(j);//libération
}

// a^h mod n
void square_and_multiply(mpz_t res, mpz_t a, mpz_t n, mpz_t h) {
    mpz_set(res, a); //res = a

    mpz_t nb;
    mpz_init(nb);
    nb_bit(nb, h);//nb= nombre de bit de h

    mpz_t i;
    mpz_init(i);
    mpz_sub_ui(i, nb, 1);//i = nb-1

    mpz_t test;
    mpz_init(test);

    for(; mpz_cmp_ui(i, 0) >= 0; mpz_sub_ui(i, i, 1)) {
        mpz_mul(res, res, res);//res=res*res
        mpz_mod(res, res, n);//res=res%n

        pos(test, i);//test=2^i
        mpz_and(test, test, h);
        if(mpz_cmp_ui(test, 0) != 0) {
            mpz_mul(res, res, a);//res=res*a
            mpz_mod(res, res, n);//res=res %n
        }
    }
//libération
    mpz_clear(nb);
    mpz_clear(i);
    mpz_clear(test);
}
