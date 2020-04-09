#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>

int popcount(int n) {
    int pc = 0;
    for(int i = 0; i < 32; i++) {
        pc += (n & 1);
        n >>= 1;
    }
    return pc;
}

void nb_bit(mpz_t nb, mpz_t h) {
    mpz_set_ui(nb, 1);
    while( mpz_div_ui(h, h, 2) && mpz_cmp_ui(h, 0) > 0 ) {
        mpz_add_ui(nb, nb, 1);
    }
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
    mpz_set(i, nb);
    mpz_sub_ui(i, i, 1);

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

    decompose(n, s, t);
    printf("s :");
    mpz_out_str(0, 10, s);
    printf("\n");
    printf("t :");
    mpz_out_str(0, 10, t);
    printf("\n");
    
    // test
    mpz_t i;
    mpz_init(i);

    mpz_t a;
    mpz_init(a);

    mpz_t y;
    mpz_init(y);

    mpz_t j;
    mpz_init(j);

    mpz_t deux;
    mpz_init(deux);
    mpz_set_ui(deux, 2);

    int bk = 0;

    for(mpz_set_ui(i, 0); mpz_cmp(i, k) < 0; mpz_add_ui(i, i, 1)) {
        mpz_set(a, i);
        square_and_multiply(y, a, t, n);
        if( mpz_cmp_ui(y, 1) != 0 || mpz_cmp_ui(y, -1) != 0) {
            for(mpz_set_ui(j, 1); mpz_cmp(j, s) < -1; mpz_add_ui(j, j, 1)) {
                square_and_multiply(y, y, deux, n);
                if( mpz_cmp_ui(y, 1) == 0 ) {
                    return 0;
                }
                if( mpz_cmp_ui(y, -1) == 0 ) {
                    bk = 1;
                    break;
                }
            }
            if( !bk ) {
                return 0;
            }
            bk = 0;
        }
    }

    mpz_clear(s);
    mpz_clear(t);
    mpz_clear(i);
    mpz_clear(j);
    mpz_clear(a);
    mpz_clear(y);
    mpz_clear(deux);

    return 1;
}

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