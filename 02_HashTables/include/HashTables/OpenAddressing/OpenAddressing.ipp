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

template <typename T, typename Run>
uint64_t HashTables::OpenAddressing<T, Run>::locate(
    const T& key,
    const std::vector<HashNode>& arr) {

    Run run(key);

    int64_t first_hole = -1;

    uint64_t i = 0;
    for (; i < arr.size(); ++i) {

        uint64_t curr_idx = run(i) % arr.size();

        if (arr[curr_idx].state == HashNode::NORMAL) {

            if (arr[curr_idx].key.has_value() &&
                arr[curr_idx].key.value() == key) {

                return curr_idx;

            } else if (!arr[curr_idx].key.has_value()) {

                if (-1 == first_hole) {
                    return curr_idx;
                }

                return (uint64_t)first_hole;
            }

        } else {
            if (-1 == first_hole) {
                first_hole = (int64_t)curr_idx;
            }
        }
    }

    return i;
}

template <typename T, typename Run>
bool OpenAddressing<T, Run>::find(const T& key) {

    uint64_t idx = locate(key, data);
    if (data[idx].state == HashNode::NORMAL &&
        data[idx].key.has_value()) {
        return true;
    }

    return false;
}

template <typename T, typename Run>
void OpenAddressing<T, Run>::add(const T& key) {

    uint64_t idx = locate(key, data);
    if (data[idx].state == HashNode::NORMAL &&
        data[idx].key.has_value()) {
        return;
    }

    data[idx].key.emplace(key);
    data[idx].state = HashNode::NORMAL;

    IHashSet<T>::sz += 1;
    if (IHashSet<T>::sz == data.size()) {
        rehash(IHashSet<T>::sz * 2);
    }
}

template <typename T, typename Run>
bool OpenAddressing<T, Run>::remove(const T& key) {

    uint64_t idx = locate(key, data);
    if (data[idx].state == HashNode::NORMAL &&
        data[idx].key.has_value()) {

        data[idx].key.reset();
        data[idx].state = HashNode::TOMBSTONE;

        IHashSet<T>::sz -= 1;
        if (IHashSet<T>::sz == data.size() / 4) {
            rehash(IHashSet<T>::sz / 2);
        }

        return true;
    }

    return false;
}

template <typename T, typename Run>
void OpenAddressing<T, Run>::rehash(size_t new_size) {

    std::vector<HashNode> new_data(new_size);

    for (auto& key : data) {
        if (key.state == HashNode::NORMAL &&
            key.key.has_value()) {

            uint64_t idx = locate(key.key.value(), new_data);

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