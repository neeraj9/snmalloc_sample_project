// Author: Neeraj Sharma <neerajsharma.9@outlook.com>
// License MIT

#pragma once

#include "CustomAllocator.h"

#include <list>
#include <memory>
#include <string>

namespace NativeLibrary
{
    class SearchWeb
    {
    public:
        typedef std::basic_string< char, std::char_traits<char>, CustomAllocator<char> > String;

        struct SearchResult
        {
            SearchResult();
            SearchResult(const SearchResult& other) noexcept;
            SearchResult(SearchResult&& other) noexcept;

            std::list< String, CustomAllocator<String> > mKeywords;
            int mScore;
            String mUrl;
        };

    public:
        SearchWeb();

        void Append(SearchResult&& item);

        SearchResult Search(const String& keyword) const;

    private:
        std::list< SearchResult, CustomAllocator<SearchResult> > mDatabase;
    };
}