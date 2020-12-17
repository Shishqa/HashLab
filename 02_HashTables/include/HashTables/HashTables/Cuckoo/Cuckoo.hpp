/*============================================================================*/
#ifndef HASHTABLES_RESEARCH_CUCKOO_HPP
#define HASHTABLES_RESEARCH_CUCKOO_HPP
/*============================================================================*/
#include "Interface.hpp"

#include <vector>
#include <optional>
/*============================================================================*/
namespace Research::HashTables {

    template <typename T, typename Hash1, typename Hash2 = Hash1>
    class Cuckoo : public IHashSet<T> {
    public:

        Cuckoo();

        void add(const T& key) override;

        bool find(const T& key) override;

        bool remove(const T& key) override;

        void dump();

    private:

        bool place(std::optional<T>&& elem);

        bool place(std::optional<T>&& elem, size_t table_idx, size_t iter);

        void rehash(size_t size);

        struct Table {

            uint64_t hash(const T& key) {
                return hash_impl->operator()(key) % keys.size();
            }

            std::vector<std::optional<T>> keys;
            IHash<T>* hash_impl;
        };

        Hash1 hash1;
        Hash2 hash2;

        Table tables[2];
    };

}
/*============================================================================*/
#include "Cuckoo.ipp"
/*============================================================================*/
#endif //HASHTABLES_RESEARCH_CUCKOO_HPP
/*============================================================================*/