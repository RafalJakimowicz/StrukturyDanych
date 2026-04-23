#ifndef SORT_TIMSORT_HPP
#define SORT_TIMSORT_HPP
#include <vector>
#include <iterator>

using namespace std;
template <typename T>
class TimSort{
    private:
    void _insertSort(typename vector<T>::iterator start, typename vector<T>::iterator end);
    void _merge(typename vector<T>::iterator start, typename vector<T>::iterator mid, typename vector<T>::iterator end);
    unsigned short _switchLen;
    
    public:
    TimSort(unsigned short switchLen = 16){
        this->_switchLen = switchLen;
    }
    void sort(typename vector<T>::iterator start, typename vector<T>::iterator end);
};

template <typename T>
void TimSort<T>::_insertSort(typename vector<T>::iterator start, typename vector<T>::iterator end){
    for(typename vector<T>::iterator it = start; it != end; ++it){
        T key = *it;
        typename vector<T>::iterator current = it;
        while(current > start && *prev(current) > key){
            *current = *prev(current);
            current = prev(current);
        }
        *current = key;
    }
}

template <typename T>
void TimSort<T>::_merge(typename vector<T>::iterator start, typename vector<T>::iterator mid, typename vector<T>::iterator end){
    vector<T> sorted;
    sorted.reserve(distance(start, end));

    typename vector<T>::iterator leftStart = start;
    typename vector<T>::iterator rightStart = mid;

    while(leftStart != mid && rightStart != end){
        if(*leftStart < *rightStart){
            sorted.push_back(*leftStart);
            ++leftStart;
        }
        else{
            sorted.push_back(*rightStart);
            ++rightStart;
        }
    }

    while(leftStart != mid){
        sorted.push_back(*leftStart);
        ++leftStart;
    }

    while(rightStart != end){
        sorted.push_back(*rightStart);
        ++rightStart;
    }

    typename vector<T>::iterator ogStart = start;
    for(const T& item: sorted){
        *ogStart = item;
        ++ogStart;
    }
}

template <typename T>
void TimSort<T>::sort(typename vector<T>::iterator start, typename vector<T>::iterator end){
    if(start == end || next(start) == end){
        return;
    }

    typename vector<T>::iterator mid = next(start, distance(start, end) / 2);
    if(distance(start, end) > this->_switchLen){
        this->sort(start, mid);
        this->sort(mid, end);
    }
    else {
        this->_insertSort(start, end);
    }

    this->_merge(start, mid, end);
}


#endif