/*============================================================================*/
#ifndef HASHTABLES_RESEARCH_INTERFACE_HPP
#define HASHTABLES_RESEARCH_INTERFACE_HPP
/*============================================================================*/
#include <cstddef>
#include <cstdint>
#include <string>
#include <type_traits>
/*============================================================================*/
namespace Research {

    namespace Types {
        using String = std::string;
        using Number = uint64_t;
    }

    /*------------------------------------------------------------------------*/

    template <typename T>
    class IHash {
    public:

        virtual uint64_t operator()(const T& key) = 0;

        virtual void shuffle() {}

    private:

        static constexpr bool IS_ACCEPTED =
            std::is_same<T, Types::String>::value ||
            std::is_same<T, Types::Number>::value;

        using Helper = typename std::enable_if<IS_ACCEPTED, int>::type;
    };

    /*------------------------------------------------------------------------*/

    template<typename T>
    class IHashSet {
    public:

        using Key = T;

        static constexpr size_t DEFAULT_SIZE = 4;

        explicit IHashSet()
                : sz(0)
                { }

        virtual ~IHashSet() = default;

        virtual void add(const T& key) = 0;

        virtual bool find(const T& key) = 0;

        virtual bool remove(const T& key) = 0;

        [[nodiscard]]
        virtual size_t size() const {
            return sz;
        }

    protected:

        void setSize(size_t new_size) {
            sz = new_size;
        }

    private:

        size_t sz;
    };

}
/*============================================================================*/
#endif //HASHTABLES_RESEARCH_INTERFACE_HPP
/*============================================================================*/