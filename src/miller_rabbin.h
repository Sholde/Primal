#ifndef _miller_rabbin_h
#define _miller_rabbin_h

/**
 * Permet de trouver s et t tel que n-1 = 2^s * t
 * @param n : nombre à tester
 * @param s : exposant
 * @param t : nombre impair
 */
void decompose(mpz_t n, mpz_t s, mpz_t t);

/**
 * Miller Rabbin
 * @param n : nombre à tester
 * @param k : nombre d'itération
 * @return 1 si il est premier, 0 sinon
 */
int miller_rabbin(mpz_t n, mpz_t k);

#endif // !_miller_rabbin_h
