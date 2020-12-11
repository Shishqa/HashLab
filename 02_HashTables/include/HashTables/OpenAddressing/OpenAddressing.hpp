/*============================================================================*/
#ifndef HASHTABLES_OPENADDRESSING_HPP
#define HASHTABLES_OPENADDRESSING_HPP
/*============================================================================*/
#include "Interface.hpp"

#include <vector>
#include <variant>
#include <optional>
/*============================================================================*/
namespace Research::HashTables {

    namespace Run {

        template<typename T>
        class IRun {
        public:

            explicit IRun(const T& key);

            virtual uint64_t operator()(uint64_t attempt) = 0;

        protected:

            const T& key_ref;
        };

        /*------------------------------------------------------------------------*/

        template<typename T, template<typename> typename Hash>
        class LinearRun : public IRun<T> {
        public:

            explicit LinearRun(const T& key);

            uint64_t operator()(uint64_t attempt) override;

        private:

            uint64_t key_hash;

        };

        /*------------------------------------------------------------------------*/

        template<typename T, template<typename> typename Hash>
        class QuadraticRun : public IRun<T> {
        public:

            explicit QuadraticRun(const T& key);

            uint64_t operator()(uint64_t attempt) override;

        private:

            uint64_t key_hash;
        };

        /*------------------------------------------------------------------------*/

        template<typename T,
            template<typename> typename Hash1,
            template<typename> typename Hash2>
        class DoubleHashingRun : public IRun<T> {
        public:

            explicit DoubleHashingRun(const T& key);

            uint64_t operator()(uint64_t attempt) override;

        private:

            uint64_t key_hash1;
            uint64_t key_hash2;
        };

    }

    /*------------------------------------------------------------------------*/

    template <typename T, typename Run>
    class OpenAddressing : public IHashSet<T> {
    public:

        OpenAddressing();

        void add(const T& key) override;

        bool find(const T& key) override;

        bool remove(const T& key) override;

        void dump();

    private:

        struct HashNode {

            enum State {
                NORMAL,
                TOMBSTONE
            };

            HashNode();

            explicit HashNode(const T& key);

            std::optional<T> key;
            State state;
        };

        uint64_t locate(const T& key, const std::vector<HashNode>& arr);

        void rehash(size_t new_size);

        std::vector<HashNode> data;
    };

    template <typename T, template<typename> typename Hash>
    using OpenAddressingLinear = OpenAddressing<T, Run::LinearRun<T, Hash>>;

    template <typename T, template<typename> typename Hash>
    using OpenAddressingQuadratic = OpenAddressing<T, Run::QuadraticRun<T, Hash>>;

    template <typename T,
              template<typename> typename Hash1,
              template<typename> typename Hash2>
    using OpenAddressingDbHasing =
        OpenAddressing<T, Run::DoubleHashingRun<T, Hash1, Hash2>>;

}
/*============================================================================*/
#include "Runs.ipp"
#include "OpenAddressing.ipp"
/*============================================================================*/
#endif
/*============================================================================*/