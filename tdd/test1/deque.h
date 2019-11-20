#pragma once

#include <vector>
#include <array> 
#include <memory>
#include <string> 

template<typename T, int N = 16> 
using impl_t = std::vector<std::unique_ptr<std::array<T, N>>>;  

template<typename T, int N = 16, typename IMPL = impl_t<T,N>>
class DEQ {
public: 
    void push_back(const T & t); 
    void        pop_back(); 
    bool        empty()const    { return 0 == mSize; }
    size_t      size() const    { return mSize; }
    T &         front()         { return (*mPtrs.front())[mBegin];}
    const T &  front() const    { return (*mPtrs.front())[mBegin];}
    T &         back()          { return (*mPtrs[buffNum(mSize -1)])[backPos()]; }
    const T &   back() const    { return (*mPtrs[buffNum(mSize -1)])[backPos()]; }
    const T &   at(size_t idx) const;
    T &         at(size_t idx);

    T & operator[](size_t idx) noexcept; 
    const T & operator[](size_t idx) const noexcept; 

#ifdef JUST_FOR_DEBUG
    // IMPL & getImpl() { return mPtrs; }
    // const IMPL & getImpl() const { return mPtrs; }
#endif

private: 
    size_t  mBegin{};   // index of the first used in the first buffer
    size_t  mSize{};    // number of every element in the deque
    IMPL    mPtrs;      // pointer holder

    size_t  endPos() const { return (mBegin + mSize) % N; }
    size_t  backPos() const { return (mBegin + mSize + N-1) % N;}
    size_t  buffNum(size_t idx) const { return (mBegin + idx) / N; }
    size_t  buffIdx(size_t idx) const { return (mBegin + idx) % N; }
    void    checkIndex(size_t idx) const;
}; 

template<typename T, int N, typename IMPL> 
void DEQ<T,N, IMPL>::pop_back() { 
    --mSize;
}

template<typename T, int N, typename IMPL> 
void DEQ<T,N, IMPL>::push_back(const T & t ) {
    if ( mPtrs.size() == buffNum(mSize) )  {
        mPtrs.push_back(std::unique_ptr<std::array<T, N>> (new std::array<T, N>() ));
    } 
    (*mPtrs[buffNum(mSize)])[buffIdx(mSize)] = t; 
    ++mSize; 
}

template<typename T, int N, typename IMPL> 
T &  DEQ<T,N, IMPL>::operator[](size_t idx) noexcept {
    return (*mPtrs[buffNum(idx)])[buffIdx(idx)];
}

template<typename T, int N, typename IMPL> 
const T &  DEQ<T,N, IMPL>::operator[](size_t idx) const noexcept{
    return (*mPtrs[buffNum(idx)])[buffIdx(idx)];
}

template<typename T, int N, typename IMPL> 
const T &  DEQ<T,N, IMPL>::at(size_t idx) const {
    checkIndex(idx); 
    return operator[](idx); 
}

template<typename T, int N, typename IMPL> 
T & DEQ<T,N, IMPL>::at(size_t idx) {
    checkIndex(idx); 
    return operator[](idx); 
}

template<typename T, int N, typename IMPL> 
void DEQ<T,N, IMPL>::checkIndex(size_t idx) const {
    if (idx < mSize) 
        return; 
    std::string temp = "Bad index: " + std::to_string(idx);
    // throw std::out_of_range(temp);
    throw std::out_of_range(temp); 
}