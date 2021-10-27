// Author: Neeraj Sharma <neerajsharma.9@outlook.com>
// License MIT

#pragma once

#include "SnmallocWrapper.h"

#include <iostream>
#include <thread>

namespace NativeLibrary
{
    template <class T>
    struct CustomAllocator
    {
        typedef T value_type;

        CustomAllocator()
        {
            Out() << "CustomAllocator()" << std::endl;
        }

        template <class U> constexpr CustomAllocator(const CustomAllocator <U>&) noexcept {
            Out() << "CustomAllocator(const CustomAllocator <U>&)" << std::endl;
        }

        CustomAllocator(CustomAllocator const&)
        {
            Out() << "CustomAllocator(CustomAllocator const&)" << std::endl;
        }

        //template <class U> constexpr CustomAllocator(CustomAllocator <U> const&) noexcept {
            //Out() << "CustomAllocator(CustomAllocator <U> const&)" << std::endl;
        //}

        ~CustomAllocator()
        {
            Out() << "~CustomAllocator()" << std::endl;
        }

        [[nodiscard]] T* allocate(std::size_t n) {
            Out() << "allocate(" << n << ")" << std::endl;
            if (n > std::numeric_limits<std::size_t>::max() / sizeof(T))
                throw std::bad_array_new_length();

            //if (auto p = static_cast<T*>(std::malloc(n * sizeof(T)))) {
            if (auto p = static_cast<T*>(::SNMALLOC_NAME_MANGLE(malloc)(n * sizeof(T)))) {
                report(p, n);
                Out() << "  allocate(" << n << ") = " << p << std::endl;
                return p;
            }

            throw std::bad_alloc();
        }

        void deallocate(T* p, std::size_t n) noexcept {
            Out() << "deallocate(" << p << ", " << n << ")" << std::endl;
            report(p, n, 0);
            //std::free(p);
            ::SNMALLOC_NAME_MANGLE(free)(p);
        }

    private:
        void report(T* p, std::size_t n, bool alloc = true) const {
            Out() << " " << (alloc ? "Alloc: " : "Dealloc: ") << sizeof(T) * n
                << " bytes at " << std::hex << std::showbase
                << reinterpret_cast<void*>(p) << std::dec << '\n';
        }

        std::ostream& Out()
        {
            return std::cout << "[" << GetThreadId() << ", " << this << "] ";
        }

        std::ostream& Out() const
        {
            return std::cout << "[" << GetThreadId() << ", " << this << "] ";
        }

        std::thread::id GetThreadId() const
        {
            return std::this_thread::get_id();
        }
    };
}