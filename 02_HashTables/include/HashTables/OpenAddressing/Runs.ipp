/*============================================================================*/
#ifndef HASHTABLES_RESEARCH_RUNS_IPP
#define HASHTABLES_RESEARCH_RUNS_IPP
/*============================================================================*/
namespace Research::HashTables::Run {

template <typename T>
IRun<T>::IRun(const T& key)
        : key_ref(key)
        { }

/*----------------------------------------------------------------------------*/

template <typename T, template<typename> typename Hash>
LinearRun<T, Hash>::LinearRun(const T& key)
        : IRun<T>(key) {
    Hash<T> hash;
    key_hash = hash(key);
}

template <typename T, template<typename> typename Hash>
uint64_t LinearRun<T, Hash>::operator()(uint64_t attempt) {
    return key_hash + attempt;
}

/*----------------------------------------------------------------------------*/

template <typename T, template<typename> typename Hash>
QuadraticRun<T, Hash>::QuadraticRun(const T& key)
    : IRun<T>(key) {
    Hash<T> hash;
    key_hash = hash(key);
}

template <typename T, template<typename> typename Hash>
uint64_t QuadraticRun<T, Hash>::operator()(uint64_t attempt) {
    return key_hash + attempt * attempt;
}

/*----------------------------------------------------------------------------*/

template <typename T,
          template<typename> typename Hash1,
          template<typename> typename Hash2>
DoubleHashingRun<T, Hash1, Hash2>::DoubleHashingRun(const T& key)
    : IRun<T>(key) {

    Hash1<T> hash1;
    key_hash1 = hash1(key);

    Hash2<T> hash2;
    key_hash2 = hash2(key);
}

template <typename T,
    template<typename> typename Hash1,
    template<typename> typename Hash2>
uint64_t DoubleHashingRun<T, Hash1, Hash2>::operator()(uint64_t attempt) {
    return key_hash1 + key_hash2 * attempt;
}

}
/*============================================================================*/
#endif //HASHTABLES_RESEARCH_RUNS_IPP
/*============================================================================*/