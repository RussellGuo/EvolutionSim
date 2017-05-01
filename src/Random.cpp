#include "Random.h"

#include <random>
#include <chrono>

namespace Random {
quint32 Random()
{
    static auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    static std::mt19937 mt(seed);

    auto ret = mt();
    return ret;
}

}
