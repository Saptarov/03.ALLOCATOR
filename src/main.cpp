#include <iostream>
#include <vector>
#include "container.h"
#include "custom_alloc.h"

int factorial(int key) {
    if (key == 0) {
        return 1;
    }
    return key + factorial(key - 1);
}

int main () {

    // 1. custom allocator with limit size
   {
        std::cout << "<======" << std::endl;
        custom_allocator<std::pair<const int,int>> alloc(50);
        std::map<int,int, std::less<int>, custom_allocator<std::pair<const int,int>>> map1(std::less<int>(), alloc);
        map1[1] = 1;
        map1[2] = 1;
        map1[3] = 3;
    }
    // 2. implement container
    {
        std::cout << "<======" << std::endl;
        Container<int> vec_std_allocator;
        for (auto i : {3,45,2,5,2}) {
            vec_std_allocator.push_back(i);
        }
        vec_std_allocator.push_back(6);
        for(auto iter = vec_std_allocator.begin(); iter != vec_std_allocator.end(); ++iter) {
            std::cout << *iter << std::endl;
        }

    }
    // 3. filled 0-9
    {
        std::cout << "<======" << std::endl;
        std::map<int, int> map2;
        for (auto i : {0,1,2,3,4,5,6,7,8,9}) {
            map2[i] = factorial(i);
        }
        for (auto& [k,v] : map2) {
            std::cout << " " << k << ":" << v << std::endl;
        }
    }
    // 4. filled 0-9
    {
        std::cout << "<======" << std::endl;
        custom_allocator<std::pair<const int,int>> alloc2(sizeof(int) * 10);
        std::map<int,int, std::less<int>, custom_allocator<std::pair<const int,int>>> map3(std::less<int>(), alloc2);
        for (auto i : {0,1,2,3,4,5,6,7,8,9}) {
            map3[i] = factorial(i);
        }
        for (auto& [k,v] : map3) {
            std::cout << " " << k << ":" << v << std::endl;
        }
    }
    // дополнительный пункт
    {
        Container<int> a;
        a.push_back(0);
        Container<int> b = a;
    }
    return 0;
}
