#ifndef LOOPY_FACTORIAL_H
#define LOOPY_FACTORIAL_H


namespace loopy
{
    constexpr auto factorial_v(int n)
    {
        int v = n ? n : 1;
        while (n > 1) {
            v *= --n;
        }
        return v;
    }
} // namespace loopy


#endif // LOOPY_FACTORIAL_H
