#include <complex>
#include <stdio.h>

#include "dab_parameters.h"
#include "kin.h"

using namespace gr::bad;
using iq_t = td::complex<float>;

template<std::size_t N>
static iq_t R(int m, const iq_t* zxc)
{
    iq_t R = 0;

    for (int i = 0, j = N + m; i < N; ++i, ++j)
        R += zxc[i] * std::conj(zxc[j % N]);
    
    return R;
}

int main()
{
    const iq_t fi[] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    iq_t zxc[K];

    for (int k = -K / 2; k <= K / 2; ++k)
    {
        const kin_t& x = kin[k + K/2];
        printf("k: %3d - h[%d][%2d]: %d - n: %d, arg: %d\n", k, x.i, k - x.k, h[x.i][k-x.k], x.n, h[x.i][k-x.k] + x.n);

        iq_t f = fi[(h[x.i][k-x.k] + x.n) % 4];
        if (k < 0) {
            zxc[k + K/2] = f;
        } 
        else
        if (k > 0) {
            zxc[k + K/2 - 1] = f;
        }
        printf("k: %3d - (%+1.2f,%+1.2f)\n", k, f.real(), f.imag());
    }

printf("---------------------------------------\n");
    for (int m = -8; m <=8; ++m) {
        iq_t f = R<16>(m, &zxc[32 * 0]);
        printf("m: %+d - (%+1.2f,%+1.2f)\n", m, f.real(), f.imag());
    }
printf("---------------------------------------\n");
    for (int m = -8; m <= 8; ++m) {
        iq_t f = R<16>(m, &zxc[32 * 1]);
        printf("m: %+d - (%+1.2f,%+1.2f)\n", m, f.real(), f.imag());
    }
printf("---------------------------------------\n");

    for (int m = -8; m <=8; ++m) {
        iq_t f = R<16>(m, &zxc[32 * 2]);
        printf("m: %+d - (%+1.2f,%+1.2f)\n", m, f.real(), f.imag());
    }
printf("---------------------------------------\n");
    for (int m = -8; m <=8; ++m) {
        iq_t f = R<16>(m, &zxc[32 * 3]);
        printf("m: %+d - (%+1.2f,%+1.2f)\n", m, f.real(), f.imag());
    }
printf("---------------------------------------\n");



    return 0;
}