// inversions.hpp
// Duane Shaffer
// CS411
// 10/11/2018
// This program uses a modified version of merge sort provided
// by Dr. Hartman and written by Dr. Chappell

#ifndef INVERSIONS_HPP
#define INVERSIONS_HPP

#include <vector>
using std::vector;

#include <cstddef>
using std::size_t;

#include <algorithm>
using std::copy;

#include <iterator>
using std::distance;
using std::advance;

#include <type_traits>
using std::remove_reference;

template<typename FDIter>
size_t stableMerge(FDIter first, FDIter middle, FDIter last) {
    using Value = typename remove_reference<decltype(*first)>::type;

    vector <Value> buffer(distance(first, last));
    FDIter in1 = first;
    FDIter in2 = middle;
    auto out = buffer.begin();
    size_t total = 0;
    while (in1 != middle && in2 != last) {
        if (*in2 < *in1) {
            *out++ = *in2++;
            total += distance(in1, middle);
        } else
            *out++ = *in1++;
    }

    copy(in1, middle, out);
    copy(in2, last, out);

    copy(buffer.begin(), buffer.end(), first);
    return total;
}

template<typename FDIter>
size_t mergeSort(FDIter first, FDIter last) {
    size_t size = distance(first, last);

    if (size <= 1){
        return 0;
    }

    FDIter middle = first;
    advance(middle, size / 2);

    size_t total = mergeSort(first, middle);
    total += mergeSort(middle, last);

    return total += stableMerge(first, middle, last);
}


template<typename RAIter>
size_t inversions(RAIter first, RAIter last) {
    return mergeSort(first, last);
}

#endif //INVERSIONS_HPP
