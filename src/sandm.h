#ifndef _sandm_h
#define _sandm_h

// Compte le nombre de bit de l'entier h
void nb_bit(mpz_t nb, mpz_t h);

// Calcul 2^i
void pos(mpz_t test, mpz_t i);

// res = a^h mod n
void square_and_multiply(mpz_t res, mpz_t a, mpz_t n, mpz_t h);

#endif // !_sandm_h
