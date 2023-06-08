#ifndef __CUSTOM_ALLOCATOR_H__
#define __CUSTOM_ALLOCATOR_H__

#include "common.h"

template <class T>
class custom_allocator {
  public:
    typedef T        value_type;
    typedef T*       pointer;
    typedef const T* const_pointer;
    typedef T&       reference;
    typedef const T& const_reference;
    size_t _capacity;
    size_t _size;

    template <class U>
    struct rebind {
        typedef custom_allocator<U> other;
    };

    pointer address (reference value) const {
        return &value;
    }
    const_pointer address (const_reference value) const {
        return &value;
    }

    custom_allocator()
        : _capacity(1)
        , _size(0)
    {}

    custom_allocator(size_t capacity)
        : _capacity(capacity)
        , _size(0)
    {}

    custom_allocator(const custom_allocator& alloc)
        : _capacity(alloc._capacity)
        , _size(alloc._size)
    {}

    template <class U>
    custom_allocator (const custom_allocator<U>& alloc)
        : _capacity(alloc._capacity)
        , _size(alloc._size)
    {}

    ~custom_allocator() {}

    pointer allocate (size_t num) {
        if (_size == _capacity || (_size + (num * sizeof(T))) >= _capacity) {
            throw std::bad_alloc();
        }
        std::cout << "allocate " << num << std::endl;
        return (pointer)(::operator new(num * sizeof(T)));
    }

    void construct (pointer p, const T& value) {
        new ((void*)p) T(value);
    }

    void destroy (pointer p) {
        p->~T();
    }

    void deallocate (pointer p, size_t num) {
        std::cout << "deallocate " << num << std::endl;
        ::operator delete((void*)p);
    }
};

template <class T1, class T2>
bool operator== (const custom_allocator<T1>&,
                 const custom_allocator<T2>&) throw() {
    return true;
}
template <class T1, class T2>
bool operator!= (const custom_allocator<T1>&,
                 const custom_allocator<T2>&) throw() {
    return false;
}

#endif
