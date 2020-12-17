/*============================================================================*/
#ifndef HASHTABLES_RESEARCH_OPENADDRESSING_IPP
#define HASHTABLES_RESEARCH_OPENADDRESSING_IPP
/*============================================================================*/
#include <iostream>
/*============================================================================*/
namespace Research::HashTables {

template <typename T, typename Run>
HashTables::OpenAddressing<T, Run>::HashNode::HashNode()
        : key()
        , state(NORMAL)
        { }

template <typename T, typename Run>
HashTables::OpenAddressing<T, Run>::HashNode::HashNode(const T& key)
        : key(key)
        , state(NORMAL)
        { }

/*----------------------------------------------------------------------------*/

template <typename T, typename Run>
HashTables::OpenAddressing<T, Run>::OpenAddressing() {
    data.reserve(IHashSet<T>::DEFAULT_SIZE);
    data.resize(data.capacity());
}

template <typename T, typename Run>
IRun<T>& HashTables::OpenAddressing<T, Run>::run() {
    return run_impl;
}
/*----------------------------------------------------------------------------*/

template <typename T, typename Run>
void HashTables::OpenAddressing<T, Run>::dump() {
    uint64_t idx = 0;
    for (auto& node : data) {
        std::cout << idx++ << " - ";
        if (node.state == HashNode::NORMAL) {
            if (node.key.has_value()) {
                std::cout << node.key.value();
            } else {
                std::cout << "E";
            }
        } else {
            std::cout << "T";
        }
        std::cout << "\n";
    }
}

/*----------------------------------------------------------------------------*/

template <typename T, typename Run>
int64_t HashTables::OpenAddressing<T, Run>::locate(
    const T& key,
    const std::vector<HashNode>& arr) {

    run().init(key, arr.size());
    int64_t first_hole = -1;

    uint64_t attempt = 0;
    for (; attempt < arr.size(); ++attempt) {

        uint64_t curr_idx = run().next();

        if (arr[curr_idx].state == HashNode::NORMAL) {

            if (arr[curr_idx].key.has_value() &&
                arr[curr_idx].key.value() == key) {

                return curr_idx;

            } else if (!arr[curr_idx].key.has_value()) {

                if (-1 == first_hole) {
                    return (int64_t)curr_idx;
                }

                return first_hole;
            }

        } else if (-1 == first_hole) {

            first_hole = (int64_t)curr_idx;
        }
    }

    return first_hole;
}

/*----------------------------------------------------------------------------*/

template <typename T, typename Run>
bool OpenAddressing<T, Run>::find(const T& key) {

    int64_t idx = locate(key, data);
    if (idx == -1) {
        return false;
    }

    if (data[idx].state == HashNode::NORMAL &&
        data[idx].key.has_value()) {
        return true;
    }

    return false;
}

/*----------------------------------------------------------------------------*/

template <typename T, typename Run>
void OpenAddressing<T, Run>::add(const T& key) {

    int64_t idx = locate(key, data);
    if (idx == -1) {
        rehash(IHashSet<T>::size() * 2);
        add(key);
        return;
    }

    if (data[idx].state == HashNode::NORMAL &&
        data[idx].key.has_value()) {
        return;
    }

    data[idx].key.emplace(key);
    data[idx].state = HashNode::NORMAL;

    IHashSet<T>::setSize(IHashSet<T>::size() + 1);
    if (IHashSet<T>::size() == data.size()) {
        rehash(IHashSet<T>::size() * 2);
    }
}

/*----------------------------------------------------------------------------*/

template <typename T, typename Run>
bool OpenAddressing<T, Run>::remove(const T& key) {

    int64_t idx = locate(key, data);
    if (idx == -1) {
        return false;
    }

    if (data[idx].state == HashNode::NORMAL &&
        data[idx].key.has_value()) {

        data[idx].key.reset();
        data[idx].state = HashNode::TOMBSTONE;

        IHashSet<T>::setSize(IHashSet<T>::size() - 1);
        if (IHashSet<T>::size() == data.size() / 4) {
            rehash(IHashSet<T>::size() / 2);
        }

        return true;
    }

    return false;
}

/*----------------------------------------------------------------------------*/

template <typename T, typename Run>
void OpenAddressing<T, Run>::rehash(size_t new_size) {

    std::vector<HashNode> new_data(new_size);
    run().shuffle();

    for (auto& key : data) {
        if (key.state == HashNode::NORMAL &&
            key.key.has_value()) {

            int64_t idx = locate(key.key.value(), new_data);
            if (idx == -1) {
                rehash(new_size * 2);
                return;
            }

            new_data[idx].key.emplace(std::move(*key.key));
            new_data[idx].state = HashNode::NORMAL;
        }
    }

    data = std::move(new_data);
}

}
/*============================================================================*/
#endif //HASHTABLES_RESEARCH_OPENADDRESSING_IPP
/*============================================================================*/