#ifndef PBAT_COMMON_H
#define PBAT_COMMON_H

#include <cstddef>

namespace pbat {
namespace common {

template <typename T>
void HashCombineAccumulate(std::size_t& seed, T const& val)
{
    seed ^= std::hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template <typename... Types>
std::size_t HashCombine(const Types&... args)
{
    std::size_t seed = 0;
    (HashCombineAccumulate(seed, args), ...); // create hash value with seed over all args
    return seed;
}

} // namespace common
} // namespace pbat

#endif // PBAT_COMMON_H