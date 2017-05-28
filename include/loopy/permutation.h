#ifndef LOOPY_PERMUTATION_H
#define LOOPY_PERMUTATION_H


#include <array>
#include <algorithm>
#include <numeric>


namespace loopy::detail
{
    template <unsigned char n>
    struct permutation_body
    {
        template <typename F>
        void operator () (F && f) const
        {
            std::array<int, n>  arr;
            std::iota(arr.begin(), arr.end(), 0);

            do {
                std::apply(f, arr);
            } while (std::next_permutation(arr.begin(), arr.end()));
        }
    }; 
} // namespace loopy::detail


namespace loopy
{
    constexpr auto permutation_v(int n, int r)
    {
        if (0 == r) {
            n = 0;
        }
        int v = n;
        if (0 == n) {
            v = 1;
            r = 0;
        }
        for ( ; r > 1; --r) {
            v *= --n;
        }
        return v;
    }

    template <unsigned char n>
    auto permutation()
    {
        return detail::permutation_body<n>{};
    }
} // namespace loopy


#endif // LOOPY_PERMUTATION_H
