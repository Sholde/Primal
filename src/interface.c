#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <gmp.h>

#include "miller_rabbin.h"

#define TAILLE_MAX 1024 // Tableau de taille 1024

char *lire(char *chemin) {
    FILE* fichier = NULL;
    char *chaine = malloc(sizeof(char) * TAILLE_MAX);
    fichier = fopen(chemin, "r");
    if (fichier != NULL) {
        fgets(chaine, TAILLE_MAX, fichier); // On lit maximum TAILLE_MAX caractères du fichier, on stocke le tout dans "chaine"
        fclose(fichier);
    }
    else {
 	printf("Erreur d'ouverture du fichier\n");
	exit(1);
    }
    return chaine;
}

void menu(void) {
    printf("*************************DM CRYPTO***********************\n");
    printf("Veuillez choisir une option :\n");
    printf("\t 1-Entrer directement le nombre\n");
    printf("\t 2-Utiliser le nombre dans le fichier nombre.txt \n");
    printf("\t 3-Quitter\n");
}

void test_primal(void) {
    printf("Veuillez choisir une option :\n");
    printf("\t 1-Test de Fermat\n");
    printf("\t 2-Test de miller rabbin\n");
    printf("\t 3-Retour\n");
}

void interface(void) {
    
    char *str="Bienvenue dans le programme de Lynda & Nicolas\n";
    
    system("clear");
    printf ("\033[32m");
    int f=0;
    printf("\n\n\t\t");
    while(str[f]!='\0') {
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
    printf("\t.'______________________________|/______________________________`.\n \n \n");
    
    int noQuit = 1;
    
    while( noQuit ) {
	menu();
	printf("\nFaites votre choix : ");
	int tmp;
	scanf("%d", &tmp);
	printf("\n\n");
	
	if( tmp == 1 ) {
	    system("clear");
	    test_primal();
	    printf("\nFaites votre choix : ");
	    scanf("%d", &tmp);
	    printf("\n\n");
	    
	    if( tmp == 1 ) {
		system("clear");
		printf("Nous somme désolé mais ce n'est pas encore implémenté\n\n");
	    }
	    else if( tmp == 2 ) {
		system("clear");
		mpz_t n;
		mpz_init(n);
		printf("Choisissez le nombre à tester : \n");
		mpz_inp_str(n, 0, 10);

		printf("\n");

		mpz_t k;
		mpz_init(k);
		printf("Choisissez le nombre d'itération : ");
		mpz_inp_str(k, 0, 10);

		printf("\n");
		
		if(miller_rabbin(n, k)) {
		    printf("Vôtre nombre est premier\n\n");
		}
		else {
		    printf("Vôtre nombre n'est pas premier\n\n");
		}

		mpz_clear(n);
		mpz_clear(k);
	    }
	    else if( tmp == 3 ) {
		system("clear");
	    }
	    else {
		system("clear");
		printf("Veuillez entrez un numéro valide svp\n\n");
	    }
	}
	else if( tmp == 2 ) {
	    system("clear");
	    test_primal();
	    printf("\nFaites votre choix : ");
	    scanf("%d", &tmp);
	    printf("\n\n");
	    
	    if( tmp == 1 ) {
		system("clear");
		printf("Nous somme désolé mais ce n'est pas encore implémenté\n\n");
	    }
	    else if( tmp == 2 ) {
		system("clear");
		char *chemin = malloc(sizeof(char) * 0);
		printf("Donner le chemin du Votre fichier : ");
		scanf("%s", chemin);
		char *str = lire(chemin);
		
		mpz_t n;
		mpz_init(n);
		mpz_set_str(n, str, 10);
		free(str);
		free(chemin);
		
		printf("\n\n");

		mpz_t k;
		mpz_init(k);
		printf("Choisissez le nombre d'itération : ");
		mpz_inp_str(k, 0, 10);

		printf("\n");
		
		if(miller_rabbin(n, k)) {
		    printf("Votre nombre est premier\n\n");
		}
		else {
		    printf("Votre nombre n'est pas premier\n\n");
		}

		mpz_clear(n);
		mpz_clear(k);
	    }
	    else if( tmp == 3 ) {
		system("clear");
	    }
	    else {
		system("clear");
		printf("Veuillez entrez un numéro valide svp\n\n");
	    }
	}
	else if( tmp == 3 ) {
	    system("clear");
	    noQuit = 0;
	}
	else {
	    system("clear");
	    printf("Veuillez entrez un numéro valide svp\n\n");
	}
    }
}
