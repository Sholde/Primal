#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <gmp.h>
#include "miller_rabbin.h"
#include "fermat.h"

#define TAILLE_MAX 1024 // Tableau de taille 1024

char *lire(char *chemin) {
    FILE* fichier = NULL;
    char *chaine = malloc(sizeof(char) * TAILLE_MAX);
    fichier = fopen(chemin, "r");//ouverture du fichier en mode lecture seulement
    if (fichier != NULL) {//si l ouverture n'a pas échoué 
        fgets(chaine, TAILLE_MAX, fichier); // On lit maximum TAILLE_MAX caractères du fichier, on stocke le tout dans "chaine"
        fclose(fichier);//fermeture du fichier
    }
    else {//le cas ou l'ouverture du fichier est échoué
 	printf("Erreur d'ouverture du fichier\n");
	exit(1);
    }
    return chaine;
}

void menu(void) {
    printf("************************* MENU PRINCIPALE ***********************\n");
    printf("Veuillez choisir une option :\n");
    printf("\t 1 - Entrer le nombre à tester\n");
    printf("\t 2 - Utiliser un nombre écris dans un fichier\n");
    printf("\t 3 - Ecrire le nombre dans un fichier et le tester\n");
    printf("\t 4 - Quitter\n");
    printf("********************************************************************\n");
}

void test_primal(void) {
    printf("************************* Test Primalité ***********************\n");
    printf("Vous voulez Quel Test :\n");
    printf("\t 1 - Test de Fermat\n");
    printf("\t 2 - Test de Miller Rabbin\n");
    printf("\t 3 - Retour\n");
    printf("******************************************************************\n");
}

void choisis_nombre(mpz_t n) {
    do {
	printf("Choisissez le nombre à tester > 1 : \t");
	mpz_inp_str(n, 0, 10);
	printf("\n");
    } while(mpz_cmp_ui(n, 2) < 0);
}

void choisis_iteration(mpz_t k) {
	//il faut que le nombre d'itération soit supérieur à 0
    do {
	printf("Choisissez le nombre d'itération > 0 : \t");
	mpz_inp_str(k, 0, 10);
	printf("\n");
    } while(mpz_cmp_ui(k, 1) < 0);
}

void livre(void) {
    printf ("\033[31m");
    printf("\n");
    printf("\t               .-~~~~~~~~~-._       _.-~~~~~~~~~-.                  \n ");
    printf("\t           __.'              ~.   .~              `.__               \n ");
    printf("\t          .'//                  ./                  \\`.                 \n ");
    printf("\t       .'//                     |                     \\`.\n ");
    printf("\t   .'//.-'                 `-.  |  .-'                 ''-.\\`.  \n ");
    printf("\t  .'//______.============-..    | /   ..-============.______\\`.\n ");
    printf("\t.'______________________________|/______________________________`.\n \n \n");
    printf ("\033[34m");
}
int creeEcrire(char * chemin)
{
	 FILE * fichier;
	 fichier=fopen(chemin , "w");//ouvrire le fichier en mode écriture 
	 //si le fichier existe en écrase son contenu et on écrit dedans sinon on creer un nouveau fichier 
	 //il faut qu'il soit un fichier .txt
	 if(fichier!=NULL)
	 {
	 	     char * nbr =malloc(1024*sizeof(char)); //allouer nbr 
              printf("Donner le nombre souhaité tester\t"); 
              scanf("%s",nbr);//le nombre sous forme d'une chaine de caractère pour pouvoir le stocker ds le fichier 
              fputs(nbr,fichier);//écrire le nombre saisir dans le fichier
              fclose(fichier);//fermeture du fichier
              return 1;//réussite

	 }
	 else
	 {
	 	printf("Erreur du création\n");
	 	return 0;//échoue
	 }
}

