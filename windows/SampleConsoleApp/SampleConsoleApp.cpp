// Author: Neeraj Sharma <neerajsharma.9@outlook.com>
// License MIT

#include "SnmallocWrapper.h"

#include <iostream>
#include <string>
#include <thread>
#include <mutex>

#include <cstdlib>
#include <new>
#include <limits>
#include <iostream>
#include <vector>

#define PREFIX "[" << GetThreadId() << ", " << this << "] "

using namespace std;
namespace
{
    std::thread::id GetThreadId()
    {
        return std::this_thread::get_id();
    }

    template <class T>
    struct Mallocator
    {
        typedef T value_type;

        Mallocator()
        {
            cout << PREFIX << "Mallocator()" << endl;
        }
        template <class U> constexpr Mallocator(const Mallocator <U>&) noexcept {
            cout << PREFIX << "Mallocator(const Mallocator <U>&)" << endl;
        }

        ~Mallocator()
        {
            cout << PREFIX << "~Mallocator()" << endl;
        }

        [[nodiscard]] T* allocate(std::size_t n) {
            cout << PREFIX << "allocate(" << n << ")" << endl;
            if (n > std::numeric_limits<std::size_t>::max() / sizeof(T))
                throw std::bad_array_new_length();

            //if (auto p = static_cast<T*>(std::malloc(n * sizeof(T)))) {
            if (auto p = static_cast<T*>(::SNMALLOC_NAME_MANGLE(malloc)(n * sizeof(T)))) {
                report(p, n);
                cout << PREFIX << "  allocate(" << n << ") = " << p << endl;
                return p;
            }

            throw std::bad_alloc();
        }

        void deallocate(T* p, std::size_t n) noexcept {
            cout << PREFIX << "deallocate(" << p << ", " << n << ")" << endl;
            report(p, n, 0);
            //std::free(p);
            ::SNMALLOC_NAME_MANGLE(free)(p);
        }

    private:
        void report(T* p, std::size_t n, bool alloc = true) const {
            std::cout << PREFIX << " " << (alloc ? "Alloc: " : "Dealloc: ") << sizeof(T) * n
                << " bytes at " << std::hex << std::showbase
                << reinterpret_cast<void*>(p) << std::dec << '\n';
        }
    };

    template <class T, class U>
    bool operator==(const Mallocator <T>&, const Mallocator <U>&) { return true; }
    template <class T, class U>
    bool operator!=(const Mallocator <T>&, const Mallocator <U>&) { return false; }
}

thread_local unsigned int multicounter = 1;
thread_local
std::mutex cout_mutex;

void increase_multicounter(const std::string& thread_name)
{
    ++multicounter; // modifying outside a lock is okay; this is a thread-local variable
    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << "multicounter counter for " << thread_name << ": " << multicounter << '\n';

    std::vector<int, Mallocator<int>> v(8);
    for (int i = 0; i < 4; ++i)
    {
        v.push_back(42);
    }
}

void run_test()
{
    std::thread a(increase_multicounter, "a");
    std::thread b(increase_multicounter, "b");

    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "multicounter counter for main: " << multicounter << '\n';
    }

    a.join();
    b.join();
}

int main()
{
    run_test();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
