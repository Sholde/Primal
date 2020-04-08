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

/*int * decimaletobinairempz(mpz_t h ,int * taille)
{
     int *tab= malloc(sizeof(int ));
    
     mpz_t i;
     mpz_init(i);
     for(mpz_set_ui(i,0); mpz_cmp_ui(h ,0)>0 ;mpz_add_ui(i,i,1))
     {
     	tab[i]= h%2;
     	h = h /2;
     	*taille = *taille +1 ;
     }
     
     return tab;

}*/

/*void squaremultiplympz(mpz_t a , mpz_t n ,mpz_t h , mpz_t r)
{
    mpz_t r;
    mpz_init(r);
    mpz_set(r,a);

    
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
}*/
/*int * decimaletobinairempz(mpz_t h , mpz_t taille )
{
   
    mpz_t i;
    mpz_init(i);
    mpz_set_ui(i , 0);
    int *tab =malloc(sizeof(int ));
    for(mpz_set_ui(i,0); mpz_cmp_ui(h , 0) >0 ; mpz_add_ui(i,i,1))
    {

        tab[i]
    }
     for(int i=0; h > 0;i++)
     {
     	tab[i]= h%2;
     	h = h /2;
     	*taille = *taille +1 ;
     }
     
     return tab;
}*/
int main(int argc, char const *argv[])
{

printf("%d\n",testFermat(3,5) );
}