#ifndef TYPES_H
#define TYPES_H
#include <cstdlib>
#include <cstdint>

const int MAX_COMPONENTS = 32;
const int MAX_ENTITIES = 1000;
using Signature = std::bitset<MAX_COMPONENTS>;
using Entity = std::uint32_t;
using ComponentType = std::uint8_t;

#endif

