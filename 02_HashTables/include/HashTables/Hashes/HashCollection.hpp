/*============================================================================*/
#ifndef HASHTABLES_RESEARCH_HASH_COLLECTION_HPP
#define HASHTABLES_RESEARCH_HASH_COLLECTION_HPP
/*============================================================================*/
#include <string_view>

#include "Interface.hpp"
/*============================================================================*/
namespace Research::Hashes {

    /* universal */
    /*------------------------------------------------------------------------*/

    template <typename T>
    class Md5Hash : public IHash<T> {

        uint64_t operator()(const T& key) override;

    };

    template <typename T>
    class Sha256Hash : public IHash<T> {

        uint64_t operator()(const T& key) override;

    };

    template <typename T>
    class Murmur3Hash : public IHash<T> {

        uint64_t operator()(const T& key) override;

    };

    template <typename T>
    class DumbHash : public IHash<T> {
    public:

        static constexpr uint64_t MOD = 63018038201L;

        uint64_t operator()(const T& key) override;

    };

    template <typename T>
    class RabinKarpHash : public IHash<T> {
    public:

        uint64_t operator()(const T& key) override;
    };

    template <typename T>
    class TabulationHash : public IHash<T> {
    public:

        uint64_t operator()(const T& key) override;
    };

    template <typename T>
    class PolynomialHash : public IHash<T> {
    public:

        uint64_t operator()(const T& key) override;

    };

    /* for strings */
    /*------------------------------------------------------------------------*/

    template class Md5Hash<Types::String>;
    template class Sha256Hash<Types::String>;
    template class DumbHash<Types::String>;
    template class RabinKarpHash<Types::String>;
    template class Murmur3Hash<Types::String>;

    /* for numbers */
    /*------------------------------------------------------------------------*/

    /*

    template class TabulationHash<Types::Number>;
    template class PolynomialHash<Types::Number>;
    template class Md5Hash<Types::Number>;
    template class Murmur3Hash<Types::Number>;
    template class Sha256Hash<Types::Number>;

     */

}
/*============================================================================*/
#endif //HASHTABLES_RESEARCH_HASH_COLLECTION_HPP
/*============================================================================*/
