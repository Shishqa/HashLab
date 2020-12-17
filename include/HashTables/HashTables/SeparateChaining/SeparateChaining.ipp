/*============================================================================*/
#ifndef HASHTABLES_RESEARCH_SEPARATECHAINING_IPP
#define HASHTABLES_RESEARCH_SEPARATECHAINING_IPP
/*============================================================================*/
#include <iostream>
/*============================================================================*/
namespace Research::HashTables {

template <typename T, typename Hash, int expandPercent>
SeparateChaining<T, Hash, expandPercent>::Node::Node(const T& key, Node* next_node)
    : key(key), next(next_node)
    { }


template <typename T, typename Hash, int expandPercent>
SeparateChaining<T, Hash, expandPercent>::Node::~Node() {
    delete next;
}


template <typename T, typename Hash, int expandPercent>
typename SeparateChaining<T, Hash, expandPercent>::Node*
SeparateChaining<T, Hash, expandPercent>::Node::find(const T& some_key) {

    if (some_key == key) {
        return this;
    } else if (next) {
        return next->find(some_key);
    }

    return nullptr;
}


template <typename T, typename Hash, int expandPercent>
typename SeparateChaining<T, Hash, expandPercent>::Node*
SeparateChaining<T, Hash, expandPercent>::Node::findPrev(const T& some_key) {

    if (next) {
        if (next->key == some_key) {
            return this;
        }
        return next->findPrev(some_key);
    }

    return nullptr;
}


/*----------------------------------------------------------------------------*/


template <typename T, typename Hash, int expandPercent>
SeparateChaining<T, Hash, expandPercent>::SeparateChaining()
        : IHashSet<T>() {
    buckets.resize(DEFAULT_BUCKET_COUNT, nullptr);
}


template <typename T, typename Hash, int expandPercent>
SeparateChaining<T, Hash, expandPercent>::~SeparateChaining() {
    for (auto& bucket : buckets) {
        delete bucket;
    }
}


template <typename T, typename Hash, int expandPercent>
bool SeparateChaining<T, Hash, expandPercent>::find(const T& key) {

    uint64_t idx = hash(key) % buckets.size();

    Node* where = (buckets[idx] ? buckets[idx]->find(key) : nullptr);
    return (where != nullptr);
}


template <typename T, typename Hash, int expandPercent>
void SeparateChaining<T, Hash, expandPercent>::add(const T& key) {

    uint64_t idx = hash(key) % buckets.size();

    Node* where = (buckets[idx] ? buckets[idx]->find(key) : nullptr);
    if (!where) {

        buckets[idx] = new Node(key, buckets[idx]);

        IHashSet<T>::setSize(IHashSet<T>::size() + 1);
        if (IHashSet<T>::size() >= (EXPAND_FACTOR * LOAD_FACTOR * buckets.size())) {
            rehash(buckets.size() * 2);
        }
    }
}


template <typename T, typename Hash, int expandPercent>
bool SeparateChaining<T, Hash, expandPercent>::remove(const T& key) {

    uint64_t idx = hash(key) % buckets.size();

    Node* to_delete = nullptr;
    if (buckets[idx]) {

        if (buckets[idx]->key == key) {

            to_delete = buckets[idx];
            buckets[idx] = buckets[idx]->next;

        } else {

            Node* prev = buckets[idx]->findPrev(key);
            if (prev) {
                to_delete = prev->next;
                prev->next = prev->next->next;
            }
        }
    }

    if (!to_delete) {
        return false;
    }

    to_delete->next = nullptr;
    delete to_delete;

    IHashSet<T>::setSize(IHashSet<T>::size() - 1);

    if (IHashSet<T>::size() <= (EXPAND_FACTOR * buckets.size() * LOAD_FACTOR) / 4) {
        rehash(buckets.size() / 2);
    }

    return true;
}


template <typename T, typename Hash, int expandPercent>
void SeparateChaining<T, Hash, expandPercent>::rehash(size_t new_size) {

    hash.shuffle();

    std::vector<Node*> temp = buckets;

    buckets.resize(new_size);
    buckets.assign(new_size, nullptr);

    for (size_t i = 0; i < temp.size(); ++i) {
        Node* curr_node = temp[i];
        while (curr_node) {
            add(curr_node->key);
            curr_node = curr_node->next;
        }
    }

    for (auto& bucket : temp) {
        delete bucket;
    }
}


template <typename T, typename Hash, int expandPercent>
void SeparateChaining<T, Hash, expandPercent>::dump() {
    for (size_t i = 0; i < buckets.size(); ++i) {

        std::cout << "[" << i << "]";

        Node* curr_node = buckets[i];
        while (curr_node) {
            std::cout << "->" << curr_node->key;
            curr_node = curr_node->next;
        }

        std::cout << "\n";
    }
}

}
/*============================================================================*/
#endif //HASHTABLES_RESEARCH_SEPARATECHAINING_IPP
/*============================================================================*/