/*============================================================================*/
#ifndef HASHTABLES_RESEARCH_HASHCOLLECTION_IPP
#define HASHTABLES_RESEARCH_HASHCOLLECTION_IPP
/*============================================================================*/
#include "Random.hpp"
#include <iostream>
/*============================================================================*/
namespace Research::Hashes {

template <typename T>
Murmur3Hash<T>::Murmur3Hash()
        : seed(0) {
    shuffle();
}


template <typename T>
void Murmur3Hash<T>::shuffle() {

    static std::uniform_int_distribution<uint32_t> dist(0, UINT32_MAX);

    seed = dist(Research::Random::Generator());
}

#ifdef __GNUC__
#define FORCE_INLINE __attribute__((always_inline)) inline
#else
#define FORCE_INLINE inline
#endif

    static FORCE_INLINE uint32_t rotl32 ( uint32_t x, int8_t r )
    {
        return (x << r) | (x >> (32 - r));
    }

    static FORCE_INLINE uint64_t rotl64 ( uint64_t x, int8_t r )
    {
        return (x << r) | (x >> (64 - r));
    }

#define	ROTL32(x,y)	rotl32(x,y)

#define BIG_CONSTANT(x) (x##LLU)

//-----------------------------------------------------------------------------
// Block read - if your platform needs to do endian-swapping or can only
// handle aligned reads, do the conversion here

#define getblock(p, i) (p[i])

//-----------------------------------------------------------------------------
// Finalization mix - force all bits of a hash block to avalanche

    static FORCE_INLINE uint32_t fmix32 ( uint32_t h )
    {
        h ^= h >> 16;
        h *= 0x85ebca6b;
        h ^= h >> 13;
        h *= 0xc2b2ae35;
        h ^= h >> 16;

        return h;
    }

//----------

    static FORCE_INLINE uint64_t fmix64 ( uint64_t k )
    {
        k ^= k >> 33;
        k *= BIG_CONSTANT(0xff51afd7ed558ccd);
        k ^= k >> 33;
        k *= BIG_CONSTANT(0xc4ceb9fe1a85ec53);
        k ^= k >> 33;

        return k;
    }


template <typename T>
uint64_t Murmur3Hash<T>::hash(const void* key, size_t data_size) {

    const int len = static_cast<int>(data_size);

    auto data = (const uint8_t*)key;
    const int nblocks = len / 4;
    int i;

    uint32_t h1 = seed;

    uint32_t c1 = 0xcc9e2d51;
    uint32_t c2 = 0x1b873593;

    //----------
    // body

    auto blocks = (const uint32_t *)(data + nblocks*4);

    for(i = -nblocks; i; i++)
    {
        uint32_t k1 = getblock(blocks,i);

        k1 *= c1;
        k1 = ROTL32(k1,15);
        k1 *= c2;

        h1 ^= k1;
        h1 = ROTL32(h1,13);
        h1 = h1*5+0xe6546b64;
    }

    //----------
    // tail

    auto tail = (const uint8_t*)(data + nblocks*4);

    uint32_t k1 = 0;

    switch (len & 3)
    {
        case 3: k1 ^= tail[2] << 16;
        case 2: k1 ^= tail[1] << 8;
        case 1: k1 ^= tail[0];
            k1 *= c1; k1 = ROTL32(k1,15); k1 *= c2; h1 ^= k1;
    };

    //----------
    // finalization

    h1 ^= len;

    h1 = fmix32(h1);

    return (uint32_t)h1;
}

/*============================================================================*/

template <typename T>
RabinKarpHash<T>::RabinKarpHash()
        : X(0) {
    shuffle();
}


template <typename T>
void RabinKarpHash<T>::shuffle() {
    static std::uniform_int_distribution<uint64_t> dist(0, Q - 1);
    X = dist(Random::Generator());
}

/*============================================================================*/

template <typename T>
TabulationHash<T>::TabulationHash()
        : table() {
    shuffle();
}


template <typename T>
void TabulationHash<T>::shuffle() {

    static std::uniform_int_distribution<uint64_t> dist(0, UINT64_MAX);

    for (size_t k = 0; k < N_BLOCKS; ++k) {
        for (size_t i = 0; i < N_VALUES; ++i) {
            table[k][i] = dist(Random::Generator());
        }
    }
}


template <typename T>
uint64_t TabulationHash<T>::operator()(const T& key) {

    auto data = reinterpret_cast<const uint8_t*>(&key);

    uint64_t hash = 0;
    for (size_t k = 0; k < N_BLOCKS; ++k) {
        hash = hash ^ table[k][data[k]];
    }

    return hash;
}


/*============================================================================*/


template <int Degree, typename T>
PolyHash<Degree, T>::PolyHash()
        : coeff() {
    shuffle();
}


template <int Degree, typename T>
void PolyHash<Degree, T>::shuffle() {

    static std::uniform_int_distribution<uint64_t> dist(0, MOD - 1);
    static std::uniform_int_distribution<uint64_t> high_dist(1, MOD - 1);

    coeff[0] = high_dist(Random::Generator());
    for (size_t i = 1; i < Degree; ++i) {
        coeff[i] = dist(Random::Generator());
    }
}


template <int Degree, typename T>
uint64_t PolyHash<Degree, T>::operator()(const T& key) {

    uint64_t hash = 0;
    for (size_t i = 0; i < Degree; ++i) {
        hash *= key;
        hash += coeff[i];
        hash %= MOD;
    }

    return hash;
}

}
/*============================================================================*/
#endif //HASHTABLES_RESEARCH_HASHCOLLECTION_IPP
/*============================================================================*/