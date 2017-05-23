#ifndef LOOPY_LOOP_H
#define LOOPY_LOOP_H


#include <type_traits>
#include <array>
#include <algorithm>


namespace loopy::detail
{
    template <typename T, T LoopDepth>
    struct loop_body
    {
        using array_t = std::array<T, LoopDepth>;

        template <typename F>
        void operator () (F && f) const
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


    template <typename T, T LoopDepth, typename LoopUpperLimitSeq>
    struct loop_index_generator;

    template <typename T, T LoopDepth, T... LoopUpperLimit>
    struct loop_index_generator<T, LoopDepth, std::integer_sequence<T, LoopUpperLimit...>>
    {
        constexpr static auto calc_num_of_indices()
        {
            return (... * LoopUpperLimit);
        }

        constexpr auto operator () ()
        {
            using array_t = std::array<T, LoopDepth>;
            using array_elem_t = array_t;
            using indices_array_t = std::array<array_elem_t, calc_num_of_indices()>;

            constexpr array_t loopUpperLimitVal{ LoopUpperLimit... };
            indices_array_t indicesArr{};

            array_t curLoopIndexVal{};
            for (auto & e : curLoopIndexVal) {
                e = -1;
            }
            
            int i = 0;  // current loop depth
            int j = 0;  // current number of output indices
            while (i >= 0) {
                if (curLoopIndexVal[i] >= loopUpperLimitVal[i] - 1) {
                    curLoopIndexVal[i] = -1;
                    --i;
                    continue;
                }
                ++curLoopIndexVal[i];
                if (i + 1 >= LoopDepth) {
                    for (int k = 0; k < LoopDepth; ++k) {
                        indicesArr[j][k] = curLoopIndexVal[k];
                    }
                    ++j;
                } else {
                    ++i;
                }
            }

            return indicesArr;
        }
    };
} // namespace loopy::detail


namespace loopy
{
    template
    <
        typename... T,
        typename = std::enable_if_t<std::conjunction_v<std::is_integral<T>...>>
    >
    auto loop(T... i)
    {
        using common_t = std::common_type_t<T...>;
        
        static_assert(std::is_integral_v<common_t>);
        static_assert(std::is_signed_v<common_t>);

        return detail::loop_body<
                        common_t,
                        sizeof...(i)
               >{ i... };
    }

    template <typename T, T... i>
    constexpr auto loop_indices_for()
    {
        static_assert(std::is_integral_v<T>);

        return detail::loop_index_generator<
                        T,
                        sizeof...(i),
                        std::integer_sequence<T, i...>
               >{}();
    }
} // namespace loopy


#endif // LOOPY_LOOP_H
