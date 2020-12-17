/*============================================================================*/
#ifndef HASHTABLES_RESEARCH_RUNS_IPP
#define HASHTABLES_RESEARCH_RUNS_IPP
/*============================================================================*/
namespace Research::HashTables::RunTypes {

template <typename T, typename Hash>
void LinearRun<T, Hash>::init(const T& key, size_t arr_size) {
    IRun<T>::init(key, arr_size);
    key_hash = hash(key) % IRun<T>::Mod();
}

template <typename T, typename Hash>
uint64_t LinearRun<T, Hash>::next() {
    return (key_hash + IRun<T>::curr_attempt++) % IRun<T>::Mod();
}

template <typename T, typename Hash>
void LinearRun<T, Hash>::shuffle() {
    hash.shuffle();
}

/*----------------------------------------------------------------------------*/

template <typename T, typename Hash>
void QuadraticRun<T, Hash>::init(const T& key, size_t arr_size) {
    IRun<T>::init(key, arr_size);
    key_hash = hash(key) % IRun<T>::Mod();
    curr_offset = 0;
}

template <typename T, typename Hash>
uint64_t QuadraticRun<T, Hash>::next() {

    uint64_t idx = 0;
    if (IRun<T>::curr_attempt % 2) {
        idx = (key_hash + IRun<T>::Mod() - curr_offset % IRun<T>::Mod()) % IRun<T>::Mod();
    } else {
        idx = (key_hash + curr_offset) % IRun<T>::Mod();
    }

    curr_offset = (curr_offset + (IRun<T>::curr_attempt++ << 1) + 1);

    return idx;
}

template <typename T, typename Hash>
void QuadraticRun<T, Hash>::shuffle() {
    hash.shuffle();
}

/*----------------------------------------------------------------------------*/

template <typename T, typename Hash1, typename Hash2>
void DoubleHashingRun<T, Hash1, Hash2>::init(const T& key, size_t arr_size) {

    IRun<T>::init(key, arr_size);

    key_hash1 = hash1(key) % IRun<T>::Mod();
    key_hash2 = hash2(key) % IRun<T>::Mod();
}

template <typename T, typename Hash1, typename Hash2>
uint64_t DoubleHashingRun<T, Hash1, Hash2>::next() {
    return (key_hash1 + (key_hash2) * (IRun<T>::curr_attempt++)) % IRun<T>::Mod();
}

template <typename T, typename Hash1, typename Hash2>
void DoubleHashingRun<T, Hash1, Hash2>::shuffle() {
    hash1.shuffle();
    hash2.shuffle();
}

}
/*============================================================================*/
#endif //HASHTABLES_RESEARCH_RUNS_IPP
/*============================================================================*/