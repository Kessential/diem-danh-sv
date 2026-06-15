#pragma once
#include "Vector.h"
#include <cstddef>
#include <utility>

namespace Sort {

using std::ptrdiff_t;

template <typename T> 
void swap(T &a, T &b) {
  T temp = std::move(a);
  a = std::move(b);
  b = std::move(temp);
}

template <typename T, typename Compare>
void insertionSort(Vector<T> &arr, ptrdiff_t low, ptrdiff_t high, Compare comp) {
  for (ptrdiff_t i = low + 1; i <= high; ++i) {
    T key = std::move(arr[i]);
    ptrdiff_t j = i - 1;
    while (j >= low && comp(key, arr[j])) {
      arr[j + 1] = std::move(arr[j]);
      --j;
    }
    arr[j + 1] = std::move(key);
  }
}

template <typename T, typename Compare>
ptrdiff_t medianOfThree(Vector<T> &arr, ptrdiff_t a, ptrdiff_t b, ptrdiff_t c, Compare comp) {
  if (comp(arr[a], arr[b])) {
    if (comp(arr[b], arr[c])) return b;
    if (comp(arr[a], arr[c])) return c;
    return a;
  } else {
    if (comp(arr[a], arr[c])) return a;
    if (comp(arr[b], arr[c])) return c;
    return b;
  }
}

template <typename T, typename Compare>
ptrdiff_t HoarePartition(Vector<T> &arr, ptrdiff_t low, ptrdiff_t high, Compare comp) {
  ptrdiff_t mid = low + (high - low) / 2;
  ptrdiff_t pivotIdx = medianOfThree(arr, low, mid, high, comp);

  T pivot = arr[pivotIdx];

  ptrdiff_t i = low - 1, j = high + 1;

  while (true) {
    do {
      ++i;
    } while (comp(arr[i], pivot));

    do {
      --j;
    } while (comp(pivot, arr[j]));

    if (i >= j) return j;

    swap(arr[i], arr[j]);
  }
}

template <typename T, typename Compare>
void HoareQuicksort(Vector<T> &arr, ptrdiff_t low, ptrdiff_t high, Compare comp) {
  const ptrdiff_t CUTOFF = 16; 
  
  while (low < high) {
    if (high - low < CUTOFF) {
      insertionSort(arr, low, high, comp);
      return;
    }

    ptrdiff_t p = HoarePartition(arr, low, high, comp);

    if (p - low < high - p) {
      HoareQuicksort(arr, low, p, comp);
      low = p + 1;
    } else {
      HoareQuicksort(arr, p + 1, high, comp);
      high = p;
    }
  }
}

template <typename T> 
void HoareQuicksort(Vector<T> &arr, ptrdiff_t low, ptrdiff_t high) {
  HoareQuicksort(arr, low, high, [](const T &a, const T &b) { return a < b; });
}

template <typename T, typename Compare>
void sort(Vector<T> &arr, Compare comp) {
  if (arr.size() <= 1) return;
  HoareQuicksort(arr, 0, static_cast<ptrdiff_t>(arr.size()) - 1, comp);
}

template <typename T> 
void sort(Vector<T> &arr) {
  if (arr.size() <= 1) return;
  HoareQuicksort(arr, 0, static_cast<ptrdiff_t>(arr.size()) - 1);
}

}