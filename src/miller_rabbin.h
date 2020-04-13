#ifndef _miller_rabbin_h
#define _miller_rabbin_h

// Trouve s et t tel que n-1 = 2^s * t
void decompose(mpz_t n, mpz_t s, mpz_t t);

// miller rabbin
int miller_rabbin(mpz_t n, mpz_t k);

#endif // !_miller_rabbin_h
