#pragma once
#include <cstddef>

template <typename T> class Vector {
private:
  T *data;
  size_t cap;
  size_t len;

  // Mo rong kich thuoc bo nho cua vector
  void grow(size_t newCap) {
    if (newCap <= cap)
      return;
    T *temp = new T[newCap];
    for (size_t i = 0; i < len; ++i) {
      // Dung static_cast<T&&> thay cho std::move
      temp[i] = static_cast<T &&>(data[i]);
    }
    delete[] data;
    data = temp;
    cap = newCap;
  }

public:
  // --- Constructor & Destructor ---
  Vector() : data(nullptr), cap(0), len(0) {}

  ~Vector() { delete[] data; }

  Vector(const Vector &other)
      : data(other.cap > 0 ? new T[other.cap] : nullptr), cap(other.cap),
        len(other.len) {
    for (size_t i = 0; i < len; ++i) {
      data[i] = other.data[i];
    }
  }

  // --- Toan tu gan (Copy & Move) ---
  // Copy assignment dung copy-and-swap (ko dung std::swap)
  Vector &operator=(const Vector &other) {
    if (this != &other) {
      Vector temp(other);

      T *tempData = this->data;
      this->data = temp.data;
      temp.data = tempData;

      size_t tempCap = this->cap;
      this->cap = temp.cap;
      temp.cap = tempCap;

      size_t tempLen = this->len;
      this->len = temp.len;
      temp.len = tempLen;
    }
    return *this;
  }

  Vector(Vector &&other) noexcept
      : data(other.data), cap(other.cap), len(other.len) {
    other.data = nullptr;
    other.cap = 0;
    other.len = 0;
  }

  Vector &operator=(Vector &&other) noexcept {
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

  // Them phan tu vao cuoi vector (copy)
  void push_back(const T &value) {
    if (len == cap)
      grow(cap == 0 ? 1 : cap * 2);
    data[len] = value;
    ++len;
  }

  // Them phan tu vao cuoi vector (move)
  void push_back(T &&value) {
    if (len == cap)
      grow(cap == 0 ? 1 : cap * 2);
    // Dung static_cast<T&&> thay vi std::move
    data[len] = static_cast<T &&>(value);
    ++len;
  }

  // Xoa phan tu tai vi tri index
  void remove(size_t index) {
    if (index >= len)
      return;
    for (size_t i = index; i < len - 1; ++i)
      // Dung static_cast<T&&> thay vi std::move
      data[i] = static_cast<T &&>(data[i + 1]);
    data[len - 1] = T();
    --len;
  }

  // Xoa phan tu o cuoi vector
  void pop_back() {
    if (len > 0) {
      --len;
      data[len] = T();
    }
  }

  // Xoa tat ca phan tu, dat len ve 0
  void clear() {
    for (size_t i = 0; i < len; ++i) {
      data[i] = T();
    }
    len = 0;
  }

  // Truy cap phan tu tai vi tri index
  T &operator[](size_t index) { return data[index]; }
  const T &operator[](size_t index) const { return data[index]; }

  // Truy cap phan tu cuoi cung
  T &back() { return data[len - 1]; }
  const T &back() const { return data[len - 1]; }

  // Cac ham lay thong tin kich thuoc
  size_t size() const { return len; }
  size_t capacity() const { return cap; }
  bool empty() const { return len == 0; }

  // Bo sung iterator chuan C++
  // De dung duoc range-based for: for(auto& x : vector)
  using iterator = T *;
  using const_iterator = const T *;

  iterator begin() { return data; }
  iterator end() { return data + len; }
  const_iterator begin() const { return data; }
  const_iterator end() const { return data + len; }
};