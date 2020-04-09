#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
#include <time.h>

int * decimaletobinaire(int h ,int * taille)
{
     int *tab= malloc(sizeof(int ));
    
     for(int i=0; h > 0;i++)
     {
     	tab[i]= h%2;
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
    int i;
    for(i = taille - 1 ; i>=0 ;i--)
    {
    	r = (r * r) % n ;
    	if(tab[i] == 1 )
    	{
    		r = (r * a ) % n ;
    	}
    }
    return r;
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
     
    
    int i;
    mpz_t res;
    mpz_init(res);
    int res1;

    int *tab=malloc(sizeof(int));
     
     for(i=0; mpz_cmp_ui(h ,0)>0 ;i++)
     {

     	mpz_mod_ui(res,h,2);
     	res1=mpz_get_si(res);
     	tab[i]=res1;
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

    int i;
    for(i = taille - 1 ; i>=0 ;i--)
    {
    	mpz_mul(r,r,r);
    	mpz_mod(r,r ,n);
    	
    	if(tab[i] == 1 )
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

      mpz_t sous1;
      mpz_init(sous1);
      mpz_sub_ui(sous1,n,1);


    for(mpz_set_ui(i,0);mpz_cmp(i,k)<0;mpz_add_ui(i,i,1))
    {
       do
      
      { 
      	mpz_urandomm (a, etat, sous);

      }while(mpz_cmp_ui(a,0)==0);

        squaremultiplympz(a,n, sous1,sm);
        if(mpz_cmp_ui(sm ,1)!=0 )
        {
        	  mpz_clear(i);
			  mpz_clear(a);
			  mpz_clear(sm);
			  mpz_clear(sous);
			  mpz_clear(sous1);
  
        	return 0;
        }

    }
  mpz_clear(i);
  mpz_clear(a);
  mpz_clear(sm);
  mpz_clear(sous);
  mpz_clear(sous1);
  
    return 1;
}

int millerRabin(int n ,int k)
{
	int n1 = n-1;
	int s = 0;
	while(n1 % 2 !=0)
	{
         n1 = n1 /2;

         s = s +1;
	}
	int i;
	int a;
	int n2 = n-1;
	int y;
	int j;
	//0 compose ;
	for(i= 1 ; i<=k ;i++ )
	{
		
         a = rand() % n2 + 1; 
         y = squaremultiply(a , n , n1);
       
         if(y != 1 && y != -1 )
         {
         	
         	for(j=1 ; j<s;j++ )
         	{
         		
                  y=squaremultiply(y , n ,2);

                  if(y == 1)
                  {
                  	return 0;
                  }
                  if(y == -1)
                  {
                  	break;
                  }
                  return 0;
         	}
         	
         }

		
	}
	return 1; // 1 est premie
}
int main(int argc, char const *argv[])
{
    mpz_t a;
    mpz_init(a);
    mpz_set_ui(a,10);
    mpz_t k;
    mpz_init(k);
    mpz_set_ui(k,10);

   printf("%d\n",testFermatmpz(a,k) );
   printf("%d\n",millerRabin(13,10) );

   
  }
