#include "stdlib.h"
#include "stdio.h"

int popcount(int n) {
    int pc = 0;
    for(int i = 0; i < 32; i++) {
        pc += (n & 1);
        n >>= 1;
    }
    return pc;
}

int nb_bit(int n) {
    int res = 32;
    int masque = 0x80000000;
    while( !(masque & n) ) {
        masque >>= 1;
        res--;
    }
    return res;
}

int pos(int n) {
    int res = 1;
    for(int i = 0; i < n; i++) {
        res <<= 1;
    }
    return res;
}

// a^h mod n
int square_and_multiply(int a, int n, int h) {
    int r = a;
    int nb = nb_bit(h);
    for(int i = nb - 1; i >= 0; i--) {
        r = (r * r) % n;
        if(h & pos(i)) {
            r = (r * a) % n;
        }
    }
    return r;
}

int main(int argc, char **argv) {
    if(argc != 4)
        return 1;
    
    int a = atoi(argv[1]);
    int n = atoi(argv[2]);
    int h = atoi(argv[3]);
    printf("%d\n", square_and_multiply(a, n, h));

    return 0;
}