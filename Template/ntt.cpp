const int ort = 10; // original root in MOD
const int MOD = 786433; // MOD = a * b ^ k + 1,n <= b ^ k
// this code works only when b == 2

LL pow_mod(LL a,LL b,LL p) {
    LL ret = 1;
    while (b) {
        if (b & 1) ret = ret * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return ret;
}

void ntt(LL A[],int n,int inv) {
    // inv == 1 : ntt, == -1 : intt
    LL w = 1,d = pow_mod(ort,(MOD - 1) / n,MOD),t;
    int i,j,c,s;
    if (inv == -1) {
        for (i = 1,j = n - 1; i < j; ++ i,-- j)
            std::swap(A[i],A[j]);
        for (t = pow_mod(n,MOD - 2,MOD),i = 0; i < n; ++ i)
            A[i] = A[i] * t % MOD;
    }
    for (s = n >> 1; s; s >>= w = 1,d = d * d % MOD) {
        for (c = 0; c < s; ++ c,w = w * d % MOD) {
            for (i = c; i < n; i += s << 1) {
                A[i | s] = (A[i] + MOD - (t = A[i | s])) * w % MOD;
                A[i] = (A[i] + t) % MOD;
            }
        }
    }
    for (i = 1; i < n; ++ i) {
        for (j = 0,s = i,c = n >> 1; c; c >>= 1,s >>= 1)
            j = j << 1 | s & 1;
        if (i < j) std::swap(A[i],A[j]);
    }
}
