#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <gmp.h>

#include "miller_rabbin.h"

void nb_bit(mpz_t nb, mpz_t h) {
    mpz_set_ui(nb, 1);

    mpz_t h2;
    mpz_init(h2);
    mpz_set(h2, h);

    while( mpz_div_ui(h2, h2, 2) && mpz_cmp_ui(h2, 0) > 0 ) {
        mpz_add_ui(nb, nb, 1);
    }

    mpz_clear(h2);
}

void pos(mpz_t test, mpz_t i) {
    mpz_set_ui(test, 1);

    mpz_t j;
    mpz_init(j);

    for(mpz_set_ui(j, 0); mpz_cmp(j, i) < 0; mpz_add_ui(j, j, 1)) {
        mpz_mul_ui(test, test, 2);
    }

    mpz_clear(j);
}

// a^h mod n
void square_and_multiply(mpz_t res, mpz_t a, mpz_t n, mpz_t h) {
    mpz_set(res, a);

    mpz_t nb;
    mpz_init(nb);
    nb_bit(nb, h);

    mpz_t i;
    mpz_init(i);
    mpz_sub_ui(i, nb, 1);

    mpz_t test;
    mpz_init(test);

    for(; mpz_cmp_ui(i, 0) >= 0; mpz_sub_ui(i, i, 1)) {
        mpz_mul(res, res, res);
        mpz_mod(res, res, n);

        pos(test, i);
        mpz_and(test, test, h);
        if(mpz_cmp_ui(test, 0) != 0) {
            mpz_mul(res, res, a);
            mpz_mod(res, res, n);
        }
    }

    mpz_clear(nb);
    mpz_clear(i);
    mpz_clear(test);
}

void decompose(mpz_t n, mpz_t s, mpz_t t) {
    mpz_t n_1;
    mpz_init(n_1);

    mpz_sub_ui(n_1, n, 1);

    mpz_t i;
    mpz_init(i);

    mpz_t mod;
    mpz_init(mod);

    for(mpz_set_ui(i, 0); mpz_cmp(i, n) < 0; mpz_add_ui(i, i, 1)) {
        mpz_mod_ui(mod, n_1, 2);
        if( mpz_cmp_ui(mod, 0) != 0 ) {
            mpz_set(i, n);
        }
        mpz_div_ui(n_1, n_1, 2);
        mpz_add_ui(s, s, 1);
    }
    mpz_sub_ui(n_1, n, 1);
    mpz_sub_ui(s, s, 1);

    mpz_t deux;
    mpz_init(deux);
    mpz_set_ui(deux, 2);

    mpz_t tmp;
    mpz_init(tmp);
    mpz_powm(tmp, deux, s, n);

    mpz_div(t, n_1, tmp);

    mpz_clear(n_1);
    mpz_clear(i);
    mpz_clear(deux);
    mpz_clear(tmp);
    mpz_clear(mod);
}

int miller_rabbin(mpz_t n, mpz_t k) {
    if(mpz_cmp_ui(n, 1) <= 0) {
        return 0;
    }
    if(mpz_cmp_ui(n, 2) == 0 || mpz_cmp_ui(n, 3) == 0)
        return 1;
    
    // test si il est pair
    mpz_t un;
    mpz_init(un);
    mpz_set_ui(un, 1);
    mpz_t pair;
    mpz_init(pair);
    mpz_and(pair, n, un);
    if(mpz_cmp_ui(pair, 0) == 0) {
        mpz_clear(un);
        mpz_clear(pair);
        return 0;
    }
    mpz_clear(un);
    mpz_clear(pair);

    // décomposition
    mpz_t s;
    mpz_init(s);

    mpz_t t;
    mpz_init(t);
    
    // test
    mpz_t i;
    mpz_init(i);

    time_t ti; 
    int seed;
    seed = time(&ti);
    srand(seed);
    gmp_randstate_t etat;
    gmp_randinit_default(etat);
    gmp_randseed_ui(etat, rand()); 

    mpz_t a;
    mpz_init(a);

    mpz_t y;
    mpz_init(y);

    mpz_t j;
    mpz_init(j);

    mpz_t deux;
    mpz_init(deux);
    mpz_set_ui(deux, 2);

    mpz_t n_1;
    mpz_init(n_1);
    mpz_sub_ui(n_1, n, 1);

    mpz_t n_4;
    mpz_init(n_4);
    mpz_sub_ui(n_4, n, 4);

    int bk = 0;

    for(mpz_set_ui(i, 0); mpz_cmp(i, k) < 0; mpz_add_ui(i, i, 1)) {

        mpz_urandomm(a, etat, n_4);
        mpz_add_ui(a, a, 2);
        square_and_multiply(y, a, n, t);
        mpz_out_str(0, 10, y);

        if( mpz_cmp_ui(y, 1) != 0 && mpz_cmp(y, n_1) != 0 ) {
            for(mpz_set_ui(j, 0); mpz_cmp(j, s) < 0; mpz_add_ui(j, j, 1)) {
                mpz_mul(y, y, y);
                mpz_mod(y, y ,n);
                if( mpz_cmp_ui(y, 1) == 0 ) {
                    return 0;
                }
                if( mpz_cmp(y, n_1) == 0 ) {
                    bk = 1;
                    break;
                }
            }
            if( bk == 0 ) {
                return 0;
            }
            bk = 0;
        }
    }

    mpz_clear(n_1);
    mpz_clear(n_4);
    mpz_clear(s);
    mpz_clear(t);
    mpz_clear(i);
    mpz_clear(j);
    mpz_clear(a);
    mpz_clear(y);
    mpz_clear(deux);

    return 1;
}
