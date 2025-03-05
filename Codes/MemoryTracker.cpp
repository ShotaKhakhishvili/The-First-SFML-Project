#include <cstdlib>
#include <iostream>

static size_t totalAllocated = 0;

void* operator new(std::size_t size) {
    totalAllocated += size;
    //std::cout << "Allocating " << size << " bytes, total allocated: " << totalAllocated << "\n";
    if (void* p = std::malloc(size))
        return p;
    throw std::bad_alloc();
}

void operator delete(void* ptr, std::size_t size) noexcept {
    totalAllocated -= size;
    std::cout << "Deallocating " << size << " bytes, total allocated: " << totalAllocated << "\n";
    std::free(ptr);
}
