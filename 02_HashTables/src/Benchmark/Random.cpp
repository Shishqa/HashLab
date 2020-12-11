/*============================================================================*/
#include "Random.hpp"
/*============================================================================*/
using namespace Research::Benchmark;
/*============================================================================*/

Random::RandGen& Random::Generator() {
    static RandGen GENERATOR(6274674);
    return GENERATOR;
}

/*----------------------------------------------------------------------------*/

bool Random::tossCoin(double probability) {

    static std::uniform_real_distribution<double> dist(0.0, 1.0);

    double value = dist(Generator());
    return (value < probability);
}

/*----------------------------------------------------------------------------*/

template <>
Research::Types::Number Random::getValue<Research::Types::Number>() {

    std::uniform_int_distribution<Types::Number> dist(0, UINT64_MAX);

    return dist(Generator());
}

/*----------------------------------------------------------------------------*/

template <>
Research::Types::String Random::getValue<Research::Types::String>() {

    std::uniform_int_distribution<size_t> size_dist(1, 20);
    std::uniform_int_distribution<char> char_dist(1, INT8_MAX);

    const size_t str_len = size_dist(Generator());

    Types::String str;
    str.resize(str_len);

    for (auto& ch : str) {
        ch = char_dist(Generator());
    }

    return str;
}

/*============================================================================*/
