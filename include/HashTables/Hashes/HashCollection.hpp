/*============================================================================*/
#ifndef HASHTABLES_RESEARCH_HASH_COLLECTION_HPP
#define HASHTABLES_RESEARCH_HASH_COLLECTION_HPP
/*============================================================================*/
#include <string_view>
#include <algorithm>
#include "../../modules/hash-library/md5.h"
#include "../../modules/hash-library/sha256.h"

#include "Interface.hpp"
/*============================================================================*/
namespace Research::Hashes {

    template <typename T>
    class StdHash : public IHash<T> {
    public:

        uint64_t operator()(const T& key) override {
            return hash(key);
        }

    private:

        std::hash<T> hash;
    };

    /*------------------------------------------------------------------------*/

    class LongHash {
    public:

        static uint64_t toNumber(const std::string& hex_hash);

    };

    /*------------------------------------------------------------------------*/

    template <typename T>
    class Md5Hash : public IHash<T>, public LongHash {
    public:

        uint64_t operator()(const T& key) override;

    private:

        MD5 md5;
    };

    /*------------------------------------------------------------------------*/

    template <typename T>
    class Sha256Hash : public IHash<T>, public LongHash {
    public:

        uint64_t operator()(const T& key) override;

    private:

        SHA256 sha256;
    };

    /*------------------------------------------------------------------------*/

    template <typename T>
    class Murmur3Hash : public IHash<T> {
    public:

        Murmur3Hash();

        uint64_t operator()(const T& key) override;

        void shuffle() override;

    private:

        uint64_t hash(const void* key, size_t data_size);

        uint32_t seed;
    };

    /*------------------------------------------------------------------------*/

    template <typename T>
    class DumbHash : public IHash<T> {
    public:

        static constexpr uint64_t MOD = 63018038201L;

        uint64_t operator()(const T& key) override;

    };

    /*------------------------------------------------------------------------*/

    template <typename T>
    class RabinKarpHash : public IHash<T> {
    public:

        RabinKarpHash();

        uint64_t operator()(const T& key) override;

        void shuffle() override;

    private:

        static constexpr uint64_t Q = (1UL << 61) - 1;
        uint64_t X;
    };

    /*------------------------------------------------------------------------*/

    template <typename T>
    class TabulationHash : public IHash<T> {
    public:

        TabulationHash();

        uint64_t operator()(const T& key) override;

        void shuffle() override;

    private:

        static constexpr size_t DOM_SIZE = sizeof(T);
        static constexpr size_t BLOCK_SIZE = sizeof(uint8_t);

        static constexpr size_t N_BLOCKS = DOM_SIZE / BLOCK_SIZE;
        static constexpr size_t N_VALUES = 1UL << (BLOCK_SIZE * 8);

        uint64_t table[N_BLOCKS][N_VALUES];
    };

    /*------------------------------------------------------------------------*/

    template <int Degree, typename T>
    class PolyHash : public IHash<T> {
    public:

        PolyHash();

        uint64_t operator()(const T& key) override;

        void shuffle() override;

    private:

        static constexpr uint64_t MOD = (1UL << 61) - 1;

        uint64_t coeff[Degree];
    };

    template <typename T>
    using Indep2PolyHash = PolyHash<2, T>;

    template <typename T>
    using Indep3PolyHash = PolyHash<3, T>;

    template <typename T>
    using Indep5PolyHash = PolyHash<5, T>;

    /* for strings */
    /*------------------------------------------------------------------------*/

    template class Md5Hash<Types::String>;
    template class Sha256Hash<Types::String>;
    template class DumbHash<Types::String>;
    template class RabinKarpHash<Types::String>;
    template class Murmur3Hash<Types::String>;

    /* for numbers */
    /*------------------------------------------------------------------------*/

    template class TabulationHash<Types::Number>;
    template class PolyHash<2, Types::Number>;
    template class PolyHash<3, Types::Number>;
    template class PolyHash<5, Types::Number>;
    template class Md5Hash<Types::Number>;
    template class Murmur3Hash<Types::Number>;
    template class Sha256Hash<Types::Number>;

}
/*============================================================================*/
#include "HashCollection.ipp"
/*============================================================================*/
#endif //HASHTABLES_RESEARCH_HASH_COLLECTION_HPP
/*============================================================================*/
