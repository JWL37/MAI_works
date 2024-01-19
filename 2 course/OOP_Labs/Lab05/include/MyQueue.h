#pragma once
#include <bits/stdc++.h>


template <class T, size_t Size, class Allocator = std::allocator<T>>
class MyQueue
{

public:
    using AllocType = typename std::allocator_traits<Allocator>::template rebind_alloc<T>;
    MyQueue() : _frontIndexElem(0), _lastIndexElem(0), _countCurrentElem(0), _alloc(AllocType()) {}
    ~MyQueue() {}
    class Iterator
    {

    private:
        MyQueue &_queue;
        size_t _index;

    public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using reference = T &;
        using pointer = T *;
        using iterator_category = std::forward_iterator_tag;
        Iterator(MyQueue &data, size_t index) : _queue(data), _index(index) {}
        Iterator &operator++()
        {
            _index = (_index + 1) % (Size+1);
            return *this;
        }
        reference operator*() const
        {
            return _queue._data[_index];
        }
        pointer operator->() const
        {
            return &(_queue._data[_index]);
        }
        bool operator==(const Iterator &other) const
        {
            return &_queue == &other._queue && _index == other._index;
        }
        bool operator!=(const Iterator &other) const
        {
            return !(*this == other);
        }
    };

    bool isEmpty() const
    {
        return _countCurrentElem == 0;
    }

    bool isFull() const
    {
        return _countCurrentElem == Size;
    }

    size_t getSize() const
    {
        return _countCurrentElem;
    }
    void push(const T &value)
    {
        if (isFull())
        {
            throw std::overflow_error("Queue is full");
        }
        T *newValue = _alloc.allocate(1);

        std::allocator_traits<AllocType>::construct(_alloc, newValue, value);

        _data[_lastIndexElem] = std::move(*newValue);

        _alloc.deallocate(newValue, 1);

        _lastIndexElem = (_lastIndexElem + 1) % (Size+1);
        _countCurrentElem++;
    }

    T pop()
    {
        if (isEmpty())
        {
            throw std::underflow_error("Queue is empty");
        }
        T value = _data[_frontIndexElem];
        _frontIndexElem = (_frontIndexElem + 1) % (Size+1);
        _countCurrentElem--;
        return value;
    }

    T front() const
    {
        if (isEmpty())
        {
            throw std::underflow_error("Queue is empty");
        }
        return _data[_frontIndexElem];
    }
    Iterator begin()
    {
        return Iterator(*this, _frontIndexElem);
    }
    Iterator end()
    {
        return Iterator(*this, _lastIndexElem);
    }
    using constIterator = const Iterator;

    constIterator cbegin()
    {
        return Iterator(*this, _frontIndexElem);
    }
    constIterator cend()
    {
        return Iterator(*this, _lastIndexElem+1);
    }
    private:
    
    std::array<T, Size> _data;
    size_t _frontIndexElem;
    size_t _lastIndexElem;
    size_t _countCurrentElem;
    AllocType _alloc;
};

