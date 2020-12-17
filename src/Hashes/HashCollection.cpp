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

uint64_t LongHash::toNumber(const std::string& hex_hash) {

    if (hex_hash.size() > 16) {
        return std::strtoull((hex_hash.end() - 16).base(), nullptr, 16);
    }

    return std::strtoull(hex_hash.c_str(), nullptr, 16);
}

/*----------------------------------------------------------------------------*/

template <>
uint64_t Md5Hash<String>::operator()(const String& key) {
    std::string hash_str = md5(key);
    return LongHash::toNumber(hash_str);
}

template <>
uint64_t Md5Hash<Number>::operator()(const Number& key) {
    std::string hash_str = md5(&key, sizeof(key));
    return LongHash::toNumber(hash_str);
}

/*============================================================================*/

template <>
uint64_t Sha256Hash<String>::operator()(const String& key) {
    std::string hash_str = sha256(key);
    return LongHash::toNumber(hash_str);
}

template <>
uint64_t Sha256Hash<Number>::operator()(const Number& key) {
    std::string hash_str = sha256(&key, sizeof(key));
    return LongHash::toNumber(hash_str);
}

/*============================================================================*/

template <>
uint64_t Murmur3Hash<String>::operator()(const String& key) {
    return hash(key.c_str(), key.size());
}

template <>
uint64_t Murmur3Hash<Number>::operator()(const Number& key) {
    return hash(&key, sizeof(key));
}

/*============================================================================*/

template <>
uint64_t RabinKarpHash<String>::operator()(const String& key) {

    uint64_t hash = 0;
    for (auto& ch : key) {
        hash *= X;
        hash += (uint64_t)ch;
        hash %= Q;
    }

    return hash;
}

/*============================================================================*/