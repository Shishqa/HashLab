/*============================================================================*/
#ifndef HASHTABLES_RESEARCH_CUCKOO_IPP
#define HASHTABLES_RESEARCH_CUCKOO_IPP
/*============================================================================*/
#include <iostream>
/*============================================================================*/
namespace Research::HashTables {

template <typename T, typename Hash1, typename Hash2>
Cuckoo<T, Hash1, Hash2>::Cuckoo() {

    tables[0].keys.resize(IHashSet<T>::DEFAULT_SIZE);
    tables[0].hash_impl = &hash1;

    tables[1].keys.resize(IHashSet<T>::DEFAULT_SIZE);
    tables[1].hash_impl = &hash2;
}

/*----------------------------------------------------------------------------*/

template <typename T, typename Hash1, typename Hash2>
void Cuckoo<T, Hash1, Hash2>::dump() {
    std::cout << "===============\n";
    for (size_t i = 0; i < tables[1].keys.size(); ++i) {
        std::cout << "[" << i << "]-";
        if (tables[0].keys[i].has_value()) {
            std::cout << tables[0].keys[i].value();
        } else {
            std::cout << "E";
        }
        std::cout << " -- ";
        if (tables[1].keys[i].has_value()) {
            std::cout << tables[1].keys[i].value();
        } else {
            std::cout << "E";
        }
        std::cout << "\n";
    }
    std::cout << "===============\n";
}

/*----------------------------------------------------------------------------*/

template <typename T, typename Hash1, typename Hash2>
bool Cuckoo<T, Hash1, Hash2>::place(std::optional<T>&& elem) {

    if (!place(std::move(elem), 0, 0)) {
        rehash(tables[0].keys.size());
        place(std::move(elem));
    }

    return true;
}

/*----------------------------------------------------------------------------*/

template <typename T, typename Hash1, typename Hash2>
bool Cuckoo<T, Hash1, Hash2>::place(std::optional<T>&& elem, size_t table_idx,
                                    size_t iter) {

    uint64_t idx = tables[table_idx].hash(elem.value());
    std::swap(elem, tables[table_idx].keys[idx]);
    if (!elem.has_value()) {
        return true;
    }

    if (iter > 2 * tables[0].keys.size()) {
        return false;
    }

    return place(std::move(elem), (table_idx + 1) % 2, iter + 1);
}

/*----------------------------------------------------------------------------*/

template <typename T, typename Hash1, typename Hash2>
void Cuckoo<T, Hash1, Hash2>::rehash(size_t new_size) {

    Table old_tables[2] = {};
    old_tables[0] = std::move(tables[0]);
    old_tables[1] = std::move(tables[1]);

    tables[0].keys.clear();
    tables[0].keys.resize(new_size);
    tables[0].hash_impl->shuffle();

    tables[1].keys.clear();
    tables[1].keys.resize(new_size);
    tables[1].hash_impl->shuffle();

    for (size_t i = 0; i < old_tables[0].keys.size(); ++i) {

        if (old_tables[0].keys[i].has_value()) {
            place(std::move(old_tables[0].keys[i]));
        }

        if (old_tables[1].keys[i].has_value()) {
            place(std::move(old_tables[1].keys[i]));
        }

    }
}

/*----------------------------------------------------------------------------*/

template <typename T, typename Hash1, typename Hash2>
void Cuckoo<T, Hash1, Hash2>::add(const T& key) {

    if (find(key)) {
        return;
    }

    std::optional<T>&& curr = key;
    place(std::move(curr));
}

/*----------------------------------------------------------------------------*/

template <typename T, typename Hash1, typename Hash2>
bool Cuckoo<T, Hash1, Hash2>::find(const T& key) {

    return ( tables[0].keys[tables[0].hash(key)] == key ||
             tables[1].keys[tables[1].hash(key)] == key);

}

/*----------------------------------------------------------------------------*/

template <typename T, typename Hash1, typename Hash2>
bool Cuckoo<T, Hash1, Hash2>::remove(const T& key) {

    uint64_t idx0 = tables[0].hash(key);
    if ( tables[0].keys[idx0] == key ) {
        tables[0].keys[idx0].reset();
        return true;
    }

    uint64_t idx1 = tables[1].hash(key);
    if ( tables[1].keys[idx1] == key ) {
        tables[1].keys[idx1].reset();
        return true;
    }

    return false;
}

}
/*============================================================================*/
#endif //HASHTABLES_RESEARCH_CUCKOO_IPP
/*============================================================================*/