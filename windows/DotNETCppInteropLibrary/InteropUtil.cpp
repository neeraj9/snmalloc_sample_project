// Author: Neeraj Sharma <neerajsharma.9@outlook.com>
// License MIT

#include "pch.h"

#include "InteropUtil.h"

//#include <vcclr.h>

using namespace DotNETCppInteropLibrary;

std::string InteropUtil::ToNative(String^ str)
{
    if (str == nullptr || str->Empty)
    {
        return std::string();
    }
    array<unsigned char>^ utfBytes = System::Text::Encoding::UTF8->GetBytes(str);
    pin_ptr<unsigned char> pin(&utfBytes[0]);
    return std::string(reinterpret_cast<char*>(pin), utfBytes->Length);
}

String^ InteropUtil::ToCLR(const std::string& nativeStr)
{
    if (nativeStr.empty())
    {
        return String::Empty;
    }
    cli::array<unsigned char>^ bytes = gcnew cli::array<unsigned char>(static_cast<int>(nativeStr.size()));
    pin_ptr<unsigned char> pin(&bytes[0]);
    std::copy(nativeStr.begin(), nativeStr.end(), reinterpret_cast<char*>(pin));
    return System::Text::Encoding::UTF8->GetString(bytes);
}

String^ InteropUtil::ToCLR(const NativeLibrary::SearchWeb::String& nativeStr)
{
    if (nativeStr.empty())
    {
        return String::Empty;
    }
    cli::array<unsigned char>^ bytes = gcnew cli::array<unsigned char>(static_cast<int>(nativeStr.size()));
    pin_ptr<unsigned char> pin(&bytes[0]);
    std::copy(nativeStr.begin(), nativeStr.end(), reinterpret_cast<char*>(pin));
    return System::Text::Encoding::UTF8->GetString(bytes);
}