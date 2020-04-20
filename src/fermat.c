#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <gmp.h>

#include "sandm.h"
#include "fermat.h"

//cette fonction permet de tester si un nombre est probablement premier ou composé 
//elle prend en paramètre deux nombres : n  le nombre à tester et k le nombre de fois à faire le test 
int testFermatmpz(mpz_t n ,mpz_t k)
{
	// cas particulier ou n=3 ou n=2 on dit sont premier
	//on les a met comme cas particulier car dans la boucle for quand on v prendre 1<a<3-1 donc 1<a<2 
	//et il n y pas un nombre a tester 
	if(mpz_cmp_ui(n,3)==0 || mpz_cmp_ui(n,2)==0)
	{
		return 1;
	}

    mpz_t i;
    mpz_init(i);
    mpz_t a;
    mpz_init(a);
    mpz_t sm;
    mpz_init(sm);    
    time_t t; 
    int seed;
    seed = (int) time(&t);
    gmp_randstate_t etat;
    gmp_randinit_default(etat);//pour initialisation de la génération aléatoire avec gmp
    gmp_randseed_ui(etat, seed); 
    mpz_t sous;
    mpz_init(sous);
    mpz_sub_ui(sous,n,1); //sous = n-1
    mpz_t sauv;
    mpz_init(sauv);
    for(mpz_set_ui(i,0);mpz_cmp(i,k)<0;mpz_add_ui(i,i,1)) //for i:=0 to k-1
    {
       do { 
      	mpz_urandomm (a, etat, n);//choisir un nombre aléatoire a 

      }while(mpz_cmp_ui(a,0)==0 || mpz_cmp(a,sous)==0 || mpz_cmp_ui(a,1)==0); //il faut que a soit entre 1 et n-1  , 1<a<n-1
          mpz_set(sauv,sous); //on a fait ca parce que la fonction squaremultiplympz modifier la valeur de l'exposant 
          //pour cela on la sauvegarder dans la variable sous 
          square_and_multiply(sm,a,n,sauv);
        if(mpz_cmp_ui(sm ,1)!=0 ) // si sm != 1
        {
		    mpz_clear(i);//libération
		    mpz_clear(a);
		    mpz_clear(sm);
		    mpz_clear(sous);
		    mpz_clear(sauv);
           return 0;//composé
        } 
    }
    mpz_clear(i);
    mpz_clear(a);
    mpz_clear(sm);
    mpz_clear(sous);
    mpz_clear(sauv);
   return 1;//probablement premier
}
