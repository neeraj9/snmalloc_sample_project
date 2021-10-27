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

bool InteropSearchWeb::Search(InteropSearchResults^% result, String^ keyword)
{
    NativeLibrary::SearchWeb::String strKeyword(InteropUtil::ToNative(keyword));
    NativeLibrary::SearchWeb::SearchResult nativeResult = mpSearchWeb->Search(strKeyword);
    //InteropSearchResults clrResult(nativeResult.mScore, InteropUtil::ToCLR(nativeResult.mUrl));
    // is there any other way to return this?
    // TODO: FIXME maybe take reference of input argument and set it
    result = gcnew InteropSearchResults(nativeResult.mScore, InteropUtil::ToCLR(nativeResult.mUrl));
    return true;
}