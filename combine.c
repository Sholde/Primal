#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
#include <time.h>
#include <curses.h>
#include <unistd.h>
gmp_randstate_t etat;

void nb_bit(mpz_t nb, mpz_t h) {
    mpz_set_ui(nb, 0);

    mpz_t h2;
    mpz_init(h2);
    mpz_set(h2, h);
    
    do {
        mpz_div_ui(h2, h2, 2);
        mpz_add_ui(nb, nb, 1);
    } while( mpz_cmp_ui(h2, 0) > 0 );
    mpz_sub_ui(nb, nb, 1);

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
       // squaremultiplympz(a,n, sauv,sm); // sm = a ^{n-1} mod n
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
        square_and_multiply(re,a,n,nr);
      if(mpz_cmp_ui(re,1)==0 || mpz_cmp(re,sous)==0) continue; //on passe a l'itération suivante
	for (mpz_set_ui(j, 1);mpz_cmp(j,nbr1)<=0 ;mpz_add_ui(j,j,1)) 
		{
	        mpz_t deux;
            mpz_init(deux);
            mpz_set_ui(deux,2);
	       // squaremultiplympz(re,n,deux,re); //re = re ^2 mod n
           square_and_multiply(re,re,n,deux);
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
#define TAILLE_MAX 1024 // Tableau de taille 1024
//mpz_set_str
char* lire(char * chemin)
{
    FILE* fichier = NULL;
    char *chaine; 
    chaine=malloc(TAILLE_MAX* sizeof(char));
    fichier = fopen(chemin, "r");
    if (fichier != NULL)
    {
        fgets(chaine, TAILLE_MAX, fichier); // On lit maximum TAILLE_MAX caractères du fichier, on stocke le tout dans "chaine"
        fclose(fichier);
    }
 else
 {
 	printf("Erreur d'ouverture du fichier\n");
 }
    return chaine;
}
//cette procedure permet de faire un menu  pour donner un choix à l'utilisateur 
void Menu()
{
	printf("*************************DM CRYPTO***********************\n");
	printf("Veuillez choisir une option :\n");
	printf("\t 1-Exécuter un nombre d'un fichier  \n");
	printf("\t 2-Entrer le nombre directement \n");
	printf("\t 2-Quitter\n");	
}
void Menu1()
{
	 printf("\t 1- Test de Fermat \n");
	printf("\t 2- Test de Miller Rbin \n");
	printf("\t 3-Quitter \n");
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
printf ("\033[31m");
printf("\n");
printf("\t               .-~~~~~~~~~-._       _.-~~~~~~~~~-.                  \n ");
printf("\t           __.'              ~.   .~              `.__               \n ");
printf("\t          .'//                  ./                  \\`.                 \n ");
printf("\t       .'//                     |                     \\`.\n ");
printf("\t   .'//.-'                 `-.  |  .-'                 ''-.\\`.  \n ");
printf("\t  .'//______.============-..    | /   ..-============.______\\`.\n ");
printf("\t.'______________________________|/______________________________`.\n \n \n ");
printf ("\033[34m");
    mpz_t n;
    mpz_init(n);
    mpz_t k;
    mpz_init(k);
    mpz_t res;
    mpz_init(res);
   int choix;
   int choix1;
   char * nombre;
   char * chemin;
   do
  {
   Menu();
   printf("Votre Choix SVP :\t");
   scanf("%d",&choix);
    switch(choix)
    {
    	case 1:
	chemin=malloc(sizeof(char));
	printf("Donner le chemin du Votre fichier \t");
        scanf("%s",chemin);
	nombre=lire(chemin);
	mpz_t nbr;
	mpz_init(nbr);
        mpz_set_str(nbr,nombre,10);
  do{ 
  	printf("***********************************************\n");
  	Menu1();
  	printf("*************************************************\n");
  	printf("Votre Choix SVP :\t");
        scanf("%d",&choix1);
    if(choix1==1)
    {
              printf("Choisissez le nombre d'itération : \t");
	      mpz_inp_str(k, 0, 10);
	      int f =testFermatmpz(nbr,k);
	      if(f==0)  {
	          printf ("\033[35m"); 
                  printf(" Le nombre : " );
                  mpz_out_str(stdout,10,nbr);
                  printf(" est non premier\n");
                  printf ("\033[34m");
                 
			   }
			   else
			   {
			   	if(f==1)
			   	{
	           printf ("\033[33m");
                   printf(" Le nombre :" );
                   mpz_out_str(stdout,10,nbr); 
                   printf(" est  premier \n");
                   printf ("\033[34m");
			   	}
			   }
    }
    else
    {
    	if(choix1==2)
    	{
               printf("Choisissez le nombre d'itération : \t");
	       mpz_inp_str(k, 0, 10);
	       int m =millerRabinmpz(nbr,k);
	        if(m==0)
	{
	           printf ("\033[35m");
                   printf(" Le nombre  :" );
                   mpz_out_str(stdout,10,nbr);
                   printf(" est non premier \n");
                   printf ("\033[34m");
			   }
			   else
			   {
			   	if(m==1)
			   	{
		  printf ("\033[33m");
                  printf(" Le nombre " );
                  mpz_out_str(stdout,10,nbr);
                   printf(" est  premier \n");
                   printf ("\033[34m");
			   	}
			   }
    	}
    	else
    	{
    		if(choix1==3)
    		{
    			break;
    		}
    	}
    }
 }while(choix1!=3) ;

    	break;

    	case 2:
    	do
     {
  printf("\n\n");
  printf("****************************************\n");
  Menu1();
  printf("*****************************************\n");
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
	           printf ("\033[35m");
                   printf(" Le nombre " );
                   mpz_out_str(stdout,10,n);
                   printf(" est non premier \n");
                   printf ("\033[34m");
			   }
			   else
			   {
			   	if(f==1)
			   	{
		printf ("\033[33m");
                  printf(" Le nombre " );
                   mpz_out_str(stdout,10,n); 
                   printf(" est  premier \n");
                   printf ("\033[34m");
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
		   printf ("\033[35m");
                   printf(" Le nombre " );
                   mpz_out_str(stdout,10,n);
                   printf(" est non premier \n");
                   printf ("\033[34m");
			   }
			   else
			   {
			   	if(m==1)
			   	{
		  printf ("\033[33m");
                  printf(" Le nombre " );
                   mpz_out_str(stdout,10,n);
                   printf(" est  premier \n");
                   printf ("\033[34m");
			   	}
			   } }

  if(choix1==3) 
                break;
        }while(choix1!=3);

            break;
            case 3:
            break;
    }
}while(choix !=2);

  }

