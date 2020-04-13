#ifndef _interface_h
#define _interface_h

char *lire(char *chemin);

void menu(void);

void test_primal(void);

void choisis_nombre(mpz_t n);

void choisis_iteration(mpz_t k);

// fonction principale
void interface(void);

#endif // !_interface_h
