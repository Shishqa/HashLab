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

        static constexpr bool IS_ACCEPTED =
            std::is_same<T, Types::String>::value ||
            std::is_same<T, Types::Number>::value;

        using Helper = typename std::enable_if<IS_ACCEPTED, int>::type;

        virtual uint64_t operator()(const T& key) = 0;

    };

    /*------------------------------------------------------------------------*/

    template<typename T>
    class IHashSet {
    public:

        using Type = T;

        static constexpr size_t DEFAULT_SIZE = 3;

        IHashSet() : sz(0) { }

        virtual ~IHashSet() = default;

        virtual void add(const T& key) = 0;

        virtual bool find(const T& key) = 0;

        virtual bool remove(const T& key) = 0;

        [[nodiscard]]
        virtual size_t size() const {
            return sz;
        }

    protected:

        size_t sz;
    };

}
/*============================================================================*/
#endif //HASHTABLES_RESEARCH_INTERFACE_HPP
/*============================================================================*/