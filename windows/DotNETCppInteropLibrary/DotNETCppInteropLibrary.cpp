// Author: Neeraj Sharma <neerajsharma.9@outlook.com>
// License MIT

#include "pch.h"

#include "DotNETCppInteropLibrary.h"

#include "InteropUtil.h"
#include "SearchWeb.h"

using namespace DotNETCppInteropLibrary;

InteropSearchResults::InteropSearchResults(const InteropSearchResults% other)
    : mScore(other.mScore),
      mUrl(other.mUrl)
{
}

InteropSearchWeb::InteropSearchWeb()
    : mpSearchWeb(new NativeLibrary::SearchWeb())
{
}

InteropSearchWeb::~InteropSearchWeb()
{
    delete mpSearchWeb;
}

bool InteropSearchWeb::Search([System::Runtime::InteropServices::Out] InteropSearchResults^% result, String^ keyword)
{
    NativeLibrary::SearchWeb::String strKeyword(InteropUtil::ToNative(keyword));
    NativeLibrary::SearchWeb::SearchResult nativeResult = mpSearchWeb->Search(strKeyword);
    result = gcnew InteropSearchResults(nativeResult.mScore, InteropUtil::ToCLR(nativeResult.mUrl));
    return !nativeResult.mUrl.empty();
}