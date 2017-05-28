#ifndef LOOPY_COMBINATION_H
#define LOOPY_COMBINATION_H


#include "factorial.h"
#include "permutation.h"


namespace loopy
{
    constexpr auto combination_v(int n, int r)
    {
        if (0 == n || 0 == r) {
            return 1;
        }
        return permutation_v(n, r) / factorial_v(r);
    }
} // namespace loopy


#endif // LOOPY_COMBINATION_H