void interface(void) {
    
    char *str="Bienvenue dans le programme de Lynda & Nicolas :) \n";
    
    system("clear");//effacer le contenu de la fenetre 
    printf ("\033[32m");//permet de modifier la couleur 
    int f=0;
    printf("\n\n\t\t");
    //afficher la chaine str caractère par caractère 
    while(str[f]!='\0') {
    	printf ("%c", str[f]);
        fflush(stdout);
        usleep(100000);//pour la durée entre chaque affichage d'un caractère
        f++;
       
    }
    
    livre(); 
    mpz_t n;
    mpz_init(n);
    mpz_t k;
    int rps;
    mpz_init(k);
    int tmp;
    int choix;
    do {
	menu();
	printf("\nFaîtes votre choix SVP: \t");
	scanf("%d", &tmp);
	printf("\n\n");
	
	if( tmp == 1 ) {  
	    choisis_nombre(n);
	    choisis_iteration(k);
	    
	    do {
		system("clear");
		livre();
		test_primal();
		printf("\nFaites votre choix : ");
		scanf("%d", &choix);
		printf("\n");
		
		if( choix == 1 ) {
		    if(testFermatmpz(n, k)) {
			printf("\033[33mVotre nombre est premier\n\n\033[34m");
		    }
		    else {
			printf("\033[35mVotre nombre n'est pas premier\n\n\033[34m");
		    }
		}
		else if( choix == 2 ) {
		    if(miller_rabbin(n, k)) {
			printf("\033[33mVotre nombre est premier\n\n\033[34m");
		    }
		    else {
			printf("\033[35mVotre nombre n'est pas premier\n\n\033[34m");
		    }
		}
		else if( choix == 3 ) {
		    break;
		}

		printf("Voulez vous réessayer avec les mêmes paramètres ? (1 : oui) | (0 : non)\t ");
		scanf("%d", &rps);
	    } while(choix < 1 || choix > 3 || rps == 1);
	    
	    if(rps != 1)
	    {
	  	system("clear");
	  	livre();
	    }
	}
	else if( tmp == 2 ) {
	   
	    char *chemin = malloc(sizeof(char) * 0);
	    printf("Donner le chemin du Votre fichier : ");
	    scanf("%s", chemin);
	    char *str = lire(chemin);
	    mpz_set_str(n, str, 10);
	    free(str);
	    free(chemin);
	    choisis_iteration(k);
	    
	    do {
		system("clear");
		livre();
		test_primal();
		printf("\nFaites votre choix : ");
		scanf("%d", &choix);
		printf("\n");
	   
		if( choix == 1 ) {
		    if(testFermatmpz(n, k)) {
			printf("\033[33mVotre nombre est premier\n\n\033[34m");
		    }
		    else {
			printf("\033[35mVotre nombre n'est pas premier\n\n\033[34m");
		    }
		}
		else if( choix == 2 ) {
		    if(miller_rabbin(n, k)) {
			printf("\033[33mVotre nombre est premier\n\n\033[34m");
		    }
		    else {
			printf("\033[35mVotre nombre n'est pas premier\n\n\033[34m");
		    }
		}
		else if( choix == 3 ) {
		    break;
		}
	   
		printf("Voulez vous réessayer avec les mêmes paramètres ? (1 : oui) | (0 : non)\t ");
		scanf("%d", &rps);
	    } while(choix < 1 || choix > 3 || rps==1);
	    
	    if(rps != 1){
	     	system("clear");
	     	livre();
	    }
	}
	else
		if(tmp==3)
		{

			char * nom=malloc(sizeof(char));
			printf("Donner un nom pour le fichier\t");
			scanf("%s",nom);
			char *nombre;
			int rs=creeEcrire(nom);
			if(rs==1)
			{
                  nombre=lire(nom);
                  mpz_set_str(n,nombre,10);
                  free(nombre);
                  free(nom);
                  choisis_iteration(k);
          do {
		system("clear");
		livre();
		test_primal();
		printf("\nFaites votre choix : ");
		scanf("%d", &choix);
		printf("\n");
		if( choix == 1 ) {
		    if(testFermatmpz(n, k)) {
			printf("\033[33mVotre nombre est premier\n\n\033[34m");
		    }
		    else {
			printf("\033[35mVotre nombre n'est pas premier\n\n\033[34m");
		    }
		}
		else if( choix == 2 ) {
		    if(miller_rabbin(n, k)) {
			printf("\033[33mVotre nombre est premier\n\n\033[34m");
		    }
		    else {
			printf("\033[35mVotre nombre n'est pas premier\n\n\033[34m");
		    }
		}
		else if( choix == 3 ) {
		    break;
		}
	   
		printf("Voulez vous réessayer avec les mêmes paramètres ? (1 : oui) | (0 : non)\t ");
		scanf("%d", &rps);
	    } while(choix < 1 || choix > 3 || rps==1);
	     if(rps != 1){
	     	system("clear");
	     	livre();
	    }
}
			else
			{
				if(rs==0)
				{
					printf("Erreur de creation\n");
				}
			}
		}
	else if( tmp == 4) {
	    break;
	}
    } while(tmp != 4);
    mpz_clear(n);
    mpz_clear(k);
    
    system("clear");
}
