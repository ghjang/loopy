#ifndef LOOPY_H
#define LOOPY_H


namespace loopy
{
    template <typename T, T LoopDepth>
    struct loop_index_generator
    {
        using array_t = std::array<T, LoopDepth>;

        template <typename F>
        void operator () (F && f)
        {
            array_t curLoopIndexVal;
            std::fill(curLoopIndexVal.begin(), curLoopIndexVal.end(), -1);
            
            int i = 0;  // current loop depth
            while (i >= 0) {
                if (curLoopIndexVal[i] >= loopUpperLimitVal_[i] - 1) {
                    curLoopIndexVal[i] = -1;
                    --i;
                    continue;
                }
                ++curLoopIndexVal[i];
                if (i + 1 >= LoopDepth) {
                    std::apply(f, curLoopIndexVal);
                } else {
                    ++i;
                }
            }
        }

        array_t const loopUpperLimitVal_;
    };


    template <typename... T>
    auto loop(T... i)
    {
        using common_t = std::common_type_t<T...>;
        
        static_assert(std::is_integral<common_t>());
        static_assert(std::is_signed<common_t>());

        return loop_index_generator<
                        common_t,
                        sizeof...(i)
            >{ i... };
    }
} // namespace loopy


#endif // LOOPY_H
