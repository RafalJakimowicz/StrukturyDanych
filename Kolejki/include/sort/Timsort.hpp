#ifndef SORT_TIMSORT_HPP
#define SORT_TIMSORT_HPP
#include <vector>
#include <iterator>

template <typename T>
class TimSort{
    private:
    void _insertSort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end);
    void _merge(typename std::vector<T>::iterator start, typename std::vector<T>::iterator mid, typename std::vector<T>::iterator end);
    unsigned short _switchLen;
    
    public:
    TimSort(unsigned short switchLen = 16){
        this->_switchLen = switchLen;
    }
    void sort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end);
};

template <typename T>
void TimSort<T>::_insertSort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end){
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
void TimSort<T>::_merge(typename std::vector<T>::iterator start, typename std::vector<T>::iterator mid, typename std::vector<T>::iterator end){
    vector<T> sorted;
    sorted.reserve(distance(start, end));

    typename std::vector<T>::iterator leftStart = start;
    typename std::vector<T>::iterator rightStart = mid;

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

    typename std::vector<T>::iterator ogStart = start;
    for(const T& item: sorted){
        *ogStart = item;
        ++ogStart;
    }
}

template <typename T>
void TimSort<T>::sort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end){
    if(start == end || next(start) == end){
        return;
    }

    typename std::vector<T>::iterator mid = next(start, distance(start, end) / 2);
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