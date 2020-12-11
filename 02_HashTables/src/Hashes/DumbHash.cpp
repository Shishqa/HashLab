/*============================================================================*/
#include "HashCollection.hpp"
/*============================================================================*/
using namespace Research::Hashes;
using namespace Research::Types;
/*============================================================================*/

template <>
uint64_t DumbHash<String>::operator()(const String& key) {

    uint64_t hash = 0;

    for (auto& ch : key) {
        hash = (hash + static_cast<uint64_t>(ch)) % MOD;
    }

    return hash;
}

/*============================================================================*/