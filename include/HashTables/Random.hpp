/*============================================================================*/
#ifndef HASHTABLES_RESEARCH_RANDOM_HPP
#define HASHTABLES_RESEARCH_RANDOM_HPP
/*============================================================================*/
#include "Interface.hpp"
#include <random>
/*============================================================================*/
namespace Research::Random {

    template <typename T>
    T getValue();

    bool tossCoin(double probability);

    /*------------------------------------------------------------------------*/

    template <>
    Types::Number getValue<Types::Number>();

    template <>
    Types::String getValue<Types::String>();

    /*------------------------------------------------------------------------*/

    using RandGen = std::mt19937;

    RandGen& Generator();

}
/*============================================================================*/
#endif //HASHTABLES_RESEARCH_RANDOM_HPP
/*============================================================================*/