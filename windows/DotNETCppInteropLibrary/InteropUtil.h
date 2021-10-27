// Author: Neeraj Sharma <neerajsharma.9@outlook.com>
// License MIT

#pragma once

#include "SearchWeb.h"

#include <string>

namespace DotNETCppInteropLibrary
{
    using namespace System;

    public ref class InteropUtil
    {
    public:
        static std::string ToNative(String^ str);
        static String^ ToCLR(const std::string& nativeStr);
        static String^ ToCLR(const NativeLibrary::SearchWeb::String& nativeStr);
    };
}