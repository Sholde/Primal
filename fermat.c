#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
#include <time.h>
#include <curses.h>
#include <unistd.h>
gmp_randstate_t etat;
//cette fonction permet de convertir un nombre en décimale en un nombre binaire 
/*cette fonction prend deux paramtre , le nombre à convertir  :h et une variable taille qui permet de récuperer la taille de 
l'éélement converti
*/
/*cette fonction return l'élèment converti en binaire sous forme d'un tableau */
int * decimaletobinairempz(mpz_t h ,int *taille )
{
    *taille=0; //on met ici la valeur de la variable taille à zéro au cas ou la variable est modifié à l'extérieure 
    int i;
    mpz_t res;
    mpz_init(res);
    int res1;
    int *tab=malloc(sizeof(int)); 
     while(mpz_cmp_ui(h ,0)>0) // tant que h>0
     {
     	mpz_mod_ui(res,h,2); // cette fonction permet decalculer h mod 2 
     	if(mpz_cmp_ui(res,0)==0)  //si  h mod 2 ==0 on met dans la case tab[*taille] la valeur 0 sinon 1
     	{ tab[*taille]=0;
     	}
     	else
     	{   tab[*taille]=1;
     	}
     	mpz_div_ui(h,h,2); // h = h/2;
     	*taille = *taille + 1;  	
     }
     return tab;
     mpz_clear(res);//liberer de l'espace mémoire 
}
//cette fonction permet de calculer l'expontation modulaire 
//elle prend en oaramètre a , n , h et res ou on va stocker le résultats 
//res = a ^ h mod n
void squaremultiplympz(mpz_t a , mpz_t n ,mpz_t h , mpz_t res)
{
    mpz_t r;
    mpz_init(r);
    mpz_set(r,a);  
    int taille =0;
    //convertir h en binaire 
    int * tab = decimaletobinairempz(h , &taille);
    //appliquer l 'algorithme de square and multiply '
     taille--; 
    int i;
    while(taille>0)
    {
    	mpz_mul(r,r,r); //r =r *r ;
    	mpz_mod(r,r ,n);  //r = r mod n 	
    	if(tab[--taille] == 1 )
    	{
		mpz_mul(r,r,a);
    		mpz_mod(r,r,n);		
    	}
    }
  mpz_set(res,r);
  mpz_clear(r);
}
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
    int result ;
    mpz_t a;
    mpz_init(a);
    mpz_t sm;
    mpz_init(sm);    
    time_t t; 
    int seed;
    seed = (int) time(&t);
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
        squaremultiplympz(a,n, sauv,sm); // sm = a ^{n-1} mod n
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
//cette fonction permet de tester si un nombre est probablement premier ou composé 
int millerRabinmpz(mpz_t n, mpz_t k)
{
	mpz_t mod;
	mpz_init(mod);
	mpz_set_ui(mod,0);
	mpz_mod_ui(mod,n,2);
	//mod = n %2 
	//cas particulier ou n=2 ou n=3 on dit que ils sont premiers 
	if (mpz_cmp_ui(n, 2)==0 || mpz_cmp_ui(n ,3)==0)
	 {
	 mpz_clear(mod);
	 return 1;
	} else
	 if (mpz_cmp_ui(mod,0) ==0) //le cas ou le nombre est pair alors on dit qu'il ne sont pas premiers
	  { 
	  	mpz_clear(mod);
	  	return 0;
	}
    mpz_t nbr;
    mpz_init(nbr);
    mpz_set_ui(nbr,0); // nbr =0 
    mpz_t n1;
    mpz_init(n1);
    mpz_sub_ui(n1,n,1); //n1= n-1
    mpz_mod_ui(mod,n1,2); // mod = n1 %2
    //cette boucle permet d'ecrire n-1 sous forme n-1 = 2 ^s * t
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
    mpz_sub_ui(sous,n,1); //sous=n-1
    mpz_t nbr1;
    mpz_init(nbr1);
    mpz_sub_ui(nbr1,nbr,1); //nbr1 = nbr -1 
    mpz_t j;
    mpz_init(j);
    mpz_t nr;
    mpz_init(nr);
	for (mpz_set_ui(i,0); mpz_cmp(i,k)<0; mpz_add_ui(i,i,1)) 
	{
		mpz_t result;
		mpz_init(result);
		mpz_set_ui(result,0);//cette  variable pour a chaque a dire si n est prob premier ou composé 
		mpz_t a;
		mpz_init(a);
      do{     mpz_urandomm(a,etat,n); //la génération aléatoire de a
		}while(mpz_cmp_ui(a,0)==0);
   
        mpz_t re;
        mpz_init(re);
        mpz_set(nr,n1);
        squaremultiplympz(a,n,nr,re); // re = a ^ nr mod n
      if(mpz_cmp_ui(re,1)==0 || mpz_cmp(re,sous)==0) continue; //on passe a l'itération suivante
	for (mpz_set_ui(j, 1);mpz_cmp(j,nbr1)<=0 ;mpz_add_ui(j,j,1)) 
		{
	        mpz_t deux;
            mpz_init(deux);
            mpz_set_ui(deux,2);
	    squaremultiplympz(re,n,deux,re); //re = re ^2 mod n
	    if(mpz_cmp(re,sous)==0) //si res = sous
		     {
		    mpz_set_ui(result,1); // result=1 //prob premier 
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
				return 0; // composé 
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

	return 1;//premier 
}
//cette procedure permet de faire un menu  pour donner un choix à l'utilisateur 
void Menu()
{
	printf("*************************DM CRYPTO***********************\n");
	printf("Veuillez choisir une option :\n");
	printf("\t 1-Exécuter les fonction du Dm  \n");
	printf("\t 2-Quitter\n");
	
}
char *str="Bienvenue dans notre  programme Lynda & Nicolas  :) \n";
int main(int argc, char const *argv[])
{

	 system("clear");

	 printf ("\033[32m");
	 int f=0;
    printf("\n\n\t\t\t");
    int c=1;
    while(str[f]!='\0')
    {
    	printf ("%c", str[f]);
        fflush(stdout);
        usleep(100000);
        f++;
       
    }

printf("\n");
printf("\t               .-~~~~~~~~~-._       _.-~~~~~~~~~-.                  \n ");
printf("\t           __.'              ~.   .~              `.__               \n ");
printf("\t          .'//                  ./                  \\`.                 \n ");
printf("\t       .'//                     |                     \\`.\n ");
printf("\t   .'//.-'                 `-.  |  .-'                 ''-.\\`.  \n ");
printf("\t  .'//______.============-..    | /   ..-============.______\\`.\n ");
printf("\t.'______________________________|/______________________________`.\n \n \n ");
    mpz_t n;
    mpz_init(n);
   
    mpz_t k;
    mpz_init(k);
    mpz_t res;
   mpz_init(res);
  
   int choix;
   int choix1;
   do

  {
  	 Menu();
   printf("Votre Choix SVP :\t");
    scanf("%d",&choix);

    switch(choix)
    {

    	case 1:
    printf("\t 1- Test de Fermat \n");
	printf("\t 2- Test de Miller Rbin \n");
	printf("\t 3-Quitter \n");
    printf("Votre Choix SVP :\t");
    scanf("%d",&choix1);
       if(choix1 ==1){

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
   }
   if(choix1==2){
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
  }

  if(choix1==3) 
                break;
            break;
            case 2:
            break;
           


    }

 
}while(choix !=2);

  }

