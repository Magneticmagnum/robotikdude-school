#ifndef PHEAP_H_
#define PHEAP_H_

#include <utility>
#include <algorithm>
#include <iostream>
#include <cstdlib>

template<typename K, typename V>
class MinHeap
{
  private:
    typedef std::pair<const K*, V> kv_t;

    int size_;
    int length_;
    kv_t* heap_;

  public:
    MinHeap(int size)
    {
      this->size_ = size;
      this->length_ = 0;
      this->heap_ = (kv_t*) calloc(size, sizeof(kv_t));
    }

  public:
    virtual ~MinHeap()
    {
      free(heap_);
    }

  public:
    void build()
    {
      for (int i = (length_ - 1) / 2; i >= 0; i--) {
        heapify(i);
      }
    }

  private:
    void heapify(int i)
    {
      int l = 2 * i;
      int r = l + 1;
      int largest = i;
      if (l < length_ && *(heap_[l].first) < *(heap_[i].first)) {
        largest = l;
      }
      if (r < length_ && *(heap_[r].first) < *(heap_[largest].first)) {
        largest = r;
      }
      if (largest != i) {
        std::swap(heap_[i], heap_[largest]);
        heapify(largest);
      }
    }

  public:
    bool empty()
    {
      return length_ <= 0;
    }

  public:
    bool add(const K* k, const V& v)
    {
      if (length_ >= size_)
        return false;

      heap_[length_++] = kv_t(k, v);
      return true;
    }

  public:
    bool contains(const V& v)
    {
      for (int i = 0; i < length_; i++) {
        if (heap_[i].second == v) {
          return true;
        }
      }
      return false;
    }

  public:
    V& getMin()
    {
      return heap_[0].second;
    }

  public:
    V& extractMin()
    {
      length_--;
      std::swap(heap_[0], heap_[length_]);
      heapify(0);
      return heap_[length_].second;
    }

  public:
    void print()
    {
      for (int i = 0; i < length_; i++) {
        std::cout << "(" << *(heap_[i].first) << ", " << heap_[i].second << ")";
        if (i + 1 != length_)
          std::cout << ", ";
      }
    }
};

#endif /* PHEAP_H_ */
