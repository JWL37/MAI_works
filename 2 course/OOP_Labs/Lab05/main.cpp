#include <bits/stdc++.h>
#include "MyQueue.h"
#include "factorial.h"
#include "Allocator.h"

int main()
{
    

    MyQueue<int,5,MyAllocator<std::pair<const int, int>>> exampleQueue;
    for (size_t i = 0; i < 5; ++i)
    {
        exampleQueue.push(i);
    }
    for(auto &el:exampleQueue){
        std::cout<<el<<" ";
    }
    std::cout<<std::endl;

    std::map<int, int, std::less<int>,MyAllocator<std::pair<const int, int>>> exampleMap;
    for (int i = 0; i < 10; ++i) {
        exampleMap[i] = factorial(i);
    }
    std::cout<<std::endl;
    for (const auto& pair : exampleMap) {
        std::cout << pair.first << "! = " << pair.second << std::endl;
    }

    return 0;
}