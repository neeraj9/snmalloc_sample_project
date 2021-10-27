// Author: Neeraj Sharma <neerajsharma.9@outlook.com>
// License MIT

#include "pch.h" // always be the first otherwise weird compilation issues

#include "SearchWeb.h"

#include <algorithm>

using namespace NativeLibrary;


SearchWeb::SearchResult::SearchResult()
    : mKeywords(),
      mScore(0),
      mUrl()
{
}

SearchWeb::SearchResult::SearchResult(const SearchResult& other) noexcept
    : mKeywords(other.mKeywords),
      mScore(other.mScore),
      mUrl(other.mUrl)
{
}

SearchWeb::SearchResult::SearchResult(SearchWeb::SearchResult&& other) noexcept
    : mKeywords(std::move(other.mKeywords)),
      mScore(other.mScore),
      mUrl(std::move(other.mUrl))
{
}

SearchWeb::SearchWeb()
    : mDatabase()
{
}

void SearchWeb::Append(SearchResult&& item)
{
    mDatabase.push_back(std::move(item));
}

SearchWeb::SearchResult SearchWeb::Search(const String& keyword) const
{
    for (auto& item : mDatabase)
    {
        auto tmp = std::find(item.mKeywords.begin(), item.mKeywords.end(), keyword);
        if (tmp != item.mKeywords.end())
        {
            return item;
        }
    }
    return SearchResult();
}