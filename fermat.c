#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
#include <time.h>
gmp_randstate_t etat;
int * decimaletobinairempz(mpz_t h ,int *taille )
{
    *taille=0;
    int i;
    mpz_t res;
    mpz_init(res);
    int res1;
    int *tab=malloc(sizeof(int)); 
     while(mpz_cmp_ui(h ,0)>0)
     {
     	mpz_mod_ui(res,h,2);
     	if(mpz_cmp_ui(res,0)==0)
     	{ tab[*taille]=0;
     	}
     	else
     	{   tab[*taille]=1;
     	}
     	mpz_div_ui(h,h,2);
     	*taille = *taille + 1;  	
     }
     return tab;
     mpz_clear(res);
}
void squaremultiplympz(mpz_t a , mpz_t n ,mpz_t h , mpz_t res)
{
    mpz_t r;
    mpz_init(r);
    mpz_set(r,a);  
    int taille =0;
    int * tab = decimaletobinairempz(h , &taille);
     taille--;
    int i;
    while(taille>0)
    {
    	mpz_mul(r,r,r);
    	mpz_mod(r,r ,n);  	
    	if(tab[--taille] == 1 )
    	{
		mpz_mul(r,r,a);
    		mpz_mod(r,r,n);		
    	}
    }
  mpz_set(res,r);
  mpz_clear(r);
}
int testFermatmpz(mpz_t n ,mpz_t k)
{
	if(mpz_cmp_ui(n,3)==0 || mpz_cmp_ui(n,2)==0)
	{
		return 1;
	}

    mpz_t i;
    mpz_init(i); 
    int result ;
    mpz_t a;
    mpz_init(a);
    mpz_t sm;
    mpz_init(sm);    
    time_t t; 
    int seed;
    seed = (int) time(&t);
    gmp_randinit_default(etat);
    gmp_randseed_ui(etat, seed); 
    mpz_t sous;
    mpz_init(sous);
    mpz_sub_ui(sous,n,1);
    mpz_t sauv;
    mpz_init(sauv);
    for(mpz_set_ui(i,0);mpz_cmp(i,k)<0;mpz_add_ui(i,i,1))
    {
       do { 
      	mpz_urandomm (a, etat, n);

      }while(mpz_cmp_ui(a,0)==0 || mpz_cmp(a,sous)==0 || mpz_cmp_ui(a,1)==0);
      mpz_set(sauv,sous);
        squaremultiplympz(a,n, sauv,sm);
        if(mpz_cmp_ui(sm ,1)!=0 )
        {
		    mpz_clear(i);
		    mpz_clear(a);
		    mpz_clear(sm);
		    mpz_clear(sous);
		    mpz_clear(sauv);
           return 0;
        } 
    }
    mpz_clear(i);
    mpz_clear(a);
    mpz_clear(sm);
    mpz_clear(sous);
    mpz_clear(sauv);
   return 1;
}
int millerRabinmpz(mpz_t n, mpz_t k)
{
	mpz_t mod;
	mpz_init(mod);
	mpz_set_ui(mod,0);
	mpz_mod_ui(mod,n,2);
	if (mpz_cmp_ui(n, 2)==0 || mpz_cmp_ui(n ,3)==0)
	 {
	 mpz_clear(mod);
	 return 1;
	} else
	 if (mpz_cmp_ui(mod,0) ==0)
	  { 
	  	mpz_clear(mod);
	  	return 0;
	}
    mpz_t nbr;
    mpz_init(nbr);
    mpz_set_ui(nbr,0);
    mpz_t n1;
    mpz_init(n1);
    mpz_sub_ui(n1,n,1);
    mpz_mod_ui(mod,n1,2);
    while (mpz_cmp_ui(mod,0)== 0) 
	{
	mpz_div_ui(n1,n1,2);
	mpz_add_ui(nbr,nbr,1);	
        mpz_mod_ui(mod,n1,2);
}
    mpz_t i;
    mpz_init(i);
    time_t t;
    int seed;
    seed = (int) time(&t); 
    gmp_randinit_default(etat);
    gmp_randseed_ui(etat, seed);
    mpz_t sous;
    mpz_init(sous);
    mpz_sub_ui(sous,n,1);
    mpz_t nbr1;
    mpz_init(nbr1);
    mpz_sub_ui(nbr1,nbr,1);
    mpz_t j;
    mpz_init(j);
    mpz_t nr;
    mpz_init(nr);
	for (mpz_set_ui(i,0); mpz_cmp(i,k)<0; mpz_add_ui(i,i,1)) 
	{
		mpz_t result;
		mpz_init(result);
		mpz_set_ui(result,0);
		mpz_t a;
		mpz_init(a);
      do{     mpz_urandomm(a,etat,n);
		}while(mpz_cmp_ui(a,0)==0);
   
        mpz_t re;
        mpz_init(re);
        mpz_set(nr,n1);
        squaremultiplympz(a,n,nr,re);
        if(mpz_cmp_ui(re,1)==0 || mpz_cmp(re,sous)==0) continue;
	for (mpz_set_ui(j, 1);mpz_cmp(j,nbr1)<=0 ;mpz_add_ui(j,j,1)) 
		{
	        mpz_t deux;
            mpz_init(deux);
            mpz_set_ui(deux,2);
	    squaremultiplympz(re,n,deux,re);
	    if(mpz_cmp(re,sous)==0)
		     {
		    mpz_set_ui(result,1);
		     break;
	}}
		if (mpz_cmp_ui(result, 0)==0) 
			{
				mpz_clear(mod);
				mpz_clear(nbr);
				mpz_clear(n1);
				mpz_clear(i);
				mpz_clear(sous);
				mpz_clear(nbr1);
				mpz_clear(j);
				mpz_clear(nr);
				mpz_clear(a);
				mpz_clear(re);
				return 0;
			}
	}
	mpz_clear(mod);
	mpz_clear(nbr);
	mpz_clear(n1);
	mpz_clear(i);
	mpz_clear(sous);
	mpz_clear(nbr1);
	mpz_clear(j);
	mpz_clear(nr);

	return 1;
}
void Menu()
{
	printf("*************************DM CRYPTO***********************\n");
	printf("Veuillez choisir une option :\n");
	printf("\t 1- Test de Fermat \n");
	printf("\t 2- Test de Miller Rbin \n");
	printf("\t 3-Quitter \n");

}
int main(int argc, char const *argv[])
{
    mpz_t n;
    mpz_init(n);
   
    mpz_t k;
    mpz_init(k);
    mpz_t res;
   mpz_init(res);
   Menu();
   int choix;
   do

  {
   printf("Votre Choix SVP :\t");
    scanf("%d",&choix);
    switch(choix)
    {
    	 case 1:
			   printf("Choisissez le nombre à tester : \t");
			   mpz_inp_str(n, 0, 10);
			   printf("\n");
			   printf("Choisissez le nombre d'itération : \t");
			   mpz_inp_str(k, 0, 10);
			   int f =testFermatmpz(n,k);
			   if(f==0)
			   {
                   printf(" Le nombre " );
                   mpz_out_str(stdout,10,n);
                   printf(" est non premier \n");
			   }
			   else
			   {
			   	if(f==1)
			   	{
                  printf(" Le nombre " );
                   mpz_out_str(stdout,10,n);
                   printf(" est  premier \n");
			   	}

			   }
   break;
   case 2:
			   printf("Choisissez le nombre à tester : \t");
			   mpz_inp_str(n, 0, 10);
			   printf("\n");
			   printf("Choisissez le nombre d'itération : \t");
			   mpz_inp_str(k, 0, 10);
			   int m =millerRabinmpz(n,k);
			   if(m==0)
			   {
                   printf(" Le nombre " );
                   mpz_out_str(stdout,10,n);
                   printf(" est non premier \n");
			   }
			   else
			   {
			   	if(m==1)
			   	{
                  printf(" Le nombre " );
                   mpz_out_str(stdout,10,n);
                   printf(" est  premier \n");
			   	}

			   }
   break;

   case 3:
   break;

    }
 
}while(choix !=3);

  }
