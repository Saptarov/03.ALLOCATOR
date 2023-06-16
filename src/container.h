#ifndef __CONTAINER_H
#define __CONTAINER_H
#include "../src/custom_alloc.h"

template <typename T, typename Allocator = std::allocator<T> >
class Container {
public:
    // types:
    using value_type = T;
    using iterator = typename std::iterator<std::random_access_iterator_tag, T>::pointer;
    using const_iterator = typename std::iterator<std::random_access_iterator_tag, const T>::pointer;
    using size_type = typename std::allocator_traits<Allocator>::size_type;
    using pointer = typename std::allocator_traits<Allocator>::pointer;
    using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;

    Container(const Allocator& alloc) noexcept(noexcept(Allocator())) : alloc(alloc)
    {}

    Container() noexcept(noexcept(Allocator())) : Container(Allocator())
    {}

    Container(const Container& container)
    {
        reallocate(container.size());
    }

    ~Container() {
        clear_memory();
    }

    T& operator [] (size_t index)
    {
        return elements[index];
    }

    void push_back(const T& value)
    {
        //size_type pos = 0;
        if ((size() + 2) > capacity()) {
            reallocate(size() + 2);
        }
        size_t poss = size();
        pointer new_place = &elements[poss];
        ++end_place;
        *new_place = value;
    }

    iterator                begin() noexcept            { return elements; }
    const_iterator          begin() const noexcept      { return elements; }
    iterator                end() noexcept              { return end_place; }
    const_iterator          end() const noexcept        { return end_place; }

    size_type size() const noexcept {
        return end_place - elements;
    }
    size_type capacity() const noexcept {
        return cap - elements;
    }

private:
    Allocator alloc;
    pointer elements =    nullptr;
    pointer end_place =  nullptr;
    pointer cap =         nullptr;

public:
    void clear_memory() {
        if (elements) {
            auto range = size();
            for (size_t i = 0; i < range; ++i) {
                    alloc.destroy(&elements[i]);
            }
            alloc.deallocate(elements, size());
            elements = nullptr;
        }
    }
    void reallocate(size_type count) {
        auto new_capacity = 2 * count;
        auto allocated_data = alloc.allocate(new_capacity);
        auto copy_data = std::uninitialized_copy(std::make_move_iterator(begin()), std::make_move_iterator(end()), allocated_data);
        clear_memory();
        elements = allocated_data;
        end_place = copy_data;
        cap = elements + new_capacity;
    }
};

#endif
