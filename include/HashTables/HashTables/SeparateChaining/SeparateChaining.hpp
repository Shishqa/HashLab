/*============================================================================*/
#ifndef HASHTABLES_RESEARCH_SEPARATECHAINING_HPP
#define HASHTABLES_RESEARCH_SEPARATECHAINING_HPP
/*============================================================================*/
#include "Interface.hpp"

#include <vector>
/*============================================================================*/
namespace Research::HashTables {

    template <typename T, typename Hash, int expandPercent>
    class SeparateChaining : public IHashSet<T> {
    private:

        static constexpr size_t DEFAULT_BUCKET_COUNT = 16;
        static constexpr size_t LOAD_FACTOR = 10;
        static constexpr double EXPAND_FACTOR = static_cast<double>(expandPercent) / 100;

        struct Node {

            explicit Node(const T& key, Node* next_node = nullptr);

            Node* find(const T& key);

            Node* findPrev(const T& key);

            ~Node();

            T key;
            Node* next;
        };

    public:

        explicit SeparateChaining();

        ~SeparateChaining();

        void add(const T& key) override;

        bool find(const T& key) override;

        bool remove(const T& key) override;

        void dump();

        void rehash(size_t new_size);

    private:

        std::vector<Node*> buckets;
        Hash hash;
    };

    template <typename T, typename Hash>
    using SeparateChaining75 = SeparateChaining<T, Hash, 75>;

    template <typename T, typename Hash>
    using SeparateChaining95 = SeparateChaining<T, Hash, 95>;

}
/*============================================================================*/
#include "SeparateChaining.ipp"
/*============================================================================*/
#endif //HASHTABLES_RESEARCH_SEPARATECHAINING_HPP
/*============================================================================*/