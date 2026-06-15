#pragma once
#include <cstddef>
#include <stdexcept>
#include <utility>

template <typename T> 
class Vector {
private:
    T* data;
    size_t cap;
    size_t len;

    void grow(size_t newCap) {
        if (newCap <= cap) return;
        T* temp = new T[newCap]; 
        for (size_t i = 0; i < len; ++i) {
            temp[i] = std::move(data[i]); 
        }
        delete[] data;
        data = temp;
        cap = newCap;
    }

public:
    Vector() : data(nullptr), cap(0), len(0) {}

    ~Vector() {
        delete[] data;
    }

    Vector(const Vector& other) 
        : data(other.cap > 0 ? new T[other.cap] : nullptr), cap(other.cap), len(other.len) {
        for (size_t i = 0; i < len; ++i) {
            data[i] = other.data[i];
        }
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            Vector temp(other); 
            
            std::swap(data, temp.data);
            std::swap(cap, temp.cap);
            std::swap(len, temp.len);            
        }
        return *this;
    }

    Vector(Vector&& other) noexcept 
        : data(other.data), cap(other.cap), len(other.len) {
        other.data = nullptr;
        other.cap = 0;
        other.len = 0;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] data; 
            data = other.data;
            cap = other.cap;
            len = other.len;

            other.data = nullptr;
            other.cap = 0;
            other.len = 0;
        }
        return *this;
    }

    void push_back(const T& value) {
        if (len == cap) grow(cap == 0 ? 1 : cap * 2);
        data[len] = value;
        ++len;
    }

    void push_back(T&& value) {
        if (len == cap) grow(cap == 0 ? 1 : cap * 2);
        data[len] = std::move(value);
        ++len;
    }

    void pop_back() {
        if (len > 0) {
            --len;
            data[len] = T(); 
        }
    }

    void clear() {
        for (size_t i = 0; i < len; ++i) {
            data[i] = T();
        }
        len = 0;
    }

    T& operator[](size_t index) { return data[index]; }
    const T& operator[](size_t index) const { return data[index]; }

    T& back() {
        if (empty()) throw std::out_of_range("Vector rong!");
        return data[len - 1];
    }

    const T& back() const {
        if (empty()) throw std::out_of_range("Vector rong!");
        return data[len - 1];
    }

    size_t size() const { return len; }
    size_t capacity() const { return cap; }
    bool empty() const { return len == 0; }
};