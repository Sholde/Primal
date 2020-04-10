#ifndef _miller_rabbin_h
#define _miller_rabbin_h

// Compte le nombre de bit de l'entier h
void nb_bit(mpz_t nb, mpz_t h);

// Calcul 2^i
void pos(mpz_t test, mpz_t i);

// res = a^h mod n
void square_and_multiply(mpz_t res, mpz_t a, mpz_t n, mpz_t h);

// Trouve s et t tel que n-1 = 2^s * t
void decompose(mpz_t n, mpz_t s, mpz_t t);

// miller rabbin
int miller_rabbin(mpz_t n, mpz_t k);

#endif // !_miller_rabbin_h
