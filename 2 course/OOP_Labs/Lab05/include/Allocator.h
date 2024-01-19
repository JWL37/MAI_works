#pragma once
#include <bits/stdc++.h>

template <typename T, size_t ChunkSize = 100000>
class MyAllocator {
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = size_t;

    template <typename U>
    struct rebind {
        using other = MyAllocator<U, ChunkSize>;
    };

    MyAllocator() {
        chunks_.push_back(std::vector<T>(ChunkSize));
        current_chunk_ = &chunks_.back();
        current_index_ = 0;
    }

    template <typename U>
    MyAllocator(const MyAllocator<U, ChunkSize>&) {}

    pointer allocate(size_type n) {
        if (current_index_ + n > current_chunk_->size()) {
            chunks_.push_back(std::vector<T>(ChunkSize));
            current_chunk_ = &chunks_.back();
            current_index_ = 0;
        }
        pointer p = &(*current_chunk_)[current_index_];
        current_index_ += n;
        return p;
    }

    void deallocate(pointer p, size_type n) {}

private:
    std::vector<std::vector<T>> chunks_;
    std::vector<T>* current_chunk_;
    size_type current_index_;
};
