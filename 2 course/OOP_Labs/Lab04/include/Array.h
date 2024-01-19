#pragma once

#include <iostream>

template<typename T>
class MyArray {
public:
    MyArray() : _elems(nullptr), _size(0), _capacity(0) {}
    MyArray(const MyArray& other) : _size(other._size), _capacity(other._capacity) {
        _elems = new T[_capacity];
        for (int i = 0; i < _size; ++i) {
            _elems[i] = other._elems[i];
        }
    }
    ~MyArray() {
        delete[] _elems;
    }
    MyArray& operator=(const MyArray& other) {
        if (this != &other) {
            delete[] _elems;

            _size = other._size;
            _capacity = other._capacity;

            _elems = new T[_capacity];
            for (int i = 0; i < _size; ++i) {
                _elems[i] = other._elems[i];
            }
        }
        return *this;
    }

    void resize(int newCapacity) {
        if (newCapacity > _capacity) {
            T* newElems = new T[newCapacity];
            for (int i = 0; i < _size; ++i) {
                newElems[i] = _elems[i];
            }
            delete[] _elems;
            _elems = newElems;
            _capacity = newCapacity;
        }
    }

    void push_back(const T figure) {
        if (_size == _capacity) {
            resize(_capacity == 0 ? 1 : _capacity * 2);
        }
        _elems[_size++] = figure;
    }

    void remove(int index) {
        if (index < 0 || index >= _size) {
            std::cerr << "Index out of bounds\n";
            return;
        }

        for (int i = index; i < _size - 1; ++i) {
            _elems[i] = _elems[i + 1];
        }
        --_size;
    }

    int length() const {
        return _size;
    }

    void print() const {
        for (int i = 0; i < _size; ++i) {
            std::cout << _elems[i] << " ";
        }
        std::cout << std::endl;
    }

    T operator[](int index) const {
        if (index < 0 || index >= _size) {
            std::cerr << "Index out of bounds\n";
            return T(); 
        }
        return _elems[index];
    }

    T* begin() const {
        return _elems;
    }

    T* end() const {
        return _elems + _size;
    }

private:
    T* _elems;
    int _size;
    int _capacity;
};
