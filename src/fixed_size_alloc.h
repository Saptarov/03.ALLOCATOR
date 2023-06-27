#ifndef __FIXED_ALLOCATOR_H__
#define __FIXED_ALLOCATOR_H__
#include "common.h"

template <class T, size_t N>
class fixed_size_alloc
{
public:
    using value_type = T;
    using pointer = T*;
    using iterator = typename std::iterator<std::random_access_iterator_tag, T>::pointer;
    value_type     _buffer[N];
    pointer    _begin_pos;
    pointer    _current_pos;

public:
    template <class _Up> struct rebind {typedef fixed_size_alloc<_Up, N> other;};

    fixed_size_alloc() noexcept {
        _current_pos = _buffer;
        _begin_pos = _buffer;
    }
    template <class U, size_t K>
    fixed_size_alloc(const fixed_size_alloc<U, K> & other) noexcept {
        _begin_pos = (pointer)&other._buffer[0];
        _current_pos = (pointer)other._current_pos;
    }

    fixed_size_alloc& operator = (const fixed_size_alloc&) = delete;

    bool is_good(pointer ptr) noexcept {
        return _begin_pos <= ptr && ptr <= _begin_pos + N;
    }

    pointer allocate(size_t n)
    {
        size_t size = n * sizeof(T);
        assert(is_good(_current_pos) && "out of allocated memory");
        if ((size_t) std::distance((_begin_pos + N), _current_pos) >= n)
        {
            pointer r = _current_pos;
            _current_pos += n;
            return r;
        }
        return static_cast<pointer>(::operator new(size));
    }
    void deallocate(pointer p, size_t n) noexcept
    {
        if (is_good(p))
        {
            if ((p + n) == _current_pos) {
                _current_pos = p;
            }
        }
        else
            ::operator delete(p);
    }
};

template <class T1, size_t N, class T2, size_t K>
bool operator== (const fixed_size_alloc<T1, N>&,
                 const fixed_size_alloc<T2, K>&) throw() {
    return true;
}
template <class T1, size_t N, class T2, size_t K>
bool operator!= (const fixed_size_alloc<T1, N>&,
                 const fixed_size_alloc<T2, K>&) throw() {
    return false;
}
#endif
