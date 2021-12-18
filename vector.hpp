#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP

#include "exceptions.hpp"

#include <climits>
#include <cstddef>
#include <iostream>

namespace sjtu {

template<typename T>
class vector {
    size_t siz, cap;
    T** vec;
    void expand(){
        if(siz < cap)return;
        T** pre = new T*[siz];
        for(size_t i = 0; i < siz; ++i){
            pre[i] = new T(*vec[i]);
            delete vec[i];
        }
        delete [] vec;
        cap <<= 1, vec = new T*[cap];
        for(size_t i = 0; i < siz; ++i){
            vec[i] = new T(*pre[i]);
            delete pre[i];
        }
        delete [] pre;
    }
    void shrink(){
        if(cap == 1 || siz<<2 > cap)return;
        T** pre = new T*[siz];
        for(size_t i = 0; i < siz; ++i){
            pre[i] = new T(*vec[i]);
            delete vec[i];
        }
        delete [] vec;
        cap >>= 1, vec = new T*[cap];
        for(size_t i = 0; i < siz; ++i){
            vec[i] = new T(*pre[i]);
            delete pre[i];
        }
        delete [] pre;
    }    
    public:
    class const_iterator;
    class iterator {
    friend class vector;
    friend class const_iterator;
    private:
        size_t num;
        T** iter;    
    public:
        iterator(){num = 0;}
        iterator(const iterator &other){
            iter = other.iter, num = other.num;
        }
        iterator operator+(const int &n) const {
            iterator tmp = *this;
            tmp.num += n;
            return tmp;
        }
        iterator operator-(const int &n) const {
            iterator tmp = *this;
            tmp.num -= n;
            return tmp;
        }
        int operator-(const iterator &rhs) const {
            if(iter != rhs.iter){throw invalid_iterator();}
            return num - rhs.num;
        }
        iterator& operator+=(const int &n) {
            num += n;
            return *this;
        }
        iterator& operator-=(const int &n) {
            num -= n;
            return *this;            
        }
        iterator operator++(int) {
            iterator pre = *this;
            num++;
            return pre;
        }
        iterator& operator++() {
            ++num;
            return *this;
        }
        iterator operator--(int) {
            iterator pre = *this;
            num--;
            return pre;            
        }
        iterator& operator--() {
            --num;
            return *this;
        }
        T& operator*() const{return *iter[num];}
        bool operator==(const iterator &rhs) const {
            if(iter != rhs.iter){throw invalid_iterator();}
            return num == rhs.num;
        }
        bool operator==(const const_iterator &rhs) const {
            if(iter != rhs.iter){throw invalid_iterator();}
            return num == rhs.num;
        }
        bool operator!=(const iterator &rhs) const {
            if(iter != rhs.iter){throw invalid_iterator();}
            return num != rhs.num;
        }
        bool operator!=(const const_iterator &rhs) const {
            if(iter != rhs.iter){throw invalid_iterator();}
            return num != rhs.num;
        }
    };
    class const_iterator {
    friend class vector;
    friend class iterator;
    private:
        size_t num;
        T** iter;        
    public:
        const_iterator(){num = 0;}
        const_iterator(const const_iterator &other){
            iter = other.iter, num = other.num;
        }
        const_iterator operator+(const int &n) const {
            const_iterator tmp = *this;
            tmp.num += n;
            return tmp;
        }
        const_iterator operator-(const int &n) const {
            const_iterator tmp = *this;
            tmp.num -= n;
            return tmp;
        }
        int operator-(const const_iterator &rhs) const {
            if(iter != rhs.iter){throw invalid_iterator();}
            return num - rhs.num;
        }
        const_iterator& operator+=(const int &n) {
            num += n;
            return *this;
        }
        const_iterator& operator-=(const int &n) {
            num -= n;
            return *this;            
        }
        const_iterator operator++(int) {
            const_iterator pre = *this;
            num++;
            return pre;
        }
        const_iterator& operator++() {
            ++num;
            return *this;
        }
        const_iterator operator--(int) {
            const_iterator pre = *this;
            num--;
            return pre;            
        }
        const_iterator& operator--() {
            --num;
            return *this;
        }
        const T& operator*() const{return *iter[num];}
        bool operator==(const const_iterator &rhs) const {
            if(iter != rhs.iter){throw invalid_iterator();}
            return num == rhs.num;
        }
        bool operator==(const iterator &rhs) const {
            if(iter != rhs.iter){throw invalid_iterator();}
            return num == rhs.num;
        }
        bool operator!=(const const_iterator &rhs) const {
            if(iter != rhs.iter){throw invalid_iterator();}
            return num != rhs.num;
        }
        bool operator!=(const iterator &rhs) const {
            if(iter != rhs.iter){throw invalid_iterator();}
            return num != rhs.num;
        }
    };
    vector():cap(1), siz(0){vec = new T*[1];}
    vector(const vector &other) {
        siz = other.siz;
        cap = other.cap;
        vec = new T*[cap];
        for(size_t i = 0; i < siz; ++i)vec[i] = new T(*(other.vec[i]));
    }
    ~vector() {
        for(size_t i = 0; i < siz; ++i)delete vec[i];
        delete [] vec;
    }
    vector & operator=(const vector &other){
        if(this == &other)return *this;
        for(size_t i = 0; i < siz; ++i)delete vec[i];
        delete [] vec;
        siz = other.siz;
        cap = other.cap;
        vec = new T*[cap];
        for(size_t i = 0; i < siz; ++i)vec[i] = new T(*(other.vec[i]));
        return *this;
    }
    T & at(const size_t &pos) {
        if(pos >= siz || pos < 0)throw index_out_of_bound();
        return *(vec[pos]);
    }
    const T & at(const size_t &pos) const {
        if(pos >= siz || pos < 0)throw index_out_of_bound();
        return *(vec[pos]);
    }
    T & operator[](const size_t &pos) {
        if(pos >= siz || pos < 0)throw index_out_of_bound();
        return *(vec[pos]);
    }
    const T & operator[](const size_t &pos) const {
        if(pos >= siz || pos < 0)throw index_out_of_bound();
        return *(vec[pos]);
    }
    const T & front() const {
        if(siz == 0)throw container_is_empty();
        return *vec[0];
    }
    const T & back() const {
        if(siz == 0)throw container_is_empty();
        return *vec[siz - 1];
    }
    iterator begin() {
        iterator tmp;
        tmp.iter = vec;
        return tmp;
    }
    const_iterator cbegin() const {
        const_iterator tmp;
        tmp.iter = vec;
        return tmp;
    }
    iterator end() {
        iterator tmp;
        tmp.iter = vec, tmp.num = siz;
        return tmp;
    }
    const_iterator cend() const {
        const_iterator tmp;
        tmp.iter = vec, tmp.num = siz;
        return tmp;
    }
    bool empty() const {return siz == 0;}
    size_t size() const {return siz;}
    void clear() {
        for(int i = 0; i < siz; ++i)delete vec[i];
        delete vec;
        cap = 1, siz = 0, *vec = new T[1];
    }
    iterator insert(iterator pos, const T &value) {
        expand();
        // std::cerr<<"inserting:"<<value<<'\n';
        size_t cur = pos.num;
        vec[siz] = new T(*vec[siz - 1]);
        for(size_t i = siz - 1; i > cur; --i){
            delete vec[i];
            vec[i] = new T(*vec[i - 1]);
        }
        delete vec[cur];
        vec[cur] = new T(value);
        iterator it;
        it.iter = vec;
        it.num = cur;
        ++siz;
        return it;
    }
    iterator insert(const size_t &ind, const T &value) {
        if(ind > siz)throw index_out_of_bound();
        expand();
        vec[siz] = new T(*vec[siz - 1]);
        for(size_t i = siz - 1; i > ind; --i){
            delete vec[i];
            vec[i] = new T(*vec[i - 1]);
        }
        delete vec[ind];
        vec[ind] = new T(value);
        iterator it;
        it.iter = vec;
        it.num = ind;
        ++siz;
        return it;
    }
    iterator erase(iterator pos) {
        size_t ind = pos.num;
        // std::cerr<<ind<<":"<<*pos<<'\n';
        for(size_t i = ind + 1; i < siz; ++i){
            delete vec[i - 1];
            vec[i - 1] = new T(*vec[i]);
        }
        // for(size_t i = 0; i < siz - 1; ++i)std::cerr<<*vec[i]<<' ';std::cerr<<'\n';
        delete vec[siz - 1];
        --siz;
        shrink();
        return pos + 1;
    }
    iterator erase(const size_t &ind) {
        if(ind >= siz)throw index_out_of_bound(); 
        for(size_t i = ind + 1; i < siz; ++i){
            delete vec[i - 1];
            vec[i - 1] = new T(*vec[i]);
        }
        delete vec[siz - 1];
        --siz;
        shrink();
        iterator pos;
        pos.iter = vec;
        pos.num = ind;
        return pos + 1;
    }
    void push_back(const T &value) {
        expand();
        vec[siz] = new T(value), siz++;
    }
    void pop_back() {
        if(!siz)throw container_is_empty();
        delete vec[siz - 1];
        --siz,shrink();
    }
};

}

#endif
