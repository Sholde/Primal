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
   
     

}


int main(int argc, char const *argv[])
{
    mpz_t h;
    mpz_init(h);
    mpz_set_ui(h,8);
   int taille;
   
  
   int *tab ;
   tab= decimaletobinairempz(h,&taille);
   
    for(int j = taille -1 ;j>=0 ; j--)
    {
    	
    	printf("%d\n", tab[j]);

    }
  }
