#ifndef _interface_h
#define _interface_h

/**
 * Permet de lire un fichier contenant un nombre
 * @param chemin : chemin du fichier à partir de l'exécution du programme
 * @return chaîne de caractère contenant le nombre
 */
char *lire(char *chemin);

/**
 * Affiche le menu principale
 */
void menu(void);

/**
 * Affiche le menu des différent test de primalité possible
 */
void test_primal(void);

/**
 * Permet à l'utilisateur de choisir le nombre à tester
 * @param n : le nombre à tester
 */
void choisis_nombre(mpz_t n);

/**
 * Permet à l'utilisateur de choisir le nombre d'itération
 * @param n : le nombre d'itération
 */
void choisis_iteration(mpz_t k);

/**
 * Affiche un livre
 */
void livre(void);

/**
 * Fonction principale d'affichage et gestion entrée/sortie avec l'utilisateur
 */
void interface(void);

#endif // !_interface_h
