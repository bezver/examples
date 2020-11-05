//
// Created by bezver on 24.06.2020.
//

#ifndef ARRAY_H
#define ARRAY_H

#include <initializer_list>
#include <ostream>

template<typename T>
class Array {
    T*  data;
    int data_size;

    template<typename inputIterator>
    void rangeInitialize_(inputIterator begin, inputIterator end) {
        data_size = end - begin;    // it is not good
        data = new T[data_size];
        for (size_t i = 0; begin != end; begin++, i++) {
            data[i] = *begin;
        }
    }

public:
    Array() : data(0), data_size(0) {}

    Array(int size) {
        resize(size);
    }

    template<class iteratorType>
    Array(iteratorType begin, iteratorType end) {
        rangeInitialize_(begin, end);
    }

    Array(const Array& array) {
        unsigned int size = array.size();
        if (size > 0) {
            data = new T[size];
            for (int i = 0; i < size; i++) {    //copy data
                data[i] = array.data[i];
            }
            data_size = size;
        } else {
            data = 0;
            data_size = 0;
        }
    }

    Array(std::initializer_list<T> list) {
        rangeInitialize_(list.begin(), list.end());
    }

    ~Array() {
        clear();
    }

    void resize(int new_size) {
        if (new_size == 0) {
            clear();
        }
        else {
            T *new_data = new T[new_size];
            for (int i = 0; i < data_size; i++) {   //copy element in new_data
                new_data[i] = data[i];
            }
            T *remove = data;
            data = new_data;
            data_size = new_size;
            if (remove)
                delete[] remove;
        }
    }

    void push_back(const T& value) {
        this->resize(data_size + 1);
        data[data_size - 1] = value;
    }

    void clear() {
        if (data) {
            delete[] data;
            data = 0;
            data_size = 0;
        }
    }

    int size() const {
        return data_size;
    }

    T pop_up() const {
        if (data_size > 0)
            return data[data_size - 1];
        throw "empty array";
    }

    T* begin() {
        return data;
    }

    T* end() {
        return data + data_size;
    }

    T& operator[](int index) {
        if (index >= 0 && index < data_size) {
            return data[index];
        }
        throw "interputed by array";
    }

    Array& operator=(Array& array) {
        if (data) {         //if empty array
            delete[] data;
            data = 0;
            data_size = 0;
        }
        if (array.size() == 0) {      //if empty rhv
            return *this;
        }
        data_size = array.size();
        data = new T[data_size];
        for (size_t i = 0; i < data_size; i++) {
            data[i] = array[i];
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, Array& array) {
        for (size_t i = 0; i < array.data_size; i++) {
            out << array.data[i] << ' ';
        }
        out << std::endl;
        return out;
    }
};

#endif //ARRAY_H
