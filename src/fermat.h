#ifndef _fermat_h
#define _fermat_h

/**
 * Miller Rabbin
 * @param n : nombre à tester
 * @param k : nombre d'itération
 * @return 1 si il est premier, 0 sinon
 */
int testFermatmpz(mpz_t n ,mpz_t k);

#endif // !_fermat_h
