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
    template <unsigned char n>
    auto permutation()
    {
        return detail::permutation_body<n>{};
    }
} // namespace loopy


#endif // LOOPY_PERMUTATION_H
