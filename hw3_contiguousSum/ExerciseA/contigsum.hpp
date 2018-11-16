// contigsum.hpp
// Duane Shaffer
// CS411
// 10/11/2018
#include <algorithm>

#ifndef CONTIGSUM_HPP
#define CONTIGSUM_HPP

struct GCS_Container{
    int greatestContinuousSum = 0;
    int sumWithFirstElement = 0;
    int sumWithLastElement = 0;
    int totalOfAllElements = 0;
};

const GCS_Container merge(const GCS_Container & l, const GCS_Container & r){
    GCS_Container t;
    t.greatestContinuousSum = std::max({l.greatestContinuousSum, r.greatestContinuousSum, (l.sumWithLastElement + r.sumWithFirstElement)});
    t.sumWithFirstElement = std::max(l.sumWithFirstElement, l.totalOfAllElements + r.sumWithFirstElement);
    t.sumWithLastElement = std::max(r.sumWithLastElement, r.totalOfAllElements + l.sumWithLastElement);
    t.totalOfAllElements = r.totalOfAllElements + l.totalOfAllElements;
    return t;

}

template<typename RAIter>
const GCS_Container gcsRecurse(const RAIter first, const RAIter last){

    if(distance(first, last) == 1){
        GCS_Container base;
        base.greatestContinuousSum = *first;
        base.sumWithFirstElement = *first;
        base.sumWithLastElement = *first;
        base.totalOfAllElements = *first;
        return base;
    }

    auto middle = first;
    advance(middle,distance(first,last)/2);
    auto left_gcs = gcsRecurse(first, middle);
    auto right_gcs = gcsRecurse(middle, last);

    return merge(left_gcs, right_gcs);

}


template<typename RAIter>
int contigSum(const RAIter first, const RAIter last) {
    if(distance(first,last) == 0){
        return 0;
    }
    auto gcsTest = gcsRecurse(first, last);
    return std::max(gcsTest.greatestContinuousSum, 0);
}








#endif //CONTIGSUM_HPP
