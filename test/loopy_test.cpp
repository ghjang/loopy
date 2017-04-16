#include "catch.hpp"

#include <iostream>

#include "loopy/loopy.h"
using namespace loopy;


TEST_CASE("loop", "[loopy]")
{
    /*
    loop(2, 2)(
        [](auto i, auto j) {
            std::cout << '(' << i << ", " << j << ")\n";
        }
    );
    */

    // This is somewhat like the following:
    //      for (int i = 0; i < 3; ++i)
    //          for (int j = 0; j < 3; ++j)
    //              for (int k = 0; k < 3; ++k)
    //                  f(i, j, k);
    loop(3, 3, 3)(
        [](auto i, auto j, auto k) {
            std::cout << '(' << i << ", " << j << ", " << k << ")\n";
        }
    );

    /*
    loop(2, 3, 4, 5)(
        [](auto i, auto j, auto k, auto l) {
            std::cout << '(' << i << ", " << j << ", " << k << ", " << l << ")\n";
        }
    );
    */

    // TODO: add following function call support.

    // The function has smaller number of parameters than the loop depth.
    /*
    loop(3, 3, 3)(
        [](auto i, auto j) {
            std::cout << '(' << i << ", " << j << ")\n";
        }
    );
    */

    // The function don't use the loop index at all.
    /*
    loop(3, 3, 3)(
        []{
            std::cout << "just do something.\n";
        }
    );
    */

    // ...
}
