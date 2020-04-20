#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <gmp.h>

#include "sandm.h"
#include "miller_rabbin.h"

void decompose(mpz_t n, mpz_t s, mpz_t t) {
    mpz_t n_1;
    mpz_init(n_1); //initialisation d'une variable nommé n_1

    mpz_sub_ui(n_1, n, 1);//n_1=n-1

    mpz_t i;
    mpz_init(i);//initialisation d'une variable nommé i  

    mpz_t mod;//initialisation d'une variable nommé mod
    mpz_init(mod);

    for(mpz_set_ui(i, 0); mpz_cmp(i, n) < 0; mpz_add_ui(i, i, 1)) {
        mpz_mod_ui(mod, n_1, 2);//mod=n_1 % 2
        if( mpz_cmp_ui(mod, 0) != 0 ) { //si mod !=0 
            mpz_set(i, n);
        }
        mpz_div_ui(n_1, n_1, 2);//n_1 = n_1 /2
        mpz_add_ui(s, s, 1);//s=s+1;
    }
    mpz_sub_ui(n_1, n, 1);//n_1 = n - 1;
    mpz_sub_ui(s, s, 1); //s =s -1;

    mpz_t deux;
    mpz_init(deux);//initialisation d'une variable nommé deux pour stocker la valeur 2
    mpz_set_ui(deux, 2);//deux = 2

    mpz_t tmp;
    mpz_init(tmp);
    square_and_multiply(tmp,deux,n,s);//tmp = 2 ^s mod n
    mpz_div(t, n_1, tmp);//t = n_1 / tmp
   //libération de l'espace mémoire
    mpz_clear(n_1);
    mpz_clear(i);
    mpz_clear(deux);
    mpz_clear(tmp);
    mpz_clear(mod);
}

int miller_rabbin(mpz_t n, mpz_t k) {
    //cas particulier
    if(mpz_cmp_ui(n, 1) <= 0) {
        return 0;//non premier
    }
    if(mpz_cmp_ui(n, 2) == 0 || mpz_cmp_ui(n, 3) == 0)
        return 1;//premier si n=2 ou n=3 cas particulier
    
    // test si il est pair ,si c'est pair on returne non premier :0
    mpz_t un;
    mpz_init(un);//initialisation d'une variable nommé un pour stocker la valeur 1
    mpz_set_ui(un, 1);//un=1
    mpz_t pair;
    mpz_init(pair);//initialisation d'une variable nommé pair
    mpz_and(pair, n, un);
    if(mpz_cmp_ui(pair, 0) == 0) { //pair alors non premier 
        mpz_clear(un);
        mpz_clear(pair);
        return 0;//non premier 
    }
    mpz_clear(un);
    mpz_clear(pair);

    // décomposition
    mpz_t s;
    mpz_init(s);

    mpz_t t;
    mpz_init(t);
    
    decompose(n, s, t);
    
    // test
    mpz_t i;
    mpz_init(i);

    time_t ti; 
    int seed;
    seed = time(&ti);
    srand(seed);
    gmp_randstate_t etat;
    gmp_randinit_default(etat);
    gmp_randseed_ui(etat, rand()); //initialisation d'un générateur aléatoire

    mpz_t a;
    mpz_init(a);//initialisation d'une variable nommé a

    mpz_t y;
    mpz_init(y);//initialisation d'une variable nommé y

    mpz_t j;//initialisation d'une variable nommé j
    mpz_init(j);

    mpz_t deux;
    mpz_init(deux);//initialisation d'une variable nommé deux 
    mpz_set_ui(deux, 2);//deux=2

    mpz_t n_1;
    mpz_init(n_1);//initialisation d'une variable nommé n_1
    mpz_sub_ui(n_1, n, 1);//n_1=n-1

    mpz_t n_4;
    mpz_init(n_4);//initialisation d'une variable nommé n_4
    mpz_sub_ui(n_4, n, 4);//n_4 = n-4

    int bk = 0;
//la boucle qui va de i=0 à k-1
    for(mpz_set_ui(i, 0); mpz_cmp(i, k) < 0; mpz_add_ui(i, i, 1)) {
        
        mpz_urandomm(a, etat, n_4); //génération aléatoire d'un nombre a tel que 0<a<n-4
        mpz_add_ui(a, a, 2);//ajouter de 2 pour que a soit entre 2=<a<=n-2
        square_and_multiply(y, a, n, t);//y = a^t mod n

        if( mpz_cmp_ui(y, 1) != 0 && mpz_cmp(y, n_1) != 0 ) { //si y \equiv 1 mod n ou y\equiv n-1 mod n alors on continue
            for(mpz_set_ui(j, 0); mpz_cmp(j, s) < 0; mpz_add_ui(j, j, 1)) {
                square_and_multiply(y, y, n, deux);
                if( mpz_cmp_ui(y, 1) == 0 ) {//si y==1 alors composé 
                    return 0;
                }
                if( mpz_cmp(y, n_1) == 0 ) { //si y ==n-1 alors prob premier et break 
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
//libération de l'espace mémoire
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
