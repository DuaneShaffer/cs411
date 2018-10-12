// contigsum.hpp
// Duane Shaffer
// CS411
// 10/11/2018
#include <algorithm>

#ifndef CONTIGSUM_HPP
#define CONTIGSUM_HPP

struct GCS{
    int gcs = 0;
    int sumFirst = 0;
    int sumLast = 0;
    int total = 0;
};

const GCS merge(const GCS & left, const GCS & right){
    GCS mergedGCS;
    mergedGCS.gcs = std::max({left.gcs, right.gcs, (left.sumLast + right.sumFirst)});
    mergedGCS.sumFirst = std::max(left.sumFirst, left.total + right.sumFirst);
    mergedGCS.sumLast = std::max(right.sumLast, right.total + left.sumLast);
    mergedGCS.total = right.total + left.total;
    return mergedGCS;

}

template<typename RAIter>
const GCS gcsRecurse(const RAIter first, const RAIter last){
    GCS gcs;

    if(distance(first, last) == 1){
        gcs.gcs = *first;
        gcs.sumFirst = *first;
        gcs.sumLast = *first;
        gcs.total = *first;
        return gcs;
    }

    auto middle = first;
    advance(middle,distance(first,last)/2);
    auto left_gcs = gcsRecurse(first, middle);
    auto right_gcs = gcsRecurse(middle, last);

    return (merge(left_gcs, right_gcs));

}


template<typename RAIter>
int contigSum(const RAIter first, const RAIter last) {
    if(distance(first,last) == 0){
        return 0;
    }
    auto gcsTest = gcsRecurse(first, last);
    return std::max(gcsTest.gcs, 0);
}








#endif //CONTIGSUM_HPP
