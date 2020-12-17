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

    template <typename T>
    class IRun {
    public:

        IRun() : mod(0), curr_attempt(0) {}

        virtual void init(const T&, size_t arr_size) {
            mod = arr_size;
            curr_attempt = 0;
        }

        virtual uint64_t next() = 0;

        virtual void shuffle() = 0;

    protected:

        size_t Mod() const {
            return mod;
        }

        uint64_t curr_attempt;

    private:

        size_t mod;
    };

    namespace RunTypes {

        template <typename T, typename Hash>
        class LinearRun : public IRun<T> {
        public:

            void init(const T& key, size_t arr_size) override;

            uint64_t next() override;

            void shuffle() override;

        private:

            uint64_t key_hash;

            Hash hash;
        };

        /*------------------------------------------------------------------------*/

        template <typename T, typename Hash>
        class QuadraticRun : public IRun<T> {
        public:

            void init(const T& key, size_t arr_size) override;

            uint64_t next() override;

            void shuffle() override;

        private:

            uint64_t key_hash;
            uint64_t curr_offset;
            uint64_t curr_attempt;

            Hash hash;
        };

        /*------------------------------------------------------------------------*/

        template<typename T, typename Hash1, typename Hash2 = Hash1>
        class DoubleHashingRun : public IRun<T> {
        public:

            void init(const T& key, size_t arr_size) override;

            uint64_t next() override;

            void shuffle() override;

        private:

            uint64_t key_hash1;
            uint64_t key_hash2;

            Hash1 hash1;
            Hash2 hash2;
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

    protected:

        IRun<T>& run();

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

        int64_t locate(const T& key, const std::vector<HashNode>& arr);

        void rehash(size_t new_size);

        ////////////////////////////
        std::vector<HashNode> data;
        Run run_impl;
        ////////////////////////////
    };

    template <typename T, typename Hash>
    using OpenAddressingLinear =
        OpenAddressing<T, RunTypes::LinearRun<T, Hash>>;

    template <typename T, typename Hash>
    using OpenAddressingQuadratic =
        OpenAddressing<T, RunTypes::QuadraticRun<T, Hash>>;

    template <typename T, typename Hash>
    using OpenAddressingDoubleHasing =
        OpenAddressing<T, RunTypes::DoubleHashingRun<T, Hash>>;

}
/*============================================================================*/
#include "Runs.ipp"
#include "OpenAddressing.ipp"
/*============================================================================*/
#endif
/*============================================================================*/