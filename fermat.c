#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
#include <time.h>

int * decimaletobinaire(int h ,int * taille)
{
     int *tab= malloc(sizeof(int ));
     *taille=0;
    while(h>0)
     {
     	if(h %2 ==0 )
           	tab[*taille]= 0;
           else tab[*taille]=1;

     	h = h /2;
     	*taille = *taille +1 ;
     }
     
     return tab;

}
//cette fonction permet de calculer l'expontation modulaire 
// a^h mod n

int squaremultiply(int a , int n ,int h)
{ 
    int r = a;
    int taille =0;
    int * tab = decimaletobinaire(h , &taille);

    taille--;
    while(taille>0)
    {
    	r = (r * r) % n ;
    	if(tab[--taille] == 1 )
    	{
    		r = (r * a ) % n ;
   	}
    }
    return r;
}

int millerRabin(int n ,int k)
{
    int s = 0;
    int n1 = n - 1;
    while ((n1 % 2) == 0) 
	{
		n1 /= 2;
		s++;
	}

	for (int i = 0; i < k; i++)
	 {
		int result = 0;
		int a = (rand() % (n - 1)) + 1;   
		int re =squaremultiply(a,n,n1);
		if (re == 1 || re == (n - 1)) continue;
		for (int j = 1; j <= (s - 1); j++) 
		{
			re =squaremultiply(re,n,2);
			if (re == (n - 1)) {
				result = 1;
				break;
			}
		}
		if (result == 0) return 0;
	}
	return 1;
}
//cette fonction permet de tester si un nombre est premier ou compose :return  1 si n est premier  sinon return 0  pour composé 
int testFermat(int n ,int k)
{
	int i;
	int result ;
	int  a;
	int sm;
    for(i=0;i<k;i++)
    {
        a = rand() %(n-1) + 1;
        sm=squaremultiply(a,n, (n-1));
        if(sm != 1)
        {
        	return 0;
        }

    }
    return 1;
}
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
     	{
     		 tab[*taille]=0;
     	}
     	else
     	{
     		tab[*taille]=1;
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

gmp_randstate_t etat;

int testFermatmpz(mpz_t n ,mpz_t k)
{
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
    for(mpz_set_ui(i,0);mpz_cmp(i,k)<0;mpz_add_ui(i,i,1))
    {
       do
      
      { 
      	mpz_urandomm (a, etat, n);

      }while(mpz_cmp_ui(a,0)==0);

        squaremultiplympz(a,n, sous,sm);
        if(mpz_cmp_ui(sm ,1)!=0 )
        {
        	  mpz_clear(i);
			  mpz_clear(a);
			  mpz_clear(sm);
			  mpz_clear(sous);
			
  
        	return 0;
        }

    }
  mpz_clear(i);
  mpz_clear(a);
  mpz_clear(sm);
  mpz_clear(sous);
  
  
    return 1;
}

int millerRabinmpz(mpz_t n, mpz_t k)
{
	mpz_t mod;
	printf("k=");
  mpz_out_str(stdout,10,k);
  printf("\n\n");
	mpz_init(mod);
	mpz_set_ui(mod,0);
	mpz_mod_ui(mod,n,2);
	if (mpz_cmp_ui(n, 2)==0 || mpz_cmp_ui(n ,3)==0)
	 {
	 	
		return 1;
	} 
	else
	 if (mpz_cmp_ui(mod,0) ==0)
	  {
	  
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
      do
		{

			mpz_urandomm(a,etat,n);

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
			}
		}
		if (mpz_cmp_ui(result, 0)==0) return 0;
	}
	return 1;
}

int main(int argc, char const *argv[])
{
    mpz_t a;
    mpz_init(a);
    mpz_set_ui(a,17);
    mpz_t h;
    mpz_init(h);
    mpz_set_ui(h,3);
    mpz_t n;
    mpz_init(n);
    mpz_set_ui(n,13);

  // printf("%d\n",testFermatmpz(a,k) );
   printf("sq=%d\n",squaremultiply(11,13,3) );
   mpz_t res;
   mpz_init(res);
 //  squaremultiplympz(a,n,h,res);
   mpz_out_str(stdout,10,res);
   printf("\n\n");
   printf("%d\n",millerRabin(13,10) );
   printf("fermat=%d\n",testFermat(20,10) );
   printf("miller =%d\n",millerRabinmpz(a,h) );


   
  }
